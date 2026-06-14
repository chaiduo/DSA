// Heap (Min-Heap) Manual Implementation
// Supports: build heap, insert, pop top, query top
// Uses array storage, based on complete binary tree properties, down/up operations maintain heap order

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
    // Array build heap: first put into array, then adjust down from last non-leaf node
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
    // Down adjustment: swap node with smaller child, maintain min-heap property
    void down(int u){
        int t = u;
        if(u * 2 <= size && hp[u * 2] < hp[t]) t = u * 2;
        if(u * 2 + 1 <= size && hp[u * 2 + 1] < hp[t]) t = u * 2 + 1;
        if(u != t){
            swap(hp[u], hp[t]);
            down(t);
        }
    }

    // Up adjustment: after inserting new node, compare with parent, maintain heap order
    void up(int u){
        while(u / 2 && hp[u] < hp[u / 2]){
            swap(hp[u], hp[u / 2]);
            u /= 2;
        }
    }

    int top(){
        return hp[1];
    }

    // Pop top: replace top with last element, then adjust down
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
