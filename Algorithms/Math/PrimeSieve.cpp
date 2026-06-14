// Three Methods for Prime Sieve
// 1. Naive Sieve O(nlogn): Mark multiples of each number
// 2. Sieve of Eratosthenes O(nloglogn): Only mark multiples of primes
// 3. Linear Sieve (Euler Sieve) O(n): Each composite is sieved only by its smallest prime factor

#include <iostream>
using namespace std;

const int N = 1e6;
bool st[N];
int primes[N];
int cnt;

// Naive Sieve O(nlogn): Each number marks its multiples, has redundant marking
void getPrimes1(int n) {
    for(int i = 2; i <= n; i++) {
        if(!st[i]) primes[cnt++] = i;
        for(int j = i + i; j <= n; j += i) {
            st[j] = true;
        }
    }
}
// Sieve of Eratosthenes O(nloglogn): Only primes mark their multiples, reduces redundancy
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
// Linear Sieve O(n): Each composite is sieved only by its smallest prime factor
// Key: Break when i % primes[j] == 0, ensuring primes[j] is the smallest prime factor of i*primes[j]
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