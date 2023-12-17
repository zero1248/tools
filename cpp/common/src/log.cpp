/*
 * @Author: gaoy
 * @Date: 2023-02-24 00:02:11
 * @LastEditors: gaoy
 * @LastEditTime: 2023-02-25 01:10:38
 * @Description: file content
 */
/************************************
/* FileName : log.cpp
/* CreatTime: 2023-02-16 21:15:46
/* Create by: Isaac
/************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "log.h"

LogG::LogG(std::string log_file_path) {
    m_log_file_path = log_file_path;
    m_out_log.open(log_file_path.c_str(), std::ofstream::app);
    if(!m_out_log.is_open()) {
        std::cerr << "open error log file failed!" << std::endl;
        exit(-1);
    }
    time_t now = time(0);
    char* dt = ctime(&now);
    write_log("********************************************");
    write_log(dt);
}

LogG::~LogG() {
    m_out_log.close();
}

void LogG::write_log(std::string err_log_content) {

    m_out_log << err_log_content << std::endl;
    m_out_log.flush();
}
