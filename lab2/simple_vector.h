//
// Created by nikita on 21.09.2018.
//
#pragma once
#include <stddef.h>
#include <utility>

template<typename T>
class simple_vector {

public:
    explicit simple_vector(size_t i = 1);

    virtual ~simple_vector();

    void push_back(const T& i_element);

    void reserve(size_t i_capacity);

    void resize(size_t i_size, const T& i_value = T());

    T& operator[](size_t i_index);

    bool empty() const;

    size_t size() const;

    size_t capacity() const;
private:
    T* storage;
    size_t size_;
    size_t capacity_;
};
