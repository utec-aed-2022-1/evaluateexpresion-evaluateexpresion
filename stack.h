#include "circular.h"
#include <iostream>
using namespace std;

template <typename T>
class StackArray : public CircularArray<T> {


public:
    StackArray(int _capacity);
    virtual ~StackArray();
    void display();
    void push(T data);
    bool is_empty();
    T pop();
    T top();



};

template <typename T>
StackArray<T>::StackArray(int _capacity):CircularArray<T>(_capacity){}
template <typename T>
StackArray<T>::~StackArray(){
    CircularArray<T>::clear();
}


template <typename T>
void StackArray<T>::display()
{

    CircularArray<T>::to_string();
}
template <typename T>
void StackArray<T>::push(T data)
{

    CircularArray<T>::push_front(data);
}
template <typename T>
T StackArray<T>::pop()
{

    return CircularArray<T>::pop_front();
}
template <typename T>
T StackArray<T>::top()
{

    return CircularArray<T>::top();
}

template <typename T>
bool StackArray<T>::is_empty()
{

    return CircularArray<T>::is_empty();
}

