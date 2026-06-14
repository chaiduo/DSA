// Multiple Knapsack Problem (Naive Version)
// Each item has s[i] copies, enumerate the number k to take (0 ~ s[i])
// Time Complexity: O(n * m * s)

#include <iostream>
using namespace std;
const int N = 110;

int v[N], w[N], s[N];
int f[N][N];
int n, m;

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
        cin >> v[i] >> w[i] >> s[i];

    // f[i][j] = max(f[i-1][j-k*v[i]] + k*w[i]), k = 0..s[i]
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j++)
            for(int k = 0; k <= s[i]; k ++)
                if(j >=  k * v[i])
                    f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
    cout << f[n][m] << endl;
    return 0;
}
