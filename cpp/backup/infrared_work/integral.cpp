#include"integral.h"
#include<math.h>
#include"macro_definition.h"

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
�������ƣ�Integral_Function01
��    �ܣ������
��ڲ�����lower_limit-�������ޣ�upper_limit-��������,range_num-ϸ����������
���ڲ��������ֽ��
˵    ����
********************************************/
double Integral_Function01(double lower_limit,double upper_limit,long range_num){
    double range_h = 0.0; //ϸ��������
    double temp_a = 0.0 , temp_b = 0.0;//С����߽�ֵ
    double s = 0.0;          //�ۼӺ�
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
�������ƣ�Integral_Function02
��    �ܣ������
��ڲ�����lower_limit-�������ޣ�upper_limit-��������,range_num-ϸ����������
���ڲ��������ֽ��
˵    ����
********************************************/
double Integral_Function02(void){
    int i,n;
    double f1,f2,f3,h,s0,s;
    f1 = f(a) + f(b); //����ֵ
    f2 = f(((double)(b+a)/2));
    f3 = 0;
    s = ((double)(b-a)/6)*(f1+4*f2);
    n = 2;
    h = (double)(b-a)/4;
    do{    //�����������㷨
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
    //printf("%.8lf",s);
    return s;
}

