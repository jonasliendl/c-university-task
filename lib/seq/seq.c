#include "seq.h"

int main() 
{
    Node* head = Gen(100000);
    Node* tail = getTail(head);
    Sort(head, tail);
    ListOut(head, head, head->next->next->next);
    ListFree(head);
    return 0;
}