#include<iostream>
#include<bits/stdc++.h>
#include <unordered_map>
#define MAX 30001
 
using namespace std;
 
struct node {
    int count;
    node *left,*right;  
 
    node(){}
    node(node* l, node* r, int val){
        left=l;
        right=r;
        count=val;
    }
};
 
unordered_map<int, int> lastOccur;
int arr[MAX];
int n;
 
node* roots[MAX];
 
void build(node *curr, int l, int r){
    if(l==r)return;
    int m=(l+r)/2;
    curr->left= new node(nullptr,nullptr,0);
    curr->right= new node(nullptr,nullptr,0);
    build(curr->left, l, m);
    build(curr->right, m+1, r);
}
 
node* upgrade(node* prev,int l, int r,int p, int x){
    node* curr = new node(nullptr,nullptr,prev->count+x);
    if(p>r || p<l || l>=r){
        return curr;
    }
    int m=(l+r)/2;
    if(p<=m){
        curr->left = upgrade(prev->left,l,m,p,x);
        curr->right=prev->right;
    }else{
        curr->right = upgrade(prev->right,m+1,r,p,x);
        curr->left=prev->left;
    }
    return curr;
}
 
int query(int l , int r, int ql, node* qrRoot){
    if(l==r){
        return qrRoot->count;
    }
    int m=(l+r)/2;
    if(ql<=m)
        return query(l,m,ql,qrRoot->left)+qrRoot->right->count;
    return query(m+1,r,ql,qrRoot->right);
}
 
 
int main(){
    int m;
    
    scanf("%d",&n);
    int arrCount;
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
        
    }
    roots[0]=new node(nullptr,nullptr,0);
    build(roots[0],1,n);
    scanf("%d",&m);
    int ql,qr;
    for(int i=1;i<=n;i++){
        if(lastOccur.find(arr[i])!=lastOccur.end()){
            roots[i]=upgrade(upgrade(roots[i-1],1,n,lastOccur[arr[i]],-1),1,n,i,1);
        }else{
            roots[i]=upgrade(roots[i-1],1,n,i,1);
        }
        lastOccur[arr[i]]=i;
    }
    for(int i=1;i<=m;i++){
        scanf("%d %d",&ql,&qr);
        cout<<query(1,n,ql,roots[qr])<<endl;
    }
    return 0;
}