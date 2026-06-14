// 二分查找模板
// 查找第一个 >= x 的位置（lower_bound 语义）
// 也可切换为查找第一个 > x 的位置（upper_bound 语义）

#include <iostream>

using namespace std;
int a[10] = {1,1,3,3,4,4,4,5,5,9};

// 查找第一个 >= x 的位置
int binsearch(int x, int n) {
    int l = 0, r = n;
    while(l < r) {
        int mid = l + r >> 1;
        if(a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

// 查找第一个 > x 的位置（与上面仅判断条件不同）
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