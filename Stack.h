#ifndef _STACK_
#define _STACK_
#include <iostream>
#include "StackItem.h"
using namespace std;

class Stack{
    StackItem *head;
public:
    Stack();
    void push(StackItem *);
    StackItem * pop();
    StackItem * top();
    bool isEmpty();
    ~Stack();
};
#endif