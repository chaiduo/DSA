// Complete Knapsack Problem
// Each item can be selected unlimited times, find max value within capacity
// Key: Iterate volume in forward order (allows same item to be selected multiple times)

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;

// Naive 3D version (commented out): enumerate each item, each capacity, each count k
#if 0
int f[N][N], v[N], w[N];
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            for(int k = 0; k * v[i] <= j; k++)
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);

    cout << f[n][m] << endl;
    return 0;
}
#endif

// Mathematical derivation to optimize to 2D: f[i][j] = max(f[i-1][j], f[i][j-v]+w)
// Because f[i][j-v] already includes the case where item i was selected, we can reuse it
#if 0

f[i][j]     = max(f[i - 1][j],     f[i - 1][j - v] + w,  f[i - 1][j - 2v] + 2w ....)
f[i][j - v] = max(f[i - 1][j - v], f[i - 1][j - 2v] + w, f[i - 1][j - 3v] + 3w ....)

f[i][j] = max(f[i - 1][j], f[i][j - v] + w);

int f[N][N], v[N], w[N];
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            f[i][j] = f[i - 1][j];
            if(j >= v[i])
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
#endif

// 1D optimization: iterate j in forward order, f[j-v[i]] already includes current item, allowing repeated selection
int f[N], v[N], w[N];
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i++)
        for(int j = v[i]; j <= m; j++)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
    return 0;
}