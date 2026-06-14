// Tarjan 算法求割边/桥（无向图）
// 割边：删除该边后图的连通分量数增加
// 时间复杂度 O(n + m)
// 判定条件：low[y] > dfn[x]（注意是严格大于，区别于割点）
// 用边编号避免走回父边（而非用 vis 标记节点）

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 160, M = 5010;
typedef pair<int,int> edge;

int n, m;
vector<edge> eg;       // 存所有边
vector<int> h[N];      // 邻接表，存边编号
vector<edge>bridge;    // 存储割边
int dfn[N], low[N], tot;

void add(int a, int b) {
    eg.push_back({a, b});
    h[a].push_back(eg.size() - 1);  // 记录边编号
}

// in_edge 为进入当前节点的边的编号，用于避免走回父边
void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++tot;
    for(int i : h[x]) {
        int y = eg[i].second;
        if(!dfn[y]) {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if(low[y] > dfn[x]) bridge.push_back({x, y});  // 割边判定
        } else if(abs(i - in_edge) != 1) {  // 不是同一条边的反向边
            low[x] = min(low[x], dfn[y]);
        }
    }
}
int main()
{
    cin >> n >> m;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        add(a, b); add(b, a);  // 无向边存为两条有向边
    }

    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) tarjan(i, -1);

    sort(bridge.begin(), bridge.end());
    for(auto t : bridge) cout << t.first << " " << t.second << endl;
    return 0;
}
