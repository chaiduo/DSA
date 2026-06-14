// 线性筛法求约数之和
// 利用积性函数性质，在线性筛中递推每个数的约数之和
// g[i]：i 的最小质因子的等比级数和（1 + p + p^2 + ... + p^k）
// f[i]：i 的约数之和
// 递推关系：
//   - i 为质数：g[i] = f[i] = i + 1
//   - i % p == 0：g[i*p] = g[i]*p + 1, f[i*p] = f[i]/g[i] * g[i*p]
//   - i % p != 0：g[i*p] = 1 + p, f[i*p] = f[i] * g[i*p]

#include <iostream>
using namespace std;
const int N = 100010;
int primes[N], vis[N], cnt;
int g[N]; // g[i]表示i的最小质因子的 1 + p^1 + p^2 + ...
int f[N]; // f[i]表示i的约数之和
void get_primes(int n) {
    g[1] = f[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            primes[cnt++] = i;
            g[i] = f[i] = i + 1;  // 质数的约数和 = 1 + i
        }
        for(int j = 0; i * primes[j] <= n; j++) {
            int m = i * primes[j];
            vis[m] = 1;
            if(i % primes[j] == 0) {
                // primes[j] 是 i 的最小质因子，等比级数多一项
                g[m] = g[i] * primes[j] + 1;
                // 约数和是积性函数，替换对应因子部分
                f[m] = f[i] / g[i] * g[m];
            } else {
                // primes[j] 不是 i 的因子，新增因子 (1 + p)
                g[m] = 1 + primes[j];
                f[m] = g[m] * f[i];
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    get_primes(n);
    return 0;
}