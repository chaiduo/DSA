// 高精度除法实现（大数除以普通整数）
// 模拟竖式除法：从高位到低位逐位除，余数带入下一位继续除
// 同时输出商和余数

#include <iostream>
#include <vector>
using namespace std;

void div(string a, int b)
{
    int r = 0;          // 余数
    vector<int>ans;
    for(int i = 0; i < a.length(); i++) {
        r = r * 10 + (a[i] - '0');  // 余数*10 + 当前位
        ans.push_back(r / b);        // 当前位的商
        r %= b;                      // 更新余数
    }
    int i = 0;
    while(i < ans.size() && !ans[i]) i++;  // 跳过前导零
    if(i == ans.size()) cout << 0;
    while(i < ans.size()) cout << ans[i++];
    cout << endl << "余数" << r;
}
int main()
{
    string a;
    int b;
    cin >> a >> b;
    div(a, b);
    return 0;
}