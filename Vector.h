#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <iterator>
#include <type_traits>

template <typename T>
class Vector {
public:
    // Type definitions
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    size_type cap;    // capacity
    size_type sz;     // size (number of elements)
    pointer elem;     // pointer to elements

public:
    // Constructors
    Vector() noexcept : sz(0), cap(0), elem(nullptr) {}
    
    explicit Vector(size_type s)
        : sz(s), cap(s), elem(s > 0 ? new value_type[s]() : nullptr) {
        if (s < 0) throw std::invalid_argument("Negative size");
    }
    
    Vector(size_type s, const value_type& val)
        : sz(s), cap(s), elem(s > 0 ? new value_type[s] : nullptr) {
        if (s < 0) throw std::invalid_argument("Negative size");
        std::fill_n(elem, s, val);
    }
    
    // Range constructor
    template<typename InputIt,
             typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    Vector(InputIt first, InputIt last)
        : sz(0), cap(0), elem(nullptr) {
        assign(first, last);
    }
    
    // Initializer list constructor
    Vector(std::initializer_list<value_type> init)
        : sz(init.size()), cap(init.size()), 
          elem(init.size() > 0 ? new value_type[init.size()] : nullptr) {
        std::copy(init.begin(), init.end(), elem);
    }
    
    // Copy constructor
    Vector(const Vector& other)
        : sz(other.sz), cap(other.sz), 
          elem(other.sz > 0 ? new value_type[other.sz] : nullptr) {
        std::copy(other.elem, other.elem + other.sz, elem);
    }
    
    // Move constructor
    Vector(Vector&& other) noexcept
        : sz(other.sz), cap(other.cap), elem(other.elem) {
        other.sz = 0;
        other.cap = 0;
        other.elem = nullptr;
    }
    
    // Copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;  // Self-assignment check
        
        if (cap < other.sz) {
            delete[] elem;
            cap = other.sz;
            elem = new value_type[cap];
        }
        
        sz = other.sz;
        std::copy(other.elem, other.elem + other.sz, elem);
        
