#ifndef REDBLACK_H
#define REDBLACK_H

#include <Set.h>
#include "Vector.h"
#include "Stack.h"

using namespace std;

template<class T>
class RedBlack
{
    struct rbnode
    {
        T data;
        short color; //red - 1, black - 0, double black 2
        rbnode* left;
        rbnode* right;
        rbnode* parent;
        rbnode(const T& x): data(x), color(1),left(nullptr), right(nullptr), parent(nullptr){}
    };
    Stack<rbnode*> nodeStack;
    Stack<int> leftStack;
    Stack<int> rightStack;

    int num;
    rbnode* root;
    Vector<T> arr, arr1,arr2;

    rbnode* add(rbnode* rt, rbnode* nd)
    {
        if(rt == nullptr)
        {
            num++;
            return nd;
        }

        if(nd->data == rt->data)
        {
            cout<<"Already have that element\n";
        }
        else if(nd->data < rt->data)
        {
            rt->left = add(rt->left, nd);
            rt->left->parent = rt;
        }
        else
        {
            rt->right = add(rt->right, nd);
            rt->right->parent = rt;
        }
        return rt;
    }

    rbnode* findMin(rbnode* nd)
	{
		if (nd == nullptr)
			return nullptr;
		else if (nd->left == nullptr)
			return nd;
		else
			return findMin(nd->left);
	}

    rbnode* removee(rbnode* rt, const T& x)
    {
        if(rt == nullptr) return rt;

        if(rt->data < x)
        {
            return removee(rt->right, x);
        }
        if(rt->data > x)
        {
            return removee(rt->left, x);
        }
        if ((rt->left == nullptr) || (rt->right == nullptr))
        {
            return rt;
        }

        rbnode* temp = findMin(rt->right);
        rt->data = temp->data;
        return removee(rt->right, temp->data);
    }

    void leftRotate(rbnode*& rt, rbnode*& nd)
    {
        rbnode* ndright = nd->right;
        nd->right = ndright->left;

        if(nd->right != nullptr)
        {
            nd->right->parent = nd;
        }

        ndright->parent = nd->parent;

        if(nd->parent == nullptr)
        {
            rt = ndright;
        }
        else if(nd->parent->left == nd)
        {
            nd->parent->left = ndright;
        }
        else
        {
            nd->parent->right = ndright;
        }

        ndright->left = nd;
        nd->parent = ndright;
    }

    void rightRotate(rbnode*& rt, rbnode*& nd)
    {
        rbnode* ndleft = nd->left;
        nd->left = ndleft->right;

        if(nd->left != nullptr)
        {
            nd->left->parent = nd;
        }

        ndleft->parent = nd->parent;

        if(nd->parent == nullptr)
        {
            rt = ndleft;
        }
        else if(nd->parent->left == nd)
        {
            nd->parent->left = ndleft;
        }
        else
        {
            nd->parent->right = ndleft;
        }

        ndleft->right = nd;
        nd->parent = ndleft;
    }

    void fixAddViolation(rbnode*& rt, rbnode*& nd)
    {
        if(nd == nullptr) return;
        rbnode* parentnd = nullptr;
        rbnode* grandparentnd = nullptr;

        while((nd != rt) && (color(nd) == 1))
        if(color(nd->parent) == 1)
        {
            parentnd = nd->parent;
            grandparentnd = nd->parent->parent;

            if(parentnd == grandparentnd->left)
            {
                rbnode* uncle = grandparentnd->right;
                bool flag = true;

                if(uncle != nullptr)
                if(color(uncle) == 1)
                {
                    flag = false;
                    grandparentnd->color = 1;
                    uncle->color = 0;
                    parentnd->color = 0;
                    nd = grandparentnd;
                }

                if(flag)
                {
                    if(nd == parentnd->right)
                    {
                        leftRotate(rt,parentnd);
                        nd = parentnd;
                        parentnd = nd->parent;
                    }

                    rightRotate(rt,grandparentnd);
                    swap(parentnd->color, grandparentnd->color);
                    nd = parentnd;
                }

            }
            else
            {
                rbnode* uncle = grandparentnd->left;
                bool flag = true;

                if(uncle != nullptr)
                if(color(uncle) == 1)
                {
                    flag = false;
                    grandparentnd->color = 1;
                    uncle->color = 0;
                    parentnd->color = 0;
                    nd = grandparentnd;
                }
                if(flag)
                {
                    if(nd == parentnd->left)
                    {
                        rightRotate(rt,parentnd);
                        nd = parentnd;
                        parentnd = nd->parent;
                    }

                    leftRotate(rt,grandparentnd);
                    swap(parentnd->color, grandparentnd->color);
                    nd = parentnd;
                }
            }
        }
        else break;

        rt->color = 0;
    }

