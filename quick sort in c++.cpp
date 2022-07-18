#include <iostream>
using namespace std;

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int check_pivot(int val[], int low, int high){
    int pivot = val[high];
    int temp = low;
    for (int i = low; i < high; i++){
        if (val[i] <= pivot){
            swap(&val[temp], &val[i]);
            temp++;
        }
    }
    swap(&val[temp], &val[high]);
    return temp;
}

//using quicksort algorithm
void quick_sort(int val[], int low, int high){
    if (low < high){
        int pivot = check_pivot(val, low, high);
        quick_sort(val, low, pivot - 1);
        quick_sort(val, pivot + 1, high);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int val[n];
    for (int i = 0; i < n; i++) cin >> val[i];
    quick_sort(val, 0, n-1);
    cout << "output :" << endl;
    for (int i = 0; i < n; i++) cout << val[i] << endl;

    return 0;
}