#include <iostream>

using namespace std;


int* arr;
int* segTree;

int sign(int val){
    if(val>0){
        return 1;
    }
    if(val<0){
        return -1;
    }
    return 0;
}


void build(int x, int l, int r){
    if(l==r){
        segTree[x]=sign(arr[l]);

        return;
    }
    if(l<r){
        int m=(l+r)/2;
        build(2*x,l,m);
        build(2*x+1,m+1,r);
        
        segTree[x]=segTree[2*x]*segTree[2*x+1];
    }
}

int product(int x,int l , int r, int ql, int qr){
    if(ql>qr)
        return 1;
    if(l==ql && r==qr)
        return segTree[x];
    int m=(l+r)/2;
    return product(2*x,l,m,ql,min(qr,m))*product(2*x+1,m+1,r,max(m+1,ql),qr);
}


void update(int x,int l, int r, int p, int val){

    if(l==r){
        segTree[x]=sign(val);
        return;
    }
    int m=(l+r)/2;
    if(p<=m)
        update(2*x,l,m,p,val);
    else
        update(2*x+1,m+1,r,p,val);
    segTree[x]=segTree[2*x]*segTree[2*x+1];
}



int main(){
    int n,k;
    while(scanf("%d %d",&n,&k)==2){
        arr = new int[n+1];
        segTree = new int[4*(n+1)];
        for(int i=1;i<=n;i++)
            scanf("%d",&(arr[i]));
            
        build(1,1,n);
        
        int count=0;
        while(count<k){
            char ch;
            scanf("%c",&ch);
            if(ch=='C'){
                int i,v;
                scanf("%d",&i);
                scanf("%d",&v); 
                update(1,1,n,i,v);
                count++;
            }else if(ch=='P'){
                int i,j;
                scanf("%d",&i);
                scanf("%d",&j);
                int p=product(1,1,n,i,j);
                if(p>0)
                    cout<<"+";
                else if(p<0)
                    cout<<"-";
                else
                    cout<<"0";
                count++;
            }
        }
        cout<<endl;
    }
    return 0;   
}