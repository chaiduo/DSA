// 求逆元的两种方法
// 逆元定义：a * inv(a) ≡ 1 (mod p)，即 inv(a) 是 a 在模 p 下的乘法逆元
// 1. 扩展欧几里得：解 ax + py = 1，x 即为 a 模 p 的逆元（要求 a,p 互素）
// 2. 费马小定理：当 p 为质数时，inv(a) = a^(p-2) mod p

#include <iostream>
using namespace std;

// 扩展欧几里得（注释掉的版本）
// void exgcd(int a, int b, int &x, int &y){
//     if(!b) {
//         x = 1, y = 0;
//     } else {
//         exgcd(b, a % b, x, y);
//         int t = x;
//         x = y;
//         y = t -  a / b * y;
//     }
// }

// 扩展欧几里得求解 ax + by = gcd(a,b)
// 求逆元时 a,b 必须互素，即求解 ax + by = 1，x 为 a 在 mod b 下的模乘逆元
void exgcd(int a, int b, int &x, int &y){
    if(!b) {
        x = 1, y = 0;    // a*1 + b*0 = gcd(a,b) = a
    } else {
        exgcd(b, a % b, y, x);  // 递归求解
        y -= a / b * x;         // 回溯更新 y
    }
}

// 快速幂（用于费马小定理方法）
int quick_pow(int a, int b, int p){
    int res = 1;
    while(b){
        if(b & 1)res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// 费马小定理求逆元：当 p 为质数时，a^(p-1) ≡ 1 (mod p)
// 所以 a * a^(p-2) ≡ 1 (mod p)，即 inv(a) = a^(p-2) mod p
int inv(int a, int p){
    return quick_pow(a, p - 2, p);
}

int main()
{
    int x, y;
    exgcd(5, 7, x, y);
    cout << inv(5, 7) <<endl;
    cout << x;
}