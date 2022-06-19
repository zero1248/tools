#ifndef SELECT_SORT_H
#define SELECT_SORT_H


#include "base_function.h"

template <typename T>
bool SelectSort(T* arr, int size) {

    if(size == 1) return true;
    if(size < 1) return false;

    int pos;
    for(int i = 0; i < size; i++) {
        pos = i;
        for(int j = i+1; j < size; j++) {
            if(arr[j] > arr[pos])
                pos = j;
        }
        Swap(arr[i], arr[pos]);
    }

    return true;
}














#endif

