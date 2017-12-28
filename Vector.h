#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>

using namespace std;

template<class T>
class Vector {
	T* arr;
	int allocated;
	int busy;
public:
	Vector() {
		arr = (T*)malloc(sizeof(T));
		allocated = 1;
		busy = 0;
	}

	void push_backk(T const& x)
	{
		if (allocated > busy)
			arr[busy++] = x;
		else
		{
            allocated *=2;
			arr = (T*)realloc(arr, allocated * sizeof(T));
			arr[busy++] = x;
		}
	}

	T& operator [](const int& i)
	{
		return arr[i];
	}

	void clearr()
	{
        busy = 0;
	}

	int sizee() const
	{
		return busy;
	}

	bool emptyy() const
	{
		if(busy == 0) return true;
		return false;
	}


};

#endif // VECTOR_H
