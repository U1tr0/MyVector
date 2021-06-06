#include "MyVector.h"
#include <iostream>
MyVector::MyVector(const size_t size, ResizeStrategy strategy, size_t coef) {
    this->_size = size;
    this->_capacity = 1;
    this->_resizeCoef = coef;
    this->_strategy = strategy;
    if (_size > 0) {
        if(_strategy == ResizeStrategy::Multiplicative) {
            _capacity = _size * ResizeCoef;
        }
        else{
            _capacity = _size + ResizeCoef;
        }
    }
     _data = new ValueType[_capacity];
}

MyVector::MyVector(MyVector& other) {
    _size = other.size();
    _capacity = other._capacity;
    _data = new ValueType[_capacity];
    _strategy = other._strategy;
    _resizeCoef = other._resizeCoef;
    for(size_t i = 0; i < _size; ++i) {
            _data[i] = other[i];
    }
}

MyVector::MyVector(MyVector&& other) noexcept {
    _size = other.size();
    _data = other._data;
    _capacity = other._capacity;
    _strategy = other._strategy;
    _resizeCoef = other._resizeCoef;
    other._size = 0;
    other._data = nullptr;
    other._capacity = 0;
    other._resizeCoef = 0;
    other._strategy = ResizeStrategy::Multiplicative;
}

MyVector::~MyVector() {
    delete[] _data;
    _size = 0;
    _capacity = 0;
    _resizeCoef = 0;
    _strategy = ResizeStrategy::Multiplicative;
}

ValueType& MyVector::at(size_t idx) {
    if (idx >= size()) {
		throw std::out_of_range("idx >= size");
	}
    return _data[idx];
}

const ValueType& MyVector::at(const size_t idx) const {
       if (idx >= size()) {
		throw std::out_of_range("idx >= size");
	}
    return _data[idx];
}

ValueType& MyVector::operator[](const size_t idx) {
    return at(idx);
}

const ValueType& MyVector::operator[](const size_t idx) const {
    return at(idx);
}

void MyVector::insert(const ValueType& value, size_t idx) {
    if(idx > size()) {
        throw std::out_of_range("idx > size");
    }
    ValueType* newData = _data;
    if(_size == _capacity) {
        if(_strategy == ResizeStrategy::Multiplicative) {
            _capacity *= ResizeCoef;
        }
        else {
            _capacity += ResizeCoef;
        }
        newData = new ValueType[_capacity];
        for(size_t i = 0; i < idx; i++) {
            newData[i] = _data[i];
        }
    }
    for(size_t i = _size; i > idx; i--) {
        newData[i] = _data[i];
    }
    if(_size == _capacity) {
        delete[] _data;
        _data = newData;
    }
    _data[idx] = value;
    _size++;
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
    _resizeCoef = 0;
}

void MyVector::erase(size_t idx) {
    this->erase(idx, 1);
}

void MyVector::erase(size_t idx, size_t len) {
    if (idx >= _size) {
        throw std::out_of_range("idx >= _size");
    }
    if (idx + len - 1 >= size()) {
        len = _size - idx;
    }
    ValueType* newData = _data;
    size_t newSize = _size - len;
    bool flag = false;
    if(_strategy == ResizeStrategy::Multiplicative) {
        while(newSize < (_capacity / ResizeCoef)) {
            _capacity /= ResizeCoef;
            flag = true;
        }
    }
    else {
        while(newSize < (_capacity - _resizeCoef)) {
            _capacity -= _resizeCoef;
        }
    }
    if(flag) {
        newData = new ValueType[_capacity];
        for(size_t i = 0; i < idx; i++) {
            newData[i] = _data[i];
        }
    }
    for(size_t i = idx; i < newSize; i++) {
        newData[i] = _data[i + len];
    }
    if(flag) {
        delete[] _data;
        _data = newData;
    }
    _size = newSize;
}

void MyVector::popBack() {
    if (size() == 0) {
        throw std::out_of_range("size = 0");
    }
    this->erase(size() - 1);
}

MyVector::Iterator::Iterator(ValueType* ptr) {
    _ptr = ptr;
}

MyVector::Iterator::Iterator(const MyVector::Iterator& other) {
    _ptr = other._ptr;
}

MyVector::Iterator& MyVector::Iterator::operator=(const MyVector::Iterator& other) {
    _ptr = other._ptr;
    return *this;
}

ValueType& MyVector::Iterator::operator*() const {
    return *_ptr;
}

MyVector::Iterator& MyVector::Iterator::operator++() {
    _ptr++;
    return *this;
}

MyVector::Iterator MyVector::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool MyVector::Iterator::operator!=(const MyVector::Iterator& other) const {
    return _ptr != other._ptr;
}

bool MyVector::Iterator::operator==(const MyVector::Iterator& other) const {
    return !(*this != other);
}

bool MyVector::Iterator::operator<(const MyVector::Iterator& other) const {
    return _ptr < other._ptr;
}

bool MyVector::Iterator::operator>(const MyVector::Iterator& other) const {
    return _ptr > other._ptr;
}

bool MyVector::Iterator::operator<=(const MyVector::Iterator& other) const {
    return !(*this > other);
}

bool MyVector::Iterator::operator>=(const MyVector::Iterator& other) const {
    return !(*this < other);
}

MyVector::Iterator MyVector::begin() const {
    return MyVector::Iterator(&_data[0]);
}

MyVector::Iterator MyVector::end() const noexcept {
    return MyVector::Iterator(&_data[size()]);
}