    bool color(rbnode* nd)
    {
        if(nd == nullptr) return 0;
        return nd->color;
    }

    void fixDeleteViolation(rbnode*& root,rbnode*& nd)
    {
        if(nd == nullptr) return;
        if(nd == root)
        {
            delete root;
            root == nullptr;
            num--;
            return;
        }

        if((color(nd) == 1) || (color(nd->left) == 1) || (color(nd->right) == 1))
        {
            rbnode* temp = nd->left? nd->left : nd->right;
            if(nd == nd->parent->left)
            {
                if (nd == nd->parent->left)
                {
                    nd->parent->left = temp;
                    if (temp != nullptr)
                    {
                        temp->parent = nd->parent;
                        temp->color = 0;
                    }
                    num--;
                    delete nd;
                }
            }
            else
            {
                nd->parent->right = temp;
                if (temp != nullptr)
                {
                    temp->parent = nd->parent;
                    temp->color = 0;
                }
                num--;
                delete nd;
            }
        }
        else
        {
            rbnode* siblingnd = nullptr;
            rbnode* parentnd = nullptr;
            rbnode* p = nd;
            p->color = 2;

            while((p != root) || (p->color == 2))
            {
                parentnd = p->parent;
                if(p == parentnd->left)
                {
                    siblingnd = parentnd->right;
                    if(color(siblingnd) == 1)
                    {
                        siblingnd->color = 0;
                        parentnd->color = 1;
                        leftRotate(root,parentnd);
                    }
                    else
                    {
                        if((color(siblingnd->left) == 0) && (color(siblingnd->right) == 0))
                        {
                            siblingnd->color = 1;
                            if(color(parentnd) == 1)
                            parentnd->color = 0;
                            else
                            parentnd->color = 2;
                            p = parentnd;
                        }
                        else
                        {
                            if (color(siblingnd->right) == 0)
                            {
                                siblingnd->left->color = 0;
                                siblingnd->color = 1;
                                rightRotate(root,siblingnd);
                                siblingnd = parentnd->right;
                            }
                            siblingnd->color = parentnd->color;
                            parentnd->color = 0;
                            siblingnd->right->color = 0;
                            leftRotate(root,parentnd);
                            break;
                        }
                    }
                }
                else
                {
                    siblingnd = parentnd->left;
                    if(color(siblingnd) == 1)
                    {
                        siblingnd->color = 0;
                        parentnd->color = 1;
                        rightRotate(root,parentnd);
                    }
                    else
                    {
                        if((color(siblingnd->left) == 0) && (color(siblingnd->right) == 0))
                        {
                            siblingnd->color = 1;
                            if(color(parentnd) == 1)
                            parentnd->color = 0;
                            else
                            parentnd->color = 2;
                            p = parentnd;
                        }
                        else
                        {
                            if (color(siblingnd->left) == 0)
                            {
                                siblingnd->right->color = 0;
                                siblingnd->color = 1;
                                leftRotate(root,siblingnd);
                                siblingnd = parentnd->left;
                            }
                            siblingnd->color = parentnd->color;
                            parentnd->color = 0;
                            siblingnd->left->color = 0;
                            rightRotate(root,parentnd);
                            break;
                        }
                    }
                }
            }

        if (nd == nd->parent->left)
            nd->parent->left = nullptr;
        else
            nd->parent->right = nullptr;

        delete nd;
        num--;
        root->color = 0;
        }

    }

    public:
        RedBlack(): num(0), root(nullptr){};
        ~RedBlack()
        {

        }

        bool findElem(const T& x) const
        {
            rbnode* curr = root;
            while(curr != nullptr)
            {
                if(curr->data == x)
                return true;
                else if(curr->data < x)
                curr = curr->right;
                else
                curr = curr->left;
            }
            return false;
        }

        void addElem(const T& x)
        {
            rbnode* nd = new rbnode(x);
            root = add(root,nd);
            fixAddViolation(root,nd);
        }

        void deleteElem(const T& x)
        {
            rbnode* nd = removee(root,x);
            fixDeleteViolation(root,nd);
        }

