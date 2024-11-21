#include "seq.h"

int main() 
{
    unsigned int node_amount = 10000000;
    Node* head = Gen(node_amount);

    clock_t begin = clock();

    Sort(head);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent: %f\n", time_spent);
    
    FILE *file = fopen(LOG_FILE_SEQUENTIAL, "w");
    if (file != NULL) {
        fprintf(file, "Sorting duration: %.8f seconds\n", time_spent);
        fprintf(file, "Node amount: %d\n", node_amount);
        fclose(file);
    }
    bool sorted = is_sorted(head);
    if (sorted) {
        printf("List is sorted\n");
    } else {
        printf("List is not sorted\n");
    }
    int length = get_length(head);
    printf("List length: %d\n", length);

    ListFree(head);
    return 0;
}