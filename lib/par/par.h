#include "../com/com.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define AMOUNT_THREADS 4
#define LOG_FILE "./log/par.log"

/*
Diese Funktion führt jeder Thread (außer Haupt-Thread) aus. Sie muss die standardmäßigen
Parameter und Rückgabewert haben, sonst funktioniert sie nicht. Als Parameter bekommt sie die
Anfangsadresse der Liste. Sie merk die Startzeit, ruft die Funktion Sort() auf, übergibt ihr die
Anfangsadresse der Liste. Nach der Sortierung merk sie die Endzeit und schreibt die oben
benannten Daten in die log-Datei
*/
void* ThrdFunc(void* args);

typedef struct ThreadArgs 
{
    Node* head;
    pthread_mutex_t* thread_lock;
} ThreadArgs;
