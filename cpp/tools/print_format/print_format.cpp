/*************************************************************************
	> File Name: print_format.cpp
	> Author: Isaac
	> Created Time: Thu 07 Jul 2022 11:04:46 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;



int main() {

	printf("*************** printf format ***************\n");

	int tmp = 123456;
	printf("\n\033[7mDecimal int: \033[0m\n");
	printf("%%hd   : %hd       # signed short \n", tmp);
	printf("%%d    : %d      # signed int \n" , tmp);
	printf("%%ld   : %ld      # signed long \n", tmp);

	printf("%%10d  : %10d  # aligned with space \n", tmp);
	printf("%%010d : %010d  # aligned with 0 \n", tmp);

	printf("%%hu   : %hu       # unsigned short \n", tmp);
	printf("%%u    : %u      # unsigned int \n", tmp);
	printf("%%lu   : %lu      # unsigned long \n", tmp);


	printf("\n\033[7mHexdecimal int: \033[0m\n");
	printf("%%hx   : %hx        # unsigned short \n", tmp);
	printf("%%x    : %x       # unsigned int \n", tmp);
	printf("%%lx   : %lx       # unsigned long \n", tmp);
	printf("%%hX   : %hX        # unsigned short \n", tmp);
	printf("%%X    : %X       # unsigned int \n", tmp);
	printf("%%lX   : %lX       # unsigned long \n", tmp);

	printf("%%10x  : %10hx  # aligned with space \n", tmp);
	printf("%%010x : %010hx  # aligned with 0 \n", tmp);

	printf("%%#hx  : %#hx      # unsigned short with prefix \n", tmp);
	printf("%%#x   : %#x     # unsigned int with prefix \n", tmp);
	printf("%%#lx  : %#lx     # unsigned long with prefix \n", tmp);
	printf("%%#hX  : %#hX      # unsigned short with prefix \n", tmp);
	printf("%%#X   : %#X     # unsigned int with prefix \n", tmp);
	printf("%%#lX  : %#lX     # unsigned long with prefix \n", tmp);


	float  ft = 3.14;
	double db = 3.14;
	printf("\n\033[7mfloat && double: \033[0m\n");
	printf("%%f    : %f \n", ft);
	printf("%%lf   : %lf \n", db);

	printf("%%e    : %e \n", ft);
	printf("%%le   : %le \n", db);
	printf("%%E    : %E \n", ft);
	printf("%%lE   : %lE \n", db);
	printf("%%g    : %g         # the short one in %%f and %%e \n", ft);
	printf("%%lg   : %lg         # the short one in %%lf and %%le \n", db);
	printf("%%G    : %G         # the short one in %%f and %%E \n", ft);
	printf("%%lG   : %lG         # the short one in %%lf and %%lE \n", db);

	printf("%%4f   : %4f \n", ft);
	printf("%%4.f  : %4.f         # error format \n", ft);
	printf("%%4.5f : %4.5f \n", ft);
	printf("%%04f  : %04f \n", ft);
	printf("%%04.f : %04.f         # error format \n", ft);
	printf("%%04.5f: %4.5f      # the 0 in front does not work \n", ft);


    char* ch = {"123\n223\n323\n423"};
    printf("\n\033[7mchar: \033[0m\n");
    printf("%%s    : %s          # all string\n", ch);
    printf("%%.*s  : %.*s        # output 6 charactors without \\0\n", 6, ch);

	return 0;
}
