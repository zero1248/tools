/*
 * @Author: gaoy
 * @Date: 2022-07-15 14:08:53
 * @LastEditors: gaoy
 * @LastEditTime: 2022-07-15 14:25:59
 * @Description: file content
 */
#include <iostream>
#include "print_cpu.h"

using namespace std;

int main() {

    char* cpu_brand;

    cpu_brand = cpu_brand_string();

    cout << cpu_brand << endl;

    return 0;
}