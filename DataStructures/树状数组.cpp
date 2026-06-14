// 树状数组（Binary Indexed Tree / Fenwick Tree）实现
// 支持：单点修改、区间求和
// 时间复杂度：修改/查询均为 O(log n)
// 核心：利用 lowbit(x) = x & -x 维护树形结构

#include <iostream>

using namespace std;

const int N = 500010;
int a[N];  // 树状数组
int n, m;

// 单点修改：在位置 x 加上 k，向上更新所有祖先节点
void update(int x, int k) { 
    while(x <= n) {
        a[x] += k;
        x += (x & -x);  // 跳到父节点
    }
}

// 前缀查询：求 1~x 的和，沿路径累加
int query(int x) {
    int sum = 0;
    while(x) {
        sum += a[x];
        x -= (x & -x);  // 跳到左兄弟
    }
    return sum;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int k; cin >> k;
        update(i, k);  // 初始化
    }

    int op, x, y;
    while(m--) {
        cin >> op >> x >> y;
        if(op == 1) update(x, y);           // 单点修改
        else cout << query(y) - query(x - 1) << endl;  // 区间求和
    }
    return 0;
}