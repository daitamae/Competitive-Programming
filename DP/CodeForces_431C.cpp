#include<iostream>
#define MAX 101
#define MAXVAL 1000000007
using namespace std;

int table[MAX][2];

int k;

int numPaths(int n, int d){
    if(table[n][d!=0]!=-1){
        return table[n][d!=0];
    }
    
    if(n==0 && d==0){
        table[0][0]=1;
        return 1;
    }
    if(n==0){
        table[0][1]=0;
        return 0;
    }
    int sum=0;
    for(int i=1;i<=k;i++){
        if(i>n)break;
        if(d==0){
            sum=(sum+numPaths(n-i,0))%MAXVAL;
        }else{
            if(d<=i){
                sum=(sum+numPaths(n-i,0))%MAXVAL;
            }else{
                sum=(sum+numPaths(n-i,d))%MAXVAL;
            }
        }
    }
    table[n][d!=0]=sum;
    return sum;
}

int main(){
    int n,d;
    for(int i=0;i<MAX;i++){
        table[i][0]=-1;
        table[i][1]=-1;
    }
    scanf("%d %d %d",&n,&k,&d);
    cout<<numPaths(n,d)<<endl;
}