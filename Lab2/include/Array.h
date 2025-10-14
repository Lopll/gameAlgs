#pragma once

#include <cstdlib>
#include <iostream>

template <typename T>
class Array final
{   
    // private:
    public:
    int capacity = 8;
    int length = 0;
    int* arr;
    
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
        capacity *= 1.6;
        // std::free(arr);
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
    Array(Array& obj)
        : capacity(obj.capacity), length(obj.length)
    {
        arr = static_cast<int*>(std::malloc(sizeof(T) * capacity));
        
        for(int i = 0; i < length; i++)
        {
            arr[i] = T(obj.arr[i]);
        }
    }
    
    ~Array()
    {
        for(int i = 0; i < length; i++)
        {
            arr[i].~T();
        }
        std::free(arr);
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
            increaseCap();
        }
    }
    int insert(int index, const T& value);
    
    void remove(int index);
    
    // Iterator iterator();
    // ConstIterator iterator() const;
    
    // Iterator reverseIterator();
    // ConstIterator reverseIterator() const;
    
    const T& operator[](int index) const;
    T& operator[](int index);
    
    T& operator=(T& obj);
};