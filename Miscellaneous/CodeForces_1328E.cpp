#include <iostream>
#include <bits/stdc++.h>
#define MAXSIZE 200001

using namespace std;

int parents[MAXSIZE];
int depths[MAXSIZE];
int *vertices;
int k;
int pass1[MAXSIZE];
int pass2[MAXSIZE];
int pass1Count=0;
int pass2Count=0;
vector<int> G[MAXSIZE];

void addEdge(int u, int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

void dfs(int parent,int curr, int depth){
    if(parents[curr]!=0)return;
    depths[curr]=depth;
    parents[curr]=parent;
    pass1[curr]=(pass1Count++);
    for (auto it = G[curr].begin();it != G[curr].end(); ++it){
        int x=*it;
        dfs(curr,x,depth+1);
    }
    pass2[curr]=(pass2Count++);
}

int isAncestor(int x, int y){
    if(pass1[x]<=pass1[y] && pass2[x]>=pass2[y]){
        return 1;
    }
    return 0;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n-1;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }
    dfs(-1,1,0); 
    for(int i=0;i<m;i++){
        int yes=1;
        scanf("%d",&k);
        vertices = new int[k+1];
        int maxDepth=0;
        int deepest=1;
        for(int j=1;j<=k;j++){
            int l;
            scanf("%d",&l);
            vertices[j]=l;
            if(maxDepth<depths[l]){
                maxDepth=depths[l];
                deepest=l;
            }
        }
        for(int j=1;j<=k;j++){
            int x=vertices[j];
            if(x!=deepest && x!=1){
                vertices[j]=parents[x];                 
            }
            if(!isAncestor(vertices[j],deepest)){
                yes=0;
                break;
            }        
        }
        if(yes){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
        free(vertices);
    }
    return 0;
}
