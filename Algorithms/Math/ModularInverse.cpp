// Two Methods for Computing Modular Inverse
// Definition: a * inv(a) ≡ 1 (mod p), inv(a) is the multiplicative inverse of a modulo p
// 1. Extended Euclidean: Solve ax + py = 1, x is the inverse of a mod p (requires gcd(a,p)=1)
// 2. Fermat's Little Theorem: When p is prime, inv(a) = a^(p-2) mod p

#include <iostream>
using namespace std;

// Extended Euclidean (commented version)
// void exgcd(int a, int b, int &x, int &y){
//     if(!b) {
//         x = 1, y = 0;
//     } else {
//         exgcd(b, a % b, x, y);
//         int t = x;
//         x = y;
//         y = t -  a / b * y;
//     }
// }

// Extended Euclidean to solve ax + by = gcd(a,b)
// For inverse: a,b must be coprime, solving ax + by = 1, x is the modular inverse of a mod b
void exgcd(int a, int b, int &x, int &y){
    if(!b) {
        x = 1, y = 0;    // a*1 + b*0 = gcd(a,b) = a
    } else {
        exgcd(b, a % b, y, x);  // Recursive call
        y -= a / b * x;         // Backtrack to update y
    }
}

// Fast Power (for Fermat's method)
int quick_pow(int a, int b, int p){
    int res = 1;
    while(b){
        if(b & 1)res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// Fermat's Little Theorem for inverse: When p is prime, a^(p-1) ≡ 1 (mod p)
// So a * a^(p-2) ≡ 1 (mod p), i.e., inv(a) = a^(p-2) mod p
int inv(int a, int p){
    return quick_pow(a, p - 2, p);
}

int main()
{
    int x, y;
    exgcd(5, 7, x, y);
    cout << inv(5, 7) <<endl;
    cout << x;
}