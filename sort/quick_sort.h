#ifndef QUICK_SORT_H
#define QUICK_SORT_H


template <typename T>
static int adj_array(T* arr, int l, int r) {

    int i = l, j = r;
    int x = arr[l];

    while(i < j) {
        // r to l    
        while(i < j && arr[j] >= x) j--;
        if(i < j) {
            arr[i] = arr[j];
            i++;
        }

        // l to r
        while(i < j && arr[i] < x) i++;
        if(i < j) {
            arr[j] = arr[i];
            j--;
        }

    }
    arr[i] = x;
    return i;
}


template <typename T>
static void quick_sort(T* arr, int l, int r) {

    if(l < r) {
        int i = adj_array(arr, l, r);
        quick_sort(arr, l, i-1);
        quick_sort(arr, i+1, r);        
    }
}


template <typename T>
bool QuickSort(T* arr, int size) {

    quick_sort(arr, 0, size-1);

    return true;
}


#endif  //QUICK_SORT_H
