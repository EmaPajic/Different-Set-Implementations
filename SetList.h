#ifndef SETLIST_H
#define SETLIST_H
#include <iostream>
#include <Set.h>

using namespace std;

template<class T>
class SetList : public Set<T>
{
    struct node
    {
        T data;
        node* next;
        node(const T& x): data(x),next(nullptr) {};
    };
    node* head;
    int num;

    public:

        SetList(): num(0),head(nullptr){ Set<T>::implementation = 1; }
        ~SetList()
        {
            num = 0;
            if(head == nullptr) return;
            if(head == head->next)
            {
                delete head;
                return;
            }

            node *curr = head->next;
            while(curr != head)
            {
                node *tmp = curr;
                curr = curr->next;
                delete tmp;
            }
            delete head;
            }

        bool findElem(const T& x) const
        {
            if(head == nullptr) return false;
            if(head->data == x) return true;
            node* curr = head->next;
            while(curr != head)
            {
                if(curr->data == x) return true;
                curr = curr->next;
            }
            return false;

        }

        void addElem(const T& x)
        {

            node* nd = new node(x);
            if(head == nullptr)
            {
                head = nd;
                head->next = head;
                num++;
                return;
            }
            if(head->data > x)
            {
                nd->next = head->next;
                head->next = nd;
                nd->data = head->data;
                head->data = x;
                num++;
                return;
            }
            if(head->data == x)
            {
                cout<<"Already have that element"<<endl;
                return;
            }
            node *curr = head;

            while(curr->next->data <= x && curr->next != head)
            {
                if(curr->next->data == x)
                {
                    cout<<"Already have that element"<<endl;
                    return;
                }
                curr = curr->next;
            }

            num++;
            nd->next = curr->next;
            curr->next = nd;
        }

        void deleteElem(const T& x)
        {
            if(head == nullptr)
            {
                cout<<"Trying to delete from empty set"<<endl;
                return;
            }
            if(head->data == x)
            {
                if(head == head->next)
                {
                    delete head;
                    num--;
                    return;
                }
                node* curr = head;
                head = head->next;
                num--;
                delete curr;
                return;
            }
            node* curr = head;
            while(curr->next != head)
            {
                if(curr->next->data == x)
                {
                    node* tmp = curr->next;
                    curr->next = curr->next->next;
                    num--;
                    delete tmp;
                    return;
                }
                curr=curr->next;
            }
            cout<<"Trying to delete number that is not in the set"<<endl;
        }

        void deleteFromTo(const T& x1,const T& x2)
        {
            if(head == nullptr)
            {
                cout<<"Trying to delete from empty set"<<endl;
                return;
            }
            node* last = head;
            if((head->data >= x1) && (head->data <= x2))
            {
                while(last->next != head)
                {
                    last = last->next;
                }
            }
            while((head->data >= x1) && (head->data <= x2))
            {
                if(head == head->next)
                {
                    delete head;
                    num--;
                    return;
                }
                node* curr = head;
                head = head->next;
                delete curr;
                num--;
                if(num==0)
                {
                    head = nullptr;
                    return;
                }
            }
            last->next = head;
            node* curr = head;
            bool check = false;
            while(curr->next != head)
            {
                while((curr->next->data >= x1) && (curr->next->data <= x2))
                {
                    node* tmp = curr->next;
                    curr->next = curr->next->next;
                    delete tmp;
                    num--;
                }
                curr = curr->next;
            }
        }

        int getNumOfElements() const
        {
            return num;
        }

        Set<T>* union2(Set<T>* s1)
        {
            SetList<T>* s = dynamic_cast<SetList<T>*>(s1);
            node* nd1 = head;
            node* nd2 = s->head;
            SetList<T>* st=new SetList<T>;

            if(s->head == nullptr)
            {
                st->head = head;
                st->num = num;
                return st;
            }
            if(head == nullptr)
            {
                st->head = s->head;
                st->num = s->num;
                return st;
            }

            int cnt1 = 0, cnt2 = 0;

            while(st->head == nullptr)
            {
                if(nd1->data < nd2->data)
                {
                    node* tmp = new node(nd1->data);
                    st->head = tmp;
                    cnt1++;
                    st->num++;
                    nd1 = nd1->next;
                }
                else if(nd1->data > nd2->data)
                {
                    node* tmp = new node(nd2->data);
                    st->head = tmp;
                    cnt2++;
                    st->num++;
                    nd2 = nd2->next;
                }
                else
                {
                    cnt2++;
                    nd2 = nd2->next;
                }
            }

            node* cr = st->head;

            while(cnt1 < num && cnt2 < s->num)
            {
                if(nd1->data < nd2->data)
                {
                    node* tmp = new node(nd1->data);
                    cr->next = tmp;
                    cnt1++;
                    st->num++;
                    nd1 = nd1->next;
                    cr = cr->next;
                }
                else if(nd1->data > nd2->data)
                {
                    node* tmp = new node(nd2->data);
                    cr->next = tmp;
                    cnt2++;
                    st->num++;
                    nd2 = nd2->next;
                    cr = cr->next;
                }
                else
                {
                    cnt2++;
                    nd2 = nd2->next;
                }
            }

            while(cnt1 < num)
            {
                node* tmp = new node(nd1->data);
                cr->next = tmp;
                cnt1++;
                st->num++;
                nd1 = nd1->next;
                cr = cr->next;
            }

            while(cnt2 < s->num)
            {
                node* tmp = new node(nd2->data);
                cr->next = tmp;
                cnt2++;
                st->num++;
                nd2 = nd2->next;
                cr = cr->next;
            }
            cr->next = st->head;
            return st;
        }

        void print() const
        {
            if(head == nullptr)
            {
                cout<<"Empty set"<<endl;
                return;
            }
            node* curr = head;
            while(curr->next != head)
            {
                cout<<curr->data<<" ";
                curr = curr->next;
            }
            cout<<curr->data<<endl;
        }
};

#endif // SETLIST_H
