// 快速幂算法
// 计算 a^b，时间复杂度 O(log b)
// 原理：将指数 b 按二进制分解，如 b=13=1101，则 a^13 = a^8 * a^4 * a^1

#include <iostream>
#include <algorithm>

using namespace std;

// 去掉最低位的1
int removeLowBit(int n) {
    return n & (n - 1);
}

// 获取最低位的1（用于位运算技巧）
int lowbit(int n) {
    return n & (-n);
}

// 辗转相除法求最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 快速幂：计算 a^b
// 核心：b为奇数时乘上当前的a，然后a平方，b右移
long long fastPower(int a, int b) {
    long long ans = 1;
    while(b) {
        if(b & 1)ans *= a;  // b的当前位为1，乘上a
        a *= a;              // a = a^2
        b >>= 1;             // b右移一位
    }
    return ans;
}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << fastPower(a, b);
    return 0; 
}