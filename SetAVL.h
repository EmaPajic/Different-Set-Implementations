#ifndef SETAVL_H
#define SETAVL_H
#include "AVL.h"
#include <iostream>
#include "Set.h"

using namespace std;

template<class T>
class SetAVL : public Set<T>
{
    AVL<T> avltree;

    public:
        SetAVL(): avltree(AVL<T>()){ Set<T>::implementation = 3; };

        ~SetAVL()
        {

        }

        bool findElem(const T& x) const
        {
            return avltree.findElem(x);
        }

        void addElem(const T& x)
        {
            avltree.addEleme(x);
        }

        void deleteElem(const T& x)
        {
            avltree.deleteEleme(x);
        }

        void deleteFromTo(const T& x1,const T& x2)
        {
            avltree.deleteFromTo(x1,x2);
        }

        Set<T>* union2(Set<T>* a1)
        {
            SetAVL<T>* a = dynamic_cast<SetAVL<T>*>(a1);
            SetAVL<T>* av = new SetAVL<T>;
            av->avltree = this->avltree.union22(a->avltree);
            return av;
        }

        int getNumOfElements() const
        {
            return avltree.getNumElem();
        }

        void print() const
        {
            avltree.inorder(avltree.getRoot());
            cout<<endl;
        }
};

#endif // SETAVL_H
