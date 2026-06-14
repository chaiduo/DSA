// Linear Sieve for Euler's Totient Function (sum of φ(1) to φ(n))
// Based on linear sieve, compute Euler's totient for each number during prime sieving
// Recurrence:
//   - i is prime: φ(i) = i - 1
//   - i % p == 0: φ(i*p) = φ(i) * p (p is a prime factor of i, no new prime factor)
//   - i % p != 0: φ(i*p) = φ(i) * (p-1) (p is a new prime factor)

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
            eu[i] = i - 1;  // Euler's totient of prime is i-1
        }
        for(int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) {
                // primes[j] is a prime factor of i, φ(i*p) = φ(i) * p
                eu[primes[j] * i] = eu[i] * primes[j];
                break;
            } else {
                // primes[j] is not a prime factor of i, φ(i*p) = φ(i) * (p-1)
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