        return *this;
    }
    
    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;  // Self-assignment check
        
        delete[] elem;
        
        sz = other.sz;
        cap = other.cap;
        elem = other.elem;
        
        other.sz = 0;
        other.cap = 0;
        other.elem = nullptr;
        
        return *this;
    }
    
    // Initializer list assignment
    Vector& operator=(std::initializer_list<value_type> ilist) {
        assign(ilist.begin(), ilist.end());
        return *this;
    }
    
    // Assign operations
    void assign(size_type count, const value_type& value) {
        if (count > cap) {
            delete[] elem;
            cap = count;
            elem = new value_type[cap];
        }
        sz = count;
        std::fill_n(elem, count, value);
    }
    
    template<typename InputIt,
             typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    void assign(InputIt first, InputIt last) {
        // Calculate distance between iterators
        difference_type count = std::distance(first, last);
        if (count < 0) throw std::invalid_argument("Invalid iterator range");
        
        if (static_cast<size_type>(count) > cap) {
            delete[] elem;
            cap = count;
            elem = new value_type[cap];
        }
        sz = count;
        std::copy(first, last, elem);
    }
    
    void assign(std::initializer_list<value_type> ilist) {
        assign(ilist.begin(), ilist.end());
    }
    
    // Element access
    reference at(size_type pos) {
        if (pos >= sz) throw std::out_of_range("Vector::at out of range");
        return elem[pos];
    }
    
    const_reference at(size_type pos) const {
        if (pos >= sz) throw std::out_of_range("Vector::at out of range");
        return elem[pos];
    }
    
    reference operator[](size_type pos) {
        return elem[pos];
    }
    
    const_reference operator[](size_type pos) const {
        return elem[pos];
    }
    
    reference front() {
        if (empty()) throw std::out_of_range("Vector::front called on empty vector");
        return elem[0];
    }
    
    const_reference front() const {
        if (empty()) throw std::out_of_range("Vector::front called on empty vector");
        return elem[0];
    }
    
    reference back() {
        if (empty()) throw std::out_of_range("Vector::back called on empty vector");
        return elem[sz-1];
    }
    
    const_reference back() const {
        if (empty()) throw std::out_of_range("Vector::back called on empty vector");
        return elem[sz-1];
    }
    
    pointer data() noexcept {
        return elem;
    }
    
    const_pointer data() const noexcept {
        return elem;
    }
    
    // Iterators
    iterator begin() noexcept {
        return elem;
    }
    
    const_iterator begin() const noexcept {
        return elem;
    }
    
    const_iterator cbegin() const noexcept {
        return elem;
    }
    
    iterator end() noexcept {
        return elem + sz;
    }
    
    const_iterator end() const noexcept {
        return elem + sz;
    }
    
    const_iterator cend() const noexcept {
        return elem + sz;
    }
    
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }
    
    // Capacity
    bool empty() const noexcept {
        return sz == 0;
    }
    
    size_type size() const noexcept {
        return sz;
    }
    
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    
    void reserve(size_type new_cap) {
        if (new_cap <= cap) return;
        
        pointer new_elem = new value_type[new_cap];
        
        for (size_type i = 0; i < sz; ++i) {
            new_elem[i] = std::move(elem[i]);
        }
        
        delete[] elem;
        elem = new_elem;
        cap = new_cap;
    }
    
    size_type capacity() const noexcept {
        return cap;
    }
    
    void shrink_to_fit() {
        if (sz == cap) return;
        
        if (sz == 0) {
            delete[] elem;
            elem = nullptr;
            cap = 0;
            return;
        }
        
        pointer new_elem = new value_type[sz];
        for (size_type i = 0; i < sz; ++i) {
            new_elem[i] = std::move(elem[i]);
        }
        
        delete[] elem;
        elem = new_elem;
        cap = sz;
    }
    
    // Modifiers
    void clear() noexcept {
        // Proper cleanup for non-trivial types
        for (size_type i = 0; i < sz; ++i) {
            elem[i].~value_type();
        }
        sz = 0;
    }
    
    iterator insert(const_iterator pos, const value_type& value) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        // Move elements to make space
        for (size_type i = sz; i > position; --i) {
            elem[i] = std::move(elem[i-1]);
        }
        
        elem[position] = value;
        ++sz;
        
        return begin() + position;
    }
    
    iterator insert(const_iterator pos, value_type&& value) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        // Move elements to make space
        for (size_type i = sz; i > position; --i) {
            elem[i] = std::move(elem[i-1]);
        }
        
        elem[position] = std::move(value);
        ++sz;
        
        return begin() + position;
    }
    
    iterator insert(const_iterator pos, size_type count, const value_type& value) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        if (sz + count > cap) {
            size_type new_cap = std::max(cap * 2, sz + count);
            reserve(new_cap);
        }
        
        // Move elements to make space
        for (size_type i = sz + count - 1; i >= position + count; --i) {
            elem[i] = std::move(elem[i-count]);
        }
        
        // Insert the new elements
        for (size_type i = 0; i < count; ++i) {
            elem[position + i] = value;
        }
        
        sz += count;
        return begin() + position;
    }
    
    template<typename InputIt,
             typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        size_type count = std::distance(first, last);
        
        if (sz + count > cap) {
            size_type new_cap = std::max(cap * 2, sz + count);
            reserve(new_cap);
        }
        
        // Move elements to make space
        for (size_type i = sz + count - 1; i >= position + count; --i) {
            elem[i] = std::move(elem[i-count]);
        }
        
        // Insert the new elements
        std::copy(first, last, begin() + position);
        
        sz += count;
        return begin() + position;
    }
    
    iterator insert(const_iterator pos, std::initializer_list<value_type> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }
    
    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::emplace position out of range");
        
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        // Move elements to make space
        for (size_type i = sz; i > position; --i) {
            elem[i] = std::move(elem[i-1]);
        }
        
        // Construct element in-place
        new (&elem[position]) value_type(std::forward<Args>(args)...);
        ++sz;
        
        return begin() + position;
    }
    
    iterator erase(const_iterator pos) {
        size_type position = pos - begin();
        if (position >= sz) throw std::out_of_range("Vector::erase position out of range");
        
        // Move elements to fill the gap
        for (size_type i = position; i < sz - 1; ++i) {
            elem[i] = std::move(elem[i+1]);
        }
        
        // Destroy the last element
        elem[sz-1].~value_type();
        --sz;
        
        return begin() + position;
    }
    
    iterator erase(const_iterator first, const_iterator last) {
        size_type start = first - begin();
        size_type finish = last - begin();
        
        if (start > sz || finish > sz || start > finish) {
            throw std::out_of_range("Vector::erase range out of range");
        }
        
        size_type count = finish - start;
        if (count == 0) return begin() + start;
        
        // Move elements to fill the gap
        for (size_type i = start; i <= sz - count - 1; ++i) {
            elem[i] = std::move(elem[i+count]);
        }
        
        // Destroy the remaining elements
        for (size_type i = sz - count; i < sz; ++i) {
            elem[i].~value_type();
        }
        
        sz -= count;
        return begin() + start;
    }
    
    void push_back(const value_type& value) {
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        elem[sz] = value;
        ++sz;
    }
    
    void push_back(value_type&& value) {
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        elem[sz] = std::move(value);
        ++sz;
    }
    
    template<typename... Args>
    reference emplace_back(Args&&... args) {
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        // Construct element in-place
        new (&elem[sz]) value_type(std::forward<Args>(args)...);
        ++sz;
        
        return elem[sz-1];
    }
    
    void pop_back() {
        if (empty()) throw std::out_of_range("Vector::pop_back called on empty vector");
        --sz;
        elem[sz].~value_type(); // Destroy the removed element
    }
    
    void resize(size_type count) {
        resize(count, value_type());
    }
    
    void resize(size_type count, const value_type& value) {
        if (count > sz) {
            if (count > cap) {
                reserve(count);
            }
            
            // Initialize new elements
            for (size_type i = sz; i < count; ++i) {
                elem[i] = value;
            }
        } else if (count < sz) {
            // Destroy removed elements
            for (size_type i = count; i < sz; ++i) {
                elem[i].~value_type();
            }
        }
        
        sz = count;
    }
    
    void swap(Vector& other) noexcept {
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        std::swap(elem, other.elem);
    }
    
    // Destructor
    ~Vector() {
        clear();
        delete[] elem;
    }
};

// Non-member functions
template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (typename Vector<T>::size_type i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}

template<typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

template<typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

template<typename T>
void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}