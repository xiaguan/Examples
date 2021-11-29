#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

long long cnt;
int l;
int A[1000000];
int n;
vector<int> G;

void printfn(int a[],int n){
    for(int i = 0;i<n-1;i++){
        printf("%d ",a[i]);
    }
    printf("%d",a[n-1]);
    printf("\n");
}

// 插入排序
void insertionsort(int a[],int r){
    for( int i = 1;i<r;i++)
    {
        int temp = a[i];
        int j = i-1;
        while( j>=0 && a[j]>temp)
        {

            a[j+1]=a[j];
            j--;
        }
        a[j+1]=temp;
        printfn(a,r);
    }
}

// 冒泡排序
void bubblesort(int a[],int n){
    for(int j=n-1;j>0;j--){
        for(int i = 0;i<j;i++) {
            if (a[i + 1] < a[i]) {
                swap(a[i + 1], a[i]);
            }
            printfn(a, n);
        }
    }
}

// 选择排序
void selectsort(int a[],int n){
    for(int i  = 0 ;i<n-1;i++){
        int min=i;
        for(int j =i;j<n;j++){
            if(a[j]<a[min]){
                min = j;
            }
        }
        swap(a[i],a[min]);
        printfn(a,10);
    }
}

void insertionsort_shell(int a[],int n,int g){
    for(int i = g;i<n;i++){
        int temp = a[i];
        int j = i-g;
        while(j>=0 && a[j]>temp){
            a[j+g]=a[j];
            j -=g;
            cnt++;
        }
        a[j+g]=temp;
        printfn(a,n);
    }
}
void shellsort(int a[],int n){
    for(int h =1;;){
        if(h>n) break;
        G.push_back(h);
        h= 3*h+1;
    }

    for(int i = G.size()-1;i>=0;i--){
        insertionsort_shell(a,n,G[i]);
    }
}

int main(){
    
    int q[10]={9,8,8,7,6,5,4,3,2,1};
    int test[10]={9,8,8,7,6,5,4,3,2,1};

    //printfn(test,10);
    //insertionsort(test,10);


    //printfn(test,10);
    //bubblesort(test,10);

    //printfn(test,10);
    //selectsort(test,10);

    printfn(test,10);
    shellsort(test,10);
    return 0;
}