#include<iostream>
#include <bits/stdc++.h>
#include<algorithm>
#define MAX 100001
using namespace std;

int n,q,k;

char str[MAX];
int arr[MAX];
int segTree[26][4*MAX];
int lazy[26][4*MAX];
int queries[26];


void build(int c,int x, int l, int r){
    lazy[c][x]=-1;
    if(l==r){
        segTree[c][x]= c==arr[l] ? 1 : 0;
        return;
    }
    int m=(l+r)/2;
    build(c,2*x,l,m);
    build(c,2*x+1,m+1,r);
    segTree[c][x]=segTree[c][2*x]+segTree[c][2*x+1];
}

int query(int c,int x,int l , int r, int ql, int qr){
    
    if(l>=ql && r<=qr){
        return segTree[c][x];
    }
    int m=(l+r)/2;
    if(lazy[c][x]!=-1){
        segTree[c][2*x]=(m-l+1)*lazy[c][x];
        lazy[c][2*x]=lazy[c][x];
        
        segTree[c][2*x+1]=(r-m)*lazy[c][x];
        lazy[c][2*x+1]=lazy[c][x];

        lazy[c][x]=-1;
    }
    int ret=0;
    if(ql<=m)ret+=query(c,2*x,l,m,ql,qr);
    if(qr>m)ret+=query(c,2*x+1,m+1,r,ql,qr);
    segTree[c][x] = segTree[c][2*x]+segTree[c][2*x+1];
    return ret;
}

void updateRange(int c,int x,int l, int r, int ql, int qr,int val){
    if(l>=ql && r<=qr){
        segTree[c][x]=(r-l+1)*val;
        lazy[c][x]=val;
        return;
    }
    int m=(l+r)/2;
    if(lazy[c][x]!=-1){
        segTree[c][2*x]=(m-l+1)*lazy[c][x];
        lazy[c][2*x]=lazy[c][x];
        
        segTree[c][2*x+1]=(r-m)*lazy[c][x];
        lazy[c][2*x+1]=lazy[c][x];

        lazy[c][x]=-1;
    }
    
    if(ql<=m) updateRange(c,2*x,l,m,ql,qr,val);   
    if(qr>m) updateRange(c,2*x+1,m+1,r,ql,qr,val);   
    segTree[c][x] = segTree[c][2*x]+segTree[c][2*x+1];
}

int main(){
    scanf("%d %d",&n,&q);
    scanf("%s",str+1);
    for (int i=1;i<=n;i++) arr[i]=str[i]-'a';
    for(int i=0;i<26;i++){
        build(i,1,1,n);
    }
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d %d %d",&l,&r,&k);
        for(int j=0;j<26;j++){
            queries[j]=query(j,1,1,n,l,r);
        }
        for(int j=0;j<26;j++){
            if(queries[j]>0)
                updateRange(j,1,1,n,l,r,0);
        }
        if(k){
            for(int j=0;j<26;j++){
                if(queries[j]>0){
                    updateRange(j,1,1,n,l,l+queries[j]-1,1);
                    l+=queries[j];
                }
            }
        }else{
            for(int j=25;j>=0;j--){
                if(queries[j]>0){
                    updateRange(j,1,1,n,l,l+queries[j]-1,1);
                    l+=queries[j];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<26;j++){
            if(query(j,1,1,n,i,i)){
                cout<<(char)(j+'a');
            }
        }
    }cout<<endl;
    return 0;
}