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
	cout << "| Dec | Hex  | ASCII |   | Dec | Hex  | ASCII |   ";
     	cout << "| Dec | Hex  | ASCII |   | Dec | Hex  | ASCII |" << endl; 
	for(i=32; i<56; i++) {
		printf("  %03d | 0x%02X |   %c         %03d | 0x%02X |   %c       ", i, i, i, i+24, i+24, i+24);
		printf("  %03d | 0x%02X |   %c         %03d | 0x%02X |   %c\n", i+48, i+48, i+48, i+72, i+72, i+72);
	}

	return 0;
}





