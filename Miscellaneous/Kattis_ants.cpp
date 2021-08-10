#include<iostream>
using namespace std;

int m,l,n,pos;
int minTime,maxTime;

int main(){
    scanf("%d",&m);
    while(m){
        scanf("%d %d",&l,&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&pos);
            int newMin = min(pos,l-pos);
            int newMax = max(pos,l-pos);
            if(newMin > minTime){
                minTime = newMin;
            }
            if(newMax > maxTime){
                maxTime = newMax;
            }
        }
        m--;
        cout<<minTime<<" "<<maxTime<<endl;
        minTime=0;
        maxTime=0;
        
    }
    return 0;
}