/*
 * @Author: gaoy
 * @Date: 2022-12-28 22:30:56
 * @LastEditors: gaoy
 * @LastEditTime: 2022-12-29 00:38:45
 * @Description: file content
 */
/************************************
/* FileName : deque_test.cpp
/* CreatTime: 2022-12-20 03:15:21
/* Create by: Isaac
/************************************/

#include <iostream>
#include <deque>

using namespace std;
#define VNAME(value) (#value)

template <class T>
void cout_deq(deque<T> & deq) {
    deque<int>::iterator it;
    for(it=deq.begin(); it!=deq.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}


int main(int argc, char* argv[]) {

    /*** 1、构造函数 ***/

    cout << endl << endl << "*** Construct ***" << endl;

    deque<int> deq1;  // 声明一个元素类型为type的双端队列que
    deque<int> deq2(10);  // 声明一个类型为type、含有size个默认值初始化元素的的双端队列que
    deque<int> deq3(10, 1);  // 声明一个元素类型为type、含有size个value元素的双端队列que
    deque<int> deq4(deq1);  // deq是mydeque的一个副本
    deque<int> deq5(deq3.begin()+1, deq3.end()-2);  // 使用迭代器first、last范围内的元素初始化deq

    cout << "Size of deq1: " << deq1.size() << endl;
    cout << "Size of deq2: " << deq2.size() << endl;
    cout << "Size of deq3: " << deq3.size() << endl;
    cout << "Size of deq4: " << deq4.size() << endl;
    cout << "Size of deq5: " << deq5.size() << endl;
    
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);
    cout << VNAME(deq2) << ": ";
    cout_deq(deq2);
    cout << VNAME(deq3) << ": ";
    cout_deq(deq3);
    cout << VNAME(deq4) << ": ";
    cout_deq(deq4);
    cout << VNAME(deq5) << ": ";
    cout_deq(deq5);

    /*** 2、增加元素函数 ***/

    cout << endl << endl << "*** Modify ***" << endl;

    deq1.push_front(1);  // 把元素x插入到双向队列的头部。
    deq1.push_front(2);  
    deq1.push_front(3);  
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);
    
    deq1.push_back(9);   // 把元素x插入到双向队列的尾部。
    deq1.push_back(8);  
    deq1.push_back(7);  
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);

    deq1.pop_front();    // 弹出双向队列的第一个元素。
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);

    deq1.pop_back();     // 弹出双向队列的最后一个元素。
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);

    // front() 和 back() 返回第一个和最后一个元素的引用
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);
    int &a = deq1.front();
    int &b = deq1.back();
    cout << "a= " << a << endl;
    cout << "b= " << b << endl;
    a = 66;
    b = 77;
    cout << VNAME(deq1) << ": ";
    cout_deq(deq1);


    /*** 3、遍历函数 ***/

    cout << endl << endl << "*** Traverse ***" << endl;

    // at 可以获得编号位置的数据
    cout << "data at 1 of deq1: " << deq1.at(1) << endl;

    // 利用数组脚标访问
    cout << VNAME(deq1) << ": ";
    for(int i=0; i<deq1.size(); i++) {
        cout << deq1[i] << " ";
    }
    cout << endl;

    // 利用迭代器访问
    deque<int>::iterator it;
    cout << VNAME(deq1) << ": ";
    for(it = deq1.begin(); it != deq1.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;





    return 0;
}

