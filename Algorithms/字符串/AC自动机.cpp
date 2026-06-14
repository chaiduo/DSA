// AC 自动机（Aho-Corasick Automaton）
// 用于多模式串匹配，在文本串中同时查找多个模式串的出现次数
// 时间复杂度 O(n + m + z)，n 为模式串总长，m 为文本串长，z 为匹配数
// 核心：Trie 树 + KMP 的 fail 指针（称为 next 或 fail 数组）
// 通过 BFS 构建 fail 指针，实现失配时的快速跳转

#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 500010;
int n;
char str[1000010];
int ch[N][26], cnt[N], idx;  // ch: Trie树, cnt: 单词结尾计数, idx: 节点编号
int ne[N];  // fail 指针

// 插入模式串到 Trie 树
void insert(char *s) { 
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int j = s[i] - 'a';
        if (!ch[p][j]) ch[p][j] = ++idx;
        p = ch[p][j];
    }
    cnt[p]++;  // 标记单词结尾
}

// BFS 构建 fail 指针
// fail[u] 指向 u 的最长后缀对应的节点
void build() {
    queue<int> q;
    // 根节点的子节点入队
    for (int i = 0; i < 26; i++)
        if (ch[0][i]) q.push(ch[0][i]);
    
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            int v = ch[u][i];
            if (v) {
                // 子节点的 fail 指向父节点 fail 的对应子节点
                ne[v] = ch[ne[u]][i];
                q.push(v);
            } else {
                // 虚拟边：直接指向 fail 的对应子节点
                ch[u][i] = ch[ne[u]][i];
            }
        }
    }
}

// 在文本串中查询匹配的模式串数量
int query(char *s) {
    int ans = 0;
    for (int k = 0, i = 0; s[k]; k++) {
        i = ch[i][s[k] - 'a'];  // 沿 Trie 树匹配
        // 沿 fail 指针回溯，统计所有匹配的模式串
        for (int j = i; j && ~cnt[j]; j = ne[j]) {
            ans += cnt[j];
            cnt[j] = -1;  // 标记已统计，避免重复
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> str, insert(str);
    
    build();  // 构建 fail 指针
    
    cin >> str;
    cout << query(str) << endl;
    return 0;
}