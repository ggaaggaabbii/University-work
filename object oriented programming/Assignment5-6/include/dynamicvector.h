#pragma once
#include <bits/stdc++.h>

template <typename T>
class DynamicVector {
  private:
    int capacity;
    int size = 0;
    int index = 0;
    T* vector;

  public:

    class Iter {
        friend class DynamicVector;

      private:
        DynamicVector DV;

      public:
        Iter(DynamicVector& D) {
            this->DV = D;
        }

        T& operator*() {
            return this->DV[this->DV.index];
        }

        bool operator!=(const DynamicVector::Iter& I) {
            if (this->DV.index == this->DV.size)
            { return false; }

            return true;
        }

        void operator++() {
            this->DV.index++;
        }

        ~Iter() {
            return;
        }
    };

    /*
    Basic constructor that builds a new vector
    input: an integer(optional) that represents the initial size of the vector
    */
    DynamicVector(int cap = 10) {
        this->size = 0;
        this->capacity = cap;
        this->vector = new T[this->capacity];
    }

    /*
    Constructor that builds the vector as a copy of an exiting vector
    input: a reference to the other vector
    */
    DynamicVector(const DynamicVector& V) {
        this->size = V.getSize();
        this->capacity = V.getCapacity();
        this->vector = new T[this->capacity];

        for (int i = 0; i < this->size; ++i) {
            this->vector[i] = V[i];
        }
    }

    /*
    the definition of the "=" operator, builds a copy of another vector
    input: a reference to the other vector
    output: a reference to the current vector
    */
    DynamicVector& operator=(const DynamicVector& V) {
        if ((*this) == V) {
            return *this;
        }

        this->size = V.getSize();
        this->capacity = V.getCapacity();
        delete[] this->vector;
        this->vector = new T[this->capacity];

        for (int i = 0; i < this->size; ++i) {
            this->vector[i] = V[i];
        }

        return *this;
    }

    /*
    adds an element to the last position
    input: a new element
    */
    void addElement(const T& element) {
        if (this->capacity == this->size) {
            this->capacity *= 2;
            T* V = new T[this->capacity];

            for (int i = 0; i < this->size; ++i) {
                V[i] = this->vector[i];
            }

            delete[] this->vector;
            this->vector = V;
        }

        this->vector[(this->size)++] = element;
    }

    /*
    deletes the element from the last position
    output: a NULL pointer if there are no elements left in the vector,
            or the element from the last position
    */
    T popElement() {
        if (this->size == 0)
        { return (T)NULL; }

        if (this->size == this->capacity / 4) {
            this->capacity /= 2;
        }

        this->size--;
        return this->vector[this->size + 1];
    }

    /*
    allows the acces to elements by positions
    input: the index of the element
    output: the element from that index
    */
    T& operator[](int index) const {
        if (index >= 0 && index < this->size)
        { return this->vector[index]; }

        return this->vector[0];
    }

    DynamicVector& operator-(T element) {
        for (int i = 0; i < (*this).getSize(); ++i) {
            if (element == this->vector[i]) {
                this->vector[i] = this->vector[(this->size) - 1];
                this->size--;
                break;
            }
        }

        return *this;
    }

    /*
    returns the size of the vector
    */
    int getSize() const {
        return this->size;
    }

    /*
    returns the capacity of the vector
    */
    int getCapacity() const {
        return this->capacity;
    }

    /*
    checks of two vectors are equal(contain the same elements)
    input: another vector
    output: true if they contain the same elements, false otherwise
    */
    bool operator==(const DynamicVector& V) const {
        if (this->size != V.getSize())
        { return false; }

        for (int i = 0; i < this->size; ++i) {
            if (!(this->vector[i] == V[i]))
            { return false; }
        }

        return true;
    }

    Iter begin() {
        this->index = 0;
        return Iter(*this);
    }

    Iter end() {
        return Iter(*this);
    }

    /*
    destroys the vector
    */
    ~DynamicVector() {
        delete[] this->vector;
    }

};
