#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

typedef void (*ImportFunction)(int*, int, int);
HINSTANCE hDll;
ImportFunction func;

int a[N];

void generateArray(int a[], int len){
    for(int i = 0; i < len; i++){
        a[i] = rand();
    }
}

int main(int argc, char** argv){
    if(argc < 2){
        return 10;
    }
    srand(time(NULL));
    generateArray(a, N);
    freopen("output.txt", "w", stdout);
    hDll = LoadLibrary(TEXT("sort.dll"));
    func = (ImportFunction) GetProcAddress(hDll, argv[1]);
    func(a, 0, N - 1);
    for(int i = 0; i < N; i++){
        printf("%d ", a[i]);
    }
    FreeLibrary(hDll);
    return 0;
}