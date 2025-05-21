#include "Vector.h"

// Constructors
Vector::Vector() { 
    sz = 0; 
    cap = 0;
    elem = nullptr;
}

Vector::Vector(int s) {
    if (s < 0) throw std::invalid_argument("Negative size");
    sz = s; 
    cap = s;
    elem = new double[cap]();  // Initialize to zero
}

Vector::Vector(int s, double val) {
    if (s < 0) throw std::invalid_argument("Negative size");
    sz = s; 
    cap = s;
    elem = new double[cap];
    std::fill_n(elem, s, val);  
}

// Copy constructor
Vector::Vector(const Vector& other) {
    sz = other.sz;
    cap = other.cap;
    elem = new double[cap];
    for (int i = 0; i < sz; ++i) {
        elem[i] = other.elem[i];
    }
}

// Move constructor
Vector::Vector(Vector&& other) noexcept {
    sz = other.sz;
    cap = other.cap;
    elem = other.elem;
    
    // Leave other in valid but empty state
    other.sz = 0;
    other.cap = 0;
    other.elem = nullptr;
}

// Copy assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;  // Self-assignment check
    
    if (cap < other.sz) {
        delete[] elem;
        cap = other.sz;
        elem = new double[cap];
    }
    
    sz = other.sz;
    for (int i = 0; i < sz; ++i) {
        elem[i] = other.elem[i];
    }
    
    return *this;
}

// Move assignment operator
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;  // Self-assignment check
    
    delete[] elem;
    
    sz = other.sz;
    cap = other.cap;
    elem = other.elem;
    
    // Leave other in valid but empty state
    other.sz = 0;
    other.cap = 0;
    other.elem = nullptr;
    
    return *this;
}

// Setters
void Vector::setElem(int id, double val) {
    if (id < 0 || id >= sz) {
        throw std::out_of_range("Vector::setElem out of range");
    }
    elem[id] = val;
}

// Getters
int Vector::size() const { return sz; }
int Vector::capacity() const { return cap; }
bool Vector::empty() const { return sz == 0; }

double& Vector::operator[](int i) { 
    if (i < 0 || size() <= i) throw std::out_of_range{"Vector::operator[] out of range"};
    return elem[i]; 
} 

const double& Vector::operator[](int i) const { 
    if (i < 0 || size() <= i) throw std::out_of_range{"Vector::operator[] out of range"};
    return elem[i]; 
}

double& Vector::at(int i) {
    if (i < 0 || size() <= i) throw std::out_of_range{"Vector::at out of range"};
    return elem[i];
}

const double& Vector::at(int i) const {
    if (i < 0 || size() <= i) throw std::out_of_range{"Vector::at out of range"};
    return elem[i];
}

double& Vector::front() {
    if (empty()) throw std::out_of_range{"Vector::front called on empty vector"};
    return elem[0];
}

const double& Vector::front() const {
    if (empty()) throw std::out_of_range{"Vector::front called on empty vector"};
    return elem[0];
}

double& Vector::back() {
    if (empty()) throw std::out_of_range{"Vector::back called on empty vector"};
    return elem[sz-1];
}

const double& Vector::back() const {
    if (empty()) throw std::out_of_range{"Vector::back called on empty vector"};
    return elem[sz-1];
}

// Destructor
Vector::~Vector() { 
    delete[] elem; 
}

// Swaps two elements
void Vector::swap(int i, int j) {
    if (i < 0 || size() <= i || j < 0 || size() <= j) {
        throw std::out_of_range("Vector::swap indices out of range");
    }
    std::swap(elem[i], elem[j]);
}

// Erases the vector (sets size to 0)
void Vector::erase() {
    sz = 0;
    // We keep capacity as is, just like std::vector
}

// Inserts element at position
void Vector::insert(int i, double val) {
    if (i < 0 || size() < i) {
        throw std::out_of_range("Vector::insert index out of range");
    }
    
    if (sz == cap) {
        // Need to allocate more memory
        int new_cap = cap == 0 ? 1 : cap * 2;  // Double capacity
        reserve(new_cap);
    }
    
    // Shift elements to make room
    for (int j = sz; j > i; --j) {
        elem[j] = elem[j-1];
    }
    
    elem[i] = val;
    ++sz;
}

// Removes last element
void Vector::pop_back() {
    if (empty()) throw std::out_of_range("Vector::pop_back called on empty vector");
    --sz;
}

// Clears elements (sets to 0)
void Vector::clear() {
    for (int i = 0; i < sz; ++i) {
        elem[i] = 0;
    }
}

// Changes vector size
void Vector::resize(int s) {
    resize(s, 0.0);  // Default value is 0.0
}

// Changes vector size, fills with val
void Vector::resize(int s, double val) {
    if (s < 0) throw std::invalid_argument("Vector::resize negative size");
    
    if (s > cap) {
        // Need to allocate more memory
        reserve(s);
    }
    
    // If expanding, initialize new elements
    for (int i = sz; i < s; ++i) {
        elem[i] = val;
    }
    
    sz = s;
}

// Reserves capacity
void Vector::reserve(int new_cap) {
    if (new_cap <= cap) return;  // Nothing to do
    
    double* new_elem = new double[new_cap];
    
    // Copy existing elements
    for (int i = 0; i < sz; ++i) {
        new_elem[i] = elem[i];
    }
    
    delete[] elem;
    elem = new_elem;
    cap = new_cap;
}

// Adds element to the end
void Vector::push_back(double val) {
    if (sz == cap) {
        // Need to allocate more memory with growth factor
        int new_cap = cap == 0 ? 1 : cap * 2;  // Double capacity
        reserve(new_cap);
    }
    
    elem[sz] = val;
    ++sz;
}

// Reduces capacity to fit size
void Vector::shrink_to_fit() {
    if (sz == cap) return;  // Already fit
    
    if (sz == 0) {
        delete[] elem;
        elem = nullptr;
        cap = 0;
        return;
    }
    
    double* new_elem = new double[sz];
    for (int i = 0; i < sz; ++i) {
        new_elem[i] = elem[i];
    }
    
    delete[] elem;
    elem = new_elem;
    cap = sz;
}