#include "Stack.h"
#include "StackItem.h"

Stack::Stack(){
    this->head = NULL;
}

void Stack::push(StackItem *item){
    item->next = head;
    head = item;
}

StackItem * Stack::pop(){
    StackItem *temp = head;
    if(isEmpty()){
        cout << "Stack is Empty";
        return 0;
    }
    else{
        head = temp->next;
        return temp;
        delete temp;
    }
}

StackItem * Stack::top(){
    return head;
}

bool Stack::isEmpty(){

    if(head == NULL){
        return true;
    }
    else{
        return false;
    }
}

Stack::~Stack(){
    while(!isEmpty()){
        StackItem * sItem = pop();
        delete sItem;
    }
}