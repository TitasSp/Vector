#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

class Vector {
private:
    int cap;        // capacity
    int sz;         // number of elements
    double* elem;   // pointer to elements

public:
    // Constructors  
    Vector();
    Vector(int s);
    Vector(int s, double val);
    
    Vector(const Vector& other);// Copy constructor
    Vector(Vector&& other) noexcept;// Move constructor  
    Vector& operator=(const Vector& other);// Copy assignment operator
    Vector& operator=(Vector&& other) noexcept;// Move assignment operator
    
    // Setters
    void setElem(int id, double val);
    
    // Getters
    int size() const;
    int capacity() const;
    bool empty() const;
    double& operator[](int i);
    const double& operator[](int i) const;
    double& at(int i);
    const double& at(int i) const;
    double& front();
    const double& front() const;
    double& back();
    const double& back() const;
    
    // Destructor
    ~Vector();

    // Functions
    void swap(int i, int j);           // Swaps two elements
    void erase();                      // Erases vector (sets size to 0)
    void insert(int i, double val);    // Inserts element at position
    void pop_back();                   // Removes last element
    void clear();                      // Clears elements (sets to 0)
    void resize(int s);                // Changes vector size
    void resize(int s, double val);    // Changes vector size, fills with val
    void reserve(int new_cap);         // Reserves capacity
    void push_back(double val);        // Adds element to the end
    void shrink_to_fit();              // Reduces capacity to fit size
};