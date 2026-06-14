// Linear Sieve for Count of Divisors
// Using multiplicative function property, compute divisor count during linear sieve
// a[i]: power of smallest prime factor of i (e.g., 12=2^2*3, a[12]=2)
// d[i]: count of divisors of i
// Recurrence:
//   - i is prime: d[i] = 2, a[i] = 1
//   - i % p == 0: a[i*p] = a[i]+1, d[i*p] = d[i] / a[i*p] * (a[i*p]+1)
//   - i % p != 0: a[i*p] = 1, d[i*p] = d[i] * 2

#include <iostream>
using namespace std;
const int N = 100010;
int primes[N], vis[N], cnt;
int a[N]; // a[i] = power of smallest prime factor of i
int d[N]; // d[i] = count of divisors of i
void get_primes(int n) {
    d[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            primes[cnt++] = i;
            a[i] = 1, d[i] = 2;  // Prime has 2 divisors
        }
        for(int j = 0; i * primes[j] <= n; j++) {
            int m = i * primes[j];
            vis[m] = 1;
            if(i % primes[j] == 0) {
                // primes[j] is smallest prime factor of i, power increases by 1
                a[m] = a[i] + 1;
                // Divisor count formula: d = (a1+1)(a2+1)..., update corresponding factor
                d[m] = d[i] / a[m] * (a[m] + 1);
            } else {
                // primes[j] is not a factor of i, add new prime factor with power 1
                a[m] = 1;
                d[m] = d[i] * 2;  // Multiply by (1+1)
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