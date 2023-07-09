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

void LinkedList::Insert(int val)
{
    Link * newLink = (Link*)malloc(sizeof(Link));
    newLink->value = val;
    newLink->next = head->next;

    head->next = newLink;
}

void LinkedList::Print()
{
    Link* curr = head->next;

    while(curr != nullptr)
    {
        printf("%d ->", curr->value);
        curr = curr->next;
    }
}