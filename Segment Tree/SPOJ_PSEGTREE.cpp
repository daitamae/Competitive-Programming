#include<iostream>
#define MAX 100001

using namespace std;

struct node {
    int val;
    node *left,*right;

    node(){}
    node(node* l, node* r, int val){
        left=l;
        right=r;
        val=val;
    }
};

int arr[MAX];
int n;
int q;
int k=1;

node* roots[MAX];

void build(node *n, int l, int r){
    if(l==r){
        n->val=arr[l];
        return;
    }
    int m=(l+r)/2;
    n->left= new node(nullptr,nullptr,0);
    n->right= new node(nullptr,nullptr,0);
    build(n->left, l, m);
    build(n->right, m+1, r);
    n->val = n->left->val + n->right->val;
}

void upgrade(node* prev, node* curr, int l, int r,int p, int val){
    if(p>r || p<l || l>r){
        return;
    }
    if(l==r){
        //cout<<l<<" AAA "<<val<<endl;
        curr->val = prev->val+val;
        return;
    }
    int m=(l+r)/2;
    if(p<=m){
        curr->right = prev->right;
        curr->left = new node(nullptr,nullptr,0);
        upgrade(prev->left,curr->left,l,m,p,val);
    }else{
        curr->left = prev->left;
        curr->right = new node(nullptr,nullptr,0);
        upgrade(prev->right,curr->right,m+1,r,p,val);
    }
    curr->val = curr->left->val + curr->right->val;
}

int querySum(node* x,int l , int r, int ql, int qr){
    if(ql>r || qr<l || l>r)
        return 0;
    if(l>=ql && r<=qr)
        return x->val; 
    int m=(l+r)/2;
    return querySum(x->left,l,m,ql,qr)+querySum(x->right,m+1,r,ql,qr);
}


int main(){
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
    }
    scanf("%d",&q);
    roots[0]=new node(nullptr,nullptr,0);
    build(roots[0],1,n);
    int a,idx,pos,v,ql,qr;
    for(int i=1;i<=q;i++){
        scanf("%d",&a);
        if(a==1){
            scanf("%d %d %d",&idx,&pos,&v);
            roots[k]=new node(nullptr,nullptr,0);
            upgrade(roots[idx],roots[k],1,n,pos,v);
            k++;
        }else{
            scanf("%d %d %d",&idx,&ql,&qr);
            cout<<querySum(roots[idx],1,n,ql,qr)<<endl;
        }
    }
    return 0;
}