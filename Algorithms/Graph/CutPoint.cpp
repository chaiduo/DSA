// Tarjan's Algorithm for Finding Cut Points (Articulation Points) in Undirected Graph
// Cut Point: A vertex whose removal increases the number of connected components
// Time Complexity: O(n + m)
// Criteria:
//   - Root node: cut point if it has more than 1 child
//   - Non-root node: cut point if there exists a child y such that low[y] >= dfn[x]

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 20010;

int n, m, root;
vector<int> edge[N];
int dfn[N], low[N], tot;
bool cut[N];  // cut[i] marks if i is a cut point

void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    int child = 0;
    for(int y : edge[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if(low[y] >= dfn[x]) {  // y cannot reach x's ancestors
                child++;
                if(x != root || child > 1) {  // Root needs at least 2 subtrees
                    cut[x] = true;
                }
            }
        } else {
            low[x] = min(low[x], dfn[y]);  // Back edge
        }
    }
}
int main()
{
    cin >> n >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) {
            root = i;
            tarjan(i);
        }
    for(int i = 1; i <= n; i++)
        if(cut[i]) cout << i << " ";
    return 0;
}