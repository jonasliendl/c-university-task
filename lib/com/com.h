// File: com.h
#ifndef COM_H
#define COM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "utils/rand.h"
#include <stdbool.h>

typedef struct Node {
    int data;              // Datenelement des Nodes
    struct Node* next;     // Zeiger auf den nächsten Node
    struct Node* prev;     // Zeiger auf den vorherigen Node
} Node;

#define NUM_NODES 10000000
#define MAX_RAND_VALUE 1000000

void AppendToList(Node* list_component, Node* new_item);

/*
Diese Funktion generiert eine doppelt verkettete lineare Liste mit ganzen Zahlen, deren Anzahl
als Parameter angegeben wird. Sie verwendet die Funktion Reserve(), um Arbeitsspeicher für
einzelnen Knoten zu reservieren, und verbindet den neue Knoten in die Liste. Sie gibt die
Anfangsadresse der Liste zurück.
*/
Node* Gen(unsigned int length);

/*
Diese Funktion reserviert einen Speicherbereich für einen Knoten und initialisiert ihn. Sie hat
keine Parameter und gibt die Adresse des reservierten Bereiches zurück. Die Zahl im Knoten wird
mit einem Zufallswert von 0 bis größtmöglichen Wert belegt.
*/
Node* Reserve();

/*
Diese Funktion wird in jedem Thread des parallelen Programms und im sequenziellen Programm
verwendet, um die Liste zu sortieren. Sie bekommt die Anfangsadresse der Liste (die Adresse des
1. Knotens der Liste) als Parameter und hat keinen Rückgabewert. Nach der Sortierung enthält
dieser Parameter ebenfalls die Anfangsadresse der Liste. Somit wird dieser Parameter auch in der
rufenden Funktion bekannt. 
*/
void Sort(Node* head);

/*
Diese Funktion hat drei Parameter und keinen Rückgabewert. Sie gibt die ganze Liste auf dem
Bildschirm aus, oder einen Teil der Liste, nämlich Knoten "von ... bis". Der 1. Parameter gibt die
Anfangsadresse der ganzen Liste an, der 2. und der 3. Parameter geben die Anfangs- und
Endknoten an. Befindet sich der 2. oder der 3. Parameter außerhalb des zulässigen Bereiches
(1 ... Anzahl der Knoten), so gibt diese Funktion die ganze Liste aus (keine Fehlermeldungen in
diesem Fall)
*/
void ListOut(Node* head, Node* start, Node* end);

/*
Diese Funktion hat einen Parameter (die Anfangsadresse der ganzen Liste) und keinen
Rückgabewert. Sie gibt den Speicherbereich aller Knoten in der Liste frei.
*/
void ListFree(Node* head);

/* 
Diese Funktion sucht das Ende einer verketteten Liste und hat die Adresse als Rückgabewert.
*/
Node* GetTail(Node* node);

Node* Partition(Node* low, Node* high);

bool SearchNode(Node* start, Node* query);

unsigned int GetListLength(Node* head);

bool is_sorted(Node* list);

int get_length(Node* list);

#endif