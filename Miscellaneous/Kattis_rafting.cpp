#include <iostream>
#include<bits/stdc++.h>
#define MAX 101
#define MAXDIST 1000

using namespace std;

struct pos{
    double x,y;
};

struct coefs{
    double a,b,c;
};

int n;
int mi;
int mo;
pos inner[MAX];
pos outer[MAX];

double squaredDistance(pos p1, pos p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}   

coefs getLineCoefficients(pos l1, pos l2){
    coefs co;
    co.a=l1.y-l2.y;
    co.b=l2.x-l1.x;
    co.c=l1.x*l2.y-l2.x*l1.y;
    return co;
}

double getMinDistLine(pos p,pos l1,pos l2){
    coefs co=getLineCoefficients(l1,l2);

    double d=(co.a*p.x+co.b*p.y+co.c)*(co.a*p.x+co.b*p.y+co.c)/(co.a*co.a+co.b*co.b);
    pos intersec;
    intersec.x=(co.b*(co.b*p.x-co.a*p.y)-co.a*co.c)/(co.a*co.a+co.b*co.b);
    intersec.y=(co.a*(-co.b*p.x+co.a*p.y)-co.b*co.c)/(co.a*co.a+co.b*co.b);
    if(((l1.x<=intersec.x && l2.x>=intersec.x) || (l1.x>=intersec.x && l2.x<=intersec.x)) &&
    ((l1.y<=intersec.y && l2.y>=intersec.y) || (l1.y>=intersec.y && l2.y<=intersec.y)))
    {
        return d;
    }
    double dl1=squaredDistance(p,l1);
    double dl2=squaredDistance(p,l2);
    return min(dl1,dl2);
}

double calculateMinDist(){
    double minDist=MAXDIST*MAXDIST;
    double newDist;
    for(int i=1;i<=mi;i++){
        for(int j=2;j<=mo+1;j++){
            if(j<=mo){
                newDist=getMinDistLine(inner[i],outer[j-1],outer[j]);
            }else{
                newDist=getMinDistLine(inner[i],outer[mo],outer[1]);
            }
            if(newDist<minDist){
                minDist=newDist;
            }
        }
    }
    for(int i=1;i<=mo;i++){
        for(int j=2;j<=mi+1;j++){
            if(j<=mi){
                newDist=getMinDistLine(outer[i],inner[j-1],inner[j]);
            }else{
                newDist=getMinDistLine(outer[i],inner[mi],inner[1]);
            }
            if(newDist<minDist){
                    minDist=newDist;
            }
        }
    }
    return minDist;
}


int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&mi);
        for(int j=1;j<=mi;j++){
            scanf("%lf",&(inner[j].x));
            scanf("%lf",&(inner[j].y));
        }
        scanf("%d",&mo);
        for(int j=1;j<=mo;j++){
            scanf("%lf",&(outer[j].x));
            scanf("%lf",&(outer[j].y));
        }
        double ret=sqrt(calculateMinDist())/2;
        cout<<ret<<setprecision(8)<<endl;
    }
}
