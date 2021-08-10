#include<iostream>
#include<bits/stdc++.h>
#include<map>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   
    int t;
    cin>>t;
    string str;
    while(t--){
        int j=-1;
        int freq[256]={0};
        int isUsed[256]={0};
        cin>>str;
        int n=str.size();
        char ret[n+1];
        for(int i=0;i<n;i++){
            freq[str[i]]++;
        }
        for(int i=0;i<n;i++){
            //cout<<j<<" "<<isUsed[str[i]]<<" "<<str[i]<<" A "<<ret[j]<<" "<<freq[ret[j]]<<endl;
            while(j>=0 && !isUsed[str[i]] && str[i]>ret[j] && freq[ret[j]]>0)isUsed[ret[j--]]--;
            if(!isUsed[str[i]]){
                isUsed[str[i]]++;
                freq[str[i]]--;
                ret[++j]=str[i];
            }else{
                freq[str[i]]--;
            }
            //cout<<ret<<endl;
        }
        ret[++j]='\0';
        cout<<ret<<endl;
    }
    return 0;
}