// 多种排序算法的实现集合
// 包含：快速排序(两种写法)、冒泡排序、插入排序、选择排序、归并排序、堆排序

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10000;

// 快速排序（Hoare分区方案）：选取左端点为基准，双指针交替扫描交换
int partation(int arr[], int low, int high){
    int p = arr[low];
    while(low < high){
        while(high > low && arr[high] >= p)high--;
        swap(arr[low], arr[high]);
        while(high > low && arr[low] <= p)low++;
        swap(arr[low], arr[high]);
    }
    arr[low] = p;
    return low;
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int p = partation(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// 快速排序（y总模板）：选取中间元素为基准，双指针向中间逼近
void quick_sort(int a[], int l, int r)
{
    if(l >= r) return ;
    int x = a[l + r >> 1], i = l - 1, j = r + 1;
    while(i < j) {
        while(a[++i] < x);
        while(a[--j] > x);
        if(i < j) swap(a[i], a[j]);
    }
    quick_sort(a, l, j);
    quick_sort(a, j + 1, r);
}

// 冒泡排序：相邻元素两两比较交换，每轮将最大值"冒泡"到末尾
void bubbleSort(int arr[], int size) {
    for (int i = 0, temp; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 插入排序：将未排序元素插入到已排序部分的正确位置
void insertSort(int arr[], int size){
    for(int i = 1, j, temp; i < size; i++){
        temp = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > temp){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// 选择排序：每轮选出最小值放到已排序部分末尾
void selectSort(int arr[], int size){
    for(int i = 0; i < size - 1; i++){
        int minv = arr[i], t = i;
        for(int j = i + 1; j < size; j++){
            if(arr[j] < minv){
                minv = arr[j];
                t = j;
            }
        }
        swap(arr[t], arr[i]);
    }
}

// 归并排序：分治法，先分后合，合并时借助临时数组
int tmp[N];
void merge_sort(int arr[], int left, int right){
    if(left >= right) return;

    int mid = (left + right) >> 1;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    int k = 0, i = left, j = mid + 1;
    while(i <= mid && j <= right){
        if(arr[i] < arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while(i <= mid) tmp[k++] = arr[i++];
    while(j <= right) tmp[k++] = arr[j++];

    for(int i = left, j = 0; i <= right; i++)arr[i] = tmp[j++];
}

// 堆排序：建小根堆，依次弹出堆顶得到升序序列
void down(int hp[], int size, int u){
    int t = u;
    if(u * 2 <= size && hp[u * 2] < hp[t]) t = u * 2;
    if(u * 2 + 1 <= size && hp[u * 2 + 1] < hp[t]) t = u * 2 + 1;
    if(u != t){
        swap(hp[u], hp[t]);
        down(hp, size, t);
    }
}

void heapSort(int arr[], int size){
    int hp[N];
    for(int i = 0; i < size; i++) hp[i + 1] = arr[i];
    for(int i = size / 2; i; i--) down(hp, size, i);

    int m = size, i = 0;
    while(m){
        arr[i++] = hp[1];
        hp[1] = hp[m--];
        down(hp, m, 1);
    }
}

int main() 
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 11, 0, -2};
    int size = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, size);

    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    return 0;
}