/*
 * @Author: gaoy
 * @Date: 2023-02-25 14:19:22
 * @LastEditors: gaoy
 * @LastEditTime: 2023-02-25 21:27:34
 * @Description: file content
 */
#ifndef CONTAINER_COUT_H
#define CONTAINER_COUT_H

#include <iostream>
#include <map>


template <typename T1, typename T2>
using MapIterator = typename std::map<T1, T2>::const_iterator;

template <typename T1, typename T2>
void cout_mp(std::map<T1, T2> &mp) {
    MapIterator<T1, T2> it;
    for(it=mp.begin(); it!=mp.end(); it++) {
        // it->first 为索引键值，it->second 为值
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << std::endl;
}





#endif // CONTAINER_COUT_H
