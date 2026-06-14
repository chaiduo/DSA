// KMP String Matching Algorithm
// Time Complexity: O(n + m), n = pattern length, m = text length
// Core: Use next array (failure pointer) to avoid redundant matching
// ne[i] = length of longest proper prefix that is also a suffix for pattern[1..i]

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

    // Build next array (pattern matches itself)
    for(int i = 2, j = 0; i <= n; i++) {
        while(j && p[i] != p[j + 1]) j = ne[j];  // Mismatch, backtrack
        if(p[i] == p[j + 1]) j++;
        ne[i] = j;
    }

    // Match pattern p in text s
    for(int i = 1, j = 0; i <= m; i++) {
        while(j && s[i] != p[j + 1]) j = ne[j];  // Mismatch, backtrack
        if(s[i] == p[j + 1]) j++;
        if(j == n) {
            cout << i - n << ' ';  // Output match start position (0-indexed)
            j = ne[j];             // Continue searching for next match
        }
    }
    return 0;
}