#include <new>
#include "vector.h"

Vector::Vector() {
    vector_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}
Vector::Vector(size_t size) {
    try {
        vector_ = new Vector::ValueType[size];
    } catch (...) {
        throw std::bad_alloc();
    }
    size_ = size;
    capacity_ = size;
    for (Vector::SizeType i = 0; i < size_; ++i) {
        vector_[i] = 0;
    }
}
Vector::Vector(std::initializer_list<ValueType> list) {
    try {
        vector_ = new Vector::ValueType[list.size()];
    } catch (const std::bad_alloc&) {
        throw std::bad_alloc();
    }
    size_ = list.size();
    capacity_ = size_;
    auto j = list.begin();
    for (Vector::SizeType i = 0; i < size_; ++i, ++j) {
        vector_[i] = *j;
    }
}
Vector::Vector(Vector& other) {
    try {
        vector_ = new Vector::ValueType[other.capacity_];
    } catch (const std::bad_alloc&) {
        throw std::bad_alloc();
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (Vector::SizeType i = 0; i < size_; ++i) {
        vector_[i] = other.vector_[i];
    }
}
Vector& Vector::operator=(const Vector& other) {
    ValueType* tmp = nullptr;
    try {
        tmp = new Vector::ValueType[other.capacity_];
    } catch (const std::bad_alloc&) {
        throw std::bad_alloc();
    }
    delete[] vector_;
    vector_ = tmp;
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (Vector::SizeType i = 0; i < other.size_; ++i) {
        vector_[i] = other.vector_[i];
    }
    return *this;
}
Vector::~Vector() {
    delete[] vector_;
}
Vector::SizeType Vector::Size() const {
    return size_;
}
Vector::SizeType Vector::Capacity() const {
    return capacity_;
}
const Vector::ValueType* Vector::Data() const {
    return vector_;
}
void Vector::Swap(Vector& other) {
    Vector tmp;
    tmp.size_ = this->size_;
    tmp.capacity_ = this->capacity_;
    tmp.vector_ = this->vector_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->vector_ = other.vector_;
    other.size_ = tmp.size_;
    other.capacity_ = tmp.capacity_;
    other.vector_ = tmp.vector_;
    tmp.vector_ = nullptr;
}
void Vector::Clear() {
    for (Vector::SizeType i = 0; i < size_; ++i) {
        vector_[i] = 0;
    }
    size_ = 0;
}
void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity > capacity_) {
        ValueType* tmp = nullptr;
        try {
            tmp = new Vector::ValueType[new_capacity];
        } catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
        Vector v(*this);
        delete[] vector_;
        this->vector_ = tmp;
        for (Vector::SizeType i = 0; i < size_; ++i) {
            vector_[i] = v.vector_[i];
        }
        for (Vector::SizeType i = size_; i < new_capacity; ++i) {
            vector_[i] = 0;
        }
        capacity_ = new_capacity;
    }
}
void Vector::PushBack(const Vector::ValueType& new_element) {
    if (capacity_ == 0) {
        this->Reserve(1);
    } else if (size_ == capacity_) {
        this->Reserve(capacity_ * 2);
    }
    vector_[size_] = new_element;
    size_++;
}
void Vector::PopBack() {
    vector_[size_ - 1] = 0;
    size_--;
}
Vector::ValueType& Vector::operator[](size_t position) {
    return vector_[position];
}
const Vector::ValueType& Vector::operator[](size_t position) const {
    return vector_[position];
}
Vector::Iterator Vector::Begin() {
    Vector::Iterator tmp(vector_);
    return tmp;
}
Vector::Iterator Vector::End() {
    Vector::Iterator tmp(vector_);
    tmp += size_;
    return tmp;
}
Vector::Iterator Vector::begin() {
    return this->Begin();
}
Vector::Iterator Vector::end() {
    return this->End();
}
bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (Vector::SizeType i = 0; i < size_; ++i) {
        if (vector_[i] != other.vector_[i]) {
            return false;
        }
    }
    return true;
}
bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}
std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (Vector::SizeType i = 0; i < size_ && i < other.size_; ++i) {
        if (vector_[i] < other.vector_[i]) {
            return std::strong_ordering::less;
        } else if (vector_[i] > other.vector_[i]) {
            return std::strong_ordering::greater;
        }
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    } else if (size_ > other.size_) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}
Vector::Iterator::Iterator(Vector::ValueType* pointer) {
    for_iteration_ = pointer;
}
Vector::Iterator::Iterator() {
    for_iteration_ = nullptr;
}
Vector::ValueType& Vector::Iterator::operator*() const {
    if (for_iteration_) {
        return *for_iteration_;
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
}
Vector::ValueType* Vector::Iterator::operator->() const {
    if (for_iteration_) {
        return for_iteration_;
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
}
Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    for_iteration_ = other.for_iteration_;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator++() {
    if (for_iteration_) {
        ++for_iteration_;
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Vector::Iterator tmp(for_iteration_);
    ++*this;
    return tmp;
}
Vector::Iterator& Vector::Iterator::operator--() {
    if (for_iteration_) {
        --for_iteration_;
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
    return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Vector::Iterator tmp(for_iteration_);
    --*this;
    return tmp;
}
Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Vector::Iterator tmp(*this);
    if (shift > 0) {
        for (Vector::DifferenceType i = 0; i < shift; ++i) {
            ++tmp;
        }
    } else if (shift < 0) {
        for (; shift < 0; ++shift) {
            --tmp;
        }
    }
    return tmp;
}
Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    if (other.for_iteration_ < for_iteration_) {
        return std::distance(other.for_iteration_, for_iteration_);
    }
    return std::distance(for_iteration_, other.for_iteration_);
}
Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    if (for_iteration_) {
        for (Vector::DifferenceType i = 0; i < shift; ++i) {
            ++for_iteration_;
        }
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    if (for_iteration_) {
        for (Vector::DifferenceType i = 0; i < shift; ++i) {
            --for_iteration_;
        }
    } else {
        std::cout << "for_iteration_ == nullptr!" << std::endl;
        throw std::exception();
    }
    return *this;
}
bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return for_iteration_ == other.for_iteration_;
}
bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return !(*this == other);
}
std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    if (for_iteration_ < other.for_iteration_) {
        return std::strong_ordering::less;
    } else if (for_iteration_ > other.for_iteration_) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}
