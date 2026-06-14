// Floyd-Warshall 算法：求多源最短路
// 时间复杂度 O(n^3)，空间复杂度 O(n^2)
// 核心思想：枚举中转点 k，更新所有点对 (i,j) 的最短距离
// dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

#include <iostream>
using namespace std;
int n, m;
const int N = 500, M = 100000;
int dist[N][N];

// Floyd 主循环：k 为中转点
void floyd()
{
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
int main()
{
    int x, y, z;
    cin >> n >> m;
    while(m--) {
        cin >> x >> y >> z;
        dist[x][y] = z;
    }
    floyd();
    cout << dist[1][n] << endl;
    return 0;
}
