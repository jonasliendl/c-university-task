//
// Created by Jonas Liendl on 12.11.24.
//
#include "com.h"

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
