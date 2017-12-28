#include <iostream>
#include "Stack.h"
#include "SetList.h"
#include "Set.h"
#include "BST.h"
#include "SetBST.h"
#include "AVL.h"
#include "SetAVL.h"
#include "SetRedBlack.h"
//#include <bits/stdc++.h>
#include "PerformanceCalculator.h"
#include <fstream>
#include <random>
#include<cstdio>
#include<string>
#include<iomanip>


using namespace std;

/*int sizes[6] = { 200,500,1000,10000,100000,1000000 };
int main()
{
	PerformanceCalculator pc;
	std::default_random_engine rng;
    std::uniform_int_distribution<int> dist(0, 2000000000);
	double times[6][7];
	int keys[2000005];
	for(int i=0;i<2000000;i++)
	keys[i] = dist(rng);

	for (int i = 0; i < 6 ; i++)
	{
        SetBST<int> x;
        SetBST<int> y;
        int l=0;
        pc.start();
		while(x.getNumOfElements() < sizes[i])
			x.addElem(keys[l++]);
		pc.stop();
		times[i][0] = pc.elapsedMillis();

		while(y.getNumOfElements() < sizes[i])
			y.addElem(keys[l++]);

		pc.start();
		x.addElem(keys[l++]);
		pc.stop();
		times[i][1] = pc.elapsedMillis();

		pc.start();
		x.deleteElem(keys[l++]);
		pc.stop();
		times[i][2] = pc.elapsedMillis();

		pc.start();
		x.findElem(keys[l++]);
		pc.stop();
		times[i][3] = pc.elapsedMillis();

		pc.start();
		(&x)->union2(&y);
		pc.stop();
		times[i][4] = pc.elapsedMillis();

	}
	cout << fixed << showpoint;
	cout << setprecision(4);
	cout << setw(10)<< "BST" << setw(10) << "200" << setw(10) << "500" << setw(10) << "1000" << setw(10) << "10000" << setw(10) << "100000" << setw(10) << "1000000\n";
	cout << setw(10)<< "creating" << setw(10) << times[0][0] << setw(10) << times[1][0] << setw(10) << times[2][0] << setw(10) << times[3][0] << setw(10) << times[4][0] << setw(10) << times[5][0] << "\n";
	cout << setw(10) << "add" << setw(10) << times[0][1] << setw(10) << times[1][1] << setw(10) << times[2][1] << setw(10) << times[3][1] << setw(10) << times[4][1] << setw(10) << times[5][1] << "\n";
	cout << setw(10) << "delete" << setw(10) << times[0][2] << setw(10) << times[1][2] << setw(10) << times[2][2] << setw(10) << times[3][2] << setw(10) << times[4][2] << setw(10) << times[5][2] << "\n";
	cout << setw(10) << "search" << setw(10) << times[0][3] << setw(10) << times[1][3] << setw(10) << times[2][3] << setw(10) << times[3][3] << setw(10) << times[4][3] << setw(10) << times[5][3] << "\n";
	cout << setw(10) << "union" << setw(10) << times[0][4] << setw(10) << times[1][4] << setw(10) << times[2][4] << setw(10) << times[3][4] << setw(10) << times[4][4] << setw(10) << times[5][4] << "\n";
	cout << "\n\n\n";

		for (int i = 0; i < 6 ; i++)
	{
        SetAVL<int> x;
        SetAVL<int> y;
        int l=0;
        pc.start();
		while(x.getNumOfElements() < sizes[i])
			x.addElem(keys[l++]);
		pc.stop();
		times[i][0] = pc.elapsedMillis();

		while(y.getNumOfElements() < sizes[i])
			y.addElem(keys[l++]);

		pc.start();
		x.addElem(keys[l++]);
		pc.stop();
		times[i][1] = pc.elapsedMillis();

		pc.start();
		x.deleteElem(keys[l++]);
		pc.stop();
		times[i][2] = pc.elapsedMillis();

		pc.start();
		x.findElem(keys[l++]);
		pc.stop();
		times[i][3] = pc.elapsedMillis();

		pc.start();
		(&x)->union2(&y);
		pc.stop();
		times[i][4] = pc.elapsedMillis();

	}
	cout << fixed << showpoint;
	cout << setprecision(4);
	cout << setw(10)<< "AVL" << setw(10) << "200" << setw(10) << "500" << setw(10) << "1000" << setw(10) << "10000" << setw(10) << "100000" << setw(10) << "1000000\n";
	cout << setw(10)<< "creating" << setw(10) << times[0][0] << setw(10) << times[1][0] << setw(10) << times[2][0] << setw(10) << times[3][0] << setw(10) << times[4][0] << setw(10) << times[5][0] << "\n";
	cout << setw(10) << "add" << setw(10) << times[0][1] << setw(10) << times[1][1] << setw(10) << times[2][1] << setw(10) << times[3][1] << setw(10) << times[4][1] << setw(10) << times[5][1] << "\n";
	cout << setw(10) << "delete" << setw(10) << times[0][2] << setw(10) << times[1][2] << setw(10) << times[2][2] << setw(10) << times[3][2] << setw(10) << times[4][2] << setw(10) << times[5][2] << "\n";
	cout << setw(10) << "search" << setw(10) << times[0][3] << setw(10) << times[1][3] << setw(10) << times[2][3] << setw(10) << times[3][3] << setw(10) << times[4][3] << setw(10) << times[5][3] << "\n";
	cout << setw(10) << "union" << setw(10) << times[0][4] << setw(10) << times[1][4] << setw(10) << times[2][4] << setw(10) << times[3][4] << setw(10) << times[4][4] << setw(10) << times[5][4] << "\n";
	cout << "\n\n\n";

		for (int i = 0; i < 6 ; i++)
	{
        SetRedBlack<int> x;
        SetRedBlack<int> y;
        int l=0;
        pc.start();
		while(x.getNumOfElements() < sizes[i])
			x.addElem(keys[l++]);
		pc.stop();
		times[i][0] = pc.elapsedMillis();

		while(y.getNumOfElements() < sizes[i])
			y.addElem(keys[l++]);

		pc.start();
		x.addElem(keys[l++]);
		pc.stop();
		times[i][1] = pc.elapsedMillis();

		pc.start();
		x.deleteElem(keys[l++]);
		pc.stop();
		times[i][2] = pc.elapsedMillis();

		pc.start();
		x.findElem(keys[l++]);
		pc.stop();
		times[i][3] = pc.elapsedMillis();

		pc.start();
		(&x)->union2(&y);
		pc.stop();
		times[i][4] = pc.elapsedMillis();

	}
	cout << fixed << showpoint;
	cout << setprecision(4);
	cout << setw(10)<< "RED-BLACK" << setw(10) << "200" << setw(10) << "500" << setw(10) << "1000" << setw(10) << "10000" << setw(10) << "100000" << setw(10) << "1000000\n";
	cout << setw(10)<< "creating" << setw(10) << times[0][0] << setw(10) << times[1][0] << setw(10) << times[2][0] << setw(10) << times[3][0] << setw(10) << times[4][0] << setw(10) << times[5][0] << "\n";
	cout << setw(10) << "add" << setw(10) << times[0][1] << setw(10) << times[1][1] << setw(10) << times[2][1] << setw(10) << times[3][1] << setw(10) << times[4][1] << setw(10) << times[5][1] << "\n";
	cout << setw(10) << "delete" << setw(10) << times[0][2] << setw(10) << times[1][2] << setw(10) << times[2][2] << setw(10) << times[3][2] << setw(10) << times[4][2] << setw(10) << times[5][2] << "\n";
	cout << setw(10) << "search" << setw(10) << times[0][3] << setw(10) << times[1][3] << setw(10) << times[2][3] << setw(10) << times[3][3] << setw(10) << times[4][3] << setw(10) << times[5][3] << "\n";
	cout << setw(10) << "union" << setw(10) << times[0][4] << setw(10) << times[1][4] << setw(10) << times[2][4] << setw(10) << times[3][4] << setw(10) << times[4][4] << setw(10) << times[5][4] << "\n";
	cout << "\n\n\n";


		for (int i = 0; i < 6 ; i++)
	{
        SetList<int> x;
        SetList<int> y;
        int l=0;
        pc.start();
		while(x.getNumOfElements() < sizes[i])
			x.addElem(keys[l++]);
		pc.stop();
		times[i][0] = pc.elapsedMillis();

		while(y.getNumOfElements() < sizes[i])
			y.addElem(keys[l++]);

		pc.start();
		x.addElem(keys[l++]);
		pc.stop();
		times[i][1] = pc.elapsedMillis();

		pc.start();
		x.deleteElem(keys[l++]);
		pc.stop();
		times[i][2] = pc.elapsedMillis();

		pc.start();
		x.findElem(keys[l++]);
		pc.stop();
		times[i][3] = pc.elapsedMillis();

		pc.start();
		(&x)->union2(&y);
		pc.stop();
		times[i][4] = pc.elapsedMillis();

	}
	cout << fixed << showpoint;
	cout << setprecision(4);
	cout << setw(10)<< "LIST" << setw(10) << "200" << setw(10) << "500" << setw(10) << "1000" << setw(10) << "10000" << setw(10) << "100000" << setw(10) << "1000000\n";
	cout << setw(10)<< "creating" << setw(10) << times[0][0] << setw(10) << times[1][0] << setw(10) << times[2][0] << setw(10) << times[3][0] << setw(10) << times[4][0] << setw(10) << times[5][0] << "\n";
	cout << setw(10) << "add" << setw(10) << times[0][1] << setw(10) << times[1][1] << setw(10) << times[2][1] << setw(10) << times[3][1] << setw(10) << times[4][1] << setw(10) << times[5][1] << "\n";
	cout << setw(10) << "delete" << setw(10) << times[0][2] << setw(10) << times[1][2] << setw(10) << times[2][2] << setw(10) << times[3][2] << setw(10) << times[4][2] << setw(10) << times[5][2] << "\n";
	cout << setw(10) << "search" << setw(10) << times[0][3] << setw(10) << times[1][3] << setw(10) << times[2][3] << setw(10) << times[3][3] << setw(10) << times[4][3] << setw(10) << times[5][3] << "\n";
	cout << setw(10) << "union" << setw(10) << times[0][4] << setw(10) << times[1][4] << setw(10) << times[2][4] << setw(10) << times[3][4] << setw(10) << times[4][4] << setw(10) << times[5][4] << "\n";
	cout << "\n\n\n";

    //system("pause");
    return 0;
}*/

