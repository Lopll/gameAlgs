#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T>
class Array final
{   
private:
    int capacity = 8;
    int length = 0;
    T* arr;
    
    void set(int index, T&& value)
    {
        new(&arr[index]) T(value);
    }
    
    void set(int index, const T& value)
    {
        new(&arr[index]) T(value);
    }
    
    // increases capacity
    void increaseCap()
    {
        capacity *= 1.6;
        T* temp = arr;
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));
        
        for(int i = 0; i < length; i++)
        {
            set(i, std::move(temp[i]));
            temp[i].~T();
        }
        std::free(temp);
    }
    
    
    
public:
    Array()
    {
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));
    }
    Array(int cap)
        : capacity(cap)
    {
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));
    }
    
    // copy constructor
    Array(const Array& obj)
        : capacity(obj.capacity), length(obj.length)
    {
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));
        
        for(int i = 0; i < length; i++)
        {
            std::construct_at(&arr[i], obj.arr[i]);
        }
    }
    
    // move constructor
    Array(Array&& obj) noexcept
        : capacity(std::exchange(obj.capacity, 0)), length(std::exchange(obj.length, 0)), arr(std::exchange(obj.arr, nullptr))
    {
    }
    
    ~Array()
    {
        if (arr != nullptr)
        {
            for(int i = 0; i < length; i++)
            {
                std::destroy_at(&arr[i]);
            }
            std::free(arr);
        }
    }
    
    // copy and swap assigment
    Array& operator=(Array obj) noexcept
    {
        if (this != obj)
        {
            std::swap(capacity, obj.capacity);
            std::swap(length, obj.length);
            std::swap(arr, obj.arr);
        }
        return *this;
    }
    
    const T& operator[](int index) const
    {
        return arr[index];
    }
    
    T& operator[](int index)
    {
        return arr[index];
    }
    
    inline int size() const
    {
        return length;
    }
    
    inline int getCapacity() const
    {
        return capacity;
    }
    
    inline T* getArr() const
    {
        return arr;
    }
    
    // insert at the end of arr
    int insert(const T& value)
    {
        if (length+1 >= capacity)
        {
            increaseCap();
        }
        
        set(length, std::move(value));
        
        length++;
        return length-1;
    }
    
    int insert(int index, const T& value)
    {
        if (length+1 >= capacity)
        {
            increaseCap();
        }
        length++;
        
        for(int i = length-1; i > index; i--)
        {
            set(i, std::move(arr[i-1]));
            arr[index].~T();
        }
        set(index, value);
        
        return index;
    }
    
    void remove(int index)
    {
        if(length == 0)
            return;
        for(int i = index; i<length-1; i++)
        {
            set(i, std::move(arr[i+1]));
            arr[index].~T();
        }
        length--;
    }
    
    void print()
    {
        
        std::cout << "\n----------\nCapacity: " << capacity<< std::endl << "Length: " << length << std::endl << "Arr: " << arr << std::endl;
        std::cout << "{ ";
        
        for(int i = 0; i < std::min(length, capacity); i++)
        {
            std::cout << arr[i] << " ";
        }
        
        std::cout << "}\n----------" << std::endl;
    }
    
    
    class Iterator
    {
    private:
        Array<T>& parent;
        int index;
        
    public:
        Iterator(Array<T>& p, int i) : parent(p), index(i){}
        
        const T& get() const
        {
            return parent.arr[index];
        }
        
        void set(T&& value)
        {
            parent.set(index, value);
        }
        
        void set(const T& value)
        {
            parent.set(index, value);
        }
        
        void next()
        {
            index++;
        }
        
        void prev()
        {
            index--;
        }
        
        bool hasNext() const
        {
            return index+1 < parent.length;
        }
        
        bool hasPrev() const
        {
            return index-1 >= 0;
        }
    };
    class ConstIterator
    {
    private:
        const Array<T>& parent;
        int index;
        
    public:
        ConstIterator(const Array<T>& p, int i) : parent(p), index(i){}
        const T& get() const
        {
            return parent.arr[index];
        }
        
        void next()
        {
            index++;
        }
        
        void prev()
        {
            index--;
        }
        
        bool hasNext() const
        {
            return index+1 < parent.length;
        }
        
        bool hasPrev() const
        {
            return index-1 >= 0;
        }
    };
    
    Iterator iterator()
    {
        return Iterator(*this, 0);
    }
    
    ConstIterator iterator() const
    {
        return ConstIterator(*this, 0);
    }
    
    Iterator reverseIterator()
    {
        return Iterator(*this, length-1);
    }
    
    ConstIterator reverseIterator() const
    {
        return ConstIterator(*this, length-1);
    }
};
