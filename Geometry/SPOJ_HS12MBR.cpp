#include<iostream>
#define MAX 100001
using namespace std;

int minx,miny,maxx,maxy;
int t,n;

int main(){
    scanf("%d",&t);
    char ch;
    for(int i=1;i<=t;i++){
        minx=1000;miny=1000;maxx=-1000;maxy=-1000;
        scanf("%d",&n);
        int j=1;
        while(j<=n ){
            scanf("%c",&ch);
            //cout<<ch<<endl;
            if(ch=='p'){
                int x,y;
                scanf("%d %d",&x,&y);
                if(x>maxx){
                    maxx=x;
                }
                if(x<minx){
                    minx=x;
                }
                if(y>maxy){
                    maxy=y;
                }
                if(y<miny){
                    miny=y;
                }
                j++;
            }else if(ch=='c'){
                int x,y,r;
                scanf("%d %d %d",&x,&y,&r);
                if(x+r>maxx){
                    maxx=x+r;
                }
                if(x-r<minx){
                    minx=x-r;
                }
                if(y+r>maxy){
                    maxy=y+r;
                }
                if(y-r<miny){
                    miny=y-r;
                }
                j++;
            }else if(ch=='l'){
                int x,y;
                scanf("%d %d",&x,&y);
                if(x>maxx){
                    maxx=x;
                }
                if(x<minx){
                    minx=x;
                }
                if(y>maxy){
                    maxy=y;
                }
                if(y<miny){
                    miny=y;
                }
                scanf("%d %d",&x,&y);
                if(x>maxx){
                    maxx=x;
                }
                if(x<minx){
                    minx=x;
                }
                if(y>maxy){
                    maxy=y;
                }
                if(y<miny){
                    miny=y;
                }
                j++;
            }
        }
        cout<<minx<<" "<<miny<<" "<<maxx<<" "<<maxy<<endl;
    }
    return 0;
}