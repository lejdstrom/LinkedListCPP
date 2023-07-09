#ifndef LINKED_LIST_H
#define LINDED_LIST_H

#include <stdlib.h>
#include <stdio.h>

class Link{
public:
    int value;
    Link * next;
};

typedef enum { SUCCESS, ALLOC_FAIL, NO_SUCH_ELEMENT, INVALID_PARAM, NOT_IMPLEMENTED } ErrorCodes;


class LinkedList
{
private:
    void FreeList(Link *head);
public:
    // member
    Link *head;

    // function
    LinkedList();
    ~LinkedList();
    void Insert(int val);
    void Append(int val);
    ErrorCodes Find(int valTofind, Link const ** link);
    ErrorCodes FindPrev(Link const * link, Link const ** prev);
    ErrorCodes LastLink(Link const ** lastLink);
    ErrorCodes Remove(Link* linkToRemove, bool isToFree);
    size_t Length();
    void Print();
};






#endif