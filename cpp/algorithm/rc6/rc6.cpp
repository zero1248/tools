#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned int WORD;           // 构造32位寄存器
#define w 32                         // 寄存器宽度（32位）
#define r 20                         // 加密循环轮数
#define u (w / 8)                    // 寄存器可存放的字节数
#define s_length (2*r+4)             // S 的长度
#define lgw 5                        // log2(w)
WORD S[s_length] = {0};                // 密钥数组
WORD Pw = 0xb7e15163, Qw = 0x9e3779b9; // 魔数常量

// 移位操作，x 必须是unsigned类型，以实现逻辑右移
#define ROTL(x, y) (((x) << (y & (w - 1))) | ((x) >> (w - (y & (w - 1)))))
#define ROTR(x, y) (((x) >> (y & (w - 1))) | ((x) << (w - (y & (w - 1)))))


// 密钥扩展
// b 表示加密密钥用字节表示的长度（默认用 16bytes）
void rc6_keygen(unsigned char *K, int b=16){

    int i, j, s, v;
    WORD L[(32+u-1) / u]={0};    // b 最大取32，这里为 b 留足够空间
    WORD A, B;
    int c = (b+u-1) / u;     // c = b/u 向上取整

    printf("初始L数组：\n");
    for(int i=0; i<c; i++){
        printf("%x ", L[i]);
    }
    printf("\n\n");

    printf("输入密钥数组 K：\n");
    for(int i=0; i<b; i++){
        printf("%x ", K[i]);
    }
    printf("\n\n");


    /* 1# 将密钥由字节数组 K[0,...,b-1] 填充至字数组 L[0,...,c-1] */
    // L[0] = K[3]K[2]K[1]K[0]
    // L[3] = K[15]K[14]K[13]K[12]
    // 可以不填充满，K长度若小于16，则L的高位字节填充 0
    for (int i=b-1; i>=0; i--)
        L[i/u] = (L[i/u] << 8) + K[i];

    printf("填充 L 数组：\n");
    for(int i=0; i<c; i++){
        printf("%x ", L[i]);
    }
    printf("\n\n");


    /* 2# 构造数组 S */
    int t = s_length;

    printf("初始 S 数组：\n");
    for(int i=0; i<t; i++){
        printf("%x ", S[i]);
    }
    printf("\n\n");

    S[0] = Pw;
    for (i=1; i<t; i++){
        S[i] = S[i-1] + Qw;
    }

    printf("构造 S 数组：\n");
    for(int i=0; i<t; i++){
        printf("%x ", S[i]);
    }
    printf("\n\n");


    // 3# 密钥混乱
    A = B = i = j = 0;
    v = s_length;
    if (c > t)
        v = c;
    v *= 3; // v = 3 * max{c, 2r+4}
    for (s = 1; s <= v; s++){
        A = S[i] = ROTL(S[i]+A+B, 3);
        B = L[j] = ROTL(L[j]+A+B, A+B);
        i = (i + 1) % t;
        j = (j + 1) % c;
    }

    printf("混乱 S 数组：\n");
    for(int i=0; i<t; i++){
        printf("%x ", S[i]);
    }
    printf("\n\n");
}


// 加密算法
void rc6_encrypt(unsigned char *plain, unsigned char *cipher)
{
    WORD p_temp[4], c_temp[4];
    WORD A, B, C, D, t, u_, x;

    // 将 plain[] 中的字节搬运到 p_temp[4] 中（32bit寄存器）
    // 并将各个寄存器按顺序命名为 A B C D
    for (int i=0; i<4; i++){
        p_temp[i] = plain[4*i] + (plain[4*i+1] << 8) +
                    (plain[4*i+2] << 16) + (plain[4*i+3] << 24);
    }
    A = p_temp[0];
    B = p_temp[1];
    C = p_temp[2];
    D = p_temp[3];

    // 加密过程
    B += S[0];  // B = B+S[0]
    D += S[1];  // D = D+S[1]
    for (int i=2; i <= 2*r; i+=2){
        t = ROTL(B*(2*B+1), lgw); // B*(2B+1) 本质上是移位再求和
        u_ = ROTL(D*(2*D+1), lgw);
        A = ROTL(A^t, u_) + S[i];
        C = ROTL(C^u_, t) + S[i+1];
        x = A;  // 数据交换
        A = B;
        B = C;
        C = D;
        D = x;
    }
    A += S[2*r+2];
    C += S[2*r+3];

    c_temp[0] = A;
    c_temp[1] = B;
    c_temp[2] = C;
    c_temp[3] = D;
    for (int i = 0; i < 4; i++){
        cipher[4*i] = c_temp[i] & 0xff;
        cipher[4*i+1] = (c_temp[i] >> 8) & 0xff;
        cipher[4*i+2] = (c_temp[i] >> 16) & 0xff;
        cipher[4*i+3] = (c_temp[i] >> 24) & 0xff;
    }
}


// 解密算法
void rc6_decrypt(unsigned char *cipher, unsigned char *plain)
{
    WORD p_temp[4], c_temp[4];

    for (int i=0; i<4; i++){
        c_temp[i] = cipher[4*i] + (cipher[4*i+1] << 8) +
                (cipher[4*i+2] << 16) + (cipher[4*i+3] << 24);
    }
    WORD A, B, C, D, t, u_, x;
    A = c_temp[0];
    B = c_temp[1];
    C = c_temp[2];
    D = c_temp[3];

    // 解密过程
    C -= S[2*r+3];
    A -= S[2*r+2];
    for (int i=2*r; i>=2; i-=2){
        x = D;
        D = C;
        C = B;
        B = A;
        A = x;
        u_ = ROTL(D*(2*D+1), lgw);
        t = ROTL(B*(2*B+1), lgw);
        C = ROTR(C-S[i+1], t) ^ u_;
        A = ROTR(A-S[i], u_) ^ t;
    }
    D -= S[1];
    B -= S[0];

    // 将 A B C D 寄存器中的数据搬运到 p_temp[4] 中
    // 并将 p_temp[4]中的字搬运到 plain[]（以字节为单位）中
    p_temp[0] = A;
    p_temp[1] = B;
    p_temp[2] = C;
    p_temp[3] = D;
    for (int i=0; i<4; i++){
        plain[4*i] = p_temp[i] & 0xFF;
        plain[4*i+1] = (p_temp[i] >> 8) & 0xFF;
        plain[4*i+2] = (p_temp[i] >> 16) & 0xFF;
        plain[4*i+3] = (p_temp[i] >> 24) & 0xFF;
    }
}


int main(){

    unsigned char key[] = "0123456789abcdef";

    rc6_keygen(key, 16);

    unsigned char plain[16] = "RC6 Algorithm";
    unsigned char cipher[16] = {0};
    unsigned char decrypt[16] = {0};
    cout << "明文是： " << plain << endl;
    for(int i=0; i<16; i++){
        printf("%x ", plain[i]);
    }
    printf("\n\n");

    cout << "加密前，密文是： " << cipher << endl;
    for(int i=0; i<16; i++){
        printf("%x ", cipher[i]);
    }
    printf("\n\n");

    rc6_encrypt(plain, cipher);
    cout << "加密后，密文是：" << endl;
    for(int i=0; i<16; i++){
        printf("%x ", cipher[i]);
    }
    printf("\n\n");

    rc6_decrypt(cipher, decrypt);
    cout << "解密后，译文是：" << decrypt << endl;
    for(int i=0; i<16; i++){
        printf("%x ", decrypt[i]);
    }
    printf("\n\n");


    return 0;
}
