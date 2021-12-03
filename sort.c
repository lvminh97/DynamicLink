#include <windows.h>

void swap(int a[], int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// SELECTION SORT
__declspec(dllexport) void selectionSort(int a[], int start, int end){
    for(int i = start; i < end; i++){
        int minId = i;
        for(int j = i + 1; j <= end; j++){
            if(a[minId] > a[j]){
                minId = j;
            }
        }
        if(minId != i){
            swap(a, minId, i);
        }
    }
}

// QUICK SORT
int partitionSort(int a[], int L, int R){
    int id = (L + R) / 2;
    int pivot = a[id];
    swap(a, id, R);
    id = L;
    for(int i = L; i < R; i++){
        if(a[i] < pivot){
            swap(a, i, id);
            id++;
        }
    }
    swap(a, id, R);
    return id;
}

__declspec(dllexport) void quickSort(int a[], int start, int end){
    int pivot = partitionSort(a, start, end);
    if(pivot > start){ 
        quickSort(a, start, pivot - 1);
    }
    if(pivot < end){ 
        quickSort(a, pivot + 1, end);
    }
}

// MERGE SORT
__declspec(dllexport) void mergeSort(int a[], int start, int end){
    if(start >= end)
        return;
    int mid = (start + end) / 2;
    mergeSort(a, start, mid);
    mergeSort(a, mid + 1, end);
    int *tmp = (int*) malloc(sizeof(int) * (end - start + 1));
    int id = 0, lid = start, rid = mid + 1;
    while(lid <= mid || rid <= end){
        if(lid <= mid && rid <= end){
            if(a[lid] < a[rid]){
                tmp[id] = a[lid];
                lid++;
            }
            else{
                tmp[id] = a[rid];
                rid++;
            }
        }
        else if(lid <= mid){
            tmp[id] = a[lid];
            lid++;
        }
        else{
            tmp[id] = a[rid];
            rid++;
        }
        id++;
    }
    for(int i = start; i <= end; i++){
        a[i] = tmp[i - start];
    }
    free(tmp);
}

// HEAP SORT
void heapify(int a[], int i, int n){
	int L = 2 * i + 1;
	int R = 2 * i + 2;
	int maxId = i;
	if(L < n && a[L] > a[maxId]) 
        maxId = L;
	if(R < n && a[R] > a[maxId]) 
        maxId = R;
	if(maxId != i){
		swap(a, maxId, i);
		heapify(a, maxId, n);
	}
}

__declspec(dllexport) void heapSort(int a[], int start, int end){
    int n = end + 1;
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(a, i, n);
    }
    for(int i = n - 1; i > 0; i--){
        swap(a, 0, i);
        heapify(a, 0, i - 1);
    }
}