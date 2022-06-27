/*************************************************************************
	> File Name: print_ascii.cpp
	> Author: Isaac
	> Created Time: Mon 27 Jun 2022 04:44:51 PM CST
 ************************************************************************/

#include <iostream>
#include "cstdio"

using namespace std;

int main() {

	int i;
	cout << "------ASCII Code------" << endl;
	cout << "| Dec | Hex  | ASCII |" << endl; 
	for(i=32; i<128; i++) {
		printf("  %03d | 0x%02X |   %c\n", i, i, i);
	}

	return 0;
}





