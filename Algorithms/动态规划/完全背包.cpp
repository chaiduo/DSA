// 完全背包问题
// 每种物品可以选无限次，求不超过背包容量的最大价值
// 关键：正序枚举体积（允许同一物品被多次选取）

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;

// 朴素三维写法（注释掉）：枚举每种物品、每种容量、每种选取次数k
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

// 数学推导优化到二维：f[i][j] = max(f[i-1][j], f[i][j-v]+w)
// 因为 f[i][j-v] 已经包含了选过第i件物品的情况，所以可以复用
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

// 一维优化：正序枚举j，f[j-v[i]]已包含当前物品，可重复选取
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