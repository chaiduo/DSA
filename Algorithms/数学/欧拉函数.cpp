// 欧拉函数 φ(n)：1~n中与n互质的数的个数
// 公式：φ(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk)
// 其中 p1,p2,...,pk 是 n 的所有不同质因子

#include <iostream>
using namespace std;

int main()
{
    int m, a;
    cin >> m;
    while(m--) {
        cin >> a;
        int ans = a;
        // 枚举 2~sqrt(a) 的所有质因子
        for(int i = 2; i <= a / i; i++) {
            if(a % i == 0) {
                ans = ans / i * (i - 1);  // 乘上 (1 - 1/i) = (i-1)/i
                while(a % i == 0) a /= i; // 除尽该质因子
            }
        }
        // 如果还有剩余的大于1的质因子
        if(a > 1) ans = ans / a * (a - 1);
        cout << ans << endl;
    }
    return 0;
}