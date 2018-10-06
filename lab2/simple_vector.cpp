//
// Created by nikita on 21.09.2018.
//

#include "simple_vector.h"
template<typename T>
simple_vector<T>::simple_vector(size_t i): size_(0), capacity_(i), storage(new T[i]) {}

template<typename T>
simple_vector<T>::~simple_vector() {
    delete [] (storage);
}

template<typename T>
void simple_vector<T>::push_back(const T &i_element) {
    if (capacity_ == size_)
        reserve(2*(capacity_+1));
    storage[size_] = i_element;
    size_++;
}

template<typename T>
void simple_vector<T>::reserve(size_t i_capacity) {
    T* storage_ = new T[i_capacity];
    memcpy(storage_, storage, sizeof(T)*i_capacity);
    std::swap(storage_, storage);
    capacity_ = i_capacity;
}

template<typename T>
void simple_vector<T>::resize(size_t i_size, const T &i_value) {

    if (capacity_ < i_size)
        reserve(2*i_size);

    for (int i = size_; i < i_size; i++)
        storage[i] = i_value;

    size_ = i_size;
}

template<typename T>
T &simple_vector<T>::operator[](size_t i_index) {
    return storage[i_index];
}

template<typename T>
bool simple_vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
size_t simple_vector<T>::size() const {
    return size_;
}

template<typename T>
size_t simple_vector<T>::capacity() const{
    return capacity_;
}