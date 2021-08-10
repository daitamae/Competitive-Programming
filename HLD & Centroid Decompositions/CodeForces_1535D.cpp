#include<iostream>
#include<string>
#include<algorithm>
#define MAX 300001
using namespace std;

int k,n=1,q,p;
char c;
string str;
int f[MAX];

void getNumChamps(int i){
    if(i>n)return;
    getNumChamps(2*i);
    getNumChamps(2*i+1);
    if(str[i-1]=='1'){
        f[i]= 2*i>n ? 1 : f[2*i];
    }else if(str[i-1]=='0'){
        f[i]= 2*i>n ? 1 : f[2*i+1];
    }else{
        f[i]= 2*i>n ? 2 : f[2*i]+f[2*i+1];
    }
}

void update(int i){
    if(i<1)return;
    if(str[i-1]=='1'){
        f[i]= 2*i>n ? 1 : f[2*i];
    }else if(str[i-1]=='0'){
        f[i]= 2*i>n ? 1 : f[2*i+1];
    }else{
        f[i]= 2*i>n ? 2 : f[2*i]+f[2*i+1];
    }
    update(i/2);
}

int main(){
    cin>>k;
    for(int i=1;i<=k;i++){
        n*=2;
    }
    n--;

    cin>>str;
    reverse(str.begin(),str.end());
    cin>>q;
    getNumChamps(1);
    for(int i=1;i<=q;i++){
        cin>>p>>c;
        str[n-p]=c;
        update(n-p+1);
        cout<<f[1]<<endl;
    }
    return 0;
}