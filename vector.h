#ifndef UNTITLED14_VECTOR_H
#define UNTITLED14_VECTOR_H
#include <iostream>

template<typename T>
class Vector {
private:
    T* arr;
    size_t size{};
    size_t max_size;
public:
    Vector() {
        arr = new T[1];
        max_size = 1;
    }
    ~Vector() {
        delete[] arr;
    }

    [[nodiscard]] bool isEmpty() const {return size;} // возвращаемое значение нельзя игнорировать
    size_t return_size() {return size;};
    size_t return_max_size() {return max_size;};
    void addMemory () {
        max_size *= 2;
        T* temp = arr;
        arr = new T[max_size];
        for (int i = 0; i < size; i++)
            arr[i] = temp[i];
        delete[] temp;
    }
    void push(T &element) {
        if (size >= max_size) addMemory();
        arr[size++] = element;
    }
    void pop(size_t index) {
        for (size_t i = index; i < size - 1; i++)
            arr[i] = arr[i + 1];
    }

    T &operator[](size_t index) {
        return arr[index];
    }
};

#endif //UNTITLED14_VECTOR_H
