#include <iostream>

const int maxn = 5e5+5;
int a[maxn], tmp[maxn];

int n;
long long ans;

void merge_sort(int l, int r){
    if(l==r)
        return;
    int mid = (l+r)>>1;
    merge_sort(l, mid);
    merge_sort(mid+1,r);

    int k=l, i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(a[i]>a[j]){
            tmp[k++]=a[j++];
            ans += mid - i + 1;
        }else{
            tmp[k++]=a[i++];
        }
    }

    while(i<=mid){
        tmp[k++]=a[i++];
    }
    while(j<=r){
        tmp[k++]=a[j++];
    }

    for(int s=l;s<=r;s++){
        a[s] = tmp[s];
    }
}

int main(){
    std::cin >> n;
    for(int i=0;i<n;i++){
        std::cin >> a[i];
    }
    merge_sort(0,n-1);
    std::cout << ans << std::endl;
    // for(int i=0;i<n;i++){
    //     std::cout << a[i] << ' ';
    // }
    return 0;
}
