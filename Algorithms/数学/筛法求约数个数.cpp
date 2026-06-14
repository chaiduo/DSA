// 线性筛法求约数个数
// 利用积性函数性质，在线性筛中递推每个数的约数个数
// a[i]：i 的最小质因子的幂次（如 12=2^2*3，a[12]=2）
// d[i]：i 的约数个数
// 递推关系：
//   - i 为质数：d[i] = 2, a[i] = 1
//   - i % p == 0：a[i*p] = a[i]+1, d[i*p] = d[i] / a[i*p] * (a[i*p]+1)
//   - i % p != 0：a[i*p] = 1, d[i*p] = d[i] * 2

#include <iostream>
using namespace std;
const int N = 100010;
int primes[N], vis[N], cnt;
int a[N]; // a[i]表示i的最小质因子的次数
int d[N]; // d[i]表示i的约数个数
void get_primes(int n) {
    d[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            primes[cnt++] = i;
            a[i] = 1, d[i] = 2;  // 质数约数个数为2
        }
        for(int j = 0; i * primes[j] <= n; j++) {
            int m = i * primes[j];
            vis[m] = 1;
            if(i % primes[j] == 0) {
                // primes[j] 是 i 的最小质因子，幂次+1
                a[m] = a[i] + 1;
                // 约数个数公式：d = (a1+1)(a2+1)...，更新对应因子
                d[m] = d[i] / a[m] * (a[m] + 1);
            } else {
                // primes[j] 不是 i 的因子，新增一个幂次为1的质因子
                a[m] = 1;
                d[m] = d[i] * 2;  // 乘上 (1+1)
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