// Big Integer Multiplication Implementation
// Simulate column multiplication: multiply digit by digit, accumulate results, then handle carry
// Core: a[i] * b[j] accumulates to c[i+j], c[i+j+1] stores the carry

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string mul(string a, string b)
{
    int maxlen = a.length() + b.length();
    vector<int>c(maxlen, 0);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for(int i = 0; i < a.length(); i++) {
        for(int j = 0; j < b.length(); j++) {
            c[i + j] += (a[i] - '0') * (b[j] - '0');
            c[i + j + 1] += c[i + j] / 10;
            c[i + j] %= 10;
        }
    }
    int i = c.size() - 1;
    while(!c[i])i--;
    string ans;
    while(i >= 0) ans += (c[i--] + '0');
    return ans == "" ? "0" : ans;
}
int main()
{
    string a, b;
    cin >> a >> b;
    cout << mul(a, b) << endl;
    return 0;
}