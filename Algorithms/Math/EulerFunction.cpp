// Euler's Totient Function φ(n): Count of integers in [1,n] that are coprime to n
// Formula: φ(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk)
// Where p1, p2, ..., pk are all distinct prime factors of n

#include <iostream>
using namespace std;

int main()
{
    int m, a;
    cin >> m;
    while(m--) {
        cin >> a;
        int ans = a;
        // Enumerate all prime factors from 2 to sqrt(a)
        for(int i = 2; i <= a / i; i++) {
            if(a % i == 0) {
                ans = ans / i * (i - 1);  // Multiply by (1 - 1/i) = (i-1)/i
                while(a % i == 0) a /= i; // Remove this prime factor completely
            }
        }
        // If there's a remaining prime factor > 1
        if(a > 1) ans = ans / a * (a - 1);
        cout << ans << endl;
    }
    return 0;
}