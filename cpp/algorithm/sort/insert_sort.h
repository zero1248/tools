#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include "base_function.h"


template <typename T>
bool InsertSort(T* arr, int size) {

    if(size == 1) return true;
    if(size < 1) return false;

    for(int i = 1; i < size; i++) {
        
        for(int j = i; j > 0; j--) {
            if(arr[j] < arr[j-1])
                Swap(arr[j-1], arr[j]);
        }  
    }      

    return true;
}





#endif
