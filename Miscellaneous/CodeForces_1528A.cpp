#include<iostream>
#include<bits/stdc++.h>

#define MAX 250001
typedef long long ll;

using namespace std;

int t,n;
int c;
ll l[MAX];
ll r[MAX];
vector<int> G[MAX];

ll table[MAX][2];

void dfs(int parent, int curr){
    //cout<<curr<<endl;
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son=*it;
        if(son!=parent){
            dfs(curr,son);
        }
    }
    ll sum1=0,sum2=0;
    for(auto it=G[curr].begin();it!=G[curr].end();it++){
        int son=*it;
        if(son!=parent){
            sum1+=max(table[son][1]+abs(r[son]-l[curr]),table[son][0]+abs(l[son]-l[curr]));
            sum2+=max(table[son][1]+abs(r[son]-r[curr]),table[son][0]+abs(l[son]-r[curr]));
        }
    }
    table[curr][0]=sum1;
    table[curr][1]=sum2;
}

void addEdge(int u, int v){
    G[v].push_back(u);
    G[u].push_back(v);
}

int main(){
    
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d",&n);
        //cout<<n<<endl;
        for (int j = 1; j <= n; j++)
        {
            scanf("%lld %lld",&(l[c+j]),&(r[c+j]));
        }
        for (int  j = 1; j < n; j++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            addEdge(c+u,c+v);
        }
        //cout<<"AA"<<endl;
        dfs(c+1,c+1);
        cout<<max(table[c+1][0],table[c+1][1])<<endl;
        c+=n;
    }
    return 0;
}
