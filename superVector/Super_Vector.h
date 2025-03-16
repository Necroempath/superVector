#pragma once
#include <iostream>
#include <initializer_list>

template <typename T>
class SuperVector
{
private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void ResizeArray(const T factor)
    {
        T* temp = new T[_capacity * factor]();

        for (size_t i = 0; i < _size; i++)
        {
            temp[i] = _data[i];
        }

        _capacity *= factor;
        delete[] _data;
        _data = temp;
    }

public:
    SuperVector() : _data(nullptr), _size(0), _capacity(0) {}

    SuperVector(size_t size) : _size(size), _capacity(size * 1.5f)
    {
        _data = new T[_capacity] {};
    }

    SuperVector(const SuperVector& other) : _size(other._size), _capacity(other._capacity)
    {
        _data = new T[_capacity];

        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }

    SuperVector(SuperVector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity)
    {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    SuperVector(std::initializer_list<T> init_list) : _size(init_list.size()), _capacity(init_list.size() * 1.5f)
    {
        _data = new T[_capacity];
        size_t index = 0;

        for (auto value : init_list)
        {
            _data[index++] = value;
        }
    }

    inline size_t Size() const
    {
        return _size;
    }

    T& operator[](size_t index)
    {
        if (index >= 0 && index < _size)
            return _data[index];
    }

    const T operator[](size_t index) const
    {
        if (index >= 0 && index < _size)
            return _data[index];
    }

    SuperVector operator/(const SuperVector& other) const
    {
        size_t size = _size < other.Size() ? _size : other.Size();

        SuperVector vector(size);

        for (size_t i = 0; i < size; i++)
        {
            if (vector._data[i] == 0)
                return *this;
        }

        for (size_t i = 0; i < size; i++)
        {
            vector._data[i] = _data[i] / other._data[i];
        }

        return vector;
    }

    SuperVector operator/(const T& scalar) const
    {
        if (scalar == 0) return *this;

        SuperVector vector(Size());

        for (size_t i = 0; i < Size(); i++)
        {
            vector._data[i] = _data[i] / scalar;
        }

        return vector;
    }

    SuperVector operator*(const SuperVector& other) const
    {
        size_t size = _size < other.Size() ? _size : other.Size();

        SuperVector vector(size);

        for (size_t i = 0; i < size; i++)
        {
            vector._data[i] = _data[i] * other._data[i];
        }

        return vector;
    }

    SuperVector operator*(const T& scalar) const
    {
        SuperVector vector(Size());

        for (size_t i = 0; i < Size(); i++)
        {
            vector._data[i] = _data[i] * scalar;
        }

        return vector;
    }

    SuperVector operator-(const SuperVector& other) const
    {
        size_t size = _size < other.Size() ? _size : other.Size();

        SuperVector vector(size);

        for (size_t i = 0; i < size; i++)
        {
            vector._data[i] = _data[i] - other._data[i];
        }

        return vector;
    }

    SuperVector operator+(const SuperVector& other) const
    {
        size_t size = _size < other.Size() ? _size : other.Size();

        SuperVector vector(size);

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

