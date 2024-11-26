#include "com.h"

Node* Reserve() {
    Node* result;

    Node* newNode = (Node*)malloc(sizeof(Node));

    if (!newNode) {
        perror("Memory allocation failed");
        result = NULL;
    } else {
        newNode->data = rand() % (MAX_RAND_VALUE + 1);
        newNode->next = NULL;
        newNode->prev = NULL;
        result = newNode;
    }
    return result;
}

Node* Gen(unsigned int count) {
    Node* current;
    Node* newNode;

    Node* result = NULL;

    if (count > 0) {
        result = Reserve();
        current = result;

        for (unsigned int i = 1; i < count; i++) {
            newNode = Reserve();
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
    }

    return result;
}

void ListOut(Node* list, Node* start, Node* end) {
    Node* current = list;
    int startFound = 0, endFound = 0;

    while (current) {
        if (current == start) startFound = 1;
        if (current == end) endFound = 1;
        current = current->next;
    }

    if (!startFound || !endFound) {
        // If start or end are not in the list, print entire list
        current = list;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
    } else {
        current = start;
        while (current && current != end->next) {
            printf("%d ", current->data);
            current = current->next;
        }
        
        if (current == end->next) {
            printf("%d ", end->data);
        }
    }
    printf("\n");
}

void ListFree(Node* list) {
    Node* temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

// Partition function for Quick Sort
Node* Partition(Node* low, Node* high) {
    Node* result = NULL;

    if (low && high) {
        int temp;
        Node* j;

        int pivot = high->data;
        Node* i = low ? low->prev : NULL;
        
        // Traverse through all nodes
        for (j = low; j != high; j = j->next) {
            // If current element is smaller than or equal to pivot
            if (j->data <= pivot) {
                // Move i pointer forward
                i = (i == NULL) ? low : i->next;
                
                // Swap data instead of nodes
                if (i && j) {
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
        
        // Place pivot in correct position
        i = (i == NULL) ? low : i->next;
        if (i && high) {
            temp = i->data;
            i->data = high->data;
            high->data = temp;
        }
        result = i;
    }
    return result;
}

// Recursive Quick Sort function
void QuickSort(Node* low, Node* high) {
    if (low && high && low != high && (!low->prev || low->prev != high)) {
        // Find the partition index
        Node* p = Partition(low, high);
        
        // Find the last node of the left side
        Node* left_end = p ? p->prev : NULL;
        
        // Recursively sort left and right sides
        QuickSort(low, left_end);
        QuickSort(p ? p->next : NULL, high);
    }
}

// Modified Sort function
void Sort(Node* list) {
    if (list) {
        // Find the last node
        Node* last = list;
        while (last->next) last = last->next;
        
        // Call Quick Sort
        QuickSort(list, last);
    }
}

bool IsSorted(Node* list) {
    bool is_sorted = true;

    if (list && list->next) {
        Node* current = list;
        while (current->next && is_sorted) {
            if (current->data > current->next->data) is_sorted = false;
            current = current->next;
        }
    }
    return is_sorted;
}

int GetLength(Node* list) {
    int length = 0;
    Node* current = list;
    
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}