int main()
{
    int n;
    cout<<"How many sets do you want at the beginning?\n";
    cin>>n;
    Vector<Set<int>*> s;
    for(int i=0;i<n;i++)
    {
        cout<<"Add elements to set number "<<i+1<<endl;
        int impl;
        cout<<"Which implementation of set do you want to use? \n 1. List \n 2. BST \n 3. AVL \n 4. RedBlack \n";
        cin>>impl;

        if(impl == 1)
        {
            s.push_backk(new SetList<int>);
        }
        else if(impl == 2)
        {
            s.push_backk(new SetBST<int>);
        }
        else if(impl == 3)
        {
            s.push_backk(new SetAVL<int>);
        }
        else if(impl == 4)
        {
            s.push_backk(new SetRedBlack<int>);
        }

        int p;
        cout<<"Number of elements you want to add?"<<endl;
        cin>>p;
        cout<<"Elements:\n";
        for(int j=0;j<p;j++)
        {
            int br;
            cin>>br;
            s[i]->addElem(br);
        }
        s[i]->print();
    }
    int fm;
    while(1)
    {

        cout<<"Read from: \n 1. File \n 2. Menu \n";
        cin>>fm;
        int opt;
        if(fm == 2)
        {
            cout<<"Choose an operation \n 1. Add a set \n 2. Search for an element \n 3. Add an element \n 4. Delete an element \n 5. Delete elements in range \n 6. Get numer of elements in set \n 7. Union of 2 sets \n 8. Print \n 9. End \n";
            cin>>opt;

            if(opt == 9) return 0;

            else if(opt == 1)
            {
                int impl;
                cout<<"Which implementation of set do you want to use? \n 1. List \n 2. BST \n 3. AVL \n 4. RedBlack \n";
                cin>>impl;
                if(impl == 1)
                {
                    s.push_backk(new SetList<int>);
                }
                else if(impl == 2)
                {
                    s.push_backk(new SetBST<int>);
                }
                else if(impl == 3)
                {
                    s.push_backk(new SetAVL<int>);
                }
                else if(impl == 4)
                {
                    s.push_backk(new SetRedBlack<int>);
                }
                int p;
                cout<<"Number of elements you want to add?"<<endl;
                cin>>p;
                cout<<"Elements:\n";
                for(int j=0;j<p;j++)
                {
                    int br;
                    cin>>br;
                    s[s.sizee()-1]->addElem(br);
                }
                n++;
            }
            else if(opt == 2)
            {
                int el,ns;
                cout<<"Input the number we are searching for \n";
                cin>>el;
                cout<<"Input the index of set in which we are searching \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                {
                    if(s[ns]->findElem(el))
                    cout<<el<<" is in the set \n";
                    else cout<<el<<" is not in the set \n";
                }
            }
            else if(opt == 3)
            {
                int el,ns;
                cout<<"Input the number we are adding \n";
                cin>>el;
                cout<<"Input the index of set in which we are adding \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->addElem(el);
            }
            else if(opt == 4)
            {
                int el,ns;
                cout<<"Input the number we are deleting \n";
                cin>>el;
                cout<<"Input the index of set from which we are deleting \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->deleteElem(el);
            }
            else if(opt == 5)
            {
                int l,r,ns;
                cout<<"Input the range we are deleting \n";
                cin>>l>>r;
                cout<<"Input the index of set from which we are deleting \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->deleteFromTo(l,r);
            }
            else if(opt == 6)
            {
                int ns;
                cout<<"Input the index of set we are interested in \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                cout<<s[ns]->getNumOfElements()<<endl;
            }
            else if(opt == 7)
            {
                int opt1,opt2;
                cout<<"Select sets for union \n";
                cin>>opt1>>opt2;
                if(s[opt1]->implementation != s[opt2]->implementation)
                {
                    cout<<"Error! Different implementations!\n";
                }
                else
                {
                    s[opt1]->print();
                    s[opt2]->print();
                    Set<int>* st;
                    st = s[opt1]->union2((s[opt2]));
                    s.push_backk(st);
                    s[s.sizee()-1]->print();
                    n++;
                }
            }
            else if(opt == 8)
            {
                int ns;
                cout<<"Input the index of set you want to print \n";
                cin>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->print();
            }

        }
        else if(fm == 1)
        {
            string str;
            cout<<"Name of the file?"<<endl;
            cin>>str;
            ifstream dat;
            dat.open(str);
            if( ! dat.is_open() )
            {
                cout<<"Error while opening file";
                exit(1);
            }
            dat>>opt;
            cout<<"OPTION "<<opt<<endl;

            if(opt == 9) return 0;

            else if(opt == 1)
            {
                int impl;
                //cout<<"Which implementation of set do you want to use? \n 1. List \n 2. BST \n 3. AVL \n";
                dat>>impl;
                if(impl == 1)
                {
                    s.push_backk(new SetList<int>);
                }
                else if(impl == 2)
                {
                    s.push_backk(new SetBST<int>);
                }
                else if(impl == 3)
                {
                    s.push_backk(new SetAVL<int>);
                }
                else if(impl == 4)
                {
                    s.push_backk(new SetRedBlack<int>);
                }
                int p;
                //cout<<"Number of elements you want to add?"<<endl;
                dat>>p;
                //cout<<"Elements:\n";
                for(int j=0;j<p;j++)
                {
                    int br;
                    dat>>br;
                    s[s.sizee()-1]->addElem(br);
                }
            }
            else if(opt == 2)
            {
                int el,ns;
                //cout<<"Input the number we are searching for \n";
                dat>>el;
                //cout<<"Input the index of set in which we are searching \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                {
                    if(s[ns]->findElem(el))
                    cout<<el<<" is in the set \n";
                    else cout<<el<<" is not in the set \n";
                }
            }
            else if(opt == 3)
            {
                int el,ns;
                //cout<<"Input the number we are adding \n";
                dat>>el;
                //cout<<"Input the index of set in which we are adding \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->addElem(el);
            }
            else if(opt == 4)
            {
                int el,ns;
                //cout<<"Input the number we are deleting \n";
                dat>>el;
                //cout<<"Input the index of set from which we are deleting \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->deleteElem(el);
            }
            else if(opt == 5)
            {
                int l,r,ns;
                //cout<<"Input the range we are deleting \n";
                dat>>l>>r;
                //cout<<"Input the index of set from which we are deleting \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->deleteFromTo(l,r);
            }
            else if(opt == 6)
            {
                int ns;
                //cout<<"Input the index of set we are interested in \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                cout<<s[ns]->getNumOfElements()<<endl;
            }
            else if(opt == 7)
            {
                int opt1,opt2;
                //cout<<"Select sets for union \n";
                dat>>opt1>>opt2;
                if(s[opt1]->implementation != s[opt2]->implementation)
                {
                    cout<<"Error! Different implementations!\n";
                }
                else
                {
                    s[opt1]->print();
                    s[opt2]->print();
                    Set<int>* st;
                    st = s[opt1]->union2((s[opt2]));
                    s.push_backk(st);
                    s[s.sizee()-1]->print();
                    n++;
                }
            }
            else if(opt == 8)
            {
                int ns;
                //cout<<"Input the index of set you want to print \n";
                dat>>ns;
                if(ns >= s.sizee())
                cout<<"Not in the range \n";
                else
                s[ns]->print();
            }
            else if(opt == 9)
            {
                return 0;
            }
            dat.close();
        }


    }
    //system("pause");
    return 0;
}

