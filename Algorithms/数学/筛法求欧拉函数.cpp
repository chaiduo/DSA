// 线性筛法求欧拉函数（1~n所有数的欧拉函数之和）
// 基于线性筛，在筛质数的同时递推计算每个数的欧拉函数
// 递推关系：
//   - i 为质数：φ(i) = i - 1
//   - i % p == 0：φ(i*p) = φ(i) * p（p 是 i 的质因子，不引入新质因子）
//   - i % p != 0：φ(i*p) = φ(i) * (p-1)（p 是新质因子）

#include <iostream>
using namespace std;
const int N = 1000010;
int primes[N], cnt;
int eu[N];
bool st[N];

long long get_euler(int n)
{
    eu[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!st[i]) {
            primes[cnt++] = i;
            eu[i] = i - 1;  // 质数的欧拉函数为 i-1
        }
        for(int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) {
                // primes[j] 是 i 的质因子，φ(i*p) = φ(i) * p
                eu[primes[j] * i] = eu[i] * primes[j];
                break;
            } else {
                // primes[j] 不是 i 的质因子，φ(i*p) = φ(i) * (p-1)
                eu[primes[j] * i] = eu[i] * (primes[j] - 1);
            }
        }
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) ans += eu[i];
    return ans;
}
int main()
{
    int n;
    cin >> n;
    cout << get_euler(n); 
    return 0;
}