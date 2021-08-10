#include<iostream>
#include<bits/stdc++.h>
#define MAX 200001
using namespace std;
typedef long long ll;

int n,z;
int arr[MAX];
int maxHas;

inline int has(int m){
    for(int i=1;i<=m;i++){
        int j=n-m+i;
        if(arr[j]-arr[i]<z)return 0;
    }
    return 1;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>z;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1);
    int l=0,r=n/2,m;
    while(l<=r){
        m=(l+r)/2;
        //cout<<m<<endl;
        if(has(m)){
            maxHas=m;
            l=m+1;
        }else{
            r=m-1;
        }
    }
    cout<<maxHas<<endl;
    return 0;
}