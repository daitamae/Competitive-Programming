#include<iostream>
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int n,t;

ll calcSg(ll i){
    if(i%2==0)return i/2;
    return calcSg(i/2);
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n;
        ll sgtot=0;
        for(int i=1;i<=n;i++){
            ll a;
            cin>>a;
            sgtot^=calcSg(a);
        }
        cout<<(sgtot!=0 ? "YES" : "NO")<<endl;
    } 
    return 0;
}