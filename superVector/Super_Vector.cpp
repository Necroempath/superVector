#include "Super_Vector.h"
#define ascending_factor 2.0f
#define descending_factor .7f

SuperVector::SuperVector() : _data(nullptr), _size(0), _capacity(0) {}

SuperVector::SuperVector(size_t size) : _size(size), _capacity(size * ascending_factor)
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

SuperVector::SuperVector(std::initializer_list<float> init_list) : _size(init_list.size()), _capacity(init_list.size() * ascending_factor)
{
    _data = new float[_capacity];
    size_t index = 0;

    for(auto value : init_list)
    {
        _data[index++] = value;
    }
}

void SuperVector::ResizeArray(const float factor)
{
    float* temp = new float[_capacity * factor]();

    for (int i = 0; i < _size; i++)
    {
        temp[i] = _data[i];
    }

    _capacity *= factor; 
    delete[] _data;
    _data = temp;
}

inline size_t SuperVector::Size() const
{
    return _size;
}

float& SuperVector::operator[](size_t index)
{
    if (index >= 0 && index < _size)
        return _data[index];
}

const float SuperVector::operator[](size_t index) const
{
    if (index >= 0 && index < _size)
        return _data[index];
}

SuperVector SuperVector::operator/(const SuperVector& other) const
{
    size_t size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(*this);

    for (size_t i = 0; i < size; i++)
    {
        if (other._data[i] == 0)
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
    size_t size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(*this);

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
    size_t size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(*this);

    for (size_t i = 0; i < size; i++)
    {
        vector._data[i] = _data[i] - other._data[i];
    }

    return vector;
}

SuperVector SuperVector::operator+(const SuperVector& other) const
{
    size_t size = _size < other.Size() ? _size : other.Size();

    SuperVector vector(*this);

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

SuperVector& SuperVector::operator*=(const SuperVector& other)
{
    *this = *this * other;

    return *this;
}

SuperVector& SuperVector::operator*=(const float& scalar)
{
    *this = *this * scalar;

    return *this;
}

SuperVector& SuperVector::operator/=(const SuperVector& other)
{
    *this = *this / other;

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

std::istream& operator>>(std::istream& is, SuperVector& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
    {
        is >> vector[i];
    }

    return is;
}

bool SuperVector::operator==(const SuperVector& vector) const
{
    if (_size != vector._size) return 0;

    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] != vector._data[i]) return 0;
    }

    return 1;
}

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
    if (!_data) {
        _capacity = 5;
        _data = new float[_capacity];
    }
    if (_size == _capacity) ResizeArray(ascending_factor);

    _data[_size++] = value;
}

bool SuperVector::Insert(size_t index, float value)
{
    if (index < 0 || index > _size) return 0;

    if (!_data) {
        _capacity = 5;
        _data = new float[_capacity];
    }

    if (_size == _capacity) ResizeArray(ascending_factor);

    for (size_t i = _size; i > index; i--)
    {
        _data[i] = _data[i - 1];
    }

    _data[index] = value;

    _size++;
    return 1;
}

bool SuperVector::Pop()
{
    if (!_data || _size == 0) return 0;

    _data[--_size] = _data[_capacity - 1];

    if (_size <= _capacity * 0.7f) ResizeArray(descending_factor);
    return 1;
}

bool SuperVector::Remove(size_t index)
{
    if (!_data || _size == 0) return 0;

    if (index < 0 || index >= _size) return 0;

    for (size_t i = index; i < _size - 1; i++)
    {
        _data[i] = _data[i + 1];
    }

    return Pop();
}

SuperVector::~SuperVector()
{
    delete[] _data;
}