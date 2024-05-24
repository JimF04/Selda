#ifndef SELDA_VECTOR_H
#define SELDA_VECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T *data;
    size_t capacity;
    size_t size;

public:
    // Constructor por defecto
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Constructor de copia
    Vector(const Vector& other) : data(nullptr), capacity(0), size(0) {
        *this = other;
    }

    // Operador de asignación
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }


    void push_back(const T &value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        data[size] = value;
        size++;
    }


    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Índice fuera de rango");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Índice fuera de rango");
        }
        return data[index];
    }


    size_t getSize() const {
        return size;
    }


    size_t getCapacity() const {
        return capacity;
    }


    bool empty() const {
        return size == 0;
    }


    T* begin() {
        return data;
    }


    T* end() {
        return data + size;
    }


    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Índice fuera de rango");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    void resize(size_t new_capacity) {
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

#endif //SELDA_VECTOR_H
