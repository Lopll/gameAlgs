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
    
    // increases capacity
    void increaseCap()
    {
        std::cout << "Increasing capacity" << std::endl;
        Array<T> temp = std::move(*this);
        capacity = temp.capacity * 1.6;
        length = temp.length;
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));

        Iterator iter = iterator();
        Iterator tIter = temp.iterator();
        while(iter.hasNext())
        {   
            iter.set(tIter.get());
            iter.next();
            tIter.next();
        }
        iter.set(tIter.get());
        std::cout << "Increased capacity from " << temp.capacity << " to " << capacity << std::endl;
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
        std::cout << "Copy Constructor activated" << std::endl;
        arr = static_cast<T*>(std::malloc(sizeof(T) * capacity));
        
        for(int i = 0; i < length; i++)
        {
            // arr[i] = obj.arr[i];
            new(&arr[i]) T(obj.arr[i]);
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
        std::cout<<"Destructor\n";
        if (arr != nullptr)
        {
            for(int i = 0; i < length; i++)
            {
                arr[i].~T();
            }
            std::free(arr);
        }
    }
    
    // copy and swap assigment
    Array& operator=(Array obj) noexcept
    {
        if (this != obj)
        {
            std::cout << "Copy-and-Swap Assignment activated" << std::endl;
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
        
        new(&arr[length]) T(value);
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
        
        Iterator iter = reverseIterator();
        Iterator tIter = reverseIterator();
        tIter.prev();
        for(int i = length; i > index; i--, iter.prev(), tIter.prev())
        {
            iter.set(tIter.get());
        }
        // insert
        iter.set(value);
        return index;
    }
    
    void remove(int index)
    {
        if(length == 0)
            return;
        Iterator iter = iterator();
        Iterator nIter = iterator();
        nIter.next();
        while(nIter.hasNext() && iter.get() != arr[index])
        {
            iter.next();
            nIter.next();
        }
        while(nIter.hasNext())
        {
            iter.set(nIter.get());
            iter.next();
            nIter.next();
        }
        iter.set(T());
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
        void set(const T& value)
        {
            if constexpr(std::is_move_constructible_v<T>)
            {
                new(&parent.arr[index]) T(std::move(value));
            }
            else
            {
                new(&parent.arr[index]) T(value);
            }
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
