#include<iostream>
#include<bits/stdc++.h>

#define MAX 100001
using namespace std;

int n,m;
int arr[MAX];

vector<int> G[MAX];
vector<int> T[MAX];

int depth[MAX];
int impossible;

//centroid

int isCentroid[MAX];
int subSize[MAX];

void addEdgeT(int u, int v){
    T[u].push_back(v);
    T[v].push_back(u);
}

int dfs(int curr,int parent, int *n){
    int size=1;
    *n+=1;
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son=*it;
        if(son!=parent && !isCentroid[son]){
            int sonSize = dfs(son,curr,n);
            size+=sonSize;
        }
    }
    subSize[curr]=size;
    return size;
}


int getCentroid(int curr,int parent, int n){
    int isCent=1;
    int maxSon=0;
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son=*it;
        if(son!=parent && !isCentroid[son]){
            if(subSize[son]>n/2){
                isCent=0;
            }
            if(maxSon==0 || subSize[son]>subSize[maxSon]){
                maxSon=son;
            }
        }
    }
    if(isCent && subSize[curr]>n/2)return curr;
    return getCentroid(maxSon,curr,n);
}

int getCentroid(int curr){

    int n=0;

    dfs(curr,curr, &n);

    int centroid = getCentroid(curr,curr,n);

    isCentroid[centroid]=1;

    return centroid;
}

int decomposeTree(int root,int d=0){
    int centroid = getCentroid(root);
    depth[centroid]=d;
    //cout<<"centroid: "<<centroid<<endl;
    for(auto it=G[centroid].begin();it!=G[centroid].end();it++){
        int son=*it;
        if(!isCentroid[son]){
            int centroidSub = decomposeTree(son,d+1);
            addEdgeT(centroid,centroidSub);
        }
    }
    return centroid;
}

//centroid


void addEdge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d", &u,&v);
        //cout<<u<<v<<endl;
        addEdge(u,v);
    }
    int centroid = decomposeTree(n/2);
    if(impossible)cout<<"Impossible"<<endl;
    else{
        for(int i=1;i<=n;i++){
            cout<<(char)('A'+depth[i])<<" ";
        }
    }cout<<endl;
}