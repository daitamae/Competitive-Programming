#include<iostream>
#include<bits/stdc++.h>
#define MAX 200001
#define MAXLL 5e18
using namespace std;
typedef long long ll;

int n;
string str[MAX];
string revstr[MAX];
ll c[MAX];

ll table[MAX][2];

void fillTable(){
    
    for(int i=1;i<=n;i++){
        if(i==1){
            table[1][0]=0;
            table[1][1]=c[1];
            //cout<<table[i][0]<<" "<<table[i][1]<<endl;
        }else{ 
            table[i][0]=MAXLL;
            table[i][1]=MAXLL;

            if(str[i]>=str[i-1]){
                table[i][0]=min(table[i][0],table[i-1][0]);
            }
            if(str[i]>=revstr[i-1]){
                table[i][0]=min(table[i][0],table[i-1][1]);
            }

            if(revstr[i]>=str[i-1]){
                table[i][1]=min(table[i][1],table[i-1][0]+c[i]);
            }
            if(revstr[i]>=revstr[i-1]){
                table[i][1]=min(table[i][1],table[i-1][1]+c[i]);
            }

        }
    }
    if(table[n][0]>=MAXLL && table[n][1]>=MAXLL)cout<<-1<<endl;
    else cout<<min(table[n][0],table[n][1])<<endl;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        //cout<<i<<" "<<c[i]<<endl;
    }
    for(int i=1;i<=n;i++){
        cin>>str[i];
        revstr[i]=str[i];
        reverse(revstr[i].begin(),revstr[i].end());
    }
    fillTable();
    return 0;
}