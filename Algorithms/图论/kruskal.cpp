// Kruskal 算法：求最小生成树
// 时间复杂度 O(m log m)
// 核心思想：贪心，按边权从小到大排序，依次加入不构成环的边
// 用并查集判断是否成环

#include <iostream>
#include <algorithm>
using namespace std;

const int M = 2e5, N = 1e5;
struct Edge {
    int a, b, w;
} edge[M];
int n, m;
int f[N];

int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);  // 路径压缩
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }
    // 按边权升序排序
    sort(edge, edge + m, [&](auto t1, auto t2) {
        return t1.w < t2.w;
    });
    
    for(int i = 1; i <= n; i++) f[i] = i;  // 初始化并查集
    
    int ans = 0, cnt = 0;
    for(int i = 0; i < m; i++) {
        int a = find(edge[i].a);
        int b = find(edge[i].b);
        if(a != b) {  // 不在同一集合，加入该边
            ans += edge[i].w;
            f[a] = b;
            cnt++;
        }
        if(cnt == n - 1) break;  // 已选够 n-1 条边
    }
    if(cnt < n - 1) cout << "impossible";  // 图不连通
    else cout << ans;
    return 0;
}