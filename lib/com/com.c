#include "com.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


Node* Reserve() 
{
    Node* node_new = malloc(sizeof(Node));
    node_new->data = RandZ(DIGITS_MIN + RandZ(2) % DIGITS_MAX);
    return node_new;
}

Node* Gen(unsigned int length)
{
    Node* current;

    Node* head = Reserve();
    head->prev = NULL;
    current = head;

    for (unsigned int i = 1; i < length; i++ ) {
        Node* _node = Reserve();
        current->next = _node;
        _node->prev = current;
        current = _node;
    }
    current->next = NULL;
    return head;
}

void AppendToList(Node* item_component, Node* new_item) 
{
     if (item_component->prev == NULL) {
        item_component->prev = new_item;
    } else {
         int is_found = 0;
         Node *current_item = item_component;
         while (is_found == 0) {
             if (current_item->next == NULL) {
                 current_item->next = new_item;
                 is_found = 1;
             }
             current_item = item_component->next;
         }
     }
}

int GetListLength(Node* list_component) 
{
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

void ListFree(Node* head)
{
    Node* current = head->next;
    while (current->next != NULL)
    {
        free(current->prev);
        current->prev = NULL;
        current = current->next;
    }
    free(current);
}

void ListOut(Node* head, Node* start, Node* end)
{
    // start is in list
    bool start_in_list = searchNode(head, start);
    bool end_in_list = searchNode(head, end);
    bool start_before_end = searchNode(start, end);
    Node* current;
    if (!start_in_list || !end_in_list || !start_before_end)
    {
        current = head;
    } else {
        current = start;
    }
    while(current->next != NULL)
    {   
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("%d\n", current->data);
}

bool searchNode(Node* start, Node* query)
{
    Node* current = start;
    while(current != NULL)
    {
        if (current == query)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* getTail(Node* node)
{
    while(node->next != NULL)
    {
        node = node->next;
    }
    return node;
}

Node* partition(Node* low, Node* high) {
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == NULL) ? low : i->next;
            int temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
    }
    i = (i == NULL) ? low : i->next;
    int temp = i->data;
    i->data = high->data;
    high->data = temp;
    return i;
}

void Sort(Node* head, Node* tail) {
    if (head != tail && head != NULL && tail != NULL && head != tail->next) {
        Node* pivot = partition(head, tail);
        Sort(head, pivot->prev);
        Sort(pivot->next, tail);
    }
}

bool  verifySorted(Node *head)
{
    Node* current_node = head;
    Node* comp_node = head;
    bool sorted;
    while (current_node != NULL && current_node->data >= comp_node->data)
    {
        comp_node = current_node;
        current_node = current_node->next;
    }
    if (current_node == NULL) sorted = true;
    else sorted = false;
    return sorted;
}