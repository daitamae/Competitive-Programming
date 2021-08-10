#include<iostream>
#include<bits/stdc++.h>
#define MAX 1000001
using namespace std;
typedef long long ll;

int k,l,m;
char t[MAX][2];

char other(char player){
    if(player=='A')return 'B';
    return 'A';
}

int idx(char player){
    if(player=='A')return 1;
    return 0;
}

char getWinner(int n, char player){
    if(t[n][idx(player)]!='\0')return t[n][idx(player)];
    if(n==0){
        t[0][idx(player)]=other(player);
        return t[0][idx(player)];
    }else if(n==1 || n==k || n==l){
        t[n][idx(player)]=player;
    }
    if(n-k>=0 && getWinner(n-k,other(player))==player){
        t[n][idx(player)]=player;
    }else if(n-l>=0 && getWinner(n-l,other(player))==player){
        t[n][idx(player)]=player;
    }else if(getWinner(n-1,other(player))==player){
        t[n][idx(player)]=player;
    }else{
        t[n][idx(player)]=other(player);
    }
    return t[n][idx(player)];
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>k>>l>>m;
    while(m--){
        int n;
        cin>>n;
        char winner = getWinner(n,'A');
        
        cout<<winner;
    }
    return 0;
}