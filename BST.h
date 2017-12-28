#ifndef BST_H
#define BST_H
#include <iostream>
#include "Stack.h"
#include "Vector.h"

using namespace std;

template<class T>
class BST
{

    struct treeNode
    {
        T data;
        treeNode* left;
        treeNode* right;
        treeNode(const T& x): data(x),left(nullptr),right(nullptr) {};
    };

    treeNode* root;
    int num;
    Vector<T> arr, arr1,arr2;
    Stack<treeNode*> nodeStack;
    Stack<int> leftStack;
    Stack<int> rightStack;

    public:
        BST(): num(0),root(nullptr) {};
        ~BST() {};

        BST(const BST& bt)
        { }


        bool findElem(const T& x) const
        {
            treeNode* curr = root;
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
            treeNode* parent = nullptr;
            treeNode* nd = new treeNode(x);
            if (root == nullptr)
            {
                root = nd;
                num++;
                return;
            }
            treeNode* curr = root;
            while (curr != nullptr)
            {
                parent = curr;
                if (x == curr->data)
                {
                    cout<<"Already have that element"<<endl;
                    return;
                }
                else if (x < curr->data)
                curr = curr->left;
                else
                curr = curr->right;
            }
            if (x == parent->data)
                {
                    cout<<"Already have that element"<<endl;
                    return;
                }
            if (x < parent->data)
            parent->left = nd;
            else
            parent->right = nd;
            num++;
        }

        void deleteElem(const T& x)
        {
            treeNode* parent = nullptr;
            treeNode* curr = root;
            while (curr != nullptr && curr->data != x)
            {
                parent = curr;
                if (x < curr->data)
                curr = curr->left;
                else
                curr = curr->right;
            }
            if (curr == nullptr)
            {
                cout<<"Node doesn't exist"<<endl;
                return;
            }
            //leaf node
            num--;
            if (curr->left == nullptr && curr->right == nullptr)
            {
                if (curr != root)
                {
                    if (parent->left == curr)
                    parent->left = nullptr;
                    else
                    parent->right = nullptr;
                }
                else
                root = nullptr;
                delete curr;
            }
            //two children
            else if (curr->left && curr->right)
            {

                treeNode* parent_replacement = curr;
                treeNode* replacement =  curr->left;
                bool is_left = true;
                while(replacement->right != NULL)
                {
                    parent_replacement = replacement;
                    replacement = replacement->right;
                    is_left = false;
                }
                curr->data = replacement->data;
                if (is_left)
                {
                    curr->left = replacement->left;
                    delete replacement;
                }
                else
                {
                    parent_replacement->right = replacement->left;
                    delete replacement;
                }
            }
            //one child
            else
            {
                treeNode* child = (curr->left)? curr->left: curr->right;
                if (curr != root)
                {
                    if (curr == parent->left)
                    parent->left = child;
                    else
                    parent->right = child;
                }
                else
                root = child;
                delete curr;
            }
        }

        void inorder() const
        {
            if(root == nullptr)
            {
                cout<<"Empty set"<<endl;
                return;
            }

            treeNode *curr = root,*pre;
            while(curr != nullptr)
            {
                if(curr->left == nullptr)
                {
                    cout<<curr->data<<" ";
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
                        cout<<curr->data<<" ";
                        curr = curr->right;
                    }
                }
            }
            cout<<endl;
        }

        void deleteFromTo(const T& x1, const T& x2)
        {
            arr.clearr();
            int i=0;
            treeNode *curr = root,*pre;
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

        treeNode* workplease(Vector<T> &arr, int n1)
        {
            treeNode* head = new treeNode(arr[0]);

            nodeStack.push(head);
            leftStack.push(0);
            rightStack.push(n1-1);

            while(!nodeStack.emptyStack())
            {
                treeNode* curr = nodeStack.top();
                nodeStack.pop();
                int left = leftStack.top();
                leftStack.pop();
                int right = rightStack.top();
                rightStack.pop();
                int mid = left + (right - left)/2;
                curr->data = arr[mid];

                if ( left <= mid-1 )
                {
                    curr->left = new treeNode(0);
                    nodeStack.push(curr->left);
                    leftStack.push(left);
                    rightStack.push(mid-1);
                }
                if ( mid+1 <= right )
                {
                curr->right = new treeNode(0);
                nodeStack.push(curr->right);
                leftStack.push(mid+1);
                rightStack.push(right);
                }
            }
            return head;
        }

        treeNode* union2(const BST& t)
        {
            arr1.clearr();
            arr2.clearr();
            treeNode *curr = root,*pre;
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

            treeNode *curr2 = t.root,*pre2;
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

        BST<T> union22(const BST<T>& bt)
        {
            BST<T> nw;
            nw.root = this->union2(bt);
            nw.num = num + bt.num;
            return nw;
        }

        int getNumElem() const
        {
            return num;
        }
};

#endif // BST_H
