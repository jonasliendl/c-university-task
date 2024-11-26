#include "seq.h"

int main() 
{
    clock_t end;
    double time_spent;
    FILE* file;

    unsigned int node_amount = 10000000;
    Node* head = Gen(node_amount);
    clock_t begin = clock();

    Sort(head);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    file = fopen(LOG_FILE_SEQUENTIAL, "w");
    if (file != NULL) {
        fprintf(file, "Sorting duration: %.8f seconds\n", time_spent);
        fprintf(file, "Node amount: %d\n", node_amount);
        fclose(file);
    }

    ListFree(head);
    return 0;
}