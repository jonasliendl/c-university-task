#include "../com/com.h"

int main() 
{
    Node* unsorted_list = Gen(100000);
    Node* chased_tail = chaseTail(unsorted_list);
    Sort(unsorted_list, chased_tail);
    ListOut(unsorted_list, unsorted_list, unsorted_list->next->next->next);
    ListFree(unsorted_list);
    return 0;
}