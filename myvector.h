#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <utility>
#include <cassert>
#include <initializer_list>
#include <exception>

template<class T>
class MyVector {
    size_t m_capacity;
    size_t m_size;
    T* m_data;

public:
    explicit MyVector(size_t size = 0);
    explicit MyVector(const MyVector& vec);
    explicit MyVector(MyVector&& vec);
    explicit MyVector(const std::initializer_list<T>& list);

    void reserve(size_t capacity);
    void resize(size_t newSize);

    size_t size() const;
    size_t capacity() const;

    void push_back(const T& element);
    void push_back(T&& element);

    void pop_back();

    void insert(size_t index, const T& element);
    void erase(size_t index);

    void clear();

    bool empty();
    T& front();
    T& back();
    T& at(size_t index);
    T& operator[](size_t index);
    T operator[](size_t index) const;

    MyVector& operator=(const MyVector& vector);
    MyVector& operator=(MyVector&& vector);
    MyVector& operator=(const std::initializer_list<T>& list);

    virtual ~MyVector();
};

//����������� � �����������/�� ���������:
template<class T>
MyVector<T>::MyVector(size_t size) {
    m_capacity = size;
    m_size = size;
    if (size == 0)
        m_data = nullptr;
    m_data = (T*)new unsigned char[sizeof(T) * m_capacity];
    for (uint32_t i = 0; i < m_size; ++i)
        new(m_data + i) T();
}

//����������� �����������:
template<class T>
MyVector<T>::MyVector(const MyVector& vec) {
    m_capacity = vec.m_capacity;
    m_size = vec.m_size;
    m_data = (T*)new unsigned char[sizeof(T) * m_capacity];
    for (uint32_t i = 0; i < m_size; ++i)
        new(m_data + i) T(vec[i]);
}

//����������� �����������:
template<class T>
MyVector<T>::MyVector(MyVector&& vec) {
    m_capacity = vec.m_capacity;
    vec.m_capacity = 0;
    m_size = vec.m_size;
    vec.m_size = 0;
    m_data = vec.m_data;
    vec.m_data = nullptr;
}

//����������� ����� ������������:
template<class T>
MyVector<T>::MyVector(const std::initializer_list<T>& list) {
    m_capacity = list.size();
    m_size = list.size();
    m_data = (T*)new unsigned char[sizeof(T) * m_capacity];
    uint32_t count{ 0 };
    for (const auto& element : list) {
        new(m_data + count) T(element);
        ++count;
    }
}

//��������� ������� MyVector:
template<class T>
void MyVector<T>::reserve(size_t newCapacity) {
    assert(newCapacity >= m_size);
    m_capacity = newCapacity;
    T* newData = (T*)new unsigned char[sizeof(T) * m_capacity];
    for (uint32_t i = 0; i < m_size; ++i)
        new(newData + i) T(std::move(m_data[i]));
    for (uint32_t i = 0; i < m_size; ++i)
        (m_data + i)->~T();
    delete[] (unsigned char*)m_data;
    m_data = newData;
}

//��������� ������� MyVector:
template<class T>
void MyVector<T>::resize(size_t newSize) {
    if (newSize == m_size)
        return;
    else if (newSize > m_size) {
        if (newSize > m_capacity)
            reserve(newSize);
        for (uint32_t i = m_size; i < newSize; ++i)
            new(m_data + i) T();
    }
    else {
        for (uint32_t i = newSize; i < m_size; ++i)
            (m_data + i)->~T();
    }
    m_size = newSize;
}

//��������� �������:
template<class T>
size_t MyVector<T>::size() const { return m_size; }

//��������� �������:
template<class T>
size_t MyVector<T>::capacity() const { return m_capacity; }

//push_back ��������� �����������:
template<class T>
void MyVector<T>::push_back(const T& element) {
    if (m_capacity < m_size + 1)
        reserve(m_size + 1);
    new(m_data + m_size) T(element);
    ++m_size;
}

