#include <iostream>
#include<bits/stdc++.h>
#define MAX 200001

using namespace std;

int n,m;

vector<int> G[MAX];

int d[MAX];
int neighbors[MAX];


void addEdge(int a, int b){
    G[a].push_back(b);
    G[b].push_back(a);
    (d[a])++;
    (d[b])++;
}

int main(){
    scanf("%d %d", &n,&m);
    int a,b;
    for(int i=0;i<m;i++){
        scanf("%d %d",&a,&b);
        addEdge(a,b);
    }
    int mind=MAX;
    int k=0;
    for(int i=1;i<=n;i++){
        if(d[i]<mind){
            mind=d[i];
            k=i;
        }
    }
    for (auto it = G[k].begin();it != G[k].end(); ++it){
        int x=*it;
        neighbors[x]=1;
    }
    for(int i=1;i<=n;i++){
        if(neighbors[i] || i==k){
            cout<<"0 ";
        }else{
            cout<<"1 ";
        }
    }
    cout<<endl;
    return 0;
}