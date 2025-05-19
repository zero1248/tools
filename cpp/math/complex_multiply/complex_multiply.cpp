/*
 * @Author: gaoy
 * @Date: 2025-04-14 06:43:59
 * @LastEditors: gaoy
 * @LastEditTime: 2025-04-14 06:44:03
 * @Description: file content
 */
/************************************
/* FileName : complex_multiply.cpp
/* CreatTime: 2025-04-14 06:19:51
/* Create by: Isaac
/************************************/


#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 复数乘法运算符重载
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    // 优化输出的格式化显示
    friend ostream& operator<<(ostream& os, const Complex& c) {
        bool hasReal = (c.real != 0);
        bool hasImag = (c.imag != 0);

        if (!hasReal && !hasImag) return os << "0";

        if (hasReal) os << c.real;
        
        if (hasImag) {
            if (hasReal) {
                os << (c.imag > 0 ? " + " : " - ");
                if (abs(c.imag) != 1) os << abs(c.imag);
            } else {
                if (c.imag == -1) os << "-";
                else if (c.imag != 1) os << c.imag;
            }
            os << "i";
        }
        return os;
    }
};

int main(int argc, char* argv[]) {
    // 验证命令行参数数量
    if (argc != 5) {
        cerr << "用法: " << argv[0] 
             << " <实部1> <虚部1> <实部2> <虚部2>\n"
             << "示例: " << argv[0] << " 2 3 4 5  => (2+3i)*(4+5i)\n";
        return 1;
    }

    try {
        // 从命令行参数解析复数
        Complex c1(stod(argv[1]), stod(argv[2]));
        Complex c2(stod(argv[3]), stod(argv[4]));

        // 执行乘法运算
        Complex result = c1 * c2;

        // 输出结果
        cout << "(" << c1 << ") * (" << c2 << ") = " << result << endl;
    } 
    catch (const invalid_argument& e) {
        cerr << "参数错误: 请输入有效的数字\n";
        return 2;
    }

    return 0;
}

