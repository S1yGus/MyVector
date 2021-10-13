#pragma once

#include <cassert>

template<class T>
class MyVector {
    size_t m_capacity;
    size_t m_size;
    T* m_data;

public:
    MyVector(size_t size = 0);
    MyVector(const MyVector& vec);
    MyVector(MyVector&& vec);

    void reserve(size_t capacity);

    size_t size() const;
    size_t capacity() const;

    T& operator[](size_t index);

    void push_back(const T& element);
    void push_back(T&& element);

    T& pop_back();

    void resize(size_t newSize);

    virtual ~MyVector();
};

//конструктор с параметрами/по умолчанию:
template<class T>
MyVector<T>::MyVector(size_t size) {
    m_capacity = size;
    m_size = size;
    if (size == 0)
        m_data = nullptr;
    m_data = new T[m_capacity];
}

//конструктор копирования:
template<class T>
MyVector<T>::MyVector(const MyVector& vec) {
    m_capacity = vec.m_capacity;
    m_size = vec.m_size;
    m_data = new T[m_size];
    for (int i = 0; i < m_size; ++i)
        m_data[i] = vec.m_data[i];
}

//конструктор перемещения:
template<class T>
MyVector<T>::MyVector(MyVector&& vec) {
    m_capacity = vec.m_capacity;
    vec.m_capacity = 0;
    m_size = vec.m_size;
    vec.m_size = 0;
    m_data = vec.m_data;
    vec.m_data = nullptr;
}

//изменение емкости MyVector:
template<class T>
void MyVector<T>::reserve(size_t capacity) {
    m_capacity = capacity;
    T* newData = new T[capacity];
    for (int i = 0; i < m_size; ++i)
        newData[i] = m_data[i];
    delete[] m_data;
    m_data = newData;
}

//перегрузка оператора []:
template<class T>
T& MyVector<T>::operator[](size_t index) {
    assert(index < m_size);
    return m_data[index];
}

template<class T>
size_t MyVector<T>::size() const { return m_size; }
template<class T>
size_t MyVector<T>::capacity() const { return m_capacity; }

//push_back семантика копирования:
template<class T>
void MyVector<T>::push_back(const T& element) {
    ++m_size;
    if (m_capacity < m_size)
        reserve(m_size);
    m_data[m_size - 1] = element;
}

//push_back семантика перемещения:
template<class T>
void MyVector<T>::push_back(T&& element) {
    ++m_size;
    if (m_capacity < m_size)
        reserve(m_size);
    m_data[m_size - 1] = std::move(element);
}

//pop_back:
template<class T>
T& MyVector<T>::pop_back() {
    --m_size;
    return m_data[m_size];
}


//resize:
template<class T>
void MyVector<T>::resize(size_t newSize) {
    if (newSize > m_size) {
        if (newSize > m_capacity)
            reserve(newSize);
        for (int i = m_size; i < newSize; ++i)
            m_data[i] = T();
    }
    else
        for (int i = newSize; i < m_size; ++i)
            m_data[i].~T();
    m_size = newSize;
}

//деструктор:
template<class T>
MyVector<T>::~MyVector(){
    delete[] m_data;
}