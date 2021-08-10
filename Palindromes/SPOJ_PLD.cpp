#include<iostream>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;
typedef long long ll;

int cnt;
int k;
string s;

int isPalindrome(string str)
{
    int l = 0;
    int r = str.size() - 1;
  
    while(l<r)
    {
        if (str[l++] != str[r--])return 0;
    }
    return 1;
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>k;
    cin>>s;
    for(int i=0;i<=s.size()-k;i++){
        //cout<<s.substr(i,k)<<endl;
        if(isPalindrome(s.substr(i,k)))cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}