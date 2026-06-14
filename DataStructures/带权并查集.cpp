// 带权并查集（LeetCode 399. 除法求值）
// 在普通并查集基础上维护节点间的权值关系
// f[x]：x 的父节点
// w[x]：x 到父节点的权值（路径压缩后变为到根节点的权值）
// 用于求解变量间的除法关系

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 查找根节点，同时进行路径压缩和权值累乘
// 查找后 f[x] 为根节点，w[x] 为 x 到根的权值
int findf(vector<int>& f, vector<double>& w, int x) {
    if (f[x] != x) {
        int father = findf(f, w, f[x]);
        w[x] = w[x] * w[f[x]];  // 累乘权值
        f[x] = father;          // 路径压缩
    }
    return f[x];
}

// 合并两个集合，维护权值关系
// val = x / y，即 x = val * y
void merge(vector<int>& f, vector<double>& w, int x, int y, double val) {
    int fx = findf(f, w, x);
    int fy = findf(f, w, y);
    f[fx] = fy;
    w[fx] = val * w[y] / w[x];  // 推导：w[x] * w[fx] = val * w[y]
}

// 主函数：根据已知等式求解查询
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    int nvars = 0;
    unordered_map<string, int> variables;  // 字符串映射到整数编号

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
    for (int i = 0; i < nvars; i++) f[i] = i;  // 初始化：每个节点独立
    
    // 根据已知等式构建并查集
    for (int i = 0; i < n; i++) {
        int va = variables[equations[i][0]], vb = variables[equations[i][1]];
        merge(f, w, va, vb, values[i]);
    }
    
    // 处理查询
    vector<double> ret;
    for (const auto& q: queries) {
        double result = -1.0;
        if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end()) {
            int ia = variables[q[0]], ib = variables[q[1]];
            int fa = findf(f, w, ia), fb = findf(f, w, ib);
            if (fa == fb) {  // 同一集合才可求解
                result = w[ia] / w[ib];
            }
        }
        ret.push_back(result);
    }
    return ret;
}