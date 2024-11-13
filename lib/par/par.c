#include <stdio.h>
#include "par.h"

#define AMOUNT_THREADS 2

// ThrdFunc function for managing threads
void* ThrdFunc(void* args)
{
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    Node* head = threadArgs->head;
    Node* tail = threadArgs->tail;
    int max_threads = threadArgs->max_threads;
    int active_threads = threadArgs->active_threads;
    pthread_mutex_t* thread_lock = threadArgs->thread_lock;
    if (head != tail && head != NULL && tail != NULL && head != tail->next) {
        Node* pivot = partition(head, tail);

        // Prepare arguments for the left and right partition threads
        ThreadArgs leftArgs = {head, pivot->prev, max_threads, active_threads, thread_lock};
        ThreadArgs rightArgs = {pivot->next, tail, max_threads, active_threads, thread_lock};

        pthread_t leftThread, rightThread;
        int leftThreadCreated = 0, rightThreadCreated = 0;

        pthread_mutex_lock(thread_lock);
        if (active_threads < max_threads) {
            (active_threads)++;
            leftThreadCreated = pthread_create(&leftThread, NULL, ThrdFunc, &leftArgs) == 0;
        }
        if (active_threads < max_threads) {
            (active_threads)++;
            rightThreadCreated = pthread_create(&rightThread, NULL, ThrdFunc, &rightArgs) == 0;
        }
        pthread_mutex_unlock(thread_lock);

        // If threads couldn't be created due to max_threads limit, fallback to single-threaded Sort
        if (!leftThreadCreated) Sort(head, pivot->prev);
        if (!rightThreadCreated) Sort(pivot->next, tail);

        // Join threads if they were created
        if (leftThreadCreated) {
            pthread_join(leftThread, NULL);
            pthread_mutex_lock(thread_lock);
            (active_threads)--;
            pthread_mutex_unlock(thread_lock);
        }
        if (rightThreadCreated) {
            pthread_join(rightThread, NULL);
            pthread_mutex_lock(thread_lock);
            (active_threads)--;
            pthread_mutex_unlock(thread_lock);
        }
    }
    return NULL;
}


int main()
{
    Node* head = Gen(100000);
    Node* tail = chaseTail(head);

    pthread_mutex_t thread_lock;
    pthread_mutex_init(&thread_lock, NULL);

    ThreadArgs args = {head, tail, AMOUNT_THREADS, 0, &thread_lock};

    clock_t begin = clock();
    ThrdFunc(&args);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f", time_spent);
    ListOut(head, head, tail);
    ListFree(head);
    return 0;
} 