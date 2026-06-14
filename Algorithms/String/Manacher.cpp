// Manacher's Algorithm: Find Longest Palindromic Substring in Linear Time
// Time Complexity: O(n)
// Key Ideas:
// 1. Preprocessing: Insert '#' between characters to unify odd/even length palindromes
// 2. Maintain current rightmost palindrome boundary 'right' and its center 'j'
// 3. Use palindrome symmetry to reduce redundant comparisons

#include <iostream>
#include <vector>
using namespace std;

// Expand from center, return palindrome radius
int expand(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    return (right - left - 2) / 2;
}

// Manacher main function, return longest palindromic substring
string manacher(string s) {
    int start = 0, end = -1;
    // Preprocessing: insert '#' separators, e.g., "abc" -> "#a#b#c#"
    string t = "#";
    for (const char c: s) {
        t += c;
        t += '#';
    }
    t += '#';
    s = t;
    vector<int> arm_len;  // Palindrome radius at each position
    int right = -1, j = -1;  // right = current rightmost palindrome boundary, j = its center
    for (int i = 0; i < s.size(); ++i) {
        int cur_arm_len;
        if (i <= right) {
            // Use symmetry: arm length at symmetric point i_sym of i (about j) is known
            int i_sym = j * 2 - i;
            int min_arm_len = min(arm_len[i_sym], right - i);
            cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
        } else {
            cur_arm_len = expand(s, i, i);
        }
        arm_len.push_back(cur_arm_len);
        // Update rightmost palindrome boundary
        if (i + cur_arm_len > right) {
            j = i;
            right = i + cur_arm_len;
        }
        // Update longest palindromic substring
        if (cur_arm_len * 2 + 1 > end - start) {
            start = i - cur_arm_len;
            end = i + cur_arm_len;
        }
    }
    // Extract original characters from preprocessed string (skip '#')
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