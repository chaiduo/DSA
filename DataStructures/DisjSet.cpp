// Disjoint Set (Union-Find) Implementation
// Supports: find (with path compression), union, check connectivity
// Path compression: during find, attach node directly to root, reducing future query complexity

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
    // Find root node with path compression
    int find(int x){
        if(fa[x] == x)return x;
        return fa[x] = find(fa[x]);
    }
    // Merge two sets
    void merge(int a, int b){
        fa[find(a)] = find(b);
    }
    // Check if two elements belong to the same set
    bool isconnect(int a, int b){
        return find(a) == find(b);
    }
    // Build disjoint set from edge list
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