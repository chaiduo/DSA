// Big Integer Division Implementation (big number divided by normal integer)
// Simulate column division: divide from high to low digit, carry remainder to next digit
// Output both quotient and remainder

#include <iostream>
#include <vector>
using namespace std;

void div(string a, int b)
{
    int r = 0;          // Remainder
    vector<int>ans;
    for(int i = 0; i < a.length(); i++) {
        r = r * 10 + (a[i] - '0');  // Remainder * 10 + current digit
        ans.push_back(r / b);        // Quotient for current digit
        r %= b;                      // Update remainder
    }
    int i = 0;
    while(i < ans.size() && !ans[i]) i++;  // Skip leading zeros
    if(i == ans.size()) cout << 0;
    while(i < ans.size()) cout << ans[i++];
    cout << endl << "Remainder: " << r;
}
int main()
{
    string a;
    int b;
    cin >> a >> b;
    div(a, b);
    return 0;
}