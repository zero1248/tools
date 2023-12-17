/*
 * @Author: gaoy
 * @Date: 2023-02-17 19:57:21
 * @LastEditors: gaoy
 * @LastEditTime: 2023-03-19 20:21:45
 * @Description: file content
 */
/************************************
/* FileName : get_dir_files.cpp
/* CreatTime: 2023-02-17 19:57:21
/* Create by: Isaac
/************************************/


#include "file_opt.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "common.h"



FileOpt::FileOpt() {

}


FileOpt::~FileOpt() {
    
}


void FileOpt::get_all_files(std::string dir, std::vector<std::string>& files, std::string fileType) {
    
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(dir.c_str()))){    // <sys/types.h> <dirent.h>
        // std::cout << "Folder " << dir << " doesn't Exist!" << std::endl;
        WARNING(("Dir " + dir +" doesn't Exist!").c_str());
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        std::string str_ptrName = std::string(ptr->d_name);
        if (str_ptrName != "." && str_ptrName != ".."){
            int pos = str_ptrName.find(fileType);
            if(pos != std::string::npos && pos == (str_ptrName.length() - fileType.length()))
                files.push_back(ptr->d_name);
        }
    }
    closedir(pDir);
}


bool FileOpt::access_or_mkdir(std::string dir) {
    if( access(dir.c_str(), F_OK) == -1 ) {  // create output dir  <unistd.h>
        mkdir(dir.c_str(), S_IRWXO|S_IRWXG|S_IRWXU);  // <sys/stat.h> <sys/types.h>
        INFO(("Directory " + dir + " doesn't exist, mkdir it.").c_str());
        return false;
    }
    return true;
}


bool FileOpt::dir_accessible(std::string dir) {
    if( access(dir.c_str(), F_OK) == -1 ) {  //   <unistd.h>
        return false;
    }
    return true;
}


void FileOpt::correct_dir(std::string &dir) {
    if(dir.length() == 0) {
        WARNING(("The length of dir: " + dir + " less than 1!").c_str());
        dir = "./";
        return;
    }
    if(dir == ".") {
        dir = "./";
        return;
    }
    if(dir.length()>1 && dir[dir.length() - 1] != '/')
        dir = dir + "/";
}


void FileOpt::correct_file_suffix(std::string &file_suffix) {
    if(file_suffix.length() < 1) {
        WARNING(("The length of file_suffix: " + file_suffix + " less than 1!").c_str());
        return;
    }
    if(file_suffix == ".") {
        WARNING(("The format of file_suffix: " + file_suffix + " is wrong, it only has \'.\' .").c_str());
        exit(-1);
    }
    if(file_suffix.at(0) == '.') {
        file_suffix = file_suffix.substr(1, file_suffix.length()-1);
    }
}


std::string FileOpt::get_abs_path(std::string file_path) {
    char path[PATH_MAX];
    if (realpath(file_path.c_str(), path) != NULL) {
        std::string abs_path(path);
        return abs_path;
    } else {
        WARNING(("Get absolute path of " + file_path + " failed.").c_str());
        exit(-1);
    }
}


std::string FileOpt::get_file_father_dir_from_string(std::string file_path) {

    std::string directory;

    size_t pos = file_path.find_last_of("/");
    if (pos != std::string::npos) {
        directory = file_path.substr(0, pos);
    }
    return directory;
}


std::string FileOpt::get_file_name_from_string(std::string file_path) {

    std::string file_name;
    size_t pos = file_path.find_last_of("/");
    if (pos != std::string::npos) {
        file_name = file_path.substr(pos+1);
    }
    else { // 路径中不含 /
        file_name = file_path;
    }
    return file_name;
}


std::string FileOpt::get_file_father_dir_from_abs(std::string file_path) {
    std::string directory = get_abs_path(file_path);

    size_t pos = directory.find_last_of("/");
    if (pos != std::string::npos) {
        directory = directory.substr(0, pos+1);
    }
    return directory;
}


std::string FileOpt::get_file_name_from_abs(std::string file_path) {
    
    std::string file_name;
    std::string path = get_abs_path(file_path);
    size_t pos = path.find_last_of("/");
    if (pos != std::string::npos) {
        file_name = path.substr(pos+1);
    }
    else { // 路径中不含 /
        file_name = path;
    }
    return file_name;
}


bool FileOpt::modify_file_str_suffix(std::string &file, std::string new_suffix) {

    std::string::size_type find1;    
    find1 = file.find(".");
    if (find1 != std::string::npos) {
        correct_file_suffix(new_suffix);
        file = file.substr(0, find1+1) + new_suffix;    
    }
    else {
        WARNING("File has no suffix.");
        return false;
    }
    return true;
}


bool FileOpt::modify_file_suffix(std::string &file, std::string new_suffix) {

}



