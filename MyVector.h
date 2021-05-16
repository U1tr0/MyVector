#pragma once

#include "Interface.h"
#include <cstddef>

const size_t ResizeCoef = 2;
const size_t ResizeDelta = 8;

class MyVector : public IVector {
public:
    struct Iterator {
    public:

        Iterator(ValueType* ptr);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        ValueType& operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;
    private:
        ValueType* _ptr;
    };

    Iterator begin() const;
    Iterator end() const noexcept;

    MyVector(const size_t size = 0);
    MyVector(MyVector& other);
    MyVector(MyVector&& other) noexcept;

    ~MyVector();

    ValueType& at(size_t idx) override;
    const ValueType& at(size_t idx) const override;
    ValueType& operator[](const size_t i) override;
    const ValueType& operator[](const size_t i) const override;


    void pushBack(const ValueType& value) override;
    void pushFront(const ValueType& value) override;
    void insert(const ValueType& value, size_t idx) override;

    void clear() override;
    void erase(size_t i) override;
    void erase(size_t i, size_t len) override;
    void popBack() override;

private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
};
