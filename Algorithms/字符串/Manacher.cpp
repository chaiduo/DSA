// Manacher 算法：线性时间求最长回文子串
// 时间复杂度 O(n)
// 核心思路：
// 1. 预处理：在字符间插入 '#'，统一奇偶长度回文串
// 2. 维护当前最右回文边界 right 及其中心 j
// 3. 利用回文的对称性，借助对称点的臂长来减少重复比较

#include <iostream>
#include <vector>
using namespace std;

// 从中心向两边扩展，返回回文半径
int expand(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    return (right - left - 2) / 2;
}

// Manacher 主函数，返回最长回文子串
string manacher(string s) {
    int start = 0, end = -1;
    // 预处理：插入 '#' 分隔符，如 "abc" -> "#a#b#c#"
    string t = "#";
    for (const char c: s) {
        t += c;
        t += '#';
    }
    t += '#';
    s = t;
    vector<int> arm_len;  // 每个位置的回文半径
    int right = -1, j = -1;  // right 为当前最右回文边界，j 为其中心
    for (int i = 0; i < s.size(); ++i) {
        int cur_arm_len;
        if (i <= right) {
            // 利用对称性：i 关于 j 的对称点 i_sym 的臂长已知
            int i_sym = j * 2 - i;
            int min_arm_len = min(arm_len[i_sym], right - i);
            cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
        } else {
            cur_arm_len = expand(s, i, i);
        }
        arm_len.push_back(cur_arm_len);
        // 更新最右回文边界
        if (i + cur_arm_len > right) {
            j = i;
            right = i + cur_arm_len;
        }
        // 更新最长回文子串
        if (cur_arm_len * 2 + 1 > end - start) {
            start = i - cur_arm_len;
            end = i + cur_arm_len;
        }
    }
    // 从预处理串中提取原字符（跳过 '#'）
    string ans;
    for (int i = start; i <= end; ++i) {
        if (s[i] != '#') {
            ans += s[i];
        }
    }
    return ans;
}

int main()
{
    string s = "abababab";
    cout << manacher(s);
    return 0;
}