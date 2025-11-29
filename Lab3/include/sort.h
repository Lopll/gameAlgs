#include <iostream>

template<typename T>
bool comp(const T &a, const T &b);

template<typename T>
void print(T *arr, int length)
{
    for(int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout<<std::endl;
}

template<typename T>
T* med(T* first, T* last)
{
    T* middle = first + (last - first) / 2;
    
    // std::cout << "First = " << first << std::endl;
    // std::cout << "*First = " << *first << std::endl;
    // std::cout << "Middle = " << middle << std::endl;
    // std::cout << "*Middle = " << *middle << std::endl;
    // std::cout << "Last = " << last << std::endl;
    // std::cout << "*Last = " << *last << std::endl;
    
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
    if(last - first == 1)
    {
        if(comp(*last, *first))
        {
            T temp = std::move(*first);
            *first = std::move(*last);
            *last = std::move(temp);
        }
        return first;
    }
    
    T* pivot = med(first, last);
    
    // std::cout << "Pivot = " << pivot << std::endl;
    // std::cout << "*Pivot = " << *pivot << std::endl << std::endl;
    
    T* i = first-1;
    T* j = last+1;
    while(true)
    {
        do
        {
            i++;
        }
        while(comp(*i, *pivot) && *i != *pivot);
        
        do
        {
            j--;
        }
        while(comp(*pivot, *j)  && *j != *pivot);
        
        if (i >= j)
        {
            return j;
        }
        // std::cout<<"SWAP: " << *i << " and " << *j << std::endl;
        T temp = std::move(*i);
        *i = std::move(*j);
        *j = std::move(temp);
    } 
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    if (first < last)
    {
        T* p = partition(first, last, comp);//med(first,last);
        print(first, p-first+1);
    
        sort(first, p, comp);
        sort(p+1, last, comp);
    }

    // std::cout << "Len = " << last - first << std::endl << std::endl;
    // if(last - first <= 1) return;
    // T *middle = first + (last - first)/2;
    
    // T *pivot;
    // if((comp(*middle, *first) && !comp(*middle, *last)) || (comp(*middle, *first) && !comp(*middle, *last))) pivot = middle;
    // if((comp(*first, *middle) && !comp(*first, *last)) || (comp(*first, *middle) && !comp(*first, *last))) pivot = first;
    // if((comp(*last, *first) && !comp(*last, *middle)) || (comp(*last, *first) && !comp(*last, *middle))) pivot = last;
    
    // std::cout << "First = " << first << std::endl;
    // std::cout << "*First = " << *first << std::endl;
    // std::cout << "Middle = " << middle << std::endl;
    // std::cout << "*Middle = " << *middle << std::endl;
    // std::cout << "Last = " << last << std::endl;
    // std::cout << "*Last = " << *last << std::endl;
    // std::cout << "Pivot = " << pivot << std::endl;
    // std::cout << "*Pivot = " << *pivot << std::endl << std::endl;
    
    // T *left = first;
    // T *right = last;
    // while(true)
    // {
    //     while (comp(*left, *pivot))
    //     {
    //         left++;
    //     }
    //     while (!comp(*right, *pivot))
    //     {
    //         right--;
    //     }
    //     if (left>=right) break;
    //     std::swap(*left, *right);
    //     // print(first, last-first+1);
    // }
    // // if(pivot-first < last-pivot)
    // {
    //     sort(first, pivot, comp);
    // }
    // // else
    // {
    //     sort(pivot+1, last, comp);
    // }
}
