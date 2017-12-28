#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "Stack.h"
#include "Vector.h"

using namespace std;

template<class T>
class AVL
{
	struct AvlNode
	{
		T data;
		int height;
		AvlNode* left;
		AvlNode* right;
		AvlNode(const T& x) : data(x), height(1), left(nullptr), right(nullptr) {};
	};

	AvlNode* root;
	int num;
	Vector<T> arr,arr1,arr2;
	Stack<AvlNode*> nodeStack;
    Stack<int> leftStack;
    Stack<int> rightStack;

	int getBalance(AvlNode* nd)
	{
		if (nd == nullptr)
		return 0;
		return height(nd->left) - height(nd->right);
	}

	AvlNode* leftRotate(AvlNode* nd)
	{
		AvlNode* help1 = nd->right;
		AvlNode* help2 = help1->left;
		help1->left = nd;
		nd->right = help2;
		nd->height = max(height(nd->left),height(nd->right)) + 1;
		help1->height = max(height(help1->left),height(help1->right)) + 1;
		return help1;
	}

	AvlNode* rightRotate(AvlNode* nd)
	{
		AvlNode* help1 = nd->left;
		AvlNode* help2 = help1->right;
		help1->right = nd;
		nd->left = help2;
		nd->height = max(height(nd->right), height(nd->left)) + 1;
		help1->height = max(height(help1->right), height(help1->left)) + 1;
		return help1;
	}

	AvlNode* leftRightRotate(AvlNode* nd)
	{
		nd->left = leftRotate(nd->left);
		return rightRotate(nd);
	}

	AvlNode* rightLeftRotate(AvlNode* nd)
	{
		nd->right = rightRotate(nd->right);
		return leftRotate(nd);
	}

	AvlNode* findMin(AvlNode* nd)
	{
		if (nd == nullptr)
			return nullptr;
		else if (nd->left == nullptr)
			return nd;
		else
			return findMin(nd->left);
	}

	AvlNode* findMax(AvlNode* nd)
	{
		if (nd == nullptr)
			return nullptr;
		else if (nd->right == nullptr)
			return nd;
		else
			return findMax(nd->right);
	}

	int height(AvlNode* nd)
	{
        if(nd == nullptr) return 0;
        return nd->height;
	}

public:
	AVL() : num(0), root(nullptr) {};
	~AVL()
	{

	}
	AvlNode* getRoot() const
	{
		return root;
	}
	bool findElem(const T& x) const
	{
		AvlNode* curr = root;

		while (curr != nullptr)
		{
			if (curr->data == x)
			return true;
			else if (curr->data < x)
			curr = curr->right;
			else
			curr = curr->left;
		}
		return false;
	}

	AvlNode* addElem(AvlNode* nd,const T& x)
	{
		if (nd == nullptr)
		{
			num++;
			AvlNode* tmp = new AvlNode(x);
			return tmp;
		}

		if (x < nd->data)
		{
			nd->left = addElem(nd->left, x);
		}
		else if (x > nd->data)
		{
			nd->right = addElem(nd->right, x);
		}
		else
		{
			cout << "Already have that number" << endl;
			return nd;
		}

		nd->height = 1 + max(height(nd->left),height(nd->right));

		int balance = getBalance(nd);

		if (balance > 1 && x < nd->left->data)
			return rightRotate(nd);

		if (balance < -1 && x > nd->right->data)
			return leftRotate(nd);

		if (balance > 1 && x > nd->left->data)
		{
			return leftRightRotate(nd);
		}

		if (balance < -1 && x < nd->right->data)
		{
			return rightLeftRotate(nd);
		}

		return nd;
	}

	void addEleme(const T& x)
	{
		root = addElem(root, x);
	}

	AvlNode* deleteElem(AvlNode* nd, const T& x)
	{

		if (nd == nullptr)
			return nd;

		if (x < nd->data)
		{
			nd->left = deleteElem(nd->left, x);
		}
		else if (x > nd->data)
		{
			nd->right = deleteElem(nd->right, x);
		}
		else
		{
			if ((nd->left == nullptr) || (nd->right == nullptr))
			{
				AvlNode* temp = nd->left ? nd->left : nd->right;

				if (temp == nullptr)
				{
					temp = nd;
					nd = nullptr;
				}
				else
				{
					nd->data = temp->data;
					nd->height = temp->height;
					nd->left = temp->left;
					nd->right = temp->right;
				}
				num--;
				delete temp;
			}
			else
			{
				AvlNode* temp = findMin(nd->right);
				nd->data = temp->data;
				nd->right = deleteElem(nd->right, temp->data);
			}
		}

		if (nd == nullptr) return nd;

		nd->height = 1 + max(height(nd->left),height(nd->right));

		int balance = getBalance(nd);

		if (balance > 1 && x < nd->left->data)
			return rightRotate(nd);

		if (balance < -1 && x > nd->right->data)
			return leftRotate(nd);

		if (balance > 1 && x > nd->left->data)
		{
			return leftRightRotate(nd);
		}

		if (balance < -1 && x < nd->right->data)
		{
			return rightLeftRotate(nd);
		}

		return nd;
	}

    void deleteEleme(const T& x)
    {
        root = deleteElem(root, x);
    }

	int getNumElem() const
	{
		return num;
	}

	void inorder(AvlNode* nd) const
	{
		if (nd == nullptr)
			return;
		inorder(nd->left);
		cout << nd->data << " ";
		inorder(nd->right);
	}

	void preorder(AvlNode* nd) const
	{
        if(nd == nullptr) return;
        cout<<nd->data<<" ";
        preorder(nd->left);
        preorder(nd->right);
	}

    void deleteFromTo(const T& x1, const T& x2)
        {
            arr.clearr();
            int i=0;
            AvlNode *curr = root,*pre;
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

        AvlNode* workplease(Vector<T>& arr, int n1)
        {

        AvlNode* head = new AvlNode(arr[0]);

            nodeStack.push(head);
            leftStack.push(0);
            rightStack.push(n1-1);

            while(!nodeStack.emptyStack())
            {
                AvlNode* curr = nodeStack.top();
                nodeStack.pop();
                int left = leftStack.top();
                leftStack.pop();
                int right = rightStack.top();
                rightStack.pop();
                int mid = left + (right - left)/2;
                curr->data = arr[mid];

                if ( left <= mid-1 )
                {
                    curr->left = new AvlNode(0);
                    nodeStack.push(curr->left);
                    leftStack.push(left);
                    rightStack.push(mid-1);
                }
                if ( mid+1 <= right )
                {
                curr->right = new AvlNode(0);
                nodeStack.push(curr->right);
                leftStack.push(mid+1);
                rightStack.push(right);
                }
            }
            return head;
        }

        AvlNode* union2(const AVL& t)
        {
            arr1.clearr();
            arr2.clearr();
            AvlNode *curr = root,*pre;
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

            AvlNode *curr2 = t.root,*pre2;
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

        AVL<T> union22(const AVL<T>& a)
        {
            AVL<T> nw;
            nw.root = this->union2(a);
            nw.num = num + a.num;
            return nw;
        }
};

#endif // AVL_H
