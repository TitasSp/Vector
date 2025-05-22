#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <iterator>
#include <type_traits>
#include <memory>

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

    // Helper function to allocate uninitialized memory
    pointer allocate(size_type n) {
        if (n == 0) return nullptr;
        return static_cast<pointer>(operator new(n * sizeof(value_type)));
    }
    
    // Helper function to deallocate memory
    void deallocate(pointer p, size_type n) noexcept {
        if (p) operator delete(p);
    }
    
    // Helper function to construct elements
    template<typename... Args>
    void construct(pointer p, Args&&... args) {
        new (p) value_type(std::forward<Args>(args)...);
    }
    
    // Helper function to destroy elements
    void destroy(pointer p) noexcept {
        p->~value_type();
    }
    
    // Helper function to destroy a range of elements
    void destroy_range(pointer first, pointer last) noexcept {
        for (; first != last; ++first) {
            destroy(first);
        }
    }
    
    // Helper function to move elements and handle reallocation properly
    void reallocate(size_type new_cap) {
        pointer new_elem = allocate(new_cap);
        
        // Move construct elements to new location
        size_type i = 0;
        try {
            for (; i < sz; ++i) {
                construct(new_elem + i, std::move(elem[i]));
            }
        } catch (...) {
            // If construction fails, destroy already constructed elements
            destroy_range(new_elem, new_elem + i);
            deallocate(new_elem, new_cap);
            throw;
        }
        
        // Destroy old elements and deallocate
        destroy_range(elem, elem + sz);
        deallocate(elem, cap);
        
        elem = new_elem;
        cap = new_cap;
    }

