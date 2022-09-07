
#include "get_dir_files.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <vector>
#include <typeinfo>


using std::cout;
using std::endl;

extern void getAllFile(std::string filepath, std::vector<std::string>& files) {
// void getAllFile(std::string filepath, std::vector<std::string>& files, std::string fileType) {
    
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(filepath.c_str()))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        std::string str_ptrName = std::string(ptr->d_name);
        if (str_ptrName != "." && str_ptrName != ".."){
            files.push_back(ptr->d_name);
        }
    }
    closedir(pDir);
}


extern void getAllFile(std::string filepath, std::vector<std::string>& files, std::string fileType) {
    
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(filepath.c_str()))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        std::string str_ptrName = std::string(ptr->d_name);
        if (str_ptrName != "." && str_ptrName != ".."){
            int pos = str_ptrName.find(fileType);
            if(pos != std::string::npos && pos == (str_ptrName.length() - 4))
                files.push_back(ptr->d_name);
        }
    }
    closedir(pDir);
}


int main(int argc,char *argv[]) {

    std::string path = "./";

    if(argc > 1)
        path = std::string(argv[1]);

	std::vector<std::string> tmp_no_type;
	std::vector<std::string> tmp_has_type;
    
    cout << "The input path: " << path << endl;
    
    cout << "not specify type:" << endl;
    getAllFile(path, tmp_no_type);
	for (int i = 0; i < tmp_no_type.size(); i++) {
		cout << tmp_no_type[i] << endl;
	}

    cout << "specify type to .log:" << endl;
    getAllFile(path, tmp_has_type, ".log");
	for (int i = 0; i < tmp_has_type.size(); i++) {
		cout << tmp_has_type[i] << endl;
	}
	return 0;
}


