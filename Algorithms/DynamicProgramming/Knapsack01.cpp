// 0/1 Knapsack Problem
// Each item can be chosen at most once, find max value within capacity
// Optimization: 1D array with reverse iteration on volume (ensures each item selected at most once)

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;
int v[N], w[N], f[N];

// 2D version (commented out): f[i][j] = max value using first i items with capacity j
#if 0
int f[N][N];
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            f[i][j] = f[i - 1][j];
            if(j >= v[i])
                f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);
        }

    cout << f[n][m] << endl;
    return 0;
}
#endif

// 1D optimization: reverse iterate j, ensures f[j-v[i]] is from previous layer (item not yet selected)
int main()
{
    int n, m;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i++)
        for(int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
    return 0;
}