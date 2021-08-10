#include<iostream>
#include<bits/stdc++.h>
#define MAX 100003
using namespace std;
typedef long long ll;


int n,m;
int arr[MAX];
int pairs[MAX][2];

vector<int> decomp;

//GRAPH FUNCTIONS

struct edge{
    int v,c,pair;
    ll f;
};

ll maxf;
ll maxOp;

int edge_count[MAX];
int path_length[MAX];
vector<edge> G[MAX];
queue<edge> q;

void clearG(int V){
    for(int i=0;i<V;i++) G[i].clear();
    maxf=0;
    fill(edge_count,edge_count+MAX,0);
    fill(path_length,path_length+MAX,0);
}


int bfs(int r,int s){
    fill(path_length,path_length+MAX,-1);
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
        fill(edge_count,edge_count+MAX,0);
        ll lambda = increaseFlow(r,INT_MAX,s);
        while(lambda>0){
            maxf+=lambda;
            lambda = increaseFlow(r,INT_MAX,s);
        }
    }
}

void addEdge(int a, int b, int c){
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


//GRAPH FUNCTIONS

void decompose(int x)
{
    if(x%2==0)decomp.push_back(2);
    while(x%2==0)x/=2;

    for(int i=3;i<=sqrt(x);i+=2){
        if(x%i==0)decomp.push_back(i);
        while(x%i==0)x/=i;
    }

    if(x>2)
        decomp.push_back(x);
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
    }
    for(int i=1;i<=m;i++){
        scanf("%d %d",&(pairs[i][0]),&(pairs[i][1]));
        if(pairs[i][0]%2)
            swap(pairs[i][0],pairs[i][1]);
    }

    for(int i=1;i<=n;i++){
        int x=arr[i];
        decompose(x);
    }
    sort(decomp.begin(),decomp.end());
    decomp.erase(unique(decomp.begin(),decomp.end()),decomp.end());

    for(int i=0;i<decomp.size();i++){
        int r=decomp[i];
        clearG(n+2);
        
        for(int j=1;j<=m;j++){
            addEdge(pairs[j][0],pairs[j][1],INT_MAX);
        }

        for(int j=1;j<=n;j++){
            int cap=0;
            int k=arr[j];
            while(k%r==0){
                k/=r;
                cap++;
            }
            if(j%2){
                addEdge(j,n+1,cap);
            }else{
                addEdge(0,j,cap);
            }
            
        }

        dinic(0,n+1);
        maxOp+=maxf;
    }
    cout<<maxOp<<endl;

    return 0;
}