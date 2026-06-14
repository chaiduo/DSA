// 筛质数的三种方法
// 1. 朴素筛法 O(nlogn)：对每个数标记其倍数
// 2. 埃氏筛法 O(nloglogn)：只对质数标记其倍数
// 3. 线性筛法（欧拉筛）O(n)：每个合数只被其最小质因子筛掉一次

#include <iostream>
using namespace std;

const int N = 1e6;
bool st[N];
int primes[N];
int cnt;

// 朴素筛法 O(nlogn)：每个数都去标记自己的倍数，有重复标记
void getPrimes1(int n) {
    for(int i = 2; i <= n; i++) {
        if(!st[i]) primes[cnt++] = i;
        for(int j = i + i; j <= n; j += i) {
            st[j] = true;
        }
    }
}
// 埃氏筛法 O(nloglogn)：只对质数标记倍数，减少重复
void getPrimes2(int n) {
    for(int i = 2; i <= n; i++) {
        if(!st[i]) {
            primes[cnt++] = i;
            for(int j = i + i; j <= n; j += i) {
                st[j] = true;
            }
        }
    }
}
// 线性筛法 O(n)：每个合数只被最小质因子筛掉
// 关键：i % primes[j] == 0 时 break，保证 primes[j] 是 i*primes[j] 的最小质因子
void getPrimes3(int n) {
    for(int i = 2; i <= n; i++) {
        if(!st[i]) primes[cnt++] = i;
        for(int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    getPrimes3(n);
    for(int i = 0; i < cnt; i++) cout << primes[i] << " ";
    return 0;
}