#include <iostream>
#define MAX 1000000009
#define MAXSIZE 300003

using namespace std;

int table[MAXSIZE];


int arr[MAXSIZE];

int segTree[4*MAXSIZE];
int FirstElemSum[4*MAXSIZE];
int SecondElemSum[4*MAXSIZE];

int Sum(int x, int y){
    return (x+y)%MAX;
}

int Sub(int x, int y){
    if(x<0)x+=MAX;
    int ret=x-y;
    if(ret<0){
        ret+=MAX;
    }
    return ret;
}


//fibonacci DP

int Fibonacci(int k){
    if(table[k]==-1){
        table[k]=Sum(Fibonacci(k-1),Fibonacci(k-2));
    }
    return table[k];
}

int FibonacciSum(int i, int j){
    return Sub(Fibonacci(j+2),Fibonacci(i+1));
}

//fibonacci DP

//Generalized fibonacci

int RelativeFibonacci(int x, int k,int i=-1,int j=-1){
    if(i==-1 && j==-1){
        i=FirstElemSum[x];
        j=SecondElemSum[x];
    }
    if(k==1)return i;
    if(k==2)return j;
    int ret=((unsigned long long)i*Fibonacci(k-2)+(unsigned long long)j*Fibonacci(k-1))%MAX;
    
    return ret;
}


int RelativeFibonacciSum(int x, int k, int i=-1,int j=-1){
    if(i==-1 && j==-1){
        i=FirstElemSum[x];
        j=SecondElemSum[x];
    }
    if(k==1)return i;
    if(k==2)return Sum(i,j);
    int ret=((unsigned long long)i*Fibonacci(k)+(unsigned long long)j*Fibonacci(k+1))%MAX;
   
    ret=Sub(ret,j);
     
    return ret;
}

//Generalized fibonacci


//SegTree

void updateSons(int x, int m, int l,int r){
    FirstElemSum[2*x]=Sum(FirstElemSum[2*x],FirstElemSum[x]);
    SecondElemSum[2*x]=Sum(SecondElemSum[2*x],SecondElemSum[x]);
    segTree[2*x]=Sum(segTree[2*x],RelativeFibonacciSum(x,m-l+1));

    int a=RelativeFibonacci(x,(m+1)-l+1);
    int b=RelativeFibonacci(x,(m+1)-l+2);

    FirstElemSum[2*x+1]=Sum(FirstElemSum[2*x+1],a);
    SecondElemSum[2*x+1]=Sum(SecondElemSum[2*x+1],b);
    segTree[2*x+1]=Sum(segTree[2*x+1],RelativeFibonacciSum(x,r-m,a,b));
    
    FirstElemSum[x]=0;
    SecondElemSum[x]=0;
}

void queryUpdate(int x,int l , int r, int ql, int qr){
    if(ql<= l && qr>=r){
        FirstElemSum[x]=Sum(FirstElemSum[x],Fibonacci(l-ql+1));
        SecondElemSum[x]=Sum(SecondElemSum[x],Fibonacci(l-ql+2));
        segTree[x]=Sum(segTree[x],FibonacciSum(l-ql+1,r-ql+1));
        return;
    }
    
    int m=(l+r)/2;
    if(FirstElemSum[x]!=0 && SecondElemSum[x]!=0){
        updateSons(x,m,l,r);
    }
    if(ql<=m){
        queryUpdate(2*x,l,m,ql,qr);
    }
    if(qr>m){
        queryUpdate(2*x+1,m+1,r,ql,qr);
    }
    segTree[x]=Sum(segTree[2*x],segTree[2*x+1]);
}

int querySum(int x,int l , int r, int ql, int qr){
    if(ql>qr)
        return 0;
    if(ql<=l && qr>=r){
        return segTree[x];
    }
    int m=(l+r)/2;
    if(FirstElemSum[x]!=0 && SecondElemSum[x]!=0){
        updateSons(x,m,l,r);
    }
    int sum=0;
    if(ql<=m){
        sum=Sum(sum,querySum(2*x,l,m,ql,qr));
    }
    
    if(qr>m){
        sum=Sum(sum,querySum(2*x+1,m+1,r,ql,qr));
    }
    
    return sum;
}

//SegTree


int main(){
    
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
        arr[i]=Sum(arr[i],arr[i-1]);
    }
    for(int i=0;i<=MAXSIZE;i++){
        table[i]=-1;
    }
    table[0]=0;
    table[1]=1;
    table[2]=1;
    int l,r,queryType;
    for(int j=0;j<m;j++){
        scanf("%d %d %d",&queryType,&l,&r);
        if(queryType==1){
            queryUpdate(1,1,n,l,r);
        }else if(queryType==2){
            int sum=Sum(querySum(1,1,n,l,r),Sub(arr[r],arr[l-1]));
            
            cout<<sum<<endl;
        }
    }
    return 0;
}