// Weighted Disjoint Set Union (LeetCode 399. Evaluate Division)
// Extends standard DSU to maintain weight relationships between nodes
// f[x]: parent of x
// w[x]: weight from x to parent (becomes weight to root after path compression)
// Used to solve division relationships between variables

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Find root with path compression and weight accumulation
// After finding: f[x] is root, w[x] is weight from x to root
int findf(vector<int>& f, vector<double>& w, int x) {
    if (f[x] != x) {
        int father = findf(f, w, f[x]);
        w[x] = w[x] * w[f[x]];  // Accumulate weights
        f[x] = father;          // Path compression
    }
    return f[x];
}

// Merge two sets while maintaining weight relationship
// val = x / y, i.e., x = val * y
void merge(vector<int>& f, vector<double>& w, int x, int y, double val) {
    int fx = findf(f, w, x);
    int fy = findf(f, w, y);
    f[fx] = fy;
    w[fx] = val * w[y] / w[x];  // Derivation: w[x] * w[fx] = val * w[y]
}

// Main function: solve queries based on known equations
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    int nvars = 0;
    unordered_map<string, int> variables;  // Map strings to integer indices

    int n = equations.size();
    for (int i = 0; i < n; i++) {
        if (variables.find(equations[i][0]) == variables.end()) {
            variables[equations[i][0]] = nvars++;
        }
        if (variables.find(equations[i][1]) == variables.end()) {
            variables[equations[i][1]] = nvars++;
        }
    }

    vector<int> f(nvars);
    vector<double> w(nvars, 1.0);
    for (int i = 0; i < nvars; i++) f[i] = i;  // Initialize: each node is independent

    // Build DSU based on known equations
    for (int i = 0; i < n; i++) {
        int va = variables[equations[i][0]], vb = variables[equations[i][1]];
        merge(f, w, va, vb, values[i]);
    }

    // Process queries
    vector<double> ret;
    for (const auto& q: queries) {
        double result = -1.0;
        if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end()) {
            int ia = variables[q[0]], ib = variables[q[1]];
            int fa = findf(f, w, ia), fb = findf(f, w, ib);
            if (fa == fb) {  // Solvable only if in the same set
                result = w[ia] / w[ib];
            }
        }
        ret.push_back(result);
    }
    return ret;
}