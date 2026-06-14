// 染色法判定二分图
// 时间复杂度 O(n + m)
// 核心思想：二分图等价于可以用两种颜色染色，使得相邻节点颜色不同
// 用 DFS 尝试二染色，若出现冲突则不是二分图

#include <iostream>
#include <vector>
using namespace std;
const int N = 100010;
int n, m;
vector<vector<int>>g(N);
int color[N]; // 0:未染色, 1:颜色1, -1:颜色-1

// DFS 染色，idx 为当前节点，cor 为其颜色
bool dfs(int idx, int cor) 
{
    for(auto x : g[idx]) {
        if(!color[x]) {
            color[x] = cor;       // 染上相反颜色
            if(!dfs(x, -cor)) return false;
        } else if(color[x] != cor) {
            return false;          // 相邻节点颜色相同，冲突
        }
    }
    return true;
}
int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!color[i]) {
            color[i] = 1;
            if(!dfs(i, -1)) {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}