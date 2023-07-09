#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = (Link*)malloc(sizeof(Link));
    head->value = -1;
    head->next = nullptr;
}

void LinkedList::FreeList(Link * head)
{
    if(head != nullptr){
        FreeList(head->next);
        free(head);
    }
    // iterative free
    /*
    
    Link * tmp = head;
    Link * next = head;

    while(next != nullptr)
    {
        tmp = next;
        next = next->next;
        free(tmp);
    }

    free(head);
    
    */
}

LinkedList::~LinkedList()
{
    printf("I am the dtor !\n");
    FreeList(head);
}

// add to the begining
void LinkedList::Insert(int val)
{
    Link * newLink = (Link*)malloc(sizeof(Link));
    newLink->value = val;
    newLink->next = head->next;

    head->next = newLink;
}

void LinkedList::Append(int val)
{
    Link * curr = head;
    Link * newLink = (Link*)malloc(sizeof(Link));
    newLink->value = val;
    newLink->next = nullptr;
    
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }

    curr->next = newLink;
}

void LinkedList::Print()
{
    Link* curr = head->next;

    while(curr != nullptr)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("null\n");
}