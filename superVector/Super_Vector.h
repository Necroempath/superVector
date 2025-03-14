#pragma once
#include <ostream>
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

    SuperVector& operator*=(const float& scalar);

    SuperVector& operator/=(const float& scalar);

    friend std::ostream& operator<<(std::ostream& os, const SuperVector& vector);

    friend std::istream& operator>>(std::istream& is, SuperVector& vector);

    SuperVector& operator++();

    SuperVector operator++(int);

    SuperVector& operator--();

    SuperVector operator--(int);

    const float operator[](int index) const;

    float& operator[](int index);

    size_t Size() const;

    void PushBack(float value);

    bool Insert(int index, float value);

    void Pop();

    bool Remove(int index);

    ~SuperVector();

};

