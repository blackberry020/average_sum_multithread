#pragma once

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
        array = ref.array;
        arraySize = ref.arraySize;
    }

    ~Array() {
        delete[] array;
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

    Array operator = (Array ref)
    {
        array = ref.array;
        arraySize = ref.arraySize;
        return *this;
    }

private:
    T* array;
    int arraySize;
};