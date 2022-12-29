/*
 * @Author: gaoy
 * @Date: 2022-12-29 00:40:51
 * @LastEditors: gaoy
 * @LastEditTime: 2022-12-30 02:09:43
 * @Description: file content
 */
/************************************
/* FileName : list_test.cpp
/* CreatTime: 2022-12-29 00:40:27
/* Create by: Isaac
/************************************/

#include <iostream>
#include <list>
#include <array>

// list 是 stl 实现的双向链表，与 vector 相比，允许快速插入和删除，但随机访问慢。

using namespace std;
#define VNAME(value) (#value)

template <class T>
void cout_lst(list<T> & lst) {
    list<int>::iterator it;
    for(it=lst.begin(); it!=lst.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}


int main(int argc, char* argv[]) {

    /*** 1、构造函数 ***/

    cout << endl << endl << "*** Construct ***" << endl;

    list<int>lst1;         // 创建空list

    list<int>lst2(5);     // 创建含有5个元素的list

    list<int>lst3(3,2);    // 创建含有3个元素的list

    list<int>lst4(lst2);   // 使用lst2初始化lst4

    list<int>lst5(lst2.begin(), lst2.end());  // 同lst4

    cout << "Size of lst1: " << lst1.size() << endl;
    cout << "Size of lst2: " << lst2.size() << endl;
    cout << "Size of lst3: " << lst3.size() << endl;
    cout << "Size of lst4: " << lst4.size() << endl;
    cout << "Size of lst5: " << lst5.size() << endl;
    
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);
    cout << VNAME(lst2) << ": ";
    cout_lst(lst2);
    cout << VNAME(lst3) << ": ";
    cout_lst(lst3);
    cout << VNAME(lst4) << ": ";
    cout_lst(lst4);
    cout << VNAME(lst5) << ": ";
    cout_lst(lst5);


    /*** 2、增删元素函数 ***/

    cout << endl << endl << "*** Modify ***" << endl;



    // assign 用于强制分配指定数量的值给list，或从一个列表复制到另一个列表
    lst1.assign(5, 10);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    lst1.assign(lst2.begin(), lst2.end());
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // clear 用于清空 list
    lst1.clear();
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // 头插
    lst1.push_front(3);
	lst1.push_front(2);
	lst1.push_front(1);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // 尾插
	lst1.push_back(4);
	lst1.push_back(5);
	lst1.push_back(6);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // 尾删
    lst1.pop_back();
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // 头删
    lst1.pop_front();
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // front 和 back 分别用于返回第一个和最后一个元素
    cout << "The first data of lst1: "  << lst1.front() << endl;
    cout << "The last data of lst1: "  << lst1.back() << endl;

    // 在首个元素前直接生成新的元素
    lst1.emplace_front(0);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // 在最后一个元素前直接生成新的元素
    lst1.emplace_back(9);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // emplace(pos,value) 用于在指定迭代器处生成新的元素
    // 其中 pos 表示指明位置的迭代器，value为要插入的元素值
    lst1.emplace(lst1.end(), 0);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // insert 用于在指定迭代器处插入元素，共有四种形式
    // iterator insert(pos, elem), 指定的位置之前插入一个新元素, 返回新插入元素位置的迭代器
    // iterator insert(pos,n,elem), 指定的位置之前插入一个新元素, 返回表示第一个新插入元素位置的迭代器
    // iterator insert(pos,first,last), 指定的位置之前, 插入其他容器（例如 array、vector、deque 等）
        // 中位于 [first,last) 区域的所有元素返回表示第一个新插入元素位置的迭代器
    // iterator insert(pos,initlist),  指定的位置之前，插入初始化列表（用大括号 { } 括起来的多个元素，
        // 中间有逗号隔开）中所有的元素，并返回表示第一个新插入元素位置的迭代器
    lst1.insert(lst1.begin(), 3);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    lst1.insert(lst1.end(), 2, 5);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    std::array<int, 3>test{ 7,8,9 };
    lst1.insert(lst1.end(), test.begin(), test.end());
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    lst1.insert(lst1.end(), { 10,11 });
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // splice 将其它 list 容器存储的多个元素添加到当前 list 容器的指定位置，有 3 种使用方式
    // splice 是将其他 list 中的结点摘下挂到本 list 上，因此执行后，其他 list中的成员就不存在了
    // void splice (iterator position, list& x); 
    // 将 x 容器中存储的所有元素全部移动当前 list 容器中 position 指明的位置处。
    // void splice (iterator position, list& x, iterator i);
    // 将 x 容器中 i 指向的元素移动到当前容器中 position 指明的位置处。
    // void splice (iterator position, list& x, iterator first, iterator last);
    // 将 x 容器 [first, last) 范围内所有的元素移动到当前容器 position 指明的位置处。
    cout << VNAME(lst2) << ": ";
    cout_lst(lst2);
    lst1.splice(lst1.begin(), lst2);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);
    cout << VNAME(lst2) << ": ";
    cout_lst(lst2);

    // erase 用于删除一个元素，将返回下一个元素的迭代器
    // 如果在循环中使用，需要注意 it 的增加操作
    list<int>::iterator it;
    for(it = lst1.begin(); it != lst1.end(); ) {
        if(*it == 0) {
            // it = lst1.erase(it);
            lst1.erase(it++);
        }
        else {
            it++;
        }
    }
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);

    // remove 用于删除指定，如有重复会全部删去
    lst1.remove(5);
    cout << VNAME(lst1) << ": ";
    cout_lst(lst1);





    // lst1.get_allocator(); // 返回list的配置器
    // lst1.max_size(); // 返回list能容纳的最大元素数量
    // lst1.merge(); 合并两个list
    // lst1.reverse(); //  把list的元素倒转
    // lst1.rbegin(); // 返回指向第一个元素的逆向迭代器
    // lst1.rend();   // 指向list末尾的逆向迭代器
    // lst1.get_allocator(); //  返回list的配置器
    // lst1.unique(); // 去重
    // lst1.swap(lst2); // 交换
    // lst1.sort();  // 排序


    return 0;
}
