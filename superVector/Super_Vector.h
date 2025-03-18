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

        SuperVector vector(*this);

    bool Remove(int index);

        return vector;
    }

    SuperVector operator+(const SuperVector& other) const
    {
        size_t size = _size < other.Size() ? _size : other.Size();

        SuperVector vector(*this);

        for (size_t i = 0; i < size; i++)
        {
            vector._data[i] = _data[i] + other._data[i];
        }

        return vector;
    }

    SuperVector& operator=(SuperVector&& vector) noexcept
    {
        if (&vector == this) return *this;

        _size = vector._size;
        _capacity = vector._capacity;
        _data = vector._data;

        vector._size = 0;
        vector._capacity = 0;
        vector._data = nullptr;

        return *this;
    }

    SuperVector& operator=(const SuperVector& vector)
    {
        if (&vector == this) return *this;

        _size = vector._size;
        _capacity = vector._capacity;
        _data = new float[_capacity];

        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = vector._data[i];
        }

        return *this;
    }

    SuperVector& operator+=(const SuperVector& other)
    {
        *this = *this + other;

        return *this;
    }

    SuperVector& operator-=(const SuperVector& other)
    {
        *this = *this - other;

        return *this;
    }

    SuperVector& operator*=(const float& scalar)
    {
        *this = *this * scalar;

        return *this;
    }

    SuperVector& operator/=(const float& scalar)
    {
        *this = *this / scalar;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const SuperVector& vector)
    {
        os << "[";
        for (size_t i = 0; i < vector.Size(); i++)
        {
            os << vector[i];

            if (i < vector.Size() - 1) os << ", ";
        }
        os << "]";

        return os;
    }

    friend std::istream& operator>>(std::istream& is, SuperVector& vector)
    {
        for (size_t i = 0; i < vector.Size(); i++)
        {
            is >> vector[i];
        }

        return is;
    }

    SuperVector& operator++()
    {
        for (size_t i = 0; i < Size(); i++)
        {
            _data[i]++;
        }

        return *this;
    }

    SuperVector operator++(int)
    {
        SuperVector temp = *this;

        for (size_t i = 0; i < Size(); i++)
        {
            _data[i]++;
        }

        return temp;
    }

    SuperVector& operator--()
    {
        for (size_t i = 0; i < Size(); i++)
        {
            _data[i]--;
        }

        return *this;
    }

    SuperVector operator--(int)
    {
        SuperVector temp = *this;

        for (size_t i = 0; i < Size(); i++)
        {
            _data[i]--;
        }

        return temp;
    }

    void PushBack(T value)
    {
        if (_size == _capacity) ResizeArray(1.5f);

        _data[_size++] = value;
    }

    bool Insert(size_t index, T value)
    {
        if (index < 0 || index > _size) return 0;

        if (_size == _capacity) ResizeArray(1.5f);

        for (size_t i = _size; i > index; i--)
        {
            _data[i] = _data[i - 1];
        }

        _data[index] = value;

        _size++;
        return 1;
    }

    void Pop()
    {
        _data[--_size] = 0;

        if (_size <= _capacity * 0.7f) ResizeArray(0.7f);
    }

    bool Remove(size_t index)
    {
        if (index < 0 || index >= _size) return 0;

        for (size_t i = index; i < _size - 1; i++)
        {
            _data[i] = _data[i + 1];
        }

        Pop();
        return true;
    }

    ~SuperVector()
    {
        delete[] _data;
    }

};

