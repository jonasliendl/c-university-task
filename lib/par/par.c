#include "par.h"

void* ThrdFunc(void* args)
{
    clock_t begin;
    clock_t end;
    double time_spent;
    FILE* log_file;
    pthread_t thread_id = pthread_self();
    ThreadArgs* thread_args = (ThreadArgs*) args;
    unsigned int nodes_amount = GetListLength(thread_args->head);

    begin = clock();
    Sort(thread_args->head);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    pthread_mutex_lock(thread_args->thread_lock);
    log_file = fopen(LOG_FILE, "a");
    if (log_file != NULL)
    {
        fprintf(log_file, "Thread: %llu - Seconds used: %.8f - Nodes: %d\n", (unsigned long long)thread_id, time_spent, nodes_amount);
    }
    fclose(log_file);
    pthread_mutex_unlock(thread_args->thread_lock);

    pthread_exit(NULL);
    return NULL;
}

void SplitDLL(Node* head, Node* start_nodes[], Node* end_nodes[])
{
    int current_part_size;
    Node* next_part_start;

    unsigned int totalLength = GetListLength(head);
    int partSize = totalLength / AMOUNT_THREADS;
    int remainder = totalLength % AMOUNT_THREADS;
    Node *current = head;

    for (int i = 0; i < AMOUNT_THREADS; i++) {
        start_nodes[i] = current;
        
        current_part_size = partSize + (i < remainder ? 1 : 0);
        for (int j = 1; j < current_part_size && current; j++) {
            current = current->next;
        }
        
        end_nodes[i] = current;
        next_part_start = current ? current->next : NULL;
        
        if (current) current->next = NULL;
        if (next_part_start) next_part_start->prev = NULL;
        
        current = next_part_start;
    }
}

Node* MergeDLL(Node* start_nodes[], Node* end_nodes[])
{
    // in each index pick the smallest node from the sorted lists
    // return the smallest node at index 0

    Node* head = NULL;
    Node* current = NULL;
    Node* smallest = NULL;
    int smallest_index = -1;

    Node* current_nodes[AMOUNT_THREADS];
    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        current_nodes[i] = start_nodes[i];
    }
    while (true){
        // find the smallest node in this iteration
        for (int i = 0; i < AMOUNT_THREADS; i++)
        {
            if (current_nodes[i] != NULL)
            {
                if (smallest == NULL || current_nodes[i]->data < smallest->data)
                {
                    smallest = current_nodes[i];
                    smallest_index = i;
                }
            }
        }

        if (smallest != NULL)
        {
            if (head == NULL) head = smallest;
            if (current == NULL) current = smallest;
            else if (current != NULL) {
                current->next = smallest;
                smallest->prev = current;
            }
            current = smallest;
            current_nodes[smallest_index] = current_nodes[smallest_index]->next;
            smallest = NULL;
        } else {
            break;
        }
    }

    return head;
}

int main()
{
    int exit;
    pthread_t thr;
    pthread_mutex_t thread_lock;
    Node* start_nodes[AMOUNT_THREADS];
    Node* end_nodes[AMOUNT_THREADS];
    pthread_t threads[AMOUNT_THREADS];
    ThreadArgs* args[AMOUNT_THREADS];
    Node* head = Gen(10);
    ListOut(head, head, GetTail(head));
    pthread_mutex_init(&thread_lock, NULL);

    SplitDLL(head, start_nodes, end_nodes);

    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        args[i] = malloc(sizeof(ThreadArgs));
        args[i]->head = start_nodes[i];
        args[i]->thread_lock = &thread_lock;
        pthread_create(&thr, NULL, ThrdFunc, (void*) args[i]);
        threads[i] = thr;
    }
    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        ListOut(start_nodes[i], start_nodes[i], end_nodes[i]);
    }

    head = MergeDLL(start_nodes, end_nodes);

    ListOut(head, head, GetTail(head));
    exit = verifySorted(head) ? EXIT_SUCCESS : EXIT_FAILURE;
    ListFree(head);
    return exit;
} 