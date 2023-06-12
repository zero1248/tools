#include"solutions.h"
#include<math.h>
#include"macro_definition.h"
#include"integral.h"

double Solution_01(void){
    double Mbb = 0.0;  //黑体辐出度
    double M0 = 0.0;   //半球辐射源辐出度
    double Ibeta = 0.0;
    double E0 = 0.0;   //辐射照度
    Mbb = Integral_Function02();
    M0 = 0.98 * Mbb;
    Ibeta = 0.5*Pi*0.25*0.25*(1+cos(Pi/6))*M0/Pi;
    E0 = Ibeta*cos(Pi/6)/(700*700);//l=700
    return E0;
}

double Solution_02(double E0){
    double I = 0.0;
    I = 0.88*E0*10*10*pow(10,-12)*cos(1)*cos(1)/Pi;
    return I;
}

double Solution_03(void){

}
