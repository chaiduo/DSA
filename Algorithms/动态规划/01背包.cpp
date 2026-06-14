// 01背包问题
// 每种物品只能选或不选，求不超过背包容量的最大价值
// 优化：一维数组逆序枚举体积（保证每件物品只选一次）

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;
int v[N], w[N], f[N];

// 二维写法（注释掉）：f[i][j] 表示前i个物品、容量为j时的最大价值
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

// 一维优化：逆序枚举j，保证f[j-v[i]]是上一层（未选当前物品）的状态
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