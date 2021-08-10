#include<iostream>
#include<bits/stdc++.h>
#define MAX 100001
#define MAXIT 20
using namespace std;

int n,c;
vector<int> G[MAXIT][MAX];
int size[MAX],maxSon[MAXIT][MAX],parent[MAX],depth[MAX];

inline void dfs(int curr,int par, int d){
    //cout<<curr<<" "<<par<<endl;
    size[curr]=1;
    parent[curr]=par;
    depth[curr]=d;
    for(auto it=G[c][curr].begin();it!=G[c][curr].end();it++){
        int son=*it;
        if(son!=par){
            dfs(son,curr,d+1);
            size[curr]+=size[son];
            if(maxSon[c][curr]==0 || size[maxSon[c][curr]]<size[son]){
                maxSon[c][curr]=son;
            }
        }
    }
}


int head[MAX],pos[MAX];
int currPos;

inline void hlddfs(int curr, int h){
    //cout<<curr<<" "<<maxSon[c][curr]<<endl;
    head[curr]=h;
    if(maxSon[c][curr]!=0){
        pos[curr]=++currPos;
        //cout<<"AA"<<endl;
        hlddfs(maxSon[c][curr],h);
    }else{
        pos[curr]=++currPos;
        return;
    }

    for(auto it=G[c][curr].begin();it!=G[c][curr].end();it++){
        int son = *it;
        if(son!=parent[curr] && son!=maxSon[c][curr]){
            hlddfs(son,son);
        }
    }
}

//segTree

int sgt[MAXIT][4*MAX];

inline void update(int x, int l, int r, int i, int val){
    if(l==r){
        sgt[c][x]=val;
        return;
    }
    int m=(l+r)/2;
    if(i<=m)update(2*x,l,m,i,val);
    else update(2*x+1,m+1,r,i,val);
    sgt[c][x]=max(sgt[c][2*x],sgt[c][2*x+1]);
}

inline int sgtQuery(int x, int l, int r, int ql, int qr){
    if(ql==l && qr==r){
        return sgt[c][x];
    }
    int m=(l+r)/2;
    if(qr<=m)return sgtQuery(2*x,l,m,ql,qr);
    if(ql>m)return sgtQuery(2*x+1,m+1,r,ql,qr);
    return max(sgtQuery(2*x,l,m,ql,m),sgtQuery(2*x+1,m+1,r,m+1,qr));
}

inline int query(int u, int v){
    int ret=0;      
    while(head[u]!=head[v]){
        
        if(depth[head[u]]<depth[head[v]])swap(u,v);
        ret=max(ret,sgtQuery(1,1,currPos,pos[head[u]],pos[u]));
        u=parent[head[u]];
    }
    if(u==v)return ret;
    if(depth[u]<depth[v])swap(u,v);
    return max(ret,sgtQuery(1,1,currPos,pos[maxSon[c][v]],pos[u]));
}

int costs[MAX];
pair<int,int> edgeNum[MAX];

inline void addEdge(int u,int v){
    G[c][u].push_back(v);
    G[c][v].push_back(u);
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<n;i++){
            int a,b,c;
            cin>>a>>b>>c;
            addEdge(a,b);
            costs[i]=c;
            edgeNum[i].first=a;
            edgeNum[i].second=b;
        }
        
        dfs(1,1,0);
        hlddfs(1,1);
        
        for(int i=1;i<n;i++){
            int u=edgeNum[i].first,v=edgeNum[i].second;
            if(depth[edgeNum[i].first]<depth[edgeNum[i].second]){
                swap(edgeNum[i].first,edgeNum[i].second);
            }
            update(1,1,currPos,pos[edgeNum[i].first],costs[i]);
        }
        char qstr[6];
        do{
            cin>>qstr;
            if(qstr[0]=='Q'){
                int a,b;
                cin>>a>>b;
                printf("%d\n",query(a,b));
            }else if(qstr[0]=='C'){
                int a,b;
                cin>>a>>b;
                int u=edgeNum[a].first;
                int v=edgeNum[a].second;
                update(1,1,currPos,pos[u],b);
            }
        }while(qstr[0]!='D');
        c++;
        currPos=0;
    }
    
    return 0;
}