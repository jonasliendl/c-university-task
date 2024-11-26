#include "com.h"

Node* Reserve() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->data = rand() % (MAX_RAND_VALUE + 1);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Node* Gen(unsigned int count) {
    if (count <= 0) return NULL;

    Node* head = Reserve();
    Node* current = head;

    for (unsigned int i = 1; i < count; i++) {
        Node* newNode = Reserve();
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }

    return head;
}

void ListOut(Node* list, Node* start, Node* end) {
    // If no start or end specified, print entire list
    Node* current = list;
    int startFound = 0, endFound = 0;

    if (!start || !end) {
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        return;
    }

    // Validate start and end are in the list
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
        printf("\n");
        return;
    }

    // Print from start to end
    current = start;
    while (current && current != end->next) {
        printf("%d ", current->data);
        current = current->next;
    }
    
    if (current == end->next) {
        printf("%d ", end->data);
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
    // If low or high is NULL, return NULL
    if (!low || !high) return NULL;

    // Choose the last node as pivot
    int pivot = high->data;
    
    // Pointer for the greater element
    Node* i = low ? low->prev : NULL;
    int temp;
    
    // Traverse through all nodes
    for (Node* j = low; j != high; j = j->next) {
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
    
    return i;
}

// Recursive Quick Sort function
void quickSort(Node* low, Node* high) {
    // Base case: if low is NULL or low == high or low comes after high
    if (!low || !high || low == high || 
        (low->prev && low->prev == high)) return;
    
    // Find the partition index
    Node* p = Partition(low, high);
    
    // Find the last node of the left side
    Node* left_end = p ? p->prev : NULL;
    
    // Recursively sort left and right sides
    quickSort(low, left_end);
    quickSort(p ? p->next : NULL, high);
}

// Modified Sort function
void Sort(Node* list) {
    if (!list) return;
    
    // Find the last node
    Node* last = list;
    while (last->next) last = last->next;
    
    // Call Quick Sort
    quickSort(list, last);
}

bool IsSorted(Node* list) {
    if (!list || !list->next) return true;

    Node* current = list;
    while (current->next) {
        if (current->data > current->next->data) return false;
        current = current->next;
    }

    return true;
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