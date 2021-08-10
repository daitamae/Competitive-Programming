#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#define MAX 100001
#define MAXTESTS 101
using namespace std;

struct interval{
    int l,r;
};

int n,t,m,p;

vector<interval> openInts[MAXTESTS];

bool interval_sorter(interval const& i1, interval const& i2) {
    return i1.l < i2.l;
}

int getClosestInt(int l,int r,int x,int c){
    //cout<<l<<" "<<r<<endl;
    if(l==r){
        return l-1;
    }
    int mid=(l+r)/2;
    if(openInts[c][mid].l<=x){
        return getClosestInt(mid+1,r,x,c);
    }
    return getClosestInt(l,mid,x,c);

}


int main(){
    scanf("%d",&t);
    for(int c=1;c<=t;c++){
        scanf("%d %d",&n,&m);
        interval init;
        init.l=0;   
        init.r=0;
        openInts[c].push_back(init);
        for(int i=1;i<=n;i++){
            interval I;
            scanf("%d %d",&(I.l),&(I.r));
            openInts[c].push_back(I);
        }
        sort(openInts[c].begin(), openInts[c].end(), &interval_sorter);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d",&p);
            int k;
            if(openInts[c][n].l<=p){
                k=n;
            }else{
                k=getClosestInt(0,n,p,c);
            }
            interval I=openInts[c][k];
            //cout<<I.l<<I.r<<" AAA"<<endl;
            if(I.r>p){
                cout<<0<<endl;
            }else if(k<n){
                cout<<openInts[c][k+1].l-p<<endl;
            }else if(k==n){
                cout<<-1<<endl;
            }
        }
    }
    
    return 0;
}