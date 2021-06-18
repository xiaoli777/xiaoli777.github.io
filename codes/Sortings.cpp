#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define SIZE 100

template<class type>
void swap(type Arr[], int i, int j){
    type tmp = Arr[i];
    Arr[i] = Arr[j];
    Arr[j] = tmp;
}

template<class type>
void print(type Arr[], int size){
    for(int i = 0; i < size; i++)
        cout << Arr[i] << " ";
    cout << endl;
}

template<class type>
void insSort(type Arr[], int size){
    for(int i = 0; i < size-1; i++)
        for(int j = i+1; j >= 1 && Arr[j] < Arr[j-1]; j--)
            swap(Arr, j-1, j);
}

template<class type>
void bubSort(type Arr[], int size){
    for(int i = 0; i < size; i++)
        for(int j = size-1; j > i; j--)
            if(Arr[j] < Arr[j-1])
                swap(Arr, j-1, j);
}

template<class type>
void selSort(type Arr[], int size){
    for(int i = 0; i < size; i++){
        int lowIndex = i;
        for(int j = i+1; j < size; j++){
            if(Arr[lowIndex] > Arr[j])
                lowIndex = j;
        }
        swap(Arr, i, lowIndex);
    }
}

template<class type>
void shellSort(type Arr[], int size, int gap){
    for(int inc = size/gap; inc > 0; inc/=gap){
        for(int i = 0; i < inc; i++){
            for(int j = i; j < size-inc; j+=inc){
                for(int k = j+inc; k >= inc && Arr[k] < Arr[k-inc]; k-=inc)
                    swap(Arr, k-inc, k);
            }
        }
    }
}

template<class type>
int partition(type Arr[], int left, int right){
    int tmp = left;
    int tmp_val = Arr[tmp];
    left++;

    while(true){
        while(left <= right && Arr[left] <= tmp_val)  left++;
        while(left <= right && Arr[right] >= tmp_val) right--;
        if(left > right)    break;
        swap(Arr, left, right);
    }
    swap(Arr, tmp, right);
    return right;
}

template<class type>
void quickSort(type Arr[], int left, int right){
    if(left >= right) return;

    int p = partition(Arr, left, right);
    quickSort(Arr, left, p-1);
    quickSort(Arr, p+1, right);
}

template<class type>
void mergeSortCore(type Arr[], type tmp[], int left, int right){
    if(left >= right)   return;

    int mid = left + (right - left) / 2;
    mergeSortCore(Arr, tmp, left, mid);
    mergeSortCore(Arr, tmp, mid+1, right);

    int i = left, j = mid + 1, cur = left;
    while(i <= mid && j <= right){
        if(Arr[i] < Arr[j]) tmp[cur++] = Arr[i++];
        else tmp[cur++] = Arr[j++];
    }

    while(i <= mid) tmp[cur++] = Arr[i++];
    while(j <= right)   tmp[cur++] = Arr[j++];

    for(cur = left; cur <= right; cur++)
        Arr[cur] = tmp[cur];
}

template<class type>
void mergeSort(type Arr[], int size){
    type *tmp_arr = new type[size];
    mergeSortCore(Arr, tmp_arr, 0, size-1);
    delete[] tmp_arr;
}

template<class type>
void reverse(type Arr[], int len){
    int i = 0, j = len-1;
    while(i < j)  swap(Arr, i++, j--);
}

template<class type>
void exchange(type Arr[], int leftLen, int rightLen){
    reverse(Arr, leftLen);
    reverse(Arr + leftLen, rightLen);
    reverse(Arr, leftLen + rightLen);
}

template<class type>
void mergeSortExchange(type Arr[], int left, int mid, int right){
    int i = left, j = mid + 1;
    while(i <= mid && j <= right){
        while(i <= mid && Arr[i] <= Arr[j])   i++;
        while(j <= right && Arr[j] < Arr[i])   j++;
        exchange(Arr + i, mid + 1 - i, j - mid - 1);
        
        i = i + j - mid;
        mid = j - 1;
    }
}

template<class type>
void mergeSortNoTmp(type Arr[], int left, int right){
    if(left >= right)   return;

    int mid = left + (right - left) / 2;
    mergeSortNoTmp(Arr, left, mid); // [left, mid]
    mergeSortNoTmp(Arr, mid + 1, right);    // [mid+1, right]
    mergeSortExchange(Arr, left, mid, right);
}

template<class type>
void pushHeap(type Arr[], int hole){
    type t = Arr[hole];
    int parent = (hole - 1) / 2;
    while(hole > 0 && Arr[parent] < t){
        Arr[hole] = Arr[parent];
        hole = parent;
        parent = (hole - 1) / 2;
    }
    Arr[hole] = t;
}

template<class type>
void popHeap(type Arr[], int size){
    type t = Arr[size-1];
    Arr[size-1] = Arr[0];
    size--;

    int hole = 0;
    int child = 2 * (hole + 1);
    while(child < size){
        if(Arr[child - 1] > Arr[child])
            child--;
        Arr[hole] = Arr[child];
        hole = child;
        child = 2 * (hole + 1);
    }
    if(child == size){
        Arr[hole] = Arr[child - 1];
        hole = child - 1;
    }
    Arr[hole] = t;
    pushHeap(Arr, hole);
}

template<class type>
void makeHeap(type Arr[], int size){
    for(int i = 0; i < size; i++)
        pushHeap(Arr, i);
}

template<class type>
void makeHeap2(type Arr[], int size){
    int parent = (size - 2) / 2;

    while(parent >= 0){
        int hole = parent;
        int child = 2 * (hole + 1);
        type t = Arr[hole];

        while(child < size){
            if(Arr[child - 1] > Arr[child])
                child--;
            Arr[hole] = Arr[child];
            hole = child;
            child = 2 * (hole + 1);
        }
        if(child == size){
            Arr[hole] = Arr[child - 1];
            hole = child - 1;
        }
        Arr[hole] = t;
        pushHeap(Arr, hole);
        parent--;
    }
}

template<class type>
void heapSort(type Arr[], int size){
    makeHeap(Arr, size);
    // makeHeap2(Arr, size);
    for(int j = size; j>1; j--)
        popHeap(Arr, j);
}


int main(){
    int array[SIZE];
    srand((unsigned)time(NULL));
    for(int i = 0; i < SIZE; i++)
        array[i] = rand()%SIZE;
    
    cout << "Original Order" << endl;
    print(array, SIZE);

    // insSort(array, SIZE);
    // bubSort(array, SIZE);
    // selSort(array, SIZE);
    // shellSort(array, SIZE, 2);
    // quickSort(array, 0, SIZE-1);
    // mergeSort(array, SIZE);
    // mergeSortNoTmp(array, 0, SIZE-1);
    heapSort(array, SIZE);

    cout << "Sorted Order" << endl;
    print(array, SIZE);

    return 0;
}