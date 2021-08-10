#include <iostream>
#include <bits/stdc++.h>
#define MAXSIZE 300001
#define LOG2MAXSIZE 20

using namespace std;

int ancestors[MAXSIZE][LOG2MAXSIZE];
int n;
int stackTop[MAXSIZE];
int stackSizes[MAXSIZE];
int groups[MAXSIZE];

//LCA

void addEdge(int u, int v)
{
    stackSizes[v]=stackSizes[u]+1;
    ancestors[v][0]=u;
    int count=1;
    int lastAncestor=u;
    while(stackSizes[v]-1>=(1<<count)){
        ancestors[v][count]=ancestors[lastAncestor][count-1];
        lastAncestor=ancestors[v][count];
        count++;
    }
}


int LCA(int u, int v)
{
    int k=LOG2MAXSIZE;
    if(stackSizes[u]<stackSizes[v]){
        for(int i=k-1;i>=0;i--){
            if(stackSizes[ancestors[v][i]]>=stackSizes[u]){
                v=ancestors[v][i];
            }
        }
    }else if(stackSizes[u]>stackSizes[v]){
        for(int i=k-1;i>=0;i--){
            if(stackSizes[ancestors[u][i]]>=stackSizes[v]){
                u=ancestors[u][i];
            }
        }
    }
    if(u==v)return v;
    for(int i=k-1;i>=0;i--){
        if(ancestors[u][i]!=ancestors[v][i]){
            u=ancestors[u][i];
            v=ancestors[v][i];
        }
    }
    return ancestors[u][0];
}

//UF

void build(){
    for(int i=0;i<=n;i++){
        groups[i]=i;
    }
}

int find(int x){
    if(x==groups[x])return x;
    groups[x]=find(groups[x]);
    return groups[x];
}

void unite(int x, int y){
    x=find(x);
    y=find(y);
    if(x!=y){
        groups[y]=x;
        find(y);
    }
}

//

int main(){
    scanf("%d",&n);
    build();
    char ch;
    int v;
    int w;
    int vGroup;
    int wGroup;
    for(int i=1;i<=n;i++){
        scanf("%c",&ch);
        while(ch!='a' && ch!='b' && ch!='c'){
            scanf("%c",&ch);
        }
        scanf("%d",&v);
        if(ch=='a'){
            vGroup=find(v);
            addEdge(vGroup,i);
            stackTop[i]=i;
        }else if(ch=='b'){
            vGroup=find(v);
            int vParent=ancestors[vGroup][0];
            unite(vParent,i);
            stackTop[i]=stackTop[vParent];
            cout<<stackTop[vGroup]<<endl;
        }else if(ch=='c'){
            scanf("%d",&w);
            vGroup=find(v);
            wGroup=find(w);
            stackTop[i]=stackTop[vGroup];
            unite(vGroup,i);
            int res = LCA(vGroup,wGroup);
            cout<<stackSizes[res]<<endl;
        }
    }
    return 0;

}