// Aho-Corasick Automaton (AC Automaton)
// Multi-pattern string matching: find occurrences of multiple patterns in a text
// Time Complexity: O(n + m + z), n = total pattern length, m = text length, z = match count
// Core: Trie tree + KMP's fail pointer (also called next or fail array)
// Build fail pointers via BFS for efficient mismatch transitions

#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 500010;
int n;
char str[1000010];
int ch[N][26], cnt[N], idx;  // ch: Trie tree, cnt: word end count, idx: node index
int ne[N];  // fail pointer

// Insert pattern string into Trie
void insert(char *s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int j = s[i] - 'a';
        if (!ch[p][j]) ch[p][j] = ++idx;
        p = ch[p][j];
    }
    cnt[p]++;  // Mark word end
}

// Build fail pointers via BFS
// fail[u] points to the node representing u's longest suffix
void build() {
    queue<int> q;
    // Enqueue root's children
    for (int i = 0; i < 26; i++)
        if (ch[0][i]) q.push(ch[0][i]);

    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            int v = ch[u][i];
            if (v) {
                // Child's fail points to parent's fail's corresponding child
                ne[v] = ch[ne[u]][i];
                q.push(v);
            } else {
                // Virtual edge: directly point to fail's corresponding child
                ch[u][i] = ch[ne[u]][i];
            }
        }
    }
}

// Query: count pattern occurrences in text
int query(char *s) {
    int ans = 0;
    for (int k = 0, i = 0; s[k]; k++) {
        i = ch[i][s[k] - 'a'];  // Traverse Trie
        // Backtrack via fail pointers, count all matches
        for (int j = i; j && ~cnt[j]; j = ne[j]) {
            ans += cnt[j];
            cnt[j] = -1;  // Mark as counted to avoid duplicates
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> str, insert(str);
    
    build();  // Build fail pointers
    
    cin >> str;
    cout << query(str) << endl;
    return 0;
}