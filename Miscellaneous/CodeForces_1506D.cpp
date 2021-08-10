#include<iostream>
#include<map>
#define MAX 100001
using namespace std;

int n,t;

map<int,int> freq;

int main(){
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d",&n);
        int x,maxf=0;
        freq.clear();
        for(int j=1;j<=n;j++){
            scanf("%d",&x);
            freq[x]++;
            if(freq[x]>maxf)maxf=freq[x];
        }
        if(2*maxf-n>0)cout<<2*maxf-n<<endl;
        else cout<<n%2<<endl;
    }
    return 0;
}