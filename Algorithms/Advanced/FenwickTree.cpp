// Binary Indexed Tree (Fenwick Tree) Implementation
// Supports: point update, prefix sum query
// Time Complexity: O(log n) for both update and query
// Core: Uses lowbit(x) = x & -x to maintain tree structure

#include <iostream>

using namespace std;

const int N = 500010;
int a[N];  // BIT array
int n, m;

// Point update: add k to position x, update all ancestors
void update(int x, int k) {
    while(x <= n) {
        a[x] += k;
        x += (x & -x);  // Jump to parent
    }
}

// Prefix query: get sum of 1~x, accumulate along the path
int query(int x) {
    int sum = 0;
    while(x) {
        sum += a[x];
        x -= (x & -x);  // Jump to left sibling
    }
    return sum;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int k; cin >> k;
        update(i, k);  // Initialize
    }

    int op, x, y;
    while(m--) {
        cin >> op >> x >> y;
        if(op == 1) update(x, y);           // Point update
        else cout << query(y) - query(x - 1) << endl;  // Range sum
    }
    return 0;
}