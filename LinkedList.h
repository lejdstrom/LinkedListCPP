#ifndef LINKED_LIST_H
#define LINDED_LIST_H

struct Link{
    int value;
    struct Link * next;
};

class LinkedList
{
public:
    Link head;
    LinkedList(/* args */);
    ~LinkedList();
};






#endif