//push_back ��������� �����������:
template<class T>
void MyVector<T>::push_back(T&& element) {
    if (m_capacity < m_size + 1)
        reserve(m_size + 1);
    new(m_data + m_size) T(std::move(element));
    ++m_size;
}

//pop_back:
template<class T>
void MyVector<T>::pop_back() {
    --m_size;
    (m_data + m_size)->~T();
}

//������� �������:
template<class T>
void MyVector<T>::insert(size_t index, const T& element) {
    assert(index < m_size);
    if (m_capacity < m_size + 1)
        reserve(m_size + 1);
    for (uint32_t i = m_size; i > index; --i) {
        new(m_data + i) T(std::move(m_data[i - 1]));
        (m_data + i - 1)->~T();
    }
    new(m_data + index) T(element);
    ++m_size;
}

//�������� ��������:
template<class T>
void MyVector<T>::erase(size_t index) {
    assert(index < m_size);
    (m_data + index)->~T();
    --m_size;
    for (uint32_t i = index; i < m_size; ++i) {
        new(m_data + i) T(std::move(i + 1));
        (m_data + i + 1)->~T();
    }
}

//������� MyVector:
template<class T>
void MyVector<T>::clear(){
    for (uint32_t i = 0; i < m_size; ++i)
        (m_data + i)->~T();
    m_size = 0;
}

//�������� �� ������� ��������� � MyVector:
template<class T>
bool MyVector<T>::empty() {
    return m_size == 0;
}

//��������� ������� �������� MyVector:
template<class T>
T& MyVector<T>::front() {
    return m_data[0];
}

//��������� ����������� �������� MyVector:
template<class T>
T& MyVector<T>::back() {
    return m_data[m_size - 1];
}

//��������� ������������� �������� MyVector � ��������� �� ������������:
template<class T>
T& MyVector<T>::at(size_t index) {
    if (index >= m_size)
        throw std::exception("Index is out of range!");
    return m_data[index];
}

//���������� ��������� []:
template<class T>
T& MyVector<T>::operator[](size_t index) {
    return m_data[index];
}

//���������� ��������� [] const ������:
template<class T>
T MyVector<T>::operator[](size_t index) const {
    return m_data[index];
}

//��������� ��������� ������������ ������������:
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& vec) {
    if (this == &vec)
        return *this;

    for (uint32_t i = 0; i < m_size; ++i)
        (m_data + i)->~T();
    delete[] (unsigned char*)m_data;

    m_capacity = vec.m_capacity;
    m_size = vec.m_size;
    
    m_data = (T*)new unsigned char(sizeof(T) * m_capacity);
    for (uint32_t i = 0; i < m_size; ++i)
        new(m_data + i) T(vec[i]);

    return *this;
}

//���������� ��������� ������������ ������������:
template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& vec) {
    if (this == &vec)
        return *this;

    for (unsigned int i = 0; i < m_size; ++i)
        (m_data + i)->~T();
    delete[] (unsigned char*)m_data;

    m_capacity = vec.m_capacity;
    vec.m_capacity = 0;
    m_size = vec.m_size;
    vec.m_size = 0;
    m_data = vec.m_data;
    vec.m_data = nullptr;

    return *this;
}

//���������� ��������� ������������� ����� ���� �������������:
template<class T>
MyVector<T>& MyVector<T>::operator=(const std::initializer_list<T>& list) {
    if (m_capacity < list.size())
        m_capacity = list.size();
    m_size = list.size();

    for (uint32_t i = 0; i < m_size; ++i) {
        (m_size + i)->~T();
    }
    delete[] (unsigned char*)m_data;

    m_data = (T*)new unsigned char[sizeof(T) * m_capacity];

    uint32_t count{ 0 };
    for (const auto& element : list) {
        new(m_data + count) T(element);
        ++count;
    }

    return *this;
}

//����������:
template<class T>
MyVector<T>::~MyVector(){
    for (uint32_t i = 0; i < m_size; ++i)
        (m_data + i)->~T();
    delete[] (unsigned char*)m_data;
}

#endif