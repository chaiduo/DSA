// 堆（小根堆）的手动实现
// 支持：建堆、插入、弹出堆顶、查询堆顶
// 使用数组存储，基于完全二叉树性质，down/up 操作维护堆序性

#include <iostream>
#include <algorithm>

using namespace std;

class Heap
{
private:
    int hp[100];
    int size = 0;
public:
    Heap(){};
    // 数组建堆：先放入数组，再从最后一个非叶节点向下调整
    Heap(int a[], int n){
        size = n;
        for(int i = 1; i <= n; i++) hp[i] = a[i - 1];
        for(int i = size / 2; i > 0; i--) down(i);
    }

    void print_heap(){
        for(int i = 1; i <= size; i++){
            cout << hp[i] << " ";
        }
    }
    // 向下调整：将节点与较小子节点交换，维护小根堆性质
    void down(int u){
        int t = u;
        if(u * 2 <= size && hp[u * 2] < hp[t]) t = u * 2;
        if(u * 2 + 1 <= size && hp[u * 2 + 1] < hp[t]) t = u * 2 + 1;
        if(u != t){
            swap(hp[u], hp[t]);
            down(t);
        }
    }

    // 向上调整：插入新节点后与父节点比较，维护堆序性
    void up(int u){
        while(u / 2 && hp[u] < hp[u / 2]){
            swap(hp[u], hp[u / 2]);
            u /= 2;
        }
    }

    int top(){
        return hp[1];
    }

    // 弹出堆顶：用最后一个元素覆盖堆顶，再向下调整
    int pop(){
        if(size <= 0)return -1;
        int t = top();
        hp[1] = hp[size--];
        down(1);
        return t;
    }

    void insert(int t){
        hp[++size] = t;
        up(size);
    }

    bool empty(){
        return size <= 0;
    }
};

int main()
{
    int a[] = {15, 9, 7, 8, 20, -1, 7, 4};
    Heap heap(a, 8);
    heap.insert(45);
    heap.insert(6);
    heap.insert(73);
    heap.insert(91);
    //heap.print_heap();
    while(!heap.empty()){
        cout << heap.top() << " ";
        heap.pop();
    }
    cout << endl;
    return 0;
}
