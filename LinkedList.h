#ifndef LINKED_LIST_H
#define LINDED_LIST_H

#include <stdlib.h>
#include <stdio.h>

struct Link{
    int value;
    struct Link * next;
};

class LinkedList
{
private:
    void FreeList(Link *head);
public:
    Link *head;
    LinkedList(/* args */);
    ~LinkedList();
    void Insert(int val);
    void Print();
};






#endif