/*
 * @Author: gaoy
 * @Date: 2022-09-22 01:33:14
 * @LastEditors: gaoy
 * @LastEditTime: 2022-09-23 16:52:31
 * @Description: file content
 */
#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include"integral.h"
#include"macro_definition.h"

using namespace std;

int main(void){
    double result = 0.0;
    result = Integral_Function01(3,5,100000);
    printf("%.8lf",result);
    printf("\n");
    result = Integral_Function02();
    printf("%.8lf",result);
    printf("\n");

//    initgraph(640, 480); // 初始化为640*480大小的窗口，这里和TC 略有区别
//    circle(200, 200, 100); // 画圆，圆心(200, 200)，半径100
//    getch(); // 等待用户按键，按任意键继续
//    closegraph(); // 关闭图形界面

    //设置窗口大小
    initwindow(200,200,"XTU",0,0);
    int maxX = getmaxx();
    int maxY = getmaxy();
    //设置窗口背景色
    setfillstyle(1,LIGHTGRAY);
    bar(0,0,maxX,maxY);
    //画矩形
    setcolor(RED);
    rectangle(0,0,maxX,maxY);
    rectangle(50,50,70,150);
    //画填充矩形
    setfillstyle(1,GREEN);
    bar(100,50,120,150);
    //画直线
    setcolor(RED);
    line(150,50,150,150);
    //画文字
    setcolor(BLUE);
    setbkcolor(LIGHTGRAY);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(150, 150, "3278");
    //结束绘图
    getch();
    closegraph();

    return 0;
}





