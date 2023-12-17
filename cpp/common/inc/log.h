/*
 * @Author: gaoy
 * @Date: 2023-02-24 00:02:11
 * @LastEditors: gaoy
 * @LastEditTime: 2023-02-25 21:52:38
 * @Description: file content
 */
/************************************
/* FileName : log.h
/* CreatTime: 2023-02-16 21:15:46
/* Create by: Isaac
/************************************/

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>

class LogG {


public:
    LogG(std::string log_file_path);
    ~LogG();
    void write_log(std::string err_log_content); 
    
private:
    std::string m_log_file_path;
    std::ofstream m_out_log;

};



#endif // LOG_H

