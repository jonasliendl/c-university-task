#include "par.h"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    Node* sublist;
    int thread_num;
} ThreadArgs;

void* ThrdFunc(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    FILE* logfile = fopen(LOG_FILE, "a");
    if (!logfile) {
        perror("Cannot open log file");
        return NULL;
    }

    clock_t start = clock();
    Sort(args->sublist);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&log_mutex);
    fprintf(logfile, "Thread %d Sort Time: %f seconds\n", args->thread_num, time_spent);
    pthread_mutex_unlock(&log_mutex);

    fclose(logfile);
    return args->sublist;
}

Node* merge_sorted_lists(Node* list1, Node* list2) {
    // Base cases
    if (!list1) return list2;
    if (!list2) return list1;

    // Determine which list starts first
    Node* head = (list1->data <= list2->data) ? list1 : list2;
    Node* other = (list1->data <= list2->data) ? list2 : list1;

    Node* current = head;
    while (current->next && other) {
        // If next element in current list is less than first in other list, move forward
        if (current->next->data <= other->data) {
            current = current->next;
            continue;
        }

        // Swap in an element from the other list
        Node* temp = current->next;
        Node* other_next = other->next;

        current->next = other;
        other->prev = current;
        other->next = temp;
        if (temp) temp->prev = other;

        current = other;
        other = other_next;
    }

    // Append remaining elements
    if (other) {
        while (current->next) current = current->next;
        current->next = other;
        other->prev = current;
    }

    // Ensure the first node's prev is NULL
    head->prev = NULL;

    return head;
}

int main() {
    srand(time(NULL));

    Node* list = Gen(NUM_NODES);
    Node* thread_lists[NUM_THREADS];
    
    FILE* logfile = fopen(LOG_FILE, "w");
    if (!logfile) {
        perror("Cannot open log file");
        return 1;
    } else {
        // clear file
        fclose(fopen(LOG_FILE, "w"));
    }
    logfile = fopen(LOG_FILE, "a");

    // Divide list into thread lists
    Node* current = list;
    int nodes_per_thread = NUM_NODES / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_lists[i] = current;
        for (int j = 0; j < nodes_per_thread && current; j++) {
            if (j == nodes_per_thread - 1 || current->next == NULL) {
                Node* temp = current->next;
                current->next = NULL;
                if (temp) temp->prev = NULL;
                current = temp;
                break;
            }
            current = current->next;
        }
    }

    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];

    clock_t start = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].sublist = thread_lists[i];
        thread_args[i].thread_num = i + 1;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], (void**)&thread_lists[i]);
    }

    // Merge sorted lists
    Node* merged_list = thread_lists[0];
    for (int i = 1; i < NUM_THREADS; i++) {
        merged_list = merge_sorted_lists(merged_list, thread_lists[i]);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(logfile, "Nodes: %d\n", NUM_NODES);
    fprintf(logfile, "Total Sort Time: %f seconds\n", time_spent);
    
    fclose(logfile);
    ListFree(merged_list);

    return 0;
}