public:
    // Constructors
    Vector() noexcept : sz(0), cap(0), elem(nullptr) {}
    
    explicit Vector(size_type s)
        : sz(s), cap(s), elem(allocate(s)) {
        for (size_type i = 0; i < s; ++i) {
            try {
                construct(elem + i);
            } catch (...) {
                destroy_range(elem, elem + i);
                deallocate(elem, cap);
                throw;
            }
        }
    }
    
    Vector(size_type s, const value_type& val)
        : sz(s), cap(s), elem(allocate(s)) {
        for (size_type i = 0; i < s; ++i) {
            try {
                construct(elem + i, val);
            } catch (...) {
                destroy_range(elem, elem + i);
                deallocate(elem, cap);
                throw;
            }
        }
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
        : sz(init.size()), cap(init.size()), elem(allocate(init.size())) {
        size_type i = 0;
        try {
            for (auto it = init.begin(); it != init.end(); ++it, ++i) {
                construct(elem + i, *it);
            }
        } catch (...) {
            destroy_range(elem, elem + i);
            deallocate(elem, cap);
            throw;
        }
    }
    
    // Copy constructor
    Vector(const Vector& other)
        : sz(other.sz), cap(other.sz), elem(allocate(other.sz)) {
        for (size_type i = 0; i < sz; ++i) {
            try {
                construct(elem + i, other.elem[i]);
            } catch (...) {
                destroy_range(elem, elem + i);
                deallocate(elem, cap);
                throw;
            }
        }
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
        if (this == &other) return *this;
        
        if (other.sz <= cap) {
            // Reuse existing capacity
            size_type common = std::min(sz, other.sz);
            
            // Copy assign to existing elements
            for (size_type i = 0; i < common; ++i) {
                elem[i] = other.elem[i];
            }
            
            // Copy construct new elements if other is larger
            for (size_type i = common; i < other.sz; ++i) {
                construct(elem + i, other.elem[i]);
            }
            
            // Destroy excess elements if we're larger
            destroy_range(elem + other.sz, elem + sz);
            
            sz = other.sz;
        } else {
            // Need to reallocate
            Vector temp(other);
            swap(temp);
        }
        
        return *this;
    }
    
    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        
        destroy_range(elem, elem + sz);
        deallocate(elem, cap);
        
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
        if (count <= cap) {
            size_type common = std::min(sz, count);
            
            // Assign to existing elements
            std::fill_n(elem, common, value);
            
            // Construct new elements if needed
            for (size_type i = common; i < count; ++i) {
                construct(elem + i, value);
            }
            
            // Destroy excess elements
            destroy_range(elem + count, elem + sz);
        } else {
            Vector temp(count, value);
            swap(temp);
        }
        sz = count;
    }
    
    template<typename InputIt,
             typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    void assign(InputIt first, InputIt last) {
        // For input iterators, we can't know the distance in advance
        if constexpr (std::is_same_v<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>) {
            clear();
            for (; first != last; ++first) {
                push_back(*first);
            }
        } else {
            // For forward iterators and above, we can calculate distance
            auto count = std::distance(first, last);
            if (count < 0) throw std::invalid_argument("Invalid iterator range");
            
            if (static_cast<size_type>(count) <= cap) {
                size_type new_size = static_cast<size_type>(count);
                size_type common = std::min(sz, new_size);
                
                // Copy assign to existing elements
                auto it = first;
                for (size_type i = 0; i < common; ++i, ++it) {
                    elem[i] = *it;
                }
                
                // Copy construct new elements
                for (size_type i = common; i < new_size; ++i, ++it) {
                    construct(elem + i, *it);
                }
                
                // Destroy excess elements
                destroy_range(elem + new_size, elem + sz);
                
                sz = new_size;
            } else {
                Vector temp(first, last);
                swap(temp);
            }
        }
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
    
    reference operator[](size_type pos) noexcept {
        return elem[pos];
    }
    
    const_reference operator[](size_type pos) const noexcept {
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
        reallocate(new_cap);
    }
    
    size_type capacity() const noexcept {
        return cap;
    }
    
    void shrink_to_fit() {
        if (sz == cap) return;
        
        if (sz == 0) {
            destroy_range(elem, elem + sz);
            deallocate(elem, cap);
            elem = nullptr;
            cap = 0;
        } else {
            reallocate(sz);
        }
    }
    
    // Modifiers
    void clear() noexcept {
        destroy_range(elem, elem + sz);
        sz = 0;
    }
    
    iterator insert(const_iterator pos, const value_type& value) {
        return emplace(pos, value);
    }
    
    iterator insert(const_iterator pos, value_type&& value) {
        return emplace(pos, std::move(value));
    }
    
    iterator insert(const_iterator pos, size_type count, const value_type& value) {
        if (count == 0) return const_cast<iterator>(pos);
        
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        if (sz + count > cap) {
            size_type new_cap = std::max(cap == 0 ? 1 : cap * 2, sz + count);
            
            // Allocate new memory
            pointer new_elem = allocate(new_cap);
            
            try {
                // Move construct elements before insertion point
                for (size_type i = 0; i < position; ++i) {
                    construct(new_elem + i, std::move(elem[i]));
                }
                
                // Construct new elements
                for (size_type i = 0; i < count; ++i) {
                    construct(new_elem + position + i, value);
                }
                
                // Move construct elements after insertion point
                for (size_type i = position; i < sz; ++i) {
                    construct(new_elem + i + count, std::move(elem[i]));
                }
            } catch (...) {
                // Clean up on exception
                destroy_range(new_elem, new_elem + position + count + (sz - position));
                deallocate(new_elem, new_cap);
                throw;
            }
            
            // Clean up old storage
            destroy_range(elem, elem + sz);
            deallocate(elem, cap);
            
            elem = new_elem;
            cap = new_cap;
        } else {
            // Sufficient capacity, shift elements in place
            
            // Move construct new elements at the end
            for (size_type i = sz; i < sz + count; ++i) {
                construct(elem + i, value);
            }
            
            // Move existing elements to make room
            for (size_type i = sz - 1; i != SIZE_MAX && i >= position; --i) {
                elem[i + count] = std::move(elem[i]);
            }
            
            // Fill the gap with new values
            for (size_type i = position; i < position + std::min(count, sz - position); ++i) {
                elem[i] = value;
            }
        }
        
        sz += count;
        return begin() + position;
    }
    
    template<typename InputIt,
             typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type position = pos - begin();
        if (position > sz) throw std::out_of_range("Vector::insert position out of range");
        
        // For input iterators, insert one by one
        if constexpr (std::is_same_v<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>) {
            auto current_pos = const_cast<iterator>(pos);
            for (; first != last; ++first) {
                current_pos = insert(current_pos, *first) + 1;
            }
            return begin() + position;
        } else {
            // For forward+ iterators, we can calculate distance
            auto count = std::distance(first, last);
            if (count <= 0) return const_cast<iterator>(pos);
            
            size_type num_elements = static_cast<size_type>(count);
            
            if (sz + num_elements > cap) {
                size_type new_cap = std::max(cap == 0 ? 1 : cap * 2, sz + num_elements);
                
                pointer new_elem = allocate(new_cap);
                
                try {
                    // Move construct elements before insertion
                    for (size_type i = 0; i < position; ++i) {
                        construct(new_elem + i, std::move(elem[i]));
                    }
                    
                    // Copy construct new elements
                    size_type j = 0;
                    for (auto it = first; it != last; ++it, ++j) {
                        construct(new_elem + position + j, *it);
                    }
                    
                    // Move construct elements after insertion
                    for (size_type i = position; i < sz; ++i) {
                        construct(new_elem + i + num_elements, std::move(elem[i]));
                    }
                } catch (...) {
                    destroy_range(new_elem, new_elem + position + num_elements + (sz - position));
                    deallocate(new_elem, new_cap);
                    throw;
                }
                
                destroy_range(elem, elem + sz);
                deallocate(elem, cap);
                
                elem = new_elem;
                cap = new_cap;
            } else {
                // Sufficient capacity
                
                // Move construct at the end
                for (size_type i = sz; i < sz + num_elements; ++i) {
                    construct(elem + i, value_type{});
                }
                
                // Move existing elements
                for (size_type i = sz - 1; i != SIZE_MAX && i >= position; --i) {
                    elem[i + num_elements] = std::move(elem[i]);
                }
                
                // Copy new elements
                size_type j = 0;
                for (auto it = first; it != last; ++it, ++j) {
                    elem[position + j] = *it;
                }
            }
            
            sz += num_elements;
            return begin() + position;
        }
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
            
            pointer new_elem = allocate(new_cap);
            
            try {
                // Move construct elements before insertion point
                for (size_type i = 0; i < position; ++i) {
                    construct(new_elem + i, std::move(elem[i]));
                }
                
                // Construct new element
                construct(new_elem + position, std::forward<Args>(args)...);
                
                // Move construct elements after insertion point
                for (size_type i = position; i < sz; ++i) {
                    construct(new_elem + i + 1, std::move(elem[i]));
                }
            } catch (...) {
                destroy_range(new_elem, new_elem + position + 1 + (sz - position));
                deallocate(new_elem, new_cap);
                throw;
            }
            
            destroy_range(elem, elem + sz);
            deallocate(elem, cap);
            
            elem = new_elem;
            cap = new_cap;
        } else {
            // Shift elements to make room
            construct(elem + sz, std::move(elem[sz - 1]));
            
            for (size_type i = sz - 1; i > position; --i) {
                elem[i] = std::move(elem[i - 1]);
            }
            
            // Construct or assign new element
            if (position < sz) {
                elem[position] = value_type(std::forward<Args>(args)...);
            } else {
                construct(elem + position, std::forward<Args>(args)...);
            }
        }
        
        ++sz;
        return begin() + position;
    }
    
    iterator erase(const_iterator pos) {
        size_type position = pos - begin();
        if (position >= sz) throw std::out_of_range("Vector::erase position out of range");
        
        // Move elements to fill the gap
        for (size_type i = position; i < sz - 1; ++i) {
            elem[i] = std::move(elem[i + 1]);
        }
        
        // Destroy the last element
        destroy(elem + sz - 1);
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
        for (size_type i = start; i < sz - count; ++i) {
            elem[i] = std::move(elem[i + count]);
        }
        
        // Destroy elements at the end
        destroy_range(elem + sz - count, elem + sz);
        sz -= count;
        
        return begin() + start;
    }
    
    void push_back(const value_type& value) {
        emplace_back(value);
    }
    
    void push_back(value_type&& value) {
        emplace_back(std::move(value));
    }
    
    template<typename... Args>
    reference emplace_back(Args&&... args) {
        if (sz == cap) {
            size_type new_cap = cap == 0 ? 1 : cap * 2;
            reserve(new_cap);
        }
        
        construct(elem + sz, std::forward<Args>(args)...);
        ++sz;
        
        return elem[sz - 1];
    }
    
    void pop_back() {
        if (empty()) throw std::out_of_range("Vector::pop_back called on empty vector");
        --sz;
        destroy(elem + sz);
    }
    
    void resize(size_type count) {
        resize(count, value_type());
    }
    
    void resize(size_type count, const value_type& value) {
        if (count > sz) {
            if (count > cap) {
                reserve(count);
            }
            
            // Construct new elements
            for (size_type i = sz; i < count; ++i) {
                construct(elem + i, value);
            }
        } else if (count < sz) {
            // Destroy excess elements
            destroy_range(elem + count, elem + sz);
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
        destroy_range(elem, elem + sz);
        deallocate(elem, cap);
    }
};

// Non-member functions
template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
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