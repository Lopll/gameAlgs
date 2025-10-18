#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T>
class Array final
{   
    private:
    // public:
    int capacity = 8;
    int length = 0;
    T* arr;
    
    // class Iterator
    // {
    //     const T& get() const;
    //     void set(const T& value);
    //     void next();
    //     bool hasNext() const;
    // };
    
    // increases capacity and reallocates memory for arr
    void increaseCap()
    {
        // capacity *= 1.6;
        // std::free(arr); std::is_move_constructible_v<Ex1>
        // arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));
    }
    
    public:
    Array()
    {
        arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));
    }
    Array(int cap)
        : capacity(cap)
    {
        arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));
    }
    
    // copy constructor
    Array(const Array& obj)
        : capacity(obj.capacity), length(obj.length)
    {
        std::cout << "Copy Constructor activated" << std::endl;
        arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));
        
        for(int i = 0; i < length; i++)
        {
            arr[i] = obj.arr[i];
        }
    }
    // move constructor
    Array(Array&& obj) noexcept
        : capacity(std::exchange(obj.capacity, 0)), length(std::exchange(obj.length, 0)), arr(std::exchange(obj.arr, nullptr))
    {
        std::cout << "Move Constructor activated" << std::endl;
    }
    
    ~Array()
    {
        if (arr != nullptr)
        {
            for(int i = 0; i < length; i++)
            {
                arr[i].~T();
            }
            std::free(arr);
        }
    }
    
    inline int size() const
    {
        return length;
    }
    
    
    // insert at the end of arr
    int insert(const T& value)
    {
        length++;
        if (length > capacity)
        {
            // increaseCap();
        }
        return 0;
    }
    int insert(int index, const T& value);
    
    void remove(int index);
    
    // Iterator iterator();
    // ConstIterator iterator() const;
    
    // Iterator reverseIterator();
    // ConstIterator reverseIterator() const;
    
    const T& operator[](int index) const;
    T& operator[](int index);
    
    // copy assigment
    Array& operator=(const Array& obj)
    {
        if (this != &obj)
        {
            std::cout << "Copy Assignment activated" << std::endl;
            capacity = obj.capacity;
            length = obj.length;
            
            std::free(arr);
            arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));     
            for(int i = 0; i < length; i++)
            {
                arr[i] = obj.arr[i];
            }
        }
        return *this;
    }
    // move assigment
    Array& operator=(Array&& obj) noexcept
    {
        if (this != &obj)
        {
            std::cout << "Move Assignment activated" << std::endl;
            std::swap(capacity, obj.capacity);
            std::swap(length, obj.length);
            std::swap(arr, obj.arr);
        }
        return *this;
    }
};