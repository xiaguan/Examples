#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5+10;
int q[N];

void partition(int a[],int p,int r){
    int target = a[r];
    int idx = p,j = p-1;
    while(j<r){
        while(q[++j]>target);
        if(j<r)swap(q[idx++],q[j]);
        else break;
    }
    swap(q[idx],q[j]);
    for(int i = 0;i<=r;i++){
        if(i) printf(" ");
        if(i==idx) printf("[");
        printf("%d",a[i]);
        if(i==idx) {
            printf("]");
        }
    }
    printf("\n");
}

int main(){
    int n;
    cin>>n;
    for(int i = 0;i<n;i++) scanf("%d",&q[i]);

    partition(q,0,n-1);
    return 0;
}