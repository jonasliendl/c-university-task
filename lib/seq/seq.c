#include "seq.h"

int main() 
{
    unsigned int node_amount = 10000000;
    Node* head = Gen(node_amount);
    clock_t end;
    double time_spent;
    FILE* file;
    bool sorted;
    int length;

    clock_t begin = clock();

    Sort(head);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent: %f\n", time_spent);
    
    file = fopen(LOG_FILE_SEQUENTIAL, "w");
    if (file != NULL) {
        fprintf(file, "Sorting duration: %.8f seconds\n", time_spent);
        fprintf(file, "Node amount: %d\n", node_amount);
        fclose(file);
    }
    sorted = IsSorted(head);
    if (sorted) {
        printf("List is sorted\n");
    } else {
        printf("List is not sorted\n");
    }
    length = GetLength(head);
    printf("List length: %d\n", length);

    ListOut(head, head, head->prev);

    ListFree(head);
    return 0;
}