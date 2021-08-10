#include<iostream>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;
typedef long long ll;

struct node{
    int length;
    int adj[26];
    int suffix;
};

int n;

node root1,root2;

node tree[MAX];

int curr;
string s;
int cnt;

int maxLength;

void add(int index){
    int x=curr;
    while(true){
        int currLength = tree[x].length;
        if(index-currLength>=1 && s[index] == s[index-currLength-1])break;
        x=tree[x].suffix;
    }

    int letterIdx = s[index]-'a';

    if(tree[x].adj[letterIdx]){
        curr = tree[x].adj[letterIdx];
        return;
    }

    tree[x].adj[letterIdx]=++cnt;
    tree[cnt].length = tree[x].length+2;
    maxLength = max(maxLength,tree[cnt].length);

    x = tree[x].suffix;
    curr = cnt;
    if(tree[curr].length == 1){
        tree[curr].suffix = 2;
        return;
    }
    while(true){
        int currLength = tree[x].length;
        if(index-currLength>=1 && s[index] == s[index-currLength-1])break;
        x=tree[x].suffix;
    }

    tree[cnt].suffix = tree[x].adj[letterIdx];
}

void build(){
    root1.length = -1;
    root1.suffix = 1;
    root2.length = 0;
    root2.suffix = 1;

    tree[++cnt] = root1;
    tree[++cnt] = root2;
    curr = 1;
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>s;
    build();
    for(int i=0;i<n;i++){
        add(i);
    }
    cout<<maxLength<<endl;
    return 0;
}