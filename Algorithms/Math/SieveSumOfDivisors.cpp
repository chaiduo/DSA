// Linear Sieve for Sum of Divisors
// Using multiplicative function property, compute divisor sum during linear sieve
// g[i]: geometric series sum of smallest prime factor of i (1 + p + p^2 + ... + p^k)
// f[i]: sum of divisors of i
// Recurrence:
//   - i is prime: g[i] = f[i] = i + 1
//   - i % p == 0: g[i*p] = g[i]*p + 1, f[i*p] = f[i]/g[i] * g[i*p]
//   - i % p != 0: g[i*p] = 1 + p, f[i*p] = f[i] * g[i*p]

#include <iostream>
using namespace std;
const int N = 100010;
int primes[N], vis[N], cnt;
int g[N]; // g[i] = 1 + p^1 + p^2 + ... for smallest prime factor p of i
int f[N]; // f[i] = sum of divisors of i
void get_primes(int n) {
    g[1] = f[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            primes[cnt++] = i;
            g[i] = f[i] = i + 1;  // Divisor sum of prime = 1 + i
        }
        for(int j = 0; i * primes[j] <= n; j++) {
            int m = i * primes[j];
            vis[m] = 1;
            if(i % primes[j] == 0) {
                // primes[j] is smallest prime factor of i, add one more term to geometric series
                g[m] = g[i] * primes[j] + 1;
                // Divisor sum is multiplicative, replace corresponding factor part
                f[m] = f[i] / g[i] * g[m];
            } else {
                // primes[j] is not a factor of i, add new factor (1 + p)
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