        void deleteFromTo(const T& x1, const T& x2)
        {
            arr.clearr();
            int i=0;
            rbnode *curr = root,*pre;
            while(curr != nullptr)
            {
                if(curr->left == nullptr)
                {
                    arr[i++] = curr->data;
                    curr = curr->right;
                }
                else
                {
                    pre = curr->left;
                    while(pre->right != NULL && pre->right != curr)
                    pre = pre->right;
                    if(pre->right == NULL)
                    {
                        pre->right = curr;
                        curr = curr->left;
                    }
                    else
                    {
                        pre->right = NULL;
                        arr[i++] = curr->data;
                        curr = curr->right;
                    }
                }
            }
            int n1=0;
            for(i=0;i<num;i++)
            {
                if(arr[i] < x1 || arr[i] > x2)
                {
                    arr[n1++] = arr[i];
                    //cout<<"arr "<<arr[i]<<endl;
                }
            }
            num = n1;
            if(num == 0)
            root = nullptr;
            else
            root = workplease(arr,n1);
        }

        rbnode* workplease(Vector<T>& arr, int n1)
        {

        rbnode* head = new rbnode(arr[0]);

            nodeStack.push(head);
            leftStack.push(0);
            rightStack.push(n1-1);

            while(!nodeStack.emptyStack())
            {
                rbnode* curr = nodeStack.top();
                nodeStack.pop();
                int left = leftStack.top();
                leftStack.pop();
                int right = rightStack.top();
                rightStack.pop();
                int mid = left + (right - left)/2;
                curr->data = arr[mid];

                if ( left <= mid-1 )
                {
                    curr->left = new rbnode(0);
                    nodeStack.push(curr->left);
                    leftStack.push(left);
                    rightStack.push(mid-1);
                }
                if ( mid+1 <= right )
                {
                curr->right = new rbnode(0);
                nodeStack.push(curr->right);
                leftStack.push(mid+1);
                rightStack.push(right);
                }
            }
            return head;
        }

        int getNumOfElements() const
        {
            return num;
        }

        void inorder(rbnode* nd) const
        {
            if (nd == nullptr)
			return;
            inorder(nd->left);
            cout << nd->data << " ";
            inorder(nd->right);
        }

        void preorder(rbnode* nd) const
        {
            if(nd == nullptr) return;
            cout<<nd->data<<" ";
            preorder(nd->left);
            preorder(nd->right);
        }

        rbnode* union2(const RedBlack& t)
        {
            arr1.clearr();
            arr2.clearr();
            rbnode *curr = root,*pre;
            while(curr != nullptr)
            {
                if(curr->left == nullptr)
                {
                    arr1.push_backk(curr->data);
                    curr = curr->right;
                }
                else
                {
                    pre = curr->left;
                    while(pre->right != NULL && pre->right != curr)
                    pre = pre->right;
                    if(pre->right == nullptr)
                    {
                        pre->right = curr;
                        curr = curr->left;
                    }
                    else
                    {
                        pre->right = nullptr;
                        arr1.push_backk(curr->data);
                        curr = curr->right;
                    }
                }
            }

            rbnode *curr2 = t.root,*pre2;
            while(curr2 != nullptr)
            {
                if(curr2->left == nullptr)
                {
                    arr2.push_backk(curr2->data);
                    curr2 = curr2->right;
                }
                else
                {
                    pre2 = curr2->left;
                    while(pre2->right != NULL && pre2->right != curr2)
                    pre2 = pre2->right;
                    if(pre2->right == nullptr)
                    {
                        pre2->right = curr2;
                        curr2 = curr2->left;
                    }
                    else
                    {
                        pre2->right = nullptr;
                        arr2.push_backk(curr2->data);
                        curr2 = curr2->right;
                    }
                }
            }
            arr.clearr();
            int i=0;
            int j=0;
            while(i < num && j < t.num)
            {
                if(arr1[i] == arr2[j])
                {
                    arr.push_backk(arr1[i]);
                    i++;
                    j++;
                }
                else if(arr1[i] < arr2[j])
                {
                    arr.push_backk(arr1[i]);
                    i++;
                }
                else
                {
                    arr.push_backk(arr2[j]);
                    j++;
                }
            }

            while(i < num)
            {
                arr.push_backk(arr1[i]);
                    i++;
            }

            while(j < t.num)
            {
                arr.push_backk(arr2[j]);
                    j++;
            }
            num = arr.sizee() - 1;
            if(num == 0)
            return nullptr;
            return workplease(arr,arr.sizee());
        }

        RedBlack<T> union22(const RedBlack<T>& a)
        {
            RedBlack<T> nw;
            nw.root = this->union2(a);
            nw.num = num + a.num;
            return nw;
        }

        rbnode* getRoot() const
        {
            return root;
        }
};

#endif // REDBLACK_H
