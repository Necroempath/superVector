#pragma once
class SuperVector
{
private:
    float* _data;
    size_t _size;
    size_t _capacity;

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

    const float operator[](int index) const;

    float& operator[](int index);

    size_t Size() const;

    ~SuperVector();

};

