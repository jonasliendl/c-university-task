#include "par.h"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    Node* sublist;
    int thread_num;
} ThreadArgs;

void* ThrdFunc(void* arg) {
    clock_t start;
    clock_t end;
    double time_spent;

    ThreadArgs* args = (ThreadArgs*)arg;
    Node* result = args->sublist;
    FILE* logfile = fopen(LOG_FILE, "a");

    if (!logfile) {
        perror("Cannot open log file");
        result = NULL;
    } else {
        start = clock();
        Sort(args->sublist);
        end = clock();

        time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        pthread_mutex_lock(&log_mutex);
        fprintf(logfile, "Thread %d Sort Time: %f seconds\n", args->thread_num, time_spent);
        pthread_mutex_unlock(&log_mutex);

        fclose(logfile);
    }
    return result;
}

Node* merge_sorted_lists(Node* list1, Node* list2) {
    Node* result;
    // Base cases
    if (!list1) {
        result = list2;
    } else if (!list2) {
        result = list1;
    } else {
        Node* temp;
        Node* other_next;

        // Determine which list starts first
        Node* head = (list1->data <= list2->data) ? list1 : list2;
        Node* other = (list1->data <= list2->data) ? list2 : list1;
        Node* current = head;

        while (current->next && other) {
            // If next element in current list is less than first in other list, move forward
            if (current->next->data <= other->data) {
                current = current->next;
            } else {
                // Swap in an element from the other list
                temp = current->next;
                other_next = other->next;

                current->next = other;
                other->prev = current;
                other->next = temp;
                if (temp) temp->prev = other;

                current = other;
                other = other_next;
            }
        }

        // Append remaining elements
        if (other) {
            while (current->next) current = current->next;
            current->next = other;
            other->prev = current;
        }

        // Ensure the first node's prev is NULL
        head->prev = NULL;
        result = head;
    }

    return result;
}

int main() {
    Node* thread_lists[NUM_THREADS];
    Node* merged_list;
    Node* temp;
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    clock_t start;
    clock_t end;
    double time_spent;
    int i;
    int j;
    int is_found;

    int result = 0;
    Node* list = Gen(NUM_NODES);
    Node* current = list;
    int nodes_per_thread = NUM_NODES / NUM_THREADS;
    FILE* logfile = fopen(LOG_FILE, "w");

    srand(time(NULL));

    if (!logfile) {
        perror("Cannot open log file");
        result = 1;
    } else {
        fclose(fopen(LOG_FILE, "w"));
        logfile = fopen(LOG_FILE, "a");

        // Divide list into thread lists
        for (i = 0; i < NUM_THREADS; i++) {
            thread_lists[i] = current;
            j = 0;
            is_found = 0;
            while (j++, j < nodes_per_thread && current && !is_found) {
                if (j == nodes_per_thread - 1 || current->next == NULL) {
                    temp = current->next;
                    current->next = NULL;
                    if (temp) temp->prev = NULL;
                    current = temp;
                    is_found = 1;
                }
                current = current->next;
            }
        }

        start = clock();

        for (i = 0; i < NUM_THREADS; i++) {
            thread_args[i].sublist = thread_lists[i];
            thread_args[i].thread_num = i + 1;
            pthread_create(&threads[i], NULL, ThrdFunc, &thread_args[i]);
        }

        for (i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], (void**)&thread_lists[i]);
        }

        // Merge sorted lists
        merged_list = thread_lists[0];
        for (i = 1; i < NUM_THREADS; i++) {
            merged_list = merge_sorted_lists(merged_list, thread_lists[i]);
        }
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(logfile, "Nodes: %d\n", NUM_NODES);
        fprintf(logfile, "Total Sort Time: %f seconds\n", time_spent);
        
        fclose(logfile);
        
        ListFree(merged_list);
    }
    return result;
}