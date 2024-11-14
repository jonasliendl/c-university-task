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
    Node* _node;
    Node* head = Reserve();

    head->prev = NULL;
    current = head;

    for (unsigned int i = 1; i < length; i++)
    {
        _node = Reserve();
        current->next = _node;
        _node->prev = current;
        current = _node;
    }
    current->next = NULL;
    return head;
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
    bool start_in_list = SearchNode(head, start);
    bool end_in_list = SearchNode(head, end);
    bool start_before_end = SearchNode(start, end);
    Node* current = start;

    if (!start_in_list || !end_in_list || !start_before_end)
    {
        current = head;
    }
    while(current->next != NULL)
    {   
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("%d\n", current->data);
}

bool SearchNode(Node* start, Node* query)
{
    Node* current = start;
    bool is_found = false;

    while(current != NULL && !is_found)
    {
        if (current == query)
        {
            is_found = true;
        }
        current = current->next;
    }
    return is_found;
}

Node* GetTail(Node* node)
{
    while(node->next != NULL)
    {
        node = node->next;
    }
    return node;
}

Node* Partition(Node* low, Node* high) {
    int temp;
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next)
    {
        if (j->data <= pivot)
        {
            i = (i == NULL) ? low : i->next;
            temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
    }
    i = (i == NULL) ? low : i->next;
    temp = i->data;
    i->data = high->data;
    high->data = temp;
    return i;
}

void QuickSortRecursive(Node* head, Node* tail)
{
    Node* pivot;

    if (head != NULL)
    {
        pivot = Partition(head, tail);
        QuickSortRecursive(head, pivot->prev);
        QuickSortRecursive(pivot->next, tail);
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

void Sort(Node* head)
{
    Node* tail = GetTail(head);
    QuickSortRecursive(head, tail);
}
