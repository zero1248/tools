#include <iostream>
#include "cmdline.h"

using namespace std;



int main(int argc, char **argv){

    // peremeters parse
    cmdline::parser cmd_parser;
    cmd_parser.add<string>("output", 'o', "output file path", true, "");
    cmd_parser.add<long>("size", 's', "output file size in bytes", true, 123);
    cmd_parser.add("help", 0, "print this message");
    bool ok = cmd_parser.parse(argc, argv);
    if (argc==1 || cmd_parser.exist("help")){
        cerr << cmd_parser.usage();
        return 1;
    }
    if (!ok){
        cerr << cmd_parser.error() << endl << cmd_parser.usage();
        return -1;
    }

    string output_path = "./";
    long output_size = 0;
    if(cmd_parser.exist("output")){
        output_path = cmd_parser.get<string>("output");
    }
    cout << output_path << endl;

    if(cmd_parser.exist("size")){
        output_size = cmd_parser.get<long>("size");
    }
    cout << output_size << endl;


    cout << "test parser " << endl;



	// sscanf(myarray, "%d", &i);


	return 0;
}
