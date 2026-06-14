// Floyd 求无向图最小环
// 时间复杂度 O(n^3)
// 核心思想：枚举环上编号最大的节点 k，环由 i->k、j->k 和 i~j 的最短路组成
// 在 Floyd 的第 k 轮迭代前，w[i][j] 保存的是只经过 1~k-1 的最短路
// 环长 = w[i][j] + g[i][k] + g[j][k]（i < k, j < k）
// 用 p 数组记录路径

#include <iostream>
#include <cstring>
using namespace std;

const int N = 110, INF = 0x3f3f3f3f;
int g[N][N], w[N][N], p[N][N];  // g: 邻接矩阵, w: 最短路矩阵, p: 路径记录
int cnt, path[N];

// 递归还原 i~j 的路径
void get_path(int i, int j) {
    if(p[i][j] == 0) return ;
    int k = p[i][j];
    get_path(i, k);
    path[cnt++] = k;
    get_path(k, j);
}

int main()
{
    int n, m;
    cin >> n >> m;
    
    memset(g, 0x3f, sizeof g);
    for(int i = 0; i <= n; i++) g[i][i] = 0;
    while(m --) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(c, g[a][b]);
    }
    
    int ans = INF;
    memcpy(w, g, sizeof g);
    for(int k = 1; k <= n; k++) {
        // 在第 k 轮 Floyd 前，用 w[i][j] + g[i][k] + g[j][k] 更新最小环
        for(int i = 1; i < k; i++)
            for(int j = i + 1; j < k; j++)
                if((long long)w[i][j] + g[i][k] + g[j][k] < ans) {
                    ans = (long long)w[i][j] + g[i][k] + g[j][k];
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);
                    path[cnt++] = j;
                }
        
        // 正常 Floyd 迭代
        for(int i = 1; i <= n; i++) 
            for(int j = 1; j <= n; j++) {
                if(w[i][j] > w[i][k] + w[k][j]) {
                    w[i][j] = w[i][k] + w[k][j];
                    p[i][j] = k;
                }
            }
    }
    if(ans == INF) cout << "No solution." << endl;
    else for(int i = 0; i < cnt; i++) cout << path[i] << " ";
    return 0;
}
