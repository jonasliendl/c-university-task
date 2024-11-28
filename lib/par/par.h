// File: par.h
#ifndef PAR_H
#define PAR_H

#include "../com/com.h"

#define LOG_FILE "parallel.log"
#define NUM_THREADS 4

/*
Mutex for logging
*/
extern pthread_mutex_t log_mutex;

/*
Thread arguments
*/
typedef struct {
    Node* sublist;
    int thread_num;
} ThreadArgs;


/*
Diese Funktion verbindet zwei sortierte Listen. Sie nimmt zwei Zeiger auf die Listenköpfe 
und gibt einen Zeiger auf die Kopfzeiger der zusammengeführten Liste zurück.
*/
Node* merge_sorted_lists(Node* list1, Node* list2);

/*
Diese Funktion wird von jedem Thread aufgerufen. Sie nimmt einen Zeiger auf ein ThreadArgs-Objekt.
Sie gibt einen Zeiger auf die sortierte Liste zurück. Wenn ein Fehler auftritt, wird NULL zurückgegeben.
*/
void* ThrdFunc(void* arg);

#endif