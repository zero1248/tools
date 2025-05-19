#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "cmdline.h"

using namespace std;


int main(int argc, char **argv){

    // peremeters parse
    cmdline::parser cmd_parser;
    cmd_parser.add<string>("output", 'o', "output file path", false, "./output.txt");
    cmd_parser.add<long>("size", 's', "output file size in bytes", true, 1024);
    cmd_parser.add("help", 0, "print this message");

    bool ok = cmd_parser.parse(argc, argv);
    if (argc==1 || cmd_parser.exist("help")) {
        cerr << cmd_parser.usage();
        return 1;
    }
    if (!ok) {
        cerr << cmd_parser.error() << endl << cmd_parser.usage();
		cout << "not ok" << endl;
        return -1;
    }
    string output_path = cmd_parser.get<string>("output");
    long output_size = cmd_parser.get<long>("size");

    if(output_size < 1) {
        cout << "Size must be integer greater than 1." << endl;
        return -1;
    }

    // open and write file
    FILE *fp = fopen(output_path.data(), "w");
    if(fp == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }

	srand((unsigned int)time(NULL));
    char tmp;
    for(long i=0; i<output_size; i++) {
        // fprintf(fp, "%s", "0123456789abcdef\n");

	if(i && (i%80 == 0)){        // 每 80 个字符换行
            fprintf(fp, "%c", '\n');
        } 

        tmp = rand() % 36;	// 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
        if (tmp < 10) {			// 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
            tmp += '0';
        } 
        else {				// 否则，变换成一个大写字母的 ASCII
            tmp -= 10;
            tmp += 'A';
        }
        fprintf(fp, "%c", tmp);  
    }

    fprintf(fp, "%c", '\n');   // 换一行

    fclose(fp);

	return 0;
}
