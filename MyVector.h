#pragma once

#include "Interface.h"
#include<cstddef>

class MyVector : public IVector {
public:
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

    size_t size();


private:
    ValueType* _data;
    size_t _size;
};
