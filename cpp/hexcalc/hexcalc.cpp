/*************************************************************************
	> File Name: hexcalc.cpp
	> Author: Isaac
	> Created Time: Tue 26 Jul 2022 04:07:10 PM CST
 ************************************************************************/

#include <iostream>
#include "debug.h"
#include <cstdio>

using namespace std;

void help_message() {

    printf("usage: hexdiff input1 input2 bytes.\n");
    printf("which means input1 minus input2 in hexadecimal form.\n");
    printf("" RED "input1" RESET " and " RED "input2" RESET " is the hex data.\n");
    printf("" RED "bytes" RESET " is the length of the hex data,1 or 2 or 4 or 8 are valid.\n");
}


int main(int argc, char **argv){

    // char* in1;
    // char* in2;
    uint64_t in1;
    uint64_t in2;
    int len;
    uint8_t out_1;
    uint16_t out_2;
    uint32_t out_4;
    uint64_t out_8;

    if(argc != 4) {
        help_message();
        exit(0);
    }

    // in1 = argv[1];
    // in2 = argv[2];

    sscanf(argv[1], "%lx", &in1);
    sscanf(argv[2], "%lx", &in2);
    sscanf(argv[3], "%d", &len);

    printf("" GREEN "in1:" RESET "  0x%016lx\n", in1);
    printf("" GREEN "in2:" RESET "  0x%016lx\n", in2);
    
    if(len == 1) {
        out_1 = (uint8_t)in1 - (uint8_t)in2;
        printf("" GREEN "result:" RESET "  0x%02x\n", out_1);
    }

    else if(len == 2) {
        out_2 = (uint16_t)in1 - (uint16_t)in2;
        printf("" GREEN "result:" RESET "  0x%04x\n", out_2);
    }
        
    else if(len == 4) {
        out_4 = (uint32_t)in1 - (uint32_t)in2;
        printf("" GREEN "result:" RESET "  0x%08x\n", out_4);
    }
    else if(len == 8) {
        out_8 = in1 - in2;
        printf("" GREEN "result:" RESET "  0x%016lx\n", out_8);
    }
        
    else{
        printf("parameter " RED "len" RESET " error.\n");
        help_message();
        exit(0);
    }


	return 0;
}

	