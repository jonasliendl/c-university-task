#include "seq.h"
#include <stdlib.h>

int main() 
{
    int exit;
    Node* head = Gen(100000);

    Sort(head);
    ListOut(head, head, head->next->next->next);
    exit = verifySorted(head) ? EXIT_SUCCESS : EXIT_FAILURE;
    ListFree(head);
    return exit;
}