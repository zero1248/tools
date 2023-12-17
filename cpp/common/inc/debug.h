/*
 * @Author: gaoy
 * @Date: 2023-02-24 17:49:58
 * @LastEditors: gaoy
 * @LastEditTime: 2023-02-25 14:41:13
 * @Description: file content
 */
#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define ERROR(...) \
    do{ \
        fprintf(stderr, "[" RED "ERROR" RESET "]" "[%s][%s][Line %d]: ",__FILE__, __FUNCTION__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    }while(0)    

#define WARNING(...) \
    do{ \
        fprintf(stdout, "[" YELLOW "WARNING" RESET "]" "[%s][%s][Line %d]: ",__FILE__, __FUNCTION__, __LINE__); \
        fprintf(stdout, __VA_ARGS__, "\n"); \
        fprintf(stdout, "\n"); \
    }while(0)    

#define INFO(...) \
    do{ \
        fprintf(stdout, "[" GREEN "INFO" RESET "]" "[%s][%s][Line %d]: ",__FILE__, __FUNCTION__, __LINE__); \
        fprintf(stdout, __VA_ARGS__, "\n"); \
        fprintf(stdout, "\n"); \
    }while(0)


#endif // COLORS_H
