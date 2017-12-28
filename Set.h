#ifndef SET_H
#define SET_H
#include <iostream>

using namespace std;

template<class T>
class Set
{
    public:
        int implementation;
        virtual ~Set() {};
        virtual bool findElem(const T&) const = 0;
        virtual void addElem(const T&) = 0;
        virtual void deleteElem(const T&) = 0;
        virtual void deleteFromTo(const T&,const T&) = 0;
        virtual int getNumOfElements() const = 0;
        virtual void print() const = 0;
        virtual Set<T>* union2(Set<T>*) = 0;
};

#endif // SET_H
