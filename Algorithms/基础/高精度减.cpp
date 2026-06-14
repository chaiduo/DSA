// 高精度减法实现
// 字符串模拟竖式减法，逐位相减并借位
// 自动处理负数结果（比较大小后决定符号）

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string sub(string a, string b)
{
    bool f = false; // 标记结果是否为负数
    // 确保 a >= b（按长度和字典序比较）
    if(b.length() > a.length()) {
        swap(a, b);
        f = true;
    }
    else if(a.length() == b.length() && a < b){
        swap(a, b);
        f = true;
    }
    int maxlen = max(a.length(), b.length());
    string ans(maxlen, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while(a.length() < maxlen) a += "0";
    while(b.length() < maxlen) b += "0";
    // 逐位相减，不够则向高位借1
    for(int i = 0; i < maxlen; i++) {
        ans[i] = a[i] - b[i] + '0';
        if(ans[i] < '0') {
            ans[i] += 10;
            a[i + 1]--;
        }
    }
    reverse(ans.begin(), ans.end());
    if(ans.find_first_not_of('0') == string::npos) return "0";
    string ret = ans.substr(ans.find_first_not_of('0'));
    if(f) ret = "-" + ret;
    return ret;
}
int main()
{
    string a, b;
    cin >> a >> b;
    cout << sub(a, b) << endl;
    return 0;
}