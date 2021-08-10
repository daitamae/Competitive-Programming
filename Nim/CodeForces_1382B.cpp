#include<iostream>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;
typedef long long ll;

int t;
int n;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n;
        int a;
        int next;
        int play=0;
        cin>>a;
        int i=1;
        while(i<n){
            cin>>next;
            i++;
            
            if(a==1){
                play=!play;
                a=next;
            }
            else if(next==1){
                while(next==1 && i<n){
                    i++;
                    a=next;
                    cin>>next;
                }
                if(next!=1 && i<n){
                    i++;
                    a=next;
                    cin>>next;
                }else break; 
            }else{
                a=next;
            }
            //cout<<play<<endl;
        }   
        if(!play)cout<<"First"<<endl;
        else cout<<"Second"<<endl;
    }
    return 0;
}