// KMP 字符串匹配算法
// 时间复杂度 O(n + m)，n 为模式串长度，m 为文本串长度
// 核心：利用 next 数组（失配指针）避免重复匹配
// ne[i] 表示模式串前 i 个字符组成的子串中，最长相等前后缀的长度

#include <iostream>
using namespace std;

const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n,m;
char p[N], s[M];
int ne[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;

    // 构建 next 数组（模式串自己匹配自己）
    for(int i = 2, j = 0; i <= n; i++) {
        while(j && p[i] != p[j + 1]) j = ne[j];  // 失配则回退
        if(p[i] == p[j + 1]) j++;
        ne[i] = j;
    }

    // 在文本串 s 中匹配模式串 p
    for(int i = 1, j = 0; i <= m; i++) {
        while(j && s[i] != p[j + 1]) j = ne[j];  // 失配则回退
        if(s[i] == p[j + 1]) j++;
        if(j == n) {
            cout << i - n << ' ';  // 输出匹配起始位置（0-indexed）
            j = ne[j];             // 继续寻找下一个匹配
        }
    }
    return 0;
}