#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H


#include <iostream>
#include <cstdio>
#include "base_function.h"

using namespace std;


template <typename T>
bool BubbleSort(T* arr, int size) {

    T tmp;

    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                Swap(arr[j], arr[j+1]);
            }                
        }
    }
    return true;
}


#endif


