#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>

#define MAX 2501
#define MAXQ 100001
using namespace std;

struct rect{
    int r1,c1,r2,c2;
};

int n;
int m;
int q;

vector<rect> v;

int isInside(int r, int c,rect re){
    if(r>=re.r1 && r<=re.r2 && c>=re.c1 && c<=re.c2)return 1;
    return 0;
}

int pathIntersects(rect points, rect re){
    if((isInside(points.r1,points.c1,re) && isInside(points.r2,points.c2,re)) ||
        (!isInside(points.r1,points.c1,re) && !isInside(points.r2,points.c2,re))
    )return 0;
    return 1;
}



int main(){
    scanf("%d %d %d",&n, &m, &q);
    int t,r1,c1,r2,c2;

    for(int i=1;i<=q;i++){
        rect re;
        scanf("%d %d %d %d %d",&t,&re.r1,&re.c1,&re.r2,&re.c2);
        if(t==1){
            v.push_back(re);
        }else if(t==2){
            v.erase(
                remove_if(v.begin(), v.end(), [&](rect const & re2) {
                    return re2.r1 == re.r1 && re2.r2 == re.r2 && re2.c1 == re.c1 && re2.c2 == re.c2;
                }),
                v.end());
        }else{
            int yes=1;
            
            vector<rect>::iterator it;
            for(it=v.begin();it!=v.end();it++){
                rect re2=*it;
                if(pathIntersects(re,re2)){
                    yes=0;
                    break;
                }
            }
            if(yes)printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}