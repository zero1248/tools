#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define C1 3.7415*100000000
#define C2 1.43879*10000
#define ERROR_RANGE 1e-5
#define EXE 2.718282
#define Pi  3.14159265

#define f(x) ((C1/(x*x*x*x*x))*(1/(pow(EXE,C2/(800*x))-1)))

#define a 3
#define b 5

double Integral_Function01(double,double,long);
double Integral_Function02(void);
double Func(double);
double Solution_01(double);
double Solution_02(double);
double Solution_03(double sita);

int main(void){
    double result = 0.0;
    double E0 = 0.0;
    double sita = Pi/4;
    E0 = Solution_01(Pi/6);
    printf("E0 = %.8lf\n",E0);
    result = Solution_02(E0);
    printf("I = %.8lf\n",result);
    return 0;
}

double Func(double x_){
    static double constant_C1 = 374150000.0;
    static double constant_C2 = 14387.9;
    double func_value = 0.0;
    double index_value = 0.0;
    index_value = constant_C2/(800*x_);
    func_value = constant_C1/(x_*x_*x_*x_*x_);
    func_value = func_value*(1/(pow(2.718282,index_value)-1));
    return func_value;
}

/********************************************
函数名称：Integral_Function01
功    能：求积分
入口参数：lower_limit-积分下限，upper_limit-积分上限,range_num-细分区间数量
出口参数：积分结果
说    明：
********************************************/
double Integral_Function01(double lower_limit,double upper_limit,long range_num){
    double range_h = 0.0; //细分区间宽度
    double temp_a = 0.0 , temp_b = 0.0;//小区间边界值
    double s = 0.0;          //累加和
    long i = 0;
    double integral_value = 0.0;
    range_h = (upper_limit-lower_limit)/range_num;
    temp_a = lower_limit;
    temp_b = lower_limit + range_h;
    for(i=0 ; i<range_num ; i++){
        s = s + (f(temp_a) + f(temp_b))/2;
        temp_a += range_h;
        temp_b += range_h;
    }
    integral_value = s * range_h;
    //printf("%.8lf",integral_value);
    return integral_value;
}

/********************************************
函数名称：Integral_Function02
功    能：求积分
入口参数：lower_limit-积分下限，upper_limit-积分上限,range_num-细分区间数量
出口参数：积分结果
说    明：
********************************************/
double Integral_Function02(void){
    int i,n;
    double f1,f2,f3,h,s0,s;
    f1 = f(a) + f(b); //赋初值 a
    f2 = f(((double)(b+a)/2));
    f3 = 0;
    s = ((double)(b-a)/6)*(f1+4*f2);
    n = 2;
    h = (double)(b-a)/4;
    do{    //复化抛物线算法
        f2 += f3;
        s0 = s;
        f3 = 0;
        for(i=1 ; i<=n ; i++)
            f3 += f((a+(2*i-1)*h));
        s = (h/3)*(f1+2*f2+4*f3);
        n *= 2;
        h /= 2;
    }
    while(fabs(s-s0)>ERROR_RANGE);
    return s;
}

double Solution_01(double sita){
    double Mbb = 0.0;  //黑体辐出度
    double M0 = 0.0;   //半球辐射源辐出度
    double Ibeta = 0.0;
    double E0 = 0.0;   //辐射照度
    Mbb = Integral_Function02();
    M0 = 0.98 * Mbb;
    Ibeta = 0.5*Pi*0.25*0.25*(1+cos(sita))*M0/Pi;
    E0 = Ibeta*cos(Pi/6)/(700*700);//l=700
    return E0;
}

double Solution_02(double E0){
    double I = 0.0; //辐射强度
    I = 0.88*E0*1*1*cos(Pi/4)*cos(Pi/6)/Pi;
    return I;
}

double Solution_03(double sita){
    double E0 = 0.0;
    double Lphi = 0.0;
    double Iphi = 0.0;
    double varphi = 0.0;//phi变量
    E0 = Solution_01(sita);
    for(varphi = 0.0 ; varphi<1.57 ; varphi+=0.01){
        Iphi = E0*0.5*cos(sita + varphi)*10*10*cos(sita);
        printf("%.8lf\n",Iphi);
    }
    return Iphi;
}
