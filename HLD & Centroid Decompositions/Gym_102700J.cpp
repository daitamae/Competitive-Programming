#include<iostream>
#include<bits/stdc++.h>
#include<unordered_map>
#define MAX 500001
using namespace std;

typedef long ll;

int n,b;
vector<int> G[MAX];
ll arr[MAX];
int V[MAX];
unordered_map<int,int> vertex;

int subTreeSize[MAX],maxSon[MAX],parent[MAX],depth[MAX],component[MAX];

inline void dfs(int curr,int par, int d){
    subTreeSize[curr]=1;
    parent[curr]=par;
    depth[curr]=d;
    
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son=*it;
        if(son!=par){
            dfs(son,curr,d+1);
            subTreeSize[curr]+=subTreeSize[son];
            if(maxSon[curr]==0 || subTreeSize[maxSon[curr]]<subTreeSize[son]){
                maxSon[curr]=son;
            }
        }
    }
}


int head[MAX],pos[MAX];
int currPos;

inline void hlddfs(int curr, int h){
    head[curr]=h;
    if(maxSon[curr]!=0){
        pos[curr]=++currPos;
        hlddfs(maxSon[curr],h);
    }else{
        pos[curr]=++currPos;
        return;
    }
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son = *it;
        if(son!=parent[curr] && son!=maxSon[curr]){
            hlddfs(son,son);
        }
    }
}

//sgt

ll sgt[4*MAX];
ll arr2[MAX];
map<int,int> leaves;


inline int getTot(int k,ll res){
    ll tot=0;
    if(res!=-1 && res!=0){
        for(int j=1;j<=k;j++){
            tot+=(res & 1);
            res=res>>1;
        }
    }
    else tot=-1;
    return (int)tot;
}


inline void update(int x, int l, int r, int i, ll val){
    //cout<<l<<" "<<r<<endl;
    if(l==r){
        if(!leaves.count(i)){
            leaves[i]=x;
        }
        sgt[x]=val;
        arr2[i]=val;
        return; 
    }
    int m=(l+r)/2;
    if(i<=m)update(2*x,l,m,i,val);
    else update(2*x+1,m+1,r,i,val);
    sgt[x]=sgt[2*x]&sgt[2*x+1];
}

inline void push_up(int i){
    int x=leaves[i];
    sgt[x]=arr2[i];
    x/=2;
    while(sgt[x]!=0 && x>0){
        sgt[x]=sgt[2*x]&sgt[2*x+1];
        x/=2;
    }
}

inline ll sgtQuery(int x, int l, int r, int ql, int qr){
    //cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
    if(ql==l && qr==r){
        return sgt[x];
    }
    int m=(l+r)/2;
    if(qr<=m)return sgtQuery(2*x,l,m,ql,qr);
    if(ql>m)return sgtQuery(2*x+1,m+1,r,ql,qr);
    ll res=sgtQuery(2*x,l,m,ql,m);
    if(res==0)return 0;
    return res & sgtQuery(2*x+1,m+1,r,m+1,qr);
}

//sgt

//uf

void make_set(int v) {
    component[v] = v;
}

int find_set(int v){
    if(v==component[v])return v;
    component[v]=find_set(component[v]);
    return component[v];
}

void unite(int u, int v){
    v=find_set(v);
    u=find_set(u);
    if(u!=v){
        component[u]=v;
    }
}

//

inline int query(int u, int v){
    if(find_set(u)!=find_set(v))return -1;
    ll ret=~0;
    int k=b;      
    while(head[u]!=head[v]){
        if(depth[head[u]]<depth[head[v]])swap(u,v);
        ret&=sgtQuery(1,1,currPos,pos[head[u]],pos[u]);
        if(ret==0)return -1;
        while(!((ret>>k)&1))k--;
        u=parent[head[u]];
    }
    if(u==v){
        return getTot(b,ret & arr2[pos[u]]);
    }
    if(depth[u]<depth[v])swap(u,v);
    return getTot(b,ret & sgtQuery(1,1,currPos,pos[v],pos[u]));
}


inline void addEdge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
}

int vcount;

int searched[MAX];

int queries[MAX][3];


queue<int> lazy;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>b;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        int k;
        cin>>k;
        V[i]=u;
        if(!vertex.count(u)){
            vertex[u]=++vcount;
            make_set(vertex[u]);
        }
        if(!vertex.count(v)){
            vertex[v]=++vcount;
            make_set(vertex[v]);
        }
        for(int j=1;j<=k;j++){
            int t;
            cin>>t;
            arr[vertex[u]]+=(1<<(t-1));
        }
        
        arr[vertex[u]]+=(1<<b);
        if(u!=v){
            addEdge(vertex[u],vertex[v]);
            unite(vertex[u],vertex[v]);
        }
    }
    int q;
    int q2=1;
    cin>>q;
    int t;
    for(int i=1;i<=q;i++){
        cin>>t;
        if(t==0){
            int x;
            cin>>x;
            queries[q2][0]=t;
            queries[q2++][1]=x;
        }else if(t==1){
            int x,y;
            cin>>x>>y;
            queries[q2][0]=t;
            queries[q2][1]=x;
            queries[q2++][2]=y;
        }else if(t==2){
            int u,v;
            cin>>u>>v;
            int k;
            cin>>k;
            vertex[u]=++vcount;
            make_set(vertex[u]);
            V[++n]=u;
            for(int j=1;j<=k;j++){
                int t;
                cin>>t;
                arr[vertex[u]]+=(1<<(t-1));
            }
            arr[vertex[u]]+=(1<<b);
            if(u!=v){
                addEdge(vertex[u],vertex[v]);
                unite(vertex[u],vertex[v]);
            }
        }
    }
    for(int i=1;i<=vcount;i++){
        int r=find_set(i);
        if(!searched[r]){
            searched[r]=1;
            dfs(r,r,0);
            hlddfs(r,r);
        }
    }   
    
    for(int i=1;i<=n;i++){
        //cout<<pos[vertex[V[i]]]<<" "<<vertex[V[i]]<<endl;
        update(1,1,currPos,pos[vertex[V[i]]],arr[vertex[V[i]]]);
    }
    for(int i=1;i<=q2;i++){
        t=queries[i][0];
        //cout<<"t: "<<t<<endl;
        if(t==0){
            int x=queries[i][1];
            //update(1,1,currPos,pos[vertex[x]],0);  
            arr2[pos[vertex[x]]]=0;
            lazy.push(pos[vertex[x]]);
        }else if(t==1){
            while(!lazy.empty()){
                int j=lazy.front();
                lazy.pop();
                push_up(j);
            }
            int x=queries[i][1],y=queries[i][2];
            if(depth[vertex[x]]<depth[vertex[y]])swap(x,y);
            printf("%d\n",query(vertex[x],vertex[y]));
        }
    }
    return 0;
}