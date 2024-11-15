#include "seq.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() 
{
    int exit;
    unsigned int node_amount = 100000;
    Node* head = Gen(node_amount);

    clock_t begin = clock();

    Sort(head);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent: %f\n", time_spent);
    
    FILE *file = fopen(LOG_FILE_SEQUENTIAL, "a");
    if (file != NULL) {
        fprintf(file, "Sorting duration: %.8f seconds\n", time_spent);
        fprintf(file, "Node amount: %d\n", node_amount);
        fclose(file);
    }

    ListOut(head, head, head->next->next->next);
    exit = verifySorted(head) ? EXIT_SUCCESS : EXIT_FAILURE;
    ListFree(head);
    return exit;
}