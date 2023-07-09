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
ErrorCodes LinkedList::FindPrev(Link const * link, Link const ** prev)
{
  Link * curr = head;

    while(curr != nullptr)
    {
        if(curr->next == link){
            *prev = curr;
            return SUCCESS;
        }
        curr = curr->next;
    }

    return NO_SUCH_ELEMENT;
}
ErrorCodes LinkedList::Find(int valTofind, Link const ** link)
{
    Link * curr = head;

    while(curr != nullptr)
    {
        if(curr->value == valTofind){
            *link = curr;
            return SUCCESS;
        }
        curr = curr->next;
    }

    return NO_SUCH_ELEMENT;
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

ErrorCodes LinkedList::LastLink(Link const ** lastLink)
{
    ErrorCodes res = FindPrev(nullptr, lastLink);

    if(res != SUCCESS)
        return res;

    if(*lastLink == head) // mean empty list
        return NO_SUCH_ELEMENT;

    return SUCCESS;
}

ErrorCodes LinkedList::Remove(Link* linkToRemove, bool isToFree)
{
    if(linkToRemove == nullptr){
        return INVALID_PARAM;
    }

    Link const* prev;
    ErrorCodes status = FindPrev(linkToRemove, &prev);

    if(status != SUCCESS){
        return status;
    }

    ((Link*)prev)->next = linkToRemove->next;

    if(isToFree)
        free(linkToRemove);
    
    return SUCCESS;
}