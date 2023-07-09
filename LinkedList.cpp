#include "LinkedList.h"


LinkedList::LinkedList(/* args */)
{
    head = (Link*)malloc(sizeof(Link));
    head->value = 0;
    head->next = nullptr;
}


void LinkedList::FreeList(Link * head)
{
    if(head != nullptr){
        FreeList(head->next);
        free(head);
    }
}


LinkedList::~LinkedList()
{
    FreeList(head);
}