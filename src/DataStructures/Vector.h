//
// Created by jimmy on 18/05/24.
//

#ifndef SELDA_VECTOR_H
#define SELDA_VECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T *data; // Puntero al array de elementos
    size_t capacity; // Capacidad actual del vector
    size_t size; // Tamaño actual del vector

    void resize(size_t new_capacity) {
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Constructor por defecto
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Función para añadir elementos al final del vector
    void push_back(const T &value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        data[size++] = value;
    }

    // Función para acceder a los elementos por índice
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

    // Función que devuelve el tamaño del vector
    size_t getSize() const {
        return size;
    }

    // Función que devuelve la capacidad del vector
    size_t getCapacity() const {
        return capacity;
    }

    // Método que devuelve si el vector está vacío
    bool empty() const {
        return size == 0;
    }

    T* begin() {
        return data;
    }

    // Método que devuelve un iterador al final del vector
    T* end() {
        return data + size;
    }
};



#endif //SELDA_VECTOR_H
