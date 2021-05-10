#include "MyVector.h"
#include <iostream>
MyVector::MyVector(const size_t size) {
    this->_size = size;
    this->_capacity = 1;
    if (_size > 0) {
        _capacity = _size * 2;
    }
     _data = new ValueType[_capacity];
}

MyVector::MyVector(MyVector& other) {
    _size = other.size();
    _capacity = other._capacity;
    _data = new ValueType[_capacity];
    for(size_t i = 0; i < _size; ++i) {
            _data[i] = other[i];
    }
}

MyVector::MyVector(MyVector&& other) noexcept {
    _size = other.size();
    _data = other._data;
    _capacity = other._capacity;
    other._size = 0;
    other._data = nullptr;
    other._capacity = 0;

}

MyVector::~MyVector() {
    _size = 0;
    delete[] _data;
    _capacity = 0;
}

ValueType& MyVector::at(size_t idx) {
    return _data[idx];
}

const ValueType& MyVector::at(size_t idx) const {
    return _data[idx];
}

ValueType& MyVector::operator[](const size_t i) {
    return _data[i];
}

const ValueType& MyVector::operator[](const size_t i) const {
    return _data[i];
}

void MyVector::insert(const ValueType& value, size_t idx) {
    if(_size == _capacity) {
        _capacity *= 2;
    }
    ValueType* newData = new ValueType[_capacity];
    for(size_t i = 0; i < _size + 1; ++i) {
        if(i < idx) {
            newData[i] = _data[i];
        }
        else if(i > idx) {
            newData[i] = _data[i - 1];
        }
        else if(i == idx) {
            newData[i] = value;
        }
    }
    _size++;
    delete[] _data;
    _data = newData;
}

void MyVector::pushBack(const ValueType& value) {
    this->insert(value, size());
}

void MyVector::pushFront(const ValueType& value) {
    this->insert(value, 0);
}

void MyVector::clear() {
    delete[] _data;
    _size = 0;
    _capacity = 1;
    _data = new ValueType[_capacity];
}

void MyVector::erase(size_t i) {
    this->erase(i, 1);
}

void MyVector::erase(size_t i, size_t len) {
    size_t newSize = _size - len;
    ValueType* newData = new ValueType[newSize];
    for(size_t j = 0; j < i; ++j) {
        newData[j] = _data[j];
    }
    for(size_t j = i; j < newSize; ++j) {
        newData[j] = _data[j + len];
    }
    delete[] _data;
    _data = newData;
    _size = newSize;
}

void MyVector::popBack() {
    this->erase(size() - 1);
}

size_t MyVector::size() {
    return _size;
}
