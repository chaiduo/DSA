// 单调队列求滑动窗口最小值和最大值
// 用双端队列维护下标，队列中对应元素保持单调性
// 时间复杂度 O(n)，每个元素最多入队出队各一次

#include <iostream>
#include <deque>
using namespace std;
#define N 1000010

deque<int>q;
int a[N];
int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> a[i];

    // 求滑动窗口最小值：维护单调递增队列
    for(int i = 0; i < n; i++) {
        while(!q.empty()  && (q.front() <= i - k)) q.pop_front(); // 移除超出窗口的元素
        while(!q.empty() && a[i] < a[q.back()]) q.pop_back();     // 维护单调性
        q.push_back(i);
        if(i >= k - 1) cout << a[q.front()] << " ";
    }
    cout << endl;
    q.clear();
    // 求滑动窗口最大值：维护单调递减队列
    for(int i = 0; i < n; i++) {
        while(!q.empty()  && (q.front() <= i - k)) q.pop_front();
        while(!q.empty() && a[i] > a[q.back()]) q.pop_back();
        q.push_back(i);
        if(i >= k - 1) cout << a[q.front()] << " ";
    }
    cout << endl;
    return 0;
}