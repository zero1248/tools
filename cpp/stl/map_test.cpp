/*
 * @Author: gaoy
 * @Date: 2022-12-30 02:12:25
 * @LastEditors: gaoy
 * @LastEditTime: 2023-01-02 00:59:19
 * @Description: file content
 */
/************************************
/* FileName : map_test.cpp
/* CreatTime: 2022-12-30 02:11:23
/* Create by: Isaac
/************************************/

#include <iostream>
#include <map>

// <map> 中包含 map 和 multimap
// map 的 key 不可以重复，而 multimap 可以
// 因此 map 支持 [] 运算符，而 multimap 不支持
// map 的内部数据结构是一棵红黑树（非严格平衡二叉树），具有对数据自动排序的功能

using namespace std;
#define VNAME(value) (#value)

template <typename T1, typename T2>
using MapIterator = typename map<T1, T2>::const_iterator;

template <typename T1, typename T2>
void cout_mp(map<T1, T2> & mp) {
    MapIterator<T1, T2> it;
    for(it=mp.begin(); it!=mp.end(); it++) {
        // it->first 为索引键值，it->second 为值
        cout << it->first << ": " << it->second << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    /*** 1、构造函数 ***/

    // 可以直接用 {} 赋值（从 C++11 开始）
    map<int, string> mp1 = {
                { 2015, "Jim" },
                { 2016, "Tom" },
                { 2017, "Bob" } };
    map<int, string> mp2;

    cout << mp1[2015] << endl;
    cout << VNAME(mp1) << ": " << endl;
    cout_mp(mp1);
    
    map<int, string>::iterator it;


    /*** 2、增删元素函数 ***/

    // 用 insert 函数插入 pair 数据
    mp1.insert(pair<int, string>(1, "student_one"));
    mp1.insert(pair<int, string>(2, "student_two"));
    mp1.insert(pair<int, string>(3, "student_three"));
    cout << VNAME(mp1) << ": " << endl;
    cout_mp(mp1);

    // 用 insert 函数插入 value_type 数据
    mp1.insert(map<int, string>::value_type(4, "student_four"));
    mp1.insert(map<int, string>::value_type(5, "student_five"));
    mp1.insert(map<int, string>::value_type(6, "student_six"));
    cout << VNAME(mp1) << ": " << endl;
    cout_mp(mp1);

    // 用 insert 函数进行范围多值插入
    mp2.insert(mp1.begin(), mp1.find(3));
    cout << VNAME(mp2) << ": " << endl;
    cout_mp(mp2);

    // 可以定义一个 Pair<map<int, string>::iterator, bool> Insert_Pair;
    // 来接收 insert 的返回值，pair 的第二个参数（bool 型）反映 insert 是否成功

    // 用数组方式插入数据
    // 用数组方式可以覆盖已有的 key，上面的 insert 方法则不能
    mp1[7] = "student_seven";
    mp1[8] = "student_eight";
    mp1[9] = "student_nine";
    cout << VNAME(mp1) << ": " << endl;
    cout_mp(mp1);

    // 用列表形式插入数据
    mp2.insert({{3,"stu_3"}, {4, "stu_4"}});
    cout << VNAME(mp2) << ": " << endl;
    cout_mp(mp2);


    // 删除
    // 删除迭代器指向位置的键值对，并返回一个指向下一元素的迭代器
    // iterator erase( iterator pos )
    
    // 删除一定范围内的元素，并返回一个指向下一元素的迭代器
    // iterator erase( const_iterator first, const_iterator last );
    
    // 根据Key来进行删除， 返回删除的元素数量，在map里结果非0即1
    // size_t erase( const key_type& key );
    
    // 清空map，清空后的size为0
    // void clear();


    /*** 3、排序 ***/
    // map中的元素是自动按Key升序排序，所以不能对map用sort函数



    /*** 4、其他操作 ***/

    // 查找
    // 关键字查询，找到则返回指向该关键字的迭代器，否则返回指向end的迭代器
    // 根据map的类型，返回的迭代器为 iterator 或者 const_iterator
    // iterator find (const key_type& k);
    // const_iterator find (const key_type& k) const;

    // 两个 map 交换
    // void swap( map& other );

    // 查询
    // 查询map是否为空
    // bool empty(); 
    // 查询map中键值对的数量
    // size_t size(); 
    // 查询map所能包含的最大键值对数量，和系统和应用库有关。
    // 此外，这并不意味着用户一定可以存这么多，很可能还没达到就已经开辟内存失败了
    // size_t max_size(); 
    // 查询关键字为key的元素的个数，在map里结果非0即1
    // size_t count( const Key& key ) const; 









    return 0;
}

