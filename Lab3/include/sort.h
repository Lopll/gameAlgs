#include <iostream>

int INSERTION_THRESHOLD = 32;

void setInsertThreshold(int it)
{
    INSERTION_THRESHOLD = it;
}

template<typename T>
bool comp(const T &a, const T &b);

template<typename T>
void print(T* first, T* last)
{
    for(T* i = first; i <= last; i++)
    {
        std::cout << *i << " ";
    }
    std::cout<<std::endl;
}

template<typename T>
void swap(T* a, T* b) {
    T temp = std::move(*a);
    *a = std::move(*b);
    *b = std::move(temp);
}

template<typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp)
{
    int len = last - first + 1;
    for(int i = 1; i < len; i++)
    {
        T key = std::move(*(first+i));
        int j = i-1;
        while(j >= 0 && comp(key, *(first+j)))
        {
            *(first+j+1) = std::move(*(first+j));
            j--;
        }
        *(first+j+1) = std::move(key);
    }
}

template<typename T>
T* med(T* first, T* last)
{
    T* middle = first + (last - first) / 2;
    T a = *first, b = *middle, c = *last;
    if ((a > b && a < c) || (a < b && a > c)) {
        return first;
    } else if ((b > a && b < c) || (b < a && b > c)) {
        return middle;
    } else {
        return last;
    }
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp)
{
    T* pivot = med(first, last);
    T* li = first;
    T* ei = first;
    T* gi = last;
    while(ei < gi)
    {
        if(comp(*ei, *pivot))
        {
            swap(ei, li);
            ei++;
            li++;
        }
        else if (comp(*pivot, *ei))
        {
            swap(ei, gi);
            gi--;
        }
        else
        {
            ei++;
        }
    }
    return li-first<last-gi? li : gi;
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    while (last - first > INSERTION_THRESHOLD)
    {
        T* p = partition(first, last, comp);
        int left = p - first;
        int right = last - p;
        if(left < right && left != 0)
        {
            sort(first, p, comp);
            first = p + 1;
        }
        else
        {
            sort(p, last, comp);
            last = p - 1;
        }
    }
    insertionSort(first, last, comp);
}
