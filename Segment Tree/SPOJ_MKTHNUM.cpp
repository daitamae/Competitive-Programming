#include<iostream>
#include<bits/stdc++.h>
#include <unordered_map>
#define MAX 100001

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

vector<int> v;
int arr[MAX];
int n;

node* roots[MAX];

void build(node *n, int l, int r){
    if(l==r)return;
    int m=(l+r)/2;
    n->left= new node(nullptr,nullptr,0);
    n->right= new node(nullptr,nullptr,0);
    build(n->left, l, m);
    build(n->right, m+1, r);
}

node* upgrade(node* prev,int l, int r,int p){
    
    node* curr = new node(nullptr,nullptr,prev->count+1);
    //cout<<l<<" "<<r<<" "<<curr->count<<endl;
    if(p>r || p<l || l>=r){
        return curr;
    }
    int m=(l+r)/2;
    if(p<=m){
        curr->left = upgrade(prev->left,l,m,p);
        curr->right=prev->right;
    }else{
        curr->right = upgrade(prev->right,m+1,r,p);
        curr->left=prev->left;
    }
    return curr;
}

int query(int l , int r, node* ql, node* qr, int k){
    if(l==r){
        return l;
    }
    int m=(l+r)/2;
    int c=qr->left->count-ql->left->count;
    //cout<<"c: "<<c<<endl;
    if(c>=k){
        return query(l,m,ql->left,qr->left,k);
    }
    return query(m+1,r,ql->right,qr->right,k-c);
}


int main(){
    int m;
    unordered_map<int, int> umap;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
        v.push_back(arr[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique( v.begin(), v.end() ),v.end());
    int vecCount=0;
    for(auto it = v.begin();it!=v.end();it++){
        umap[*it]=vecCount++;
    }
    roots[0]=new node(nullptr,nullptr,0);
    build(roots[0],1,v.size());
    int ql,qr,k;
    for(int i=1;i<=n;i++){
        roots[i]=upgrade(roots[i-1],1,n,umap[arr[i]]+1);
    }
    for(int i=1;i<=m;i++){
        scanf("%d %d %d",&ql,&qr,&k);
        cout<<v[query(1,n,roots[ql-1],roots[qr],k)-1]<<endl;
        
    }
    return 0;
}