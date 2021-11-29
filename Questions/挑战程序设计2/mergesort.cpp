#include <iostream>
using namespace std;

const int N = 5*1e5+10;
int q[N],cnt_cmp,temp[N];


void merge_sort(int *a,int l ,int r){
    if(l>=r) return;
    int mid = (l+r)>>1;
    merge_sort(a,l,mid);
    merge_sort(a,mid+1,r);

    int idx = 0,i = l,j = mid+1;
    while(i<=mid && j<=r){
        if(a[i]<a[j]) {
            temp[idx++] = a[i++];
            cnt_cmp++;
        }
        else {
            temp[idx++] = a[j++];
            cnt_cmp++;
        }
    }
    while(i<=mid) {
        temp[idx++] = a[i++];
        cnt_cmp++;
    }
    while(j<=r) {
        temp[idx++] = a[j++];
        cnt_cmp++;
    }
    for(j = 0;j<idx;j++) a[l++] = temp[j];
}
int main(){
    int n;
    cin>>n;
    for(int i = 0;i<n;i++) scanf("%d",&q[i]);

    merge_sort(q,0,n-1);
    for(int i = 0;i<n-1;i++) printf("%d ",q[i]);
    printf(("%d\n"),q[n-1]);
    cout <<cnt_cmp<<endl;
    return 0;
}