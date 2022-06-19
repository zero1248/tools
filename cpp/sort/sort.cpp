#include <iostream>
#include <cstdio>
#include "base_function.h"
#include "bubble_sort.h"
#include "quick_sort.h"
#include "insert_sort.h"
#include "select_sort.h"

using namespace std;


int main() { 

    cout << "sort algorithm test begin..." << endl;

    int arr[14] = {9, 8, 3, 5, 1, 2, 3, 4, 5, 9, 8, 7, 6, 0};

    for(int i = 0; i < 14; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    //BubbleSort(arr, 14);
    //QuickSort(arr, 14);
    //InsertSort(arr, 14);
    SelectSort(arr, 14);

    for(int i=0; i<14; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "sort algorithm test done..." << endl; 

    return 1;
}
