#include<iostream>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;

int n;
//int arr[MAX];

int query(int i){
    cout<<"? "<<i<<endl;
    cout.flush();
    cin>>i;
    return i;
}

int LocalMinDir(int i){
    int a,b,c;
    if(i>1 && i<n){
        a = query(i-1);
        b = query(i);
        c = query(i+1);
    }else if(i==1){
        a = INT_MAX;
        b = query(i);
        c = query(i+1);
    }else{
        a = query(i-1);
        b = query(i);
        c = INT_MAX;
    }
    if(b<c && b<a)return 0;
    if(b<c) return 1;
    return -1;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    /*
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }*/
    int l=1;
    int r=n;
    int m;
    while(l<r){
        m=(l+r)/2;
        int dir=LocalMinDir(m);
        //cout<<m<<" "<<dir<<endl;
        if(dir==0){
            break;
        }else if(dir==1){
            r=m;
        }else if(dir==-1){
            l=m+1;
        }
    }
    m=(l+r)/2;
    cout<<"! "<<m<<endl;
    return 0;
}