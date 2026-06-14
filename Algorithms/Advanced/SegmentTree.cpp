// Segment Tree Implementation (with Lazy Propagation)
// Supports: point update, range update, range sum query
// Time Complexity: O(log n) for both update and query
// Core: Lazy tag delays propagation to avoid repeated child updates

#include <iostream>
using namespace std;

#define N 100005
#define lc p << 1      // Left child
#define rc p << 1 | 1  // Right child
int n, w[N];

struct SegNode {
    int l, r;
    int sum;   // Range sum
    int add;   // Lazy tag: pending increment to push down
} tr[N * 4];

// Build tree: recursive construction, initialize leaf nodes
void build(int p, int l, int r)
{
    tr[p] = {l, r, w[l], 0};
    if(l == r) return ;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// Push down lazy tag: propagate current node's increment to children
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

// Point update: add k to position x
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

// Range update: add k to each position in [x, y]
void update(int p, int x, int y, int k)
{
    if(x <= tr[p].l && tr[p].r <= y) {
        tr[p].sum += (tr[p].r - tr[p].l + 1) * k;
        tr[p].add += k;
        return ;
    }
    int m = (tr[p].l + tr[p].r) >> 1;
    pushdown(p);  // Push down lazy tag
    if(x <= m) update(lc, x, y, k);
    if(y > m) update(rc, x, y, k);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// Range query: get sum of [x, y]
int query(int p, int x, int y)
{
    if(x <= tr[p].l && tr[p].r <= y)
        return tr[p].sum;
    int m = (tr[p].l + tr[p].r) >> 1;
    pushdown(p);  // Push down lazy tag
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