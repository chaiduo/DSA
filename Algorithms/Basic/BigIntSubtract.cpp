// Big Integer Subtraction Implementation
// Simulate column subtraction with strings, subtract digit by digit with borrowing
// Automatically handles negative results (compare sizes to determine sign)

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string sub(string a, string b)
{
    bool f = false; // Flag for negative result
    // Ensure a >= b (compare by length and lexicographic order)
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
    // Subtract digit by digit, borrow from higher position if needed
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