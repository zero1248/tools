/*************************************************************************
	> File Name: print_ascii.cpp
	> Author: Isaac
	> Created Time: Mon 27 Jun 2022 04:44:51 PM CST
 ************************************************************************/

#include <iostream>
#include "cstdio"

using namespace std;

int main() {

	cout << "\033[30;47m------ Printf color ------\033[0m" << endl  ;

	cout << endl << "\033[1m------ General format control ------\033[0m" << endl;
    printf("\033[0m Reset all attributes. \033[0m    : \\033[0m Reset all attributes. \\033[0m \n");
    printf("\033[1m High light/overstriking. \033[0m : \\033[1m High light/overstriking. \\033[0m \n");
    printf("\033[2m Dim. \033[0m                     : \\033[2m Dim. \\033[0m \n");
    printf("\033[4m Underline. \033[0m               : \\033[4m Underline. \\033[0m \n");
    printf("\033[5m Blink. \033[0m                   : \\033[5m Blink. \\033[0m \n");
    printf("\033[7m Reversal. \033[0m                : \\033[7m Reversal. \\033[0m \n");
    printf("\033[8m Hide. \033[0m                    : \\033[8m Hide. \\033[0m \n");

	cout << endl << "\033[1m------ Foreground view ------\033[0m" << endl;
	printf("\033[30m This text is black. \033[0m   : \\033[30m This text is black. \\033[0m \n");
	printf("\033[31m This text is red. \033[0m     : \\033[31m This text is red. \\033[0m \n");
	printf("\033[32m This text is green. \033[0m   : \\033[32m This text is green. \\033[0m \n");
	printf("\033[33m This text is yellow. \033[0m  : \\033[33m This text is yellow. \\033[0m \n");
	printf("\033[34m This text is blue. \033[0m    : \\033[34m This text is blue. \\033[0m \n");
	printf("\033[35m This text is magenta. \033[0m : \\033[35m This text is magenta. \\033[0m \n");
	printf("\033[36m This text is cyan. \033[0m    : \\033[36m This text is cyan. \\033[0m \n");
	printf("\033[37m This text is white. \033[0m   : \\033[37m This text is white. \\033[0m \n");

	cout << endl << "\033[1m------ Background view ------\033[0m" << endl;
	printf("\033[40m This background is black. \033[0m     : \\033[40m This text is black. \\033[0m \n");
	printf("\033[41m This background is red. \033[0m       : \\033[41m This text is red. \\033[0m \n");
	printf("\033[42m This background is green. \033[0m     : \\033[42m This text is green. \\033[0m \n");
	printf("\033[43m This background is yellow. \033[0m    : \\033[43m This text is yellow. \\033[0m \n");
	printf("\033[44m This background is blue. \033[0m      : \\033[44m This text is blue. \\033[0m \n");
	printf("\033[45m This background is magenta. \033[0m   : \\033[45m This text is magenta. \\033[0m \n");
	printf("\033[46m This background is cyan. \033[0m      : \\033[46m This text is cyan. \\033[0m \n");
	printf("\033[47m This background is white. \033[0m     : \\033[47m This text is white. \\033[0m \n");

    cout << endl << "\033[1m------ Foreground view and background view ------\033[0m" << endl;
	printf("\033[32;44m This text is green with blue background. \033[0m : \\033[32;44m This text is green with blue background. \\033[0m \n");

    cout << endl;

	return 0;
}