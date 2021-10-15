#pragma once

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

    T& pop_back();

    void insert(size_t index, const T& element);
    void erase(size_t index);

    void clear();

    bool empty();
    T& front();
    T& back();
    T& at(size_t index);
    T& operator[](size_t index);

    MyVector& operator=(const MyVector& vector);
    MyVector& operator=(MyVector&& vector);
    MyVector& operator=(const std::initializer_list<T>& list);

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
    for (unsigned int i = 0; i < m_size; ++i)
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

//конструктор листа иницализации:
template<class T>
MyVector<T>::MyVector(const std::initializer_list<T>& list) : MyVector(list.size()) {
    int count{ 0 };
    for (const auto& element : list) {
        m_data[count] = element;
        ++count;
    }
}

//изменение емкости MyVector:
template<class T>
void MyVector<T>::reserve(size_t newCapacity) {
    assert(newCapacity >= m_size);
    m_capacity = newCapacity;
    T* newData = new T[m_capacity];
    for (unsigned int i = 0; i < m_size; ++i)
        newData[i] = m_data[i];
    delete[] m_data;
    m_data = newData;
}

//изменение размера MyVector:
template<class T>
void MyVector<T>::resize(size_t newSize) {
    if (newSize == m_size)
        return;
    else if (newSize > m_size) {
        if (newSize > m_capacity)
            reserve(newSize);
        for (unsigned int i = m_size; i < newSize; ++i)
            m_data[i] = T();
    }
    else {
        T* newData = new T[m_capacity];
        for (unsigned int i = 0; i < newSize; ++i)
            newData[i] = m_data[i];
        delete[] m_data;
        m_data = newData;
    }
    m_size = newSize;
}

//получение размера:
template<class T>
size_t MyVector<T>::size() const { return m_size; }

//получение емкости:
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

//pop_back ! реализация под вопросом, если возвращать элемент и не очищать память, то возможна утечка памяти !:
template<class T>
T& MyVector<T>::pop_back() {
    --m_size;
    return m_data[m_size];
}

//вставка элмента:
template<class T>
void MyVector<T>::insert(size_t index, const T& element) {
    assert(index < m_size);
    ++m_size;
    if (m_capacity < m_size)
        reserve(m_size);
    T* newData = new T[m_size];
    for (unsigned int i = 0; i < index; ++i) {
        newData[i] = m_data[i];
    }
    newData[index] = element;
    for (unsigned int i = index + 1; i < m_size; ++i) {
        newData[i] = m_data[i - 1];
    }
    delete[] m_data;
    m_data = newData;
}

//удаление эдемента:
template<class T>
void MyVector<T>::erase(size_t index) {
    assert(index < m_size);
    T* newData = new T[m_capacity];
    for (unsigned int i = 0; i < index; ++i)
        newData[i] = m_data[i];
    for (unsigned int i = index + 1; i < m_size; ++i)
        newData[i - 1] = m_data[i];
    delete[] m_data;
    m_data = newData;
    --m_size;
}

//очистка MyVector:
template<class T>
void MyVector<T>::clear(){
    size = 0;
    delete m_data;
    m_data = new T[m_capacity];
}

//проверка на наличие элементов в MyVector:
template<class T>
bool MyVector<T>::empty() {
    return m_size == 0;
}

//получение первого элемента MyVector:
template<class T>
T& MyVector<T>::front() {
    assert(m_size > 0);
    return m_data[0];
}

//получение посследнего элемента MyVector:
template<class T>
T& MyVector<T>::back() {
    assert(m_size > 0);
    return m_data[m_size - 1];
}

//получение произвольного элемента MyVector с проверкой на корректность:
template<class T>
T& MyVector<T>::at(size_t index) {
    if (index >= m_size)
        throw std::exception("Index is out of range!");
    return m_data[index];
}

//перегрузка оператора []:
template<class T>
T& MyVector<T>::operator[](size_t index) {
    return m_data[index];
}

//прегрузка оператора присавивания копированием:
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& vec) {
    if (this == &vec)
        return *this;

    delete[] m_data;
    m_capacity = vec.m_capacity;
    m_size = vec.m_size;
    m_data = new T[m_capacity];
    for (unsigned int i = 0; i < m_size; ++i)
        m_data[i] = vec.m_data[i];

    return *this;
}

//перегрузка оператора присваивания перемещением:
template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& vec) {
    if (this == &vec)
        return *this;

    delete[] m_data;
    m_capacity = vec.m_capacity;
    vec.m_capacity = 0;
    m_size = vec.m_size;
    vec.m_size = 0;
    m_data = vec.m_data;
    vec.m_data = nullptr;

    return *this;
}

//перегрузка оператора присванивания через лист инициализации:
template<class T>
MyVector<T>& MyVector<T>::operator=(const std::initializer_list<T>& list) {
    m_capacity = list.size();
    m_size = list.size();
    delete[] m_data;
    m_data = new T[m_capacity];

    int count{ 0 };
    for (const auto& element : list) {
        m_data[count] = element;
        ++count;
    }

    return *this;
}

//деструктор:
template<class T>
MyVector<T>::~MyVector(){
    delete[] m_data;
}