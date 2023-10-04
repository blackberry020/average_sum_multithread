#pragma once

#include "ArrayError.h"

template <typename T>
class Array {
public:

    Array() {
        arraySize = 0;
        array = nullptr;
    }

    Array(const int _size) : arraySize(_size) {
        array = new T[_size];
    };

    Array(const Array& ref)
    {
        array = new T[ref.arraySize];
        arraySize = ref.arraySize;
        
        copyElements(*this, ref);
    }

    ~Array() {
        delete array;
    }

    void printArray() {
        for (int i = 0; i < arraySize; i++) {
            std::cout << array[i] << " ";
        }
    }

    void readArray() {

        for (int i = 0; i < arraySize; i++) {
            std::cin >> array[i];
        }
    }

    T& operator[](const int index) {
        return array[index];
    }

    Array& operator = (const Array& ref)
    {
        if (this != &ref) {
            delete array;

            arraySize = ref.arraySize;
            array = new T[arraySize];

            copyElements(*this, ref);
        }

        return *this;
    }

private:
    T* array;
    int arraySize;

    void copyElements(Array& array1, const Array& array2) {

        if (array1.arraySize != array2.arraySize) {
            throw ArrayError("If you copy an array to another one their sizes must be equal");
        }

        for (int i = 0; i < array1.arraySize; i++) {
            array1.array[i] = array2.array[i];
        }
    }
};