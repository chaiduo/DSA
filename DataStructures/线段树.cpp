// 线段树实现（带懒标记）
// 支持：单点修改、区间修改、区间求和
// 时间复杂度：修改/查询均为 O(log n)
// 核心：懒标记（lazy tag）延迟下推，避免重复修改子节点

#include <iostream>
using namespace std;

#define N 100005
#define lc p << 1      // 左子节点
#define rc p << 1 | 1  // 右子节点
int n, w[N];

struct SegNode {
    int l, r;
    int sum;   // 区间和
    int add;   // 懒标记：待下推的增量
} tr[N * 4];

// 建树：递归构建，叶子节点初始化
void build(int p, int l, int r) 
{
    tr[p] = {l, r, w[l], 0};
    if(l == r) return ;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// 懒标记下推：将当前节点的增量传递给子节点
void pushdown(int p)
{
    if(tr[p].add) {
        tr[lc].sum += tr[p].add * (tr[lc].r - tr[lc].l + 1);
        tr[rc].sum += tr[p].add * (tr[rc].r - tr[rc].l + 1);
        tr[lc].add += tr[p].add;
        tr[rc].add += tr[p].add;
        tr[p].add = 0;
    }
}

// 单点修改：位置 x 加上 k
void update(int p, int x, int k)
{
    if(tr[p].l == x && tr[p].r == x) {
        tr[p].sum += k;
        return ;
    }
    int m = (tr[p].r + tr[p].l) >> 1;
    if(x <= m) update(lc, x, k);
    if(x > m) update(rc, x, k);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// 区间修改：[x, y] 区间每个位置加上 k
void update(int p, int x, int y, int k)
{
    if(x <= tr[p].l && tr[p].r <= y) {
        tr[p].sum += (tr[p].r - tr[p].l + 1) * k;
        tr[p].add += k;
        return ;
    }
    int m = (tr[p].l + tr[p].r) >> 1;
    pushdown(p);  // 下推懒标记
    if(x <= m) update(lc, x, y, k);
    if(y > m) update(rc, x, y, k);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// 区间查询：求 [x, y] 的和
int query(int p, int x, int y)
{
    if(x <= tr[p].l && tr[p].r <= y) 
        return tr[p].sum;
    int m = (tr[p].l + tr[p].r) >> 1;
    pushdown(p);  // 下推懒标记
    int sum = 0;
    if(x <= m) sum += query(lc, x, y);
    if(y > m) sum += query(rc, x, y);
    return sum;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);
    int m;
    cin >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        cout << query(1, a, b) << endl;
    }
}