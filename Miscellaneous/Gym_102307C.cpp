#include <iostream>

#define MAX 100001
#define MAXTABLE 1002

using namespace std;

int n;
int range;
int table[MAXTABLE][MAXTABLE];
int maxVal;
string A,B;

void fillTable(){
    for(int i=1;i<=range;i++){
        for(int j=1;j<=range;j++){
            table[i][j]=max(table[i-1][j],table[i][j-1]);
            while(i+table[i][j]-1<n && j+table[i][j]-1<n && A[i+table[i][j]-1]==B[j+table[i][j]-1])table[i][j]++;
            if(table[i][j]>maxVal){
                maxVal=table[i][j];
                if(maxVal>=0.99*n)return;
            }
        }
    }
}

int main(){
    int ch;
    getline(cin,A);
    getline(cin,B);
    n=B.length();
    range = n/100+1;
    fillTable();
    if(maxVal>=0.99*n){
        cout<<"Long lost brothers D:"<<endl;
    }else{
        cout<<"Not brothers :("<<endl;
    }
    return 0;
}