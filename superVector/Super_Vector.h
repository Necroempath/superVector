#pragma once
#include <iostream>
#include "initializer_list"

class SuperVector
{
private:
    float* _data;
    size_t _size;
    size_t _capacity;

    void ResizeArray(const float factor);

public:
    SuperVector();

    SuperVector(size_t size);

    SuperVector(const SuperVector& other);

    SuperVector(SuperVector&& other) noexcept;

    SuperVector(std::initializer_list<float> init_list);

    SuperVector& operator=(const SuperVector& vector);

    SuperVector& operator=(SuperVector&& vector) noexcept;

    SuperVector operator+(const SuperVector& other) const;

    SuperVector operator-(const SuperVector& other) const;

    SuperVector operator*(const SuperVector& other) const;

    SuperVector operator*(const float& scalar) const;

    SuperVector operator/(const SuperVector& other) const;

    SuperVector operator/(const float& scalar) const;

    SuperVector& operator+=(const SuperVector& other);

    SuperVector& operator-=(const SuperVector& other);

    SuperVector& operator*=(const SuperVector& other);

    SuperVector& operator*=(const float& scalar);

    SuperVector& operator/=(const SuperVector& other);

    SuperVector& operator/=(const float& scalar);

    friend std::ostream& operator<<(std::ostream& os, const SuperVector& vector);

    friend std::istream& operator>>(std::istream& is, SuperVector& vector);

    bool operator==(const SuperVector& vector) const;

    SuperVector& operator++();

    SuperVector operator++(int);

    SuperVector& operator--();

    SuperVector operator--(int);

    const float operator[](size_t index) const;

    float& operator[](size_t index);

    size_t Size() const;

    void PushBack(float value);

    bool Insert(size_t index, float value);

    bool Pop();

    bool Remove(size_t index);

    ~SuperVector();
};
