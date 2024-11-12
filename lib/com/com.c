#include "com.h"
#include <stdlib.h>
#include <time.h>


Node* Reserve() {
    Node* node_new = malloc(sizeof(Node));
    node_new->data = RandZ(DIGITS_MIN + RandZ(2) % DIGITS_MAX);
    return node_new;
}

Node* Gen(unsigned int length) {
    Node* current;

    Node* head = Reserve();
    head->prev = NULL;
    current = head;

    int i;
    for (i = 1; i < length; i++ ) {
        Node* _node = Reserve();
        current->next = _node;
        _node->prev = current;
        current = _node;       
    }
    current->next = NULL;
    return head;
}