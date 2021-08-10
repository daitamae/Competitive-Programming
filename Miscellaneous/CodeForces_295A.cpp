#include<iostream>
#define MAX 100001
using namespace std;

int n;
int m;
int k;
long long arr[MAX];
long long sum[MAX];
long long l[MAX];
long long r[MAX];
long long d[MAX];
long long x[MAX];
long long y[MAX];
long long numOp[MAX];

int main(){
    cin>>n;
    cin>>m;
    cin>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        cin>>l[i];
        cin>>r[i];
        cin>>d[i];
        
    }
    for(int i=1;i<=k;i++){
        cin>>x[i];
        cin>>y[i];
        numOp[x[i]]++;
        if(y[i]<m){
            numOp[y[i]+1]--;
        }
    }
    for(int i=1;i<=m;i++){
        numOp[i]+=numOp[i-1];
        sum[l[i]]+=numOp[i]*d[i];
        if(r[i]<n){
            sum[r[i]+1]-=numOp[i]*d[i];
        }
    }
    for(int i=1;i<=n;i++){
        sum[i]+=sum[i-1];
        cout<<arr[i]+sum[i]<<" ";
    }
    cout<<endl;
    return 0;
}