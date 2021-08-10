#include<iostream>
#include <algorithm> 
#define MAX 100001

using namespace std;

typedef long long ll;

int n;
int points[9][3];

ll dists[9];


ll dist(int i,int j){
    ll x=(points[i][0]-points[j][0]);
    ll y=(points[i][1]-points[j][1]);
    ll z=(points[i][2]-points[j][2]);
    return x*x+y*y+z*z;
}

int isCube(){
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(i!=j){
                dists[j-(j>i)]=dist(i,j);
            }
            //cout<<dists[j-(j>i)]<<" "<<dists[j-(j>i)]<<endl;
        }
        sort(dists+1,dists+9);
        ll d=dists[1];
        if(d==0)return 0;
        if(dists[2]!=d || dists[3]!=d)return 0;
        d*=2;
        if(dists[4]!=d || dists[5]!=d || dists[6]!=d)return 0;
        d/=2;
        d*=3;
        if(dists[7]!=d)return 0;
    }
    return 1;   
}

int searchCube(int k){
    if(k==8)return isCube();
    sort(points[k],points[k]+3);
    do{
        if(searchCube(k+1))return 1;
    }while(next_permutation(points[k],points[k]+3));
    return 0;
}

int main(){
    for(int i=1;i<=8;i++){
        scanf("%d %d %d",&points[i][0],&points[i][1],&points[i][2]);
    }
    int found=searchCube(1);
    if(!found)cout<<"NO"<<endl;
    else{
        cout<<"YES"<<endl;
        for(int i=1;i<=8;i++){
            cout<<points[i][0]<<" "<<points[i][1]<<" "<<points[i][2]<<endl;
        }
    }
    return 0;
}