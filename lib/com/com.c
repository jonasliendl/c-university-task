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

int AppendToList(Node* item_component, Node* new_item) {
     if (item_component->prev == NULL) {
        item_component->prev = new_item;
        return 0;
    }
    int is_found = 0;
    Node* current_item = item_component;
    while (is_found == 0) {
        if (current_item->next == NULL) {
            current_item->next = new_item;
            is_found = 1;
        }
        current_item = item_component->next;
    }
    return 0;
}

int GetListLength(Node* list_component) {
    int length = 0;
    if (list_component == NULL) {
        return length;
    }
    int is_direction_forward = 1;
    Node* current_item = list_component;
    int is_end = 0;
    if (current_item->next != NULL && current_item->prev != NULL) {
        while (is_end == 0) {
            current_item = current_item->prev;
            if (current_item->prev == NULL) {
                is_end = 1;
            }
        }
    } else if (current_item->next == NULL) {
        is_direction_forward = 0;
    }
    is_end = 0;
    while (is_end == 0) {
        length++;
        if ((is_direction_forward == 1 && current_item->next == NULL)
            || (is_direction_forward == 0 && current_item->prev == NULL)
            ) {
            is_end = 1;
        } else if (is_direction_forward == 1) {
            current_item = current_item->next;
        } else {
            current_item = current_item->prev;
        }
    }
    return length;
}
