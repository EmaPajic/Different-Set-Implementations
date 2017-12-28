#ifndef SETREDBLACK_H
#define SETREDBLACK_H

#include <Set.h>
#include "RedBlack.h"

template<class T>
class SetRedBlack : public Set<T>
{

    RedBlack<T> rbtree;

    public:
        SetRedBlack(): rbtree(RedBlack<T>()) { Set<T>::implementation = 4; }
        ~SetRedBlack() {}
        bool findElem(const T& x) const
        {
            return rbtree.findElem(x);
        }

        void addElem(const T& x)
        {
            rbtree.addElem(x);
        }

        void deleteElem(const T& x)
        {
            rbtree.deleteElem(x);
        }

        void deleteFromTo(const T& x1,const T& x2)
        {
            rbtree.deleteFromTo(x1,x2);
        }

        int getNumOfElements() const
        {
            return rbtree.getNumOfElements();
        }

        void print() const
        {
            rbtree.inorder(rbtree.getRoot());
            cout<<endl;
        }

        Set<T>* union2(Set<T>* rb1)
        {
            SetRedBlack<T>* a = dynamic_cast<SetRedBlack<T>*>(rb1);
            SetRedBlack<T>* rb= new SetRedBlack<T>;
            rb->rbtree = this->rbtree.union22(a->rbtree);
            return rb;
        }
};

#endif // SETREDBLACK_H
