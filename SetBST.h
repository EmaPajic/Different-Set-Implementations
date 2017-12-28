#ifndef SETBST_H
#define SETBST_H

#include <Set.h>
#include <BST.h>

template<class T>
class SetBST : public Set<T>
{
    BST<T> tree;
    public:

        SetBST(): tree(BST<T>()){ Set<T>::implementation = 2; };
        ~SetBST()
        {

        }

        bool findElem(const T& x) const
        {
            return tree.findElem(x);
        }

        void addElem(const T& x)
        {
            tree.addElem(x);
        }

        void deleteElem(const T& x)
        {
            tree.deleteElem(x);
        }

        void deleteFromTo(const T& x1,const T& x2)
        {
            tree.deleteFromTo(x1,x2);
        }

        int getNumOfElements() const
        {
            return tree.getNumElem();
        }

        Set<T>* union2(Set<T>* bt1)
        {
            SetBST<T>* bt = dynamic_cast<SetBST<T>*>(bt1);
            SetBST<T>* btt = new SetBST<T>;
            btt->tree = this->tree.union22(bt->tree);
            return btt;
        }

        void print() const
        {
            tree.inorder();
        }
};

#endif // SETBST_H
