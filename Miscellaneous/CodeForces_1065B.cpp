#include<iostream>
#define MAX 100001
using namespace std;
typedef long long ll;

ll n,m;
ll maxIso,minIso;

ll numEdgesComplete(ll k){
    return (k*(k-1))/2;
}

int main(){
    scanf("%lld %lld",&n,&m);
    ll l=0,r=n;
    while(l<r){
        ll mid=(l+r)/2;
        ll x=numEdgesComplete(mid);
        if(x>=m){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    maxIso=n-l;
    minIso=max((ll)0,n-2*m);
    cout<<minIso<<" "<<maxIso<<endl;
    return 0;
}