/************************************
/* FileName : vector_test.cpp
/* CreatTime: 2022-12-20 03:11:55
/* Create by: Isaac
/************************************/

#include <iostream>
#include "vector_test.h"
#include <vector>

using namespace std;
#define VNAME(value) (#value)

template <class T>
void cout_vec(vector<T> & vec) {
    vector<int>::iterator it;
    for(it=vec.begin(); it!=vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}



int main(int argc, char* argv[]) {

    /*** 1、构造函数 ***/

    cout << endl << endl << "*** Construct ***" << endl;

    vector<int> vec1;         // 创建一个空向量
    vector<int> vec2(10);     // 创建容量为 10 的向量（默认初始化为 0）
    vector<int> vec3(20, 1);  // 创建容量为 10 的向量，并用 1 初始化
    vector<int> vec4(vec3.begin()+1, vec3.begin()+3); // 创建向量，并用其他向量的部分元素初始化
    vector<int> vec5(vec3);   // 创建向量，直接从 vec3 复制

    cout << "Size of vec1: " << vec1.size() << endl;
    cout << "Size of vec2: " << vec2.size() << endl;
    cout << "Size of vec3: " << vec3.size() << endl;
    cout << "Size of vec4: " << vec4.size() << endl;
    cout << "Size of vec5: " << vec5.size() << endl;
    
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);
    cout << VNAME(vec2) << ": ";
    cout_vec(vec2);
    cout << VNAME(vec3) << ": ";
    cout_vec(vec3);
    cout << VNAME(vec4) << ": ";
    cout_vec(vec4);
    cout << VNAME(vec5) << ": ";
    cout_vec(vec5);

    
    /*** 2、增加元素函数 ***/

    cout << endl << endl << "*** Add: ***" << endl;

    // 向量尾部增加一个元素 
    for(int i=0; i<10; i++) {
        vec1.push_back(i);   
    }
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 向量中迭代器指向元素前增加一个元素 6
    vector<int>::iterator it;
    it = vec1.begin();
    vec1.insert(it, 6);     
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);
    
    // 向量中迭代器指向元素前增加 3 个元素 9
    // it = vec1.begin();
    vec1.insert(it, 3, 9);     
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 从向量中迭代器指向的元素前增加另一个相同类型向量的 [first, last) 间的数据
    vec1.insert(it, vec2.begin(), vec2.begin()+3); 
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);


    /*** 3、删除元素函数 ***/

    cout << endl << endl << "*** Delete: ***" << endl;

    // 删除向量中迭代器指向元素
    it = vec1.begin();
    vec1.erase(it); 
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 删除向量中[first,last)中元素
    vec1.erase(vec1.begin(), vec1.begin()+2);
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 删除向量中最后一个元素
    vec1.pop_back();
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 清除向量中所有元素
    vec1.clear();
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // 在循环中删除元素
    // 顺序式容器 erase 之后当前迭代器会失效，会返回下一个元素的有效迭代器
    // 因此需要接收返回值作为新的迭代器
    for(int i=0; i<10; i++) {
        vec1.push_back(i);   
    }
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);
    it = vec1.begin();
    while(it != vec1.end()) {
        if( ((*it) % 2) == 0)
            it = vec1.erase(it);
        else
            it++;
    }
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);


    /*** 4、遍历函数 ***/

    cout << endl << endl << "*** Traverse: ***" << endl;

    // 利用数组脚标访问
    cout << VNAME(vec1) << ": ";
    for(int i=0; i<vec1.size(); i++) {
        cout << vec1[i] << " ";
    }
    cout << endl;

    // 利用迭代器访问
    cout << VNAME(vec1) << ": ";
    for(it = vec1.begin(); it != vec1.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;


    /*** 5、二维数组 ***/

    cout << endl << endl << "*** 2D Vector ***" << endl;

    // 方法一
    int N=5, M=6; 
    vector<vector<int> > obj1(N);      // 定义二维动态数组大小5行 
    for(int i =0; i< obj1.size(); i++) { // 动态二维数组为5行6列，值全为0  
        obj1[i].resize(M); 
    } 
 
    for(int i=0; i< obj1.size(); i++) { //输出二维动态数组 
        for(int j=0; j<obj1[i].size(); j++) {        
            cout << obj1[i][j] << " ";
        }
        cout<<"\n";
    }

    cout << endl;

    // 方法二
    vector<vector<int> > obj2(N, vector<int>(M)); //定义二维动态数组5行6列 
    for(int i=0; i< obj2.size(); i++) { //输出二维动态数组 
        for(int j=0; j<obj2[i].size(); j++) {
            cout << obj2[i][j]<<" ";
        }
        cout<<"\n";
    }


    /*** 6、其他操作 ***/
    cout << endl << endl << "*** Other Options ***" << endl;
    
    // front() 和 back() 返回第一个和最后一个元素的引用
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);
    int &a = vec1.front();
    int &b = vec1.back();
    cout << "a= " << a << endl;
    cout << "b= " << b << endl;
    a = 66;
    b = 77;
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // max_size 可以得到 vector 最大可以是多大
    cout << "max size of vector: " << vec1.max_size() << endl;

    // capacity 可以得到当前 vector 分配的大小
    // push_back 的过程中，随着容量填满，会对内存大小进行重新分配并复制，每次增加一倍
    cout << "Current capacity of vec1: " << vec1.capacity() << endl;

    // reserve 可以更改 vector 的容量，使 vector 至少可以容纳 n 个元素
    // reserve 改变的是容量，没有做填充，因此不可访问新的位置
    vec1.reserve(100);
    cout << "Current capacity of vec1: " << vec1.capacity() << endl;

    // size 可以获取当前使用数据的大小
    cout << "Current size of vec1: " << vec1.size() << endl;

    // resize 可以改变当前使用数据的大小，
    // 如果比当前使用的大就填充，如果比当前使用的小就从尾部截断
    // resize 之后新填充的元素是可访问的
    vec1.resize(3);
    cout << "Current size of vec1: " << vec1.size() << endl;
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // swap 与另一个 vector 交换数据
    vec1.swap(vec2);
    cout << VNAME(vec1) << ": ";
    cout_vec(vec1);

    // empty 判断 vector 是否为空
    cout << vec1.empty() << endl;
    vec1.clear();
    cout << vec1.empty() << endl;


    

    return 0;
}

