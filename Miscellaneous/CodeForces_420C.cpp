#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<map>
#define MAX 300001
using namespace std;
typedef long long ll;



int n,p;
int accusations[MAX];
map<pair<int,int>,int> mp;
ll suspects;

int main(){
    scanf("%d %d",&n,&p);
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        if(x>y)swap(x,y);
        accusations[x]++;
        accusations[y]++;
        mp[make_pair(x,y)]++;
    }

    for(auto &it : mp){
        if(accusations[it.first.first]+accusations[it.first.second]-it.second<p
        && accusations[it.first.first]+accusations[it.first.second]>=p
        )suspects--;
    }

    sort(accusations+1,accusations+(n+1));
    
    int r=n;
    for(int l=1;l<n;l++){
        while(l<r && accusations[l]+accusations[r]>=p)r--;
        suspects+=min(n-r,n-l);
    }
    cout<<suspects<<endl;
    return 0;
}