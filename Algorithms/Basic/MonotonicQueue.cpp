// Monotonic Queue for Sliding Window Min/Max
// Use deque to maintain indices, corresponding elements stay monotonic
// Time Complexity: O(n), each element enters and leaves queue at most once

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

    // Sliding window minimum: maintain monotonically increasing queue
    for(int i = 0; i < n; i++) {
        while(!q.empty()  && (q.front() <= i - k)) q.pop_front(); // Remove elements outside window
        while(!q.empty() && a[i] < a[q.back()]) q.pop_back();     // Maintain monotonicity
        q.push_back(i);
        if(i >= k - 1) cout << a[q.front()] << " ";
    }
    cout << endl;
    q.clear();
    // Sliding window maximum: maintain monotonically decreasing queue
    for(int i = 0; i < n; i++) {
        while(!q.empty()  && (q.front() <= i - k)) q.pop_front();
        while(!q.empty() && a[i] > a[q.back()]) q.pop_back();
        q.push_back(i);
        if(i >= k - 1) cout << a[q.front()] << " ";
    }
    cout << endl;
    return 0;
}