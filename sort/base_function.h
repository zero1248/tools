#ifndef BASE_FUNCTION_H
#define BASE_FUNCTION_H

template<typename T>
void Swap(T & x, T & y) {

    T tmp = x;
    x = y;
    y = tmp;
}

#endif
