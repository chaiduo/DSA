// 多重背包（二进制优化）
// 将每种物品的 s[i] 件拆分为 1,2,4,8... 的组，转化为 01 背包
// 原理：任意数字都可以用二进制组合表示，如 13 = 1+2+4+6
// 时间复杂度从 O(n*m*s) 优化到 O(n*m*log(s))

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

        // 二进制拆分：将 c 件物品拆成 1,2,4,8... 的组合
        int k = 1;
        while(k <= c) {
            cnt ++;
            v[cnt] = k * a;  // 体积
            w[cnt] = k * b;  // 价值
            c -= k;
            k *= 2;
        }
        // 剩余部分单独成组
        if(c) {
            cnt++;
            v[cnt] = c * a;
            w[cnt] = c * b;
        }

    }

    // 转化为 01 背包求解
    for(int i = 1; i <= cnt; i++) {
        for(int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}