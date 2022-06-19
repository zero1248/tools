#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;


int main(int argc, char **argv){

    // peremeters parse

    if(argc == 1){
        cout << "usage: ./txt_comp file1 file2" << endl;
		cout << "There must be two file paths as arguments..." << endl;
		return 1;
    }

    if(argc != 3){
        cerr << "parameter error!" << endl;
		exit(-1);
    }

    ifstream file1(argv[1]);
    ifstream file2(argv[2]);
    if (!file1.is_open()) {
        cerr << "open file failed!" << endl;
        exit(-1);
    }
    if (!file2.is_open()) {
        cerr << "open file failed!" << endl;
        exit(-1);
    }

    string s1 = "";
    string s2 = "";
    while ( getline(file1,s1) && getline(file2,s2)){
        if(!s1.compare(s2)){
            continue;
        }
        else{
            break;
        }
    }
	

    if(!s1.compare(s2))
        cout << argv[1] << " is the same with " << argv[2] << endl;
    else{
		cout << "s1: " << s1 << endl;
		cout << "s2: " << s2 << endl;
		cout << argv[1] << " is different from " << argv[2] << endl;
	}
        

    file1.close();
    file2.close();

	return 0;
}
