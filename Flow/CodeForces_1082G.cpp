#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<queue>
#define MAXN 5001
using namespace std;
typedef long long ll;

struct edge{
    int v,pair;
    ll f,c;
};

int n,m;

ll maxf;

int edge_count[MAXN];
int path_length[MAXN];

vector<edge> G[MAXN];
queue<edge> q;


int bfs(int r,int s){
    fill(path_length,path_length+MAXN,-1);
    path_length[r]=0;
    queue<int> q;
    q.push(r);

    vector<edge> :: iterator it;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(it=G[x].begin();it!=G[x].end();it++){
            edge &e = *it;
            if(path_length[e.v]==-1 && e.f<e.c){
                path_length[e.v]=path_length[x]+1;
                q.push(e.v);
            }
        }
    }
    return path_length[s] == -1 ? 0 : 1;
}

ll increaseFlow(int x, ll f, int s){
    if(x==s)return f;
    while(edge_count[x]<G[x].size()){
        edge &e=G[x][edge_count[x]];
        if(path_length[e.v]==path_length[x]+1 && e.f<e.c){
            ll eLimit = min(f, e.c-e.f);
            ll esFlow = increaseFlow(e.v,eLimit,s);
            if(esFlow>0){
                e.f+=esFlow;
                G[e.v][e.pair].f-=esFlow;
                return esFlow;
            }
        }
        edge_count[x]++;
    }
    return 0;
}

void dinic(int r, int s){
    while(bfs(r,s)){
        fill(edge_count,edge_count+MAXN,0);
        ll lambda = increaseFlow(r,LLONG_MAX,s);
        while(lambda>0){
            maxf+=lambda;
            lambda = increaseFlow(r,LLONG_MAX,s);
        }
    }
}

void addEdge(int a, int b, ll c){
    edge ea;
    ea.v=b;
    ea.f=0;
    ea.c=c;
    ea.pair=G[b].size();
    edge eb;
    eb.v=a;
    eb.f=0;
    eb.c=0;
    eb.pair=G[a].size();
    G[a].push_back(ea);
    G[b].push_back(eb);
}

ll tot;

int main(){
    scanf("%d %d",&n,&m);
    int r=0;
    int s=m+n+1;
    for(int i=1;i<=n;i++){
        ll a;
        scanf("%lld",&a);
        addEdge(m+i,s,a);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        ll w;
        scanf("%d %d %dll",&u,&v,&w);
        addEdge(i,m+u,LLONG_MAX);
        addEdge(i,m+v,LLONG_MAX);
        addEdge(r,i,w);
        tot+=w;
    }
    dinic(r,s);
    cout<<tot-maxf<<endl;
    return 0;
}