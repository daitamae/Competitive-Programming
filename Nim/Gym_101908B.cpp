#include<iostream>
#include<bits/stdc++.h>
#define MAX 101
using namespace std;
typedef long long ll;

int n;
int sg[MAX][MAX];

int calcSg(int l, int c){
    if(sg[l][c]!=-1){
        return sg[l][c];
    }
    if(l==2 && c==1 || l==1 && c==2){
        sg[l][c]=0;
        return 0;
    }
    int s[MAX*MAX]={0};
    for(int i=1;i<l;i++){
        if(i!=c)s[calcSg(i,c)]=1;
    }
    for(int i=1;i<c;i++){
        if(i!=l)s[calcSg(l,i)]=1;
    }
    for(int i=1;i<min(c,l);i++){
        s[calcSg(l-i,c-i)]=1;
    }
    int j=0;
    while(sg[l][c]==-1){
        if(!s[j])sg[l][c]=j;
        j++;
    }
    return sg[l][c];
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<MAX;i++)
        for(int j=1;j<MAX;j++)
            sg[i][j]=-1;
    int sgtot=0;
    for(int i=1;i<=n;i++){
        int l,c;
        cin>>l>>c;
        if(l==c || l==0 || c==0){
            cout<<"Y"<<endl;
            return 0;
        }
        sgtot^=calcSg(l,c);
    }
    cout<<(sgtot!=0 ? "Y" : "N")<<endl;
    return 0;
}