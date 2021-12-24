#include <iostream>
#include <stdio.h>
using namespace std;

const int N = 1e5+10;
int n;
int qn[N],gn[N],temp[N];
char qcn[N],gcn[N],tempc[N];

void quicksort(int a[],int p,int r){
    if(p>=r) return;
    int target = a[r];

    int idx = p,j = p-1;  //双指针
    while(j<r){
        while(a[++j]>target); // j经过的部分都满足a[j]>taget
        // 此时a[j]<=target ，翻译一下就是找到a[j]<=target然后和idx做交换
        // idx则一直稳定指向<=target边界的下一个，追加的时候把下一个<=target元素放到idx，然后idx自增
        if(j<r){
            swap(a[idx],a[j]);
            swap(qcn[idx],qcn[j]);
            idx++;
        }
        else break;
    }
    swap(a[idx],a[j]);
    swap(qcn[idx],qcn[j]);
    quicksort(a,p,idx-1);
    quicksort(a,idx+1,r);
}

void merge_sort(int a[],const int &l,const int &r){
    if(l>=r) return;
    int mid = (l+r)>>1;
    merge_sort(a,l,mid);
    merge_sort(a,mid+1,r);
    int i =l,j = mid+1,idx = 0;
    while(i<=mid && j<=r){
        if(a[i]<=a[j]) {
            temp[idx] = a[i];
            tempc[idx++] = gcn[i++];
        }
        else{
            temp[idx] = a[j];
            tempc[idx++] = gcn[j++];
        }
    }
    while(i<=mid) {
        tempc[idx] = gcn[i];
        temp[idx++] = a[i++];
    }
    while(j<=r) {
        tempc[idx] = gcn[j];
        temp[idx++] = a[j++];
    }
    for (i = l, j = 0; i <= r; i ++, j ++ ) {
        gcn[i] = tempc[j];
        a[i] = temp[j];
    }
}

int main(){
    bool stable = 1;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        char c[2];
        scanf("%s %d",&c,&qn[i]);
        gcn[i] = qcn[i]=c[0];
        gn[i] = qn[i];
    }
    quicksort(qn,0,n-1);
    merge_sort(gn,0,n-1);
    for( int i = 0;i<n;i++) if(qcn[i] != gcn[i]) stable = 0;
    if(stable) cout <<"Stable"<<endl;
    else cout <<"Not stable"<<endl;
    for(int i = 0;i<n;i++){
        printf("%c %d\n",qcn[i],qn[i]);
    }
}