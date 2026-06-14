// Big Integer Addition (two implementations)
// Method 1: String simulation of column addition, add digit by digit with carry
// Method 2: Vector stores digits, simulate addition process

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Method 1: String implementation
string add(string a, string b)
{
    int maxlen = max(a.length(), b.length());
    string ans(maxlen, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int k = 0;
    for(int i = 0; i < maxlen; i++) {
        if(i < a.length()) k += a[i] - '0';
        if(i < b.length()) k += b[i] - '0';
        ans[i] = k % 10 + '0';
        k /= 10;
    }
    if(k) ans += k + '0';
    reverse(ans.begin(), ans.end());
    if(ans.find_first_not_of('0') == string::npos)return "0";
    return ans.substr(ans.find_first_not_of('0'));
}
// Method 2: Vector implementation, A/B stored with least significant digit first
vector<int> add(vector<int> &A, vector<int> &B)  // C = A + B, A >= 0, B >= 0
{
    if (A.size() < B.size()) return add(B, A);
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i ++ )
    {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }

    if (t) C.push_back(t);
    reverse(C.begin(), C.end());
    return C;
}

int main()
{
    // string a, b;
    // cin >> a >> b;
    // cout << add(a, b) << endl;

    vector<int>A = {1,2,3};
    vector<int>B = {2,3};
    vector<int>C = add(A, B);
    for(auto x : C) cout << x;
    return 0;
}