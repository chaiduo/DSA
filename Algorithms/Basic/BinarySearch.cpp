// Binary Search Template
// Find the first position where value >= x (lower_bound semantics)
// Can be modified to find first position where value > x (upper_bound semantics)

#include <iostream>

using namespace std;
int a[10] = {1,1,3,3,4,4,4,5,5,9};

// Find first position where value >= x
int binsearch(int x, int n) {
    int l = 0, r = n;
    while(l < r) {
        int mid = l + r >> 1;
        if(a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

// Find first position where value > x (only condition differs from above)
// int binsearch(int x, int n) {
//     int l = 0, r = n;
//     while(l < r) {
//         int mid = l + r >> 1;
//         if(a[mid] > x) r = mid;
//         else l = mid + 1;
//     }
//     return l;
// }
int main()
{
    int i = binsearch(5, 9);
    cout << i - 1 << " " << a[i - 1] << endl;
    
    return 0;
}