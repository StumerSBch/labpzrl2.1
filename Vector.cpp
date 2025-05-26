#include "Vector.h"

#include <algorithm>
#include <stdexcept>

//Конструктор с параметрами:
Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef)
{
    _data = new ValueType[_capacity];
    std::copy(rawArray, rawArray + size, _data);
}

//Конструктор копирования:
Vector::Vector(const Vector& other) : _size(other._size), _capacity(other._size), _multiplicativeCoef(other._multiplicativeCoef)
{
    _data = new ValueType[_capacity];
    std::copy(other._data, other._data + _size, _data);
}

// Оператор присваивания копированием
Vector& Vector::operator=(const Vector& other) 
{
    if(this != &other)
    {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;

        _data = new ValueType[_capacity];
        std::copy(other._data, other._data + _size, _data);
    }
    return *this;
}

//Конструктор перемещения:
Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef)
{
    other._data = nullptr; 
    other._size = 0; 
    other._capacity = 0;
}

//Оператор присваивания перемещением
Vector& Vector::operator=(Vector&& other) noexcept
{
    if(this != &other)
    {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;

        other._data = nullptr; 
        other._size = 0; 
        other._capacity = 0;
    }
    return *this;
}

//Деструктор
Vector::~Vector()
{
    delete[] _data;
}



//Вставка в конец
void Vector::pushBack(const ValueType& value)
{
    if(_size == _capacity)
    {
        reserve((_capacity == 0) ? static_cast<size_t>(_multiplicativeCoef) : static_cast<size_t>(_capacity * _multiplicativeCoef));
    }

    _data[_size++] = value;
}

//Вставка в начало
void Vector::pushFront(const ValueType& value)
{
    insert(value, 0);
}



//Вставка элемента value в позицию pos
void Vector::insert(const ValueType& value, size_t pos)
{
    if(pos > _size)
    {
        throw std::out_of_range("Недопустимая позиция вставки!");
    }

    if(_size == _capacity)
    {
        reserve((_capacity == 0) ? static_cast<size_t>(_multiplicativeCoef) : static_cast<size_t>(_capacity * _multiplicativeCoef));
    }
    
    for(size_t i = _size; i > pos; --i)
    {
        _data[i] = _data[i - 1];
    }

    _data[pos] = value;
    ++_size;
}

//Вставка массива элементов типа ValueType в позицию pos
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if(pos > _size)
    {
        throw std::out_of_range("Недопустимая позиция вставки!");
    }

    reserve(_size + size);

    for (size_t i = _size + size; i-- > pos + size;)
    {
        _data[i] = _data[i - size];
    }

    std::copy(values, values + size, _data + pos);
    _size += size;
}

//Вставка содержимого вектора в позицию pos
void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

//Удаление с конца
void Vector::popBack()
{
    if (_size == 0)
    {
        throw std::out_of_range("Удаление из пустого вектора!!!");
    }

    --_size;
}

//Удаление из начала
void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::out_of_range("Удаление из пустого вектора!!!");
    }

    erase(0);
}




void Vector::erase(size_t pos, size_t count)
{
    if(pos >= _size)
    {
        return;
    }

    if((pos + count) > _size)
    {
        count = _size - pos;
    }

    for (size_t i = pos + count; i < _size; ++i)
    {
        _data[i - count] = _data[i];
    }

    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos >= _size) 
    {
        return;
    }

    if (endPos > _size)
    {
        endPos = _size;
    }
    if (beginPos >= endPos)
    {
        return;
    }

    erase(beginPos, endPos - beginPos);
}



//Количество элементов
size_t Vector::size() const
{
    return _size;
}

//Максимальное количество элементов
size_t Vector::capacity() const
{
    return _capacity;
}

//Фактор загруженности
double Vector::loadFactor() const
{
    return _capacity ? static_cast<double>(_size) / _capacity : 0.0;
}



//Доступ к элементу по индексу
ValueType& Vector::operator[](size_t idx)
{
    return _data[idx];
}

//Доступ к элементу по индексу
const ValueType& Vector::operator[](size_t idx) const
{
    return _data[idx];
}



//Поиск первого вхождения значения
long long Vector::find(const ValueType& value) const
{
    for(size_t i = 0; i < _size; i++)
    {
        if(_data[i] == value)
        {
            return value;
        }
    }
    
    return -1;
}

//Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
void Vector::reserve(size_t capacity)
{
    if(capacity > _capacity)
    {
        ValueType* newData = new ValueType[capacity];
        std::copy(_data, _data + _size, newData);
        delete[] _data;
        _data = newData;
        _capacity = capacity;
    }
}

//Уменьшить capacity до size
void Vector::shrinkToFit()
{
    if(_capacity > _size)
    {
        ValueType* newData = new ValueType[_size];
        std::copy(_data, _data + _size, newData);
        delete[] _data;
        _data = newData;
        _capacity = _size;
    }
}

//Итераторы
Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*() 
{ 
    return *_ptr; 
}
const ValueType& Vector::Iterator::operator*() const 
{ 
    return *_ptr; 
}

ValueType* Vector::Iterator::operator->() 
{ 
    return _ptr; 
}

const ValueType* Vector::Iterator::operator->() const 
{ 
    return _ptr; 
}


Vector::Iterator Vector::Iterator::operator++() 
{ 
    ++_ptr; return *this; 
}

Vector::Iterator Vector::Iterator::operator++(int) 
{ 
    Iterator temp = *this; ++_ptr; return temp; 
}


bool Vector::Iterator::operator==(const Iterator& other) const 
{ 
    return _ptr == other._ptr; 
}
bool Vector::Iterator::operator!=(const Iterator& other) const 
{ 
    return _ptr != other._ptr; 
}


Vector::Iterator Vector::begin() 
{ 
    return Iterator(_data); 
}
Vector::Iterator Vector::end() 
{ 
    return Iterator(_data + _size); 
}