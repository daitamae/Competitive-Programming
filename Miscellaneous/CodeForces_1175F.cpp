#include <iostream>
#include <bits/stdc++.h>
#define MAXSIZE 300001
using namespace std;

int arr[MAXSIZE];
long long sums[MAXSIZE];
vector<int> ones;

int n;
int rightMostRep[MAXSIZE];
int last[MAXSIZE];
int k;


long long sumValue(long long k){
    return ((k+1)*k)/2;
}

int isSubPermutation(int ql, int qr){
    //cout<<"AAAA "<<ql<<" "<<qr<<" "<<rightMostRep[qr]<<endl;
    if(rightMostRep[qr]<ql && sumValue(qr-ql+1)==(sums[qr]-sums[ql-1])) return 1;
    return 0;
}

void searchSubPermutations(int x,int l, int r){
    
    int maxSoFar=0;
    for(int i=x;i>l;i--){
        maxSoFar=max(arr[i],maxSoFar);
        
        int qr=i+(maxSoFar-1);
        if(qr<r && qr>=x && isSubPermutation(i,qr)){
            k++;
            //cout<<"count! "<<i<<" "<<min(i+(maxSoFar-1),r-1)<<endl;
        }
    }
    maxSoFar=1;
    for(int i=x+1;i<r;i++){
        maxSoFar=max(arr[i],maxSoFar);
        int ql=i-(maxSoFar-1);
        if(ql>l && ql<=x && isSubPermutation(ql,i)){
            k++;
            //cout<<"count! "<<max(ql,l+1)<<" "<<i<<endl;
        }
    }
}

int main(){
    scanf("%d",&n);
    ones.push_back(0);
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
        sums[i]=sums[i-1]+(long long) arr[i];
        if(arr[i]==1)ones.push_back(i);
    }
    ones.push_back(n+1);
    for(int i=1;i<=n;i++){
        if(last[arr[i]]!=0 && rightMostRep[i-1]<last[arr[i]]){
            rightMostRep[i]=last[arr[i]];
        }else{
            rightMostRep[i]=rightMostRep[i-1];
        }
        last[arr[i]]=i;
    }
    
    int c=0;
    int ant=0;
    int curr=0;
    int next=0;
    for(auto it = ones.begin(); it!=ones.end();++it){
        next=*it;
        if(c>=2){
            int x=*it; 
            searchSubPermutations(curr,ant,next);
        }
        ant=curr;
        curr=next;
        c++;
    }
    cout<<k<<endl;
    return 0;
}