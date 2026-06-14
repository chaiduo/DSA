// Fast Power Algorithm
// Compute a^b in O(log b) time
// Principle: Decompose exponent b in binary, e.g., b=13=1101, then a^13 = a^8 * a^4 * a^1

#include <iostream>
#include <algorithm>

using namespace std;

// Remove the lowest set bit
int removeLowBit(int n) {
    return n & (n - 1);
}

// Get the lowest set bit (bit manipulation trick)
int lowbit(int n) {
    return n & (-n);
}

// Euclidean algorithm for GCD
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Fast Power: compute a^b
// Core: when b is odd, multiply current a; then square a and right shift b
long long fastPower(int a, int b) {
    long long ans = 1;
    while(b) {
        if(b & 1)ans *= a;  // Current bit of b is 1, multiply by a
        a *= a;              // a = a^2
        b >>= 1;             // Right shift b by 1
    }
    return ans;
}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << fastPower(a, b);
    return 0; 
}