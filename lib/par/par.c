#include <stdio.h>
#include <stdlib.h>
#include "par.h"

#define AMOUNT_THREADS 2

void* ThrdFunc(void* args)
{
    clock_t begin;
    clock_t end;
    pthread_t thread_id = pthread_self();

    begin = clock();
    Sort((Node*)args);
    end = clock();
    return NULL;
}

int main()
{
    int exit;
    pthread_t thr;
    pthread_mutex_t thread_lock;
    pthread_t threads[AMOUNT_THREADS];
    Node* head = Gen(100000);

    pthread_mutex_init(&thread_lock, NULL);

    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        // Add head of linked list part for specific thread
        pthread_create(&thr, NULL, ThrdFunc, (void*) head);
        threads[i] = thr;
    }

    for (int i = 0; i < AMOUNT_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // After all threads are done, merge the doubly linked list

    ListOut(head, head, head->next->next);
    exit = verifySorted(head) ? EXIT_SUCCESS : EXIT_FAILURE;
    ListFree(head);
    return exit;
} 