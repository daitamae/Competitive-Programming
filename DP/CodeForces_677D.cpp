#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<queue>
#define MAX 301
#define MAXP 301*301
using namespace std;

int n,m,p;
vector<pair<int,int>> chests[MAXP];
int a[MAX][MAX];

int dist[MAX][MAX];


int bfsDist[MAX][MAX];
vector<pair<int,int>> dirs;

queue<pair<int,int>> q;

void bfs(int i){
    
    for(int j=1;j<=n;j++){
        for(int k=1;k<=m;k++){
            bfsDist[j][k]=INT_MAX;
        }
    }



    vector<pair<int,int>> :: iterator it;
    for(it=chests[i].begin();it!=chests[i].end();it++){
        pair<int,int> pair = *it;
        //cout<<pair.first<<" "<<pair.second<<" "<<i<<endl;
        bfsDist[pair.first][pair.second]=dist[pair.first][pair.second];
        q.push(pair);
    }

    while(!q.empty()){
        pair<int,int> curr = q.front();
        
        q.pop();
        for(it=dirs.begin();it!=dirs.end();it++){
            pair<int,int> pair = *it;
            int dx=pair.first;
            int dy=pair.second;
            int x1=curr.first+dx;
            int y1=curr.second+dy;
            if(x1>=1 && y1>=1 && x1<=n && y1<=m){
                if(bfsDist[x1][y1]>
                    bfsDist[curr.first][curr.second]+1){
                    bfsDist[x1][y1]=bfsDist[curr.first][curr.second]+1;
                
                    if(a[x1][y1]==i+1){
                        dist[x1][y1]=bfsDist[x1][y1];
                    }
                    q.push(make_pair(x1,y1));
                }
                
            }
            
        }
    }
    
}

void fillTable(){
    for(int i=1;i<p;i++){
        int numChests = chests[i].size();
        int numNextChests = chests[i+1].size();
        if(numChests*numNextChests<n*m){
            for(int j=0;j<numChests;j++){
                for(int k=0;k<numNextChests;k++){
                    int x1=chests[i][j].first;
                    int y1=chests[i][j].second;
                    int x2=chests[i+1][k].first;
                    int y2=chests[i+1][k].second;
                    dist[x2][y2]=
                        min(dist[x2][y2],dist[x1][y1]+abs(x2-x1)+abs(y2-y1));
                }
            }
        }else bfs(i);   
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&p);
    chests[0].push_back(make_pair(1,1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int t;
            scanf("%d",&t);
            chests[t].push_back(make_pair(i,j));
            dist[i][j]=INT_MAX;
            a[i][j]=t;
        }
    }
    
    vector<pair<int,int>> :: iterator it;
    for(it=chests[1].begin();it!=chests[1].end();it++){
        pair<int,int> onePos = *it;
        dist[onePos.first][onePos.second]=onePos.first+onePos.second-2;
    }

    dirs.push_back(make_pair(-1,0));
    dirs.push_back(make_pair(0,-1));
    dirs.push_back(make_pair(1,0));
    dirs.push_back(make_pair(0,1));

    fillTable();
    cout<<dist[chests[p][0].first][chests[p][0].second]<<endl;
    return 0;
}