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
    Node* unsorted_list = Gen(10);
    Node* chased_tail = chaseTail(unsorted_list);

    unsigned int max_threads = 4;
    int active_threads = 0;
    pthread_mutex_t thread_lock;
    pthread_mutex_init(&thread_lock, NULL);

    ThreadArgs args = {unsorted_list, chased_tail, max_threads, 0, &thread_lock};

    ThrdFunc(&args);
    ListOut(unsorted_list, unsorted_list, unsorted_list->next->next->next);
    ListFree(unsorted_list);
    return 0;
} 