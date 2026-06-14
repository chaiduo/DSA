// 并查集（Disjoint Set / Union-Find）实现
// 支持：查找（带路径压缩）、合并、判断连通性
// 路径压缩：find 时将节点直接挂到根节点下，降低后续查询复杂度

#include <iostream>
#include <vector>
using namespace std;

class DisjSet
{
private:
    int *fa;
public:
    DisjSet() {
        fa = new int[100];
        for(int i = 0; i < 100; i++)fa[i] = i;
    }
    DisjSet(int N) {
        fa = new int[N];
        for(int i = 0; i < N; i++)fa[i] = i;
    }
    // 查找根节点，同时进行路径压缩
    int find(int x){
        if(fa[x] == x)return x;
        return fa[x] = find(fa[x]);
    }
    // 合并两个集合
    void merge(int a, int b){
        fa[find(a)] = find(b);
    }
    // 判断两个元素是否属于同一集合
    bool isconnect(int a, int b){
        return find(a) == find(b);
    }
    // 根据边集构建并查集
    void buildSet(vector<vector<int>>& edges){
        for(int i = 0; i < edges.size(); i++){
            if(!isconnect(edges[i][0], edges[i][1])){
                merge(edges[i][0], edges[i][1]);
            }
        }
    }
};
int main()
{
    int n = 100;
    vector<vector<int>>edges = {{0, 1}, {0, 2}, {3, 5}, {4, 3}};
    DisjSet disjset(n);
    disjset.buildSet(edges);
    
    int a, b;
    while(true){
        cin >> a >> b;
        if(a == -1 || b == -1)break;
        cout << disjset.isconnect(a, b) << endl;
    }
    return 0;
}