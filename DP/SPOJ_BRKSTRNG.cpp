#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include<algorithm>
#define MAX 1002
#define MAXVAL 100000001
using namespace std;

int n;
int m;
int table[MAX][MAX];
int knuth[MAX][MAX];
int arr[MAX];

void fillTable(){
    for(int j=1;j<=m+1;j++){
        for(int i=j-1;i>=0;i--){
            if(i==j-1){
                table[i][j]=0;
                knuth[i][j]=i;
            }else if(i==j-2){
                table[i][j]=arr[j]-arr[i]+table[i][i+1]+table[i+1][j];;
                knuth[i][j]=i+1;
            }else{
                table[i][j]=MAXVAL;
               
                for(int l=knuth[i][j-1];l<=knuth[i+1][j];l++){
                    int newMin=arr[j]-arr[i]+table[i][l]+table[l][j];
                
                    if(table[i][j]>newMin){
                        knuth[i][j]=l;
                        table[i][j]=newMin;
                    }
                }
            }
            //cout<<table[i][j];
        }   //cout<<endl;
    }
    /*
    for(int j=1;j<=m+1;j++){
        for(int i=0;i<j;i++){
            cout<<table[i][j]<<" ";
        }   cout<<endl;
    }
    for(int j=1;j<=m+1;j++){
        for(int i=0;i<j;i++){
            cout<<knuth[i][j]<<" ";
        }   cout<<endl;
    }*/
}



int main(){
    while(scanf("%d %d",&n,&m)==2){
        arr[0]=0;
        for(int i=1;i<=m;i++){
            scanf("%d",arr+i);
        }
        arr[m+1]=n;
        fillTable();
        cout<<table[0][m+1]<<endl;
    }
    return 0;
}