// Multiple Knapsack Problem (Binary Optimization)
// Split s[i] copies of each item into groups of 1,2,4,8..., converting to 0/1 Knapsack
// Principle: Any number can be represented as binary combination, e.g., 13 = 1+2+4+6
// Time Complexity optimized from O(n*m*s) to O(n*m*log(s))

#include <iostream>
using namespace std;

const int N = 25000;
int v[N], w[N], s[N], f[N];
int n, m, cnt;
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        // Binary splitting: split c items into combinations of 1,2,4,8...
        int k = 1;
        while(k <= c) {
            cnt ++;
            v[cnt] = k * a;  // volume
            w[cnt] = k * b;  // value
            c -= k;
            k *= 2;
        }
        // Remaining part as a separate group
        if(c) {
            cnt++;
            v[cnt] = c * a;
            w[cnt] = c * b;
        }

    }

    // Convert to 0/1 Knapsack problem
    for(int i = 1; i <= cnt; i++) {
        for(int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}