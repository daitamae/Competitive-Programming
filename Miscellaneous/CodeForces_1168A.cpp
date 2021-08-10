#include <iostream>
#define MAX 300001
using namespace std;

int arr[MAX];
int n;
int m;


int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",arr+i);
    }
    int l=0;
    int r=m-1;
    int i,currMin;
    int cannot;
    while(l<r){
        cannot=0;
        i=(l+r)/2;
        currMin=arr[1];
        if(i+arr[1]>=m)currMin=0;
        for(int j=2;j<=n;j++){
            if(arr[j]<=currMin){
                if(arr[j]+i<currMin){
                    //cout<<j<<" currMin: "<<currMin<<endl;
                    cannot=1;
                    break;
                }
            }else if(arr[j]+i>=m){
                if((arr[j]+i)%m<currMin){
                    //cout<<j<<" currMin4: "<<currMin<<endl;
                    currMin=arr[j];
                }
            }else{
                //<<j<<" currMin3: "<<currMin<<endl;
                currMin=arr[j];
                
            }
        }
        if(cannot){
            l=i+1;
        }else{
            r=i;
        }
    }
    cout<<l<<endl;
    return 0;
}