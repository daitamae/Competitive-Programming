#include<iostream>
#include<bits/stdc++.h>
#define MAX 5000001
using namespace std;

typedef long long ll;

struct query{
    ll l,r;
    int i;
};

ll n,m,nsqrt;
ll k;
ll xors[MAX];
query queries[MAX];
ll freq[MAX];
ll ret[MAX];

ll c,q,p=1;

bool cmp(const query &q1,const query &q2){
    return q1.l/nsqrt==q2.l/nsqrt ? q1.r<q2.r : q1.l<q2.l;
}

void add(ll x){
    c+=freq[xors[x]^k];
    freq[xors[x]]++;
}

void sub(ll x){
    freq[xors[x]]--;
    c-=freq[xors[x]^k];
}

int main(){
    scanf("%lld %lld %lld",&n,&m,&k);
    nsqrt = sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%lld",xors+i);
        xors[i]^=xors[i-1];
    }
    for(int i=1;i<=m;i++){
        queries[i].i=i;
        scanf("%lld %lld",&(queries[i].l),&(queries[i].r));
    }
    sort(queries+1,queries+m+1,cmp);
    freq[0]++;
    for(int i=1;i<=m;i++){
        while(p<queries[i].l){
            sub(p-1);
            p++;
        }
        while(p>queries[i].l){
            p--;
            add(p-1);
        }
        while(q<queries[i].r){
            q++;
            add(q);
        }
        while(q>queries[i].r){
            sub(q);
            q--;
        }
        ret[queries[i].i]=c;
    }
    for(int i=1;i<=m;i++){
        cout<<ret[i]<<endl;
    }
    return 0;
}