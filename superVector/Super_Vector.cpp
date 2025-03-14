#include "Super_Vector.h"

SuperVector::SuperVector() : _data(nullptr), _size(0), _capacity(0) {}

SuperVector::SuperVector(size_t size) : _size(size), _capacity(size * 1.5f)
{
    _data = new float[_capacity] {};
}

SuperVector::SuperVector(const SuperVector& other) : _size(other._size), _capacity(other._capacity)
{
    _data = new float[_capacity];

    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

SuperVector::SuperVector(SuperVector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

void SuperVector::ResizeArray(const float factor)
{
    float* temp = new float[_capacity * factor]();

    for (int i = 0; i < _size; i++)
    {
        temp[i] = _data[i];
    }

    _capacity *= factor; //comment this and catch sweet bug)
    delete[] _data;
    _data = temp;
}

inline size_t SuperVector::Size() const
{
    return _size;
}

float& SuperVector::operator[](int index)
{
    if (index >= 0 && index < _size)
        return _data[index];
}

const float SuperVector::operator[](int index) const
{
    if (index >= 0 && index < _size)
        return _data[index];
}

SuperVector SuperVector::operator/(const SuperVector& other) const
{
    int size = _size < other.Size() ? _size : other.Size();

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

SuperVector SuperVector::operator/(const float& scalar) const
{
    if (scalar == 0) return *this;

    SuperVector vector(Size());

    for (size_t i = 0; i < Size(); i++)
    {
        vector._data[i] = _data[i] / scalar;
    }

    return vector;
}

SuperVector SuperVector::operator*(const SuperVector& other) const
{
    int size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(size);

    for (size_t i = 0; i < size; i++)
    {
        vector._data[i] = _data[i] * other._data[i];
    }

    return vector;
}

SuperVector SuperVector::operator*(const float& scalar) const
{
    SuperVector vector(Size());

    for (size_t i = 0; i < Size(); i++)
    {
        vector._data[i] = _data[i] * scalar;
    }

    return vector;
}

SuperVector SuperVector::operator-(const SuperVector& other) const
{
    int size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(size);

    for (size_t i = 0; i < size; i++)
    {
        vector._data[i] = _data[i] - other._data[i];
    }

    return vector;
}

SuperVector SuperVector::operator+(const SuperVector& other) const
{
    int size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(size);

    for (size_t i = 0; i < size; i++)
    {
        vector._data[i] = _data[i] + other._data[i];
    }

    return vector;
}

SuperVector& SuperVector::operator=(SuperVector&& vector) noexcept
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

SuperVector& SuperVector::operator=(const SuperVector& vector)
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

SuperVector& SuperVector::operator+=(const SuperVector& other)
{
    *this = *this + other;

    return *this;
}

SuperVector& SuperVector::operator-=(const SuperVector& other)
{
    *this = *this - other;

    return *this;
}

SuperVector& SuperVector::operator*=(const float& scalar)
{
    *this = *this * scalar;

    return *this;
}

SuperVector& SuperVector::operator/=(const float& scalar)
{
    *this = *this / scalar;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const SuperVector& vector)
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

//std::istream& operator>>(std::istream& is, SuperVector& vector)
//{
//    for (size_t i = 0; i < vector.Size(); i++)
//    {
//        is >> vector[i];
//    }
//
//    return is;
//}

SuperVector& SuperVector::operator++()
{
    for (size_t i = 0; i < Size(); i++)
    {
        _data[i]++;
    }

    return *this;
}

SuperVector SuperVector::operator++(int)
{
    SuperVector temp = *this;

    for (size_t i = 0; i < Size(); i++)
    {
        _data[i]++;
    }

    return temp;
}

SuperVector& SuperVector::operator--()
{
    for (size_t i = 0; i < Size(); i++)
    {
        _data[i]--;
    }

    return *this;
}

SuperVector SuperVector::operator--(int)
{
    SuperVector temp = *this;

    for (size_t i = 0; i < Size(); i++)
    {
        _data[i]--;
    }

    return temp;
}

void SuperVector::PushBack(float value)
{
    if (_size == _capacity) ResizeArray(1.5f);

    _data[_size++] = value;
}

bool SuperVector::Insert(int index, float value)
{
    if (index < 0 || index > _size) return 0;

    if (_size == _capacity) ResizeArray(1.5f);

    for (int i = _size; i > index; i--)
    {
        _data[i] = _data[i - 1];

    }

    _data[index] = value;

    _size++;
    return 1;
}

void SuperVector::Pop()
{
    _data[--_size] = 0;

    if (_size <= _capacity * 0.7f) ResizeArray(0.7f);
}

bool SuperVector::Remove(int index)
{
    if (index < 0 || index >= _size) return 0;

    for (int i = index; i < _size - 1; i++)
    {
        _data[i] = _data[i + 1];
    }

    Pop();
    return true;
}

SuperVector::~SuperVector()
{
    delete[] _data;
}