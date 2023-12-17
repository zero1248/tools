/*
 * @Author: gaoy
 * @Date: 2023-02-24 00:02:11
 * @LastEditors: gaoy
 * @LastEditTime: 2023-03-19 19:00:14
 * @Description: file content
 */
/************************************
/* FileName : get_dir_files.h
/* CreatTime: 2023-02-17 19:57:21
/* Create by: Isaac
/************************************/

#ifndef FILE_OPT_H
#define FILE_OPT_H

#include <iostream>
#include <vector>

//todo: output file nums, file info, file list etc.
//todo: set_dir()
//todo: construct with dir


class FileOpt {

public:
    FileOpt();
    ~FileOpt();
    
    // Get all the files in the dir 
    void get_all_files(std::string dir, std::vector<std::string>& files, std::string fileType);


    // Access a dir, if not exists, mkdir it
    bool access_or_mkdir(std::string dir);
    // test whether the dir or file is accessible
    bool dir_accessible(std::string dir);


    // Correct dir format, ensure it end with '/' , for example, "/mnt/g" -> "mnt/g/"
    void correct_dir(std::string &dir); 
    // Correct file suffix, ensure it begin without '.', for example, ".txt" -> "txt"
    void correct_file_suffix(std::string &file_suffix);
    // Get abs path
    std::string get_abs_path(std::string file_path);
    // Get the file's father directory from the file path string
    std::string get_file_father_dir_from_string(std::string file_path);
    // Get the file's name from the file path string
    std::string get_file_name_from_string(std::string file_path);
    // Get the file's father directory from the abs path
    std::string get_file_father_dir_from_abs(std::string file_path);
    // Get the file's name from the abs path
    std::string get_file_name_from_abs(std::string file_path);


    // Modify the file suffix of a file name string
    bool modify_file_str_suffix(std::string &file, std::string new_suffix);
    // Modify the file suffix of a real file
    bool modify_file_suffix(std::string &file, std::string new_suffix);


    // todo: get abs path


//dir 可访问性

};








#endif // GET_DIR_FILES_H

