#include <iostream>

template <class T>
class MyVector
{
private:
    T *_data;
    int _length;
    int _capacity;

public:
    MyVector();
    MyVector(const MyVector<T> &other);
    MyVector(T *array, int length);
    ~MyVector();
    void operator=(const MyVector<T> &other);
    bool operator==(const MyVector<T> &other);
    bool operator!=(const MyVector<T> &other);
    bool empty();
    int size();
    int length();
    int capacity();
    T at(int index);
    T operator[](int index);
    T front();
    T back();
    void clear();
    void push_back(T element);
    void pop_back();
    void reserve(int count);
    void shrink();
    void insert(int index, T element, int count = 1);
    void insert(int index, T* array, int length);
    void insert(int index, const MyVector<T> &vector);
    void erase(int index, int count = 1);
};
template <class T>
MyVector<T>::MyVector() : _data(new T[1]), _length(0), _capacity(1) {}
template <class T>
MyVector<T>::MyVector(const MyVector<T> &other) : _length(other._length), _capacity(other._capacity)
{
    _data = new T[_capacity];
    for (int i = 0; i < _length; i++)
    {
        _data[i] = other._data[i];
    }
}
template <class T>
MyVector<T>::MyVector(T *array, int length) : _length(length)
{
    _capacity = 1;
    while (_capacity < _length)
    {
        _capacity *= 2;
    }
    _data = new T[_capacity];
    for (int i = 0; i < length; i++)
    {
        _data[i] = array[i];
    }
}
template <class T>
MyVector<T>::~MyVector()
{
    delete[] _data;
}
template <class T>
void MyVector<T>::operator=(const MyVector<T> &other)
{
    _length = other._length;
    _capacity = other._capacity;
    delete[] _data;
    _data = new T[_capacity];
    for (int i = 0; i < _length; i++)
    {
        _data[i] = other._data[i];
    }
}
template <class T>
bool MyVector<T>::operator==(const MyVector<T> &other)
{
    if (_length != other._length)
    {
        return false;
    }
    for (int i = 0; i < _length; ++i)
    {
        if (_data[i] != other._data[i])
        {
            return false;
        }
    }
    return true;
}
template <class T>
bool MyVector<T>::operator!=(const MyVector<T> &other)
{
    return !(*this == other);
}
template <class T>
bool MyVector<T>::empty()
{
    return _length == 0;
}
template <class T>
int MyVector<T>::size()
{
    return _length;
}
template <class T>
int MyVector<T>::length()
{
    return _length;
}
template <class T>
int MyVector<T>::capacity()
{
    return _capacity;
}
template <class T>
T MyVector<T>::at(int index)
{
    if (index < 0 || index >= _length)
    {
        throw "out of range";
    }
    else
    {
        return _data[index];
    }
}
template <class T>
T MyVector<T>::operator[](int index)
{
    return _data[index];
}
template <class T>
T MyVector<T>::front()
{
    return _data[0];
}
template <class T>
T MyVector<T>::back()
{
    return _data[_length - 1];
}
template <class T>
void MyVector<T>::clear()
{
    delete[] _data;
    _length = 0;
    _capacity = 1;
    _data = new T[1];
}
template <class T>
void MyVector<T>::push_back(T element)
{
    if (_length + 1 > _capacity)
    {
        _capacity *= 2;
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        data[_length] = element;
        delete[] _data;
        _data = data;
    }
    else
    {
        _data[_length] = element;
    }
    _length++;
}
template <class T>
void MyVector<T>::pop_back()
{
    _length--;
    if (_length <= _capacity / 2)
    {
        _capacity /= 2;
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::reserve(int count)
{
    if(_length + count > _capacity)
    {
        while (_length + count > _capacity)
        {
            _capacity *= 2;
        }
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::shrink()
{
    if(_length == 0)
    {
        clear();
        return;
    }
    if (_length < _capacity / 2)
    {
        while (_length < _capacity / 2)
        {
            _capacity /= 2;
        }
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::insert(int index, T element, int count)
{
    if (index >= _length + 1 || index < 0)
    {
        throw "invalid insert index";
    }
    reserve(count);
    _length += count;
    for (int i = _length - 1; i >= index + count; i--)
    {
        _data[i] = _data[i - 1];
    }
    for (int i = index; i < index + count; i++)
    {
        _data[i] = element;
    }
}
template <class T>
void MyVector<T>::insert(int index, T* array, int length)
{
    if (index >= _length + 1 || index < 0)
    {
        throw "invalid insert index";
    }
    reserve(length);
    _length += length;
    for (int i = index; i < index + length; i++)
    {
        _data[i + length] = _data[i];
        _data[i] = array[i - index];
    }
}
template <class T>
void MyVector<T>::insert(int index, const MyVector<T> &vector)
{
    insert(index, vector._data, vector._length);
}
template <class T>
void MyVector<T>::erase(int index, int count)
{
    if (index < 0 || index >= _length)
    {
        throw "invalid erase index";
    }
    if(count + index >= _length)
    {
        count = _length - index;
    }
    for (int i = index; i + count < _length; i++)
    {
        _data[i] = _data[i + count];
    }
    _length -= count;
    shrink();
}

template <class T>
void printVector(MyVector<T> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    MyVector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    printVector(vector);
    vector.pop_back();
    printVector(vector);
    vector.clear();
    int a[3] = {1, 4, 7};
    MyVector<int> vector2(a, 3);
    printVector(vector2);
    vector = vector2;
    vector2.clear();
    printVector(vector);
    vector.push_back(93);
    MyVector<int> vector3(vector);
    vector.clear();
    printVector(vector3);
    std::cout << vector3.at(2) << vector3.front() << vector3.back() << vector3[1] << std::endl;
    std::cout << (vector3 == vector3) << (vector3 == vector) << (vector != vector2) << std::endl;
    std::cout << vector3.size() << vector3.capacity() << vector.length() << vector.capacity() << std::endl;
    vector3.insert(2, 43);
    printVector(vector3);
    vector3.erase(1, 3);
    printVector(vector3);
    vector3.erase(0);
    printVector(vector3);
    vector.insert(0, a, 3);
    vector3.insert(0, vector);
    printVector(vector3);
    vector.insert(2, 555, 8);
    printVector(vector);
    vector.erase(0, 213133);
    printVector(vector);
    std::cout << vector.capacity() << std::endl;
    return 0;
}
