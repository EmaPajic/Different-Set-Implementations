#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;

template<class T>
class Stack
{

    struct node
    {
        T data;
        node* next;
        node(const T& x): data(x),next(nullptr) {};
    };

    node* head;

    public:
        Stack(): head(nullptr){};
        ~Stack()
        {
            node *curr=head;
            while(curr!=nullptr)
            {
                head=head->next;
                delete curr;
                curr=head;
            }
        }

        bool emptyStack() const
        {
            if(head == nullptr) return true;
            return false;
        }

        void push(const T&x)
        {
            node* nd=new node(x);
            if(head==nullptr)
            {
                head=nd;
                return;
            }
            nd->next=head;
            head=nd;
        }

        void pop()
        {
            node* tmp=head;
            head=head->next;
            delete tmp;
        }

        T top() const
        {
            return head->data;
        }
};

#endif // STACK_H
