#include <iostream>
#include <string>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;

public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T top();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    T getmax();
    void resize(int factor = 2);
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};



template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
T CircularArray<T>::top()
{

   return array[front];

}

template <class T>
T CircularArray<T>::pop_front()
{
    if(is_empty())
        return 0;

    T result = array[front];
    if(front== capacity-1){

        front=0;
    }
    else if(size() == 1){
        front = -1;
        back = -1;
    }
    else {
        front++;
    }
    return result;
}

template <class T>
T CircularArray<T>::pop_back()
{
    if(is_empty())
        return 0;

    T result = array[back];
    if(back==0){
        back=capacity-1;
    }
    else if(size() == 1){
        back = -1;
        front = -1;
    }
    else {
        back--;
    }
    return result;

}


template <class T>
void CircularArray<T>::push_front(T data)
{
    if (is_empty()){
        front = 0;
        back = 0;
        array[0] = data;
    }
    else if(size()==capacity){
        resize();
        push_front(data);
    }
    else{
        if(front==0){
            array[capacity-1]= data;
            front=capacity-1;
        }
        else{
            array[front -1]= data;
            front--;
        }
    }
}

template <class T>
void CircularArray<T>::push_back(T data)
{
    if (is_empty()){
        front = 0;
        back = 0;
        array[0] = data;
    }else if(size() == capacity){
        resize();
        push_back(data);
    }
    else{
        if(back==capacity-1 ){
            array[0]= data;
            back=0;
        }
        else{
            array[back +1]= data;
            back++;
        }
    }
}

template <class T>
bool CircularArray<T>::is_full()
{
    if (size()== capacity){

        return true;
    }
    return false;
}

template <class T>
bool CircularArray<T>::is_empty()
{
    if (size() == 0){

        return true;
    }
    return false;
}

template <class T>
int CircularArray<T>::size()
{

    if( front == -1 && back == -1)
        return 0;

    int size;
    if (back < front ){


        if (back +1 == front){
            size = capacity;

        }
        else {
            size = capacity - (front - back - 1);

        }
    }

    else if(back == front){
        size = 1;

    }

    else{
        size = back - front +1;

    }

    return size;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = "";
    for (int i = 0; i < size(); i++) {
        result += std::to_string((*this)[i]) + sep;
    }
    //cout<<result<<endl;
    return result;
}

template<class T>
void CircularArray<T>::resize(int factor) {
    if(capacity == 0){
        capacity = 1;
        delete[] array;
        array = new T[capacity];
        return ;
    }

    if(factor < 1)
        factor = 1;

    int newcap = capacity * factor;
    T* newarr = new T[newcap];
    int it = front;
    for(int i = 0; i < capacity; i++){
        newarr[i] = array[it];
        it = next(it);
    }
    delete[] array;
    array = newarr;
    capacity = newcap;
    front = 0;
    back = capacity - 1;
}

template<class T>
void CircularArray<T>::insert(T data, int pos) {
    if(pos >= size() || pos < 0)
        return;
    if(pos == 0)
        push_front(data);
    if(pos == size()-1)
        push_back(data);

    int it = front;
    it = (front + pos)%capacity;
    T* arr = new T[capacity];
    int j = 0;
    for(int i = pos; i <= back; i++){
        arr[j] = array[i];
        j++;
    }
    back = prev(pos);
    push_back(data);
    for(int i = 0; i < j; i++){
        push_back(arr[i]);
    }

}

template<class T>
void CircularArray<T>::clear() {
    front = -1;
    back = -1;
    delete[] array;
}

template<class T>
T &CircularArray<T>::operator[](int index) {
    int it = front;
    it = (front + index)%capacity;
    return array[it];
}

template<class T>
void CircularArray<T>::sort() {
    T* sorted = new T[capacity];
    int max = getmax() + 1;
    int* count = new int[max];

    for(int i = 0 ; i < max; i++)
        count[i] = 0;

    int it = front;
    for(int i = 0; i < size(); i++) {
        count[array[it]]++;
        it = next(it);
    }

    for(int i = 1; i < max; i++)
        count[i] += count[i-1];

    for(int i = 0; i < max; i++) {
        int prepos;
        if(i == 0)
            prepos = 0;
        else
            prepos = count[i-1];
        for(int j = prepos; j < count[i]; j++){
            sorted[j] = i;
        }
    }

    it = front;
    for(int i = 0; i< size(); i++) {
        array[it] = sorted[i];
        it = next(it);
    }
    delete[] sorted;
    delete[] count;
}

template<class T>
bool CircularArray<T>::is_sorted() {
    T temp = array[front];
    int it = front;
    for(int i = 0; i < size(); i++){
        if( temp > array[it] )
            return false;

        temp = array[it];
        it = next(it);

    }
    return true;
}

template<class T>
void CircularArray<T>::reverse() {
    int temsize = size();
    if(size()%2 != 0)
        temsize = size() - 1;

    temsize = temsize / 2;

    int it = front;
    int negait = back;
    for( int i = 0; i < temsize; i++){
        T temp = array[it];
        array[it] = array[negait];
        array[negait] = temp;
        it = next(it);
        negait = prev(negait);
    }
}

template<class T>
T CircularArray<T>::getmax() {
    T max = array[0];
    for(int i = 0; i < size(); i++) {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}