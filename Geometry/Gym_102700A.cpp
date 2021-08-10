#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct pos{
    long double x,y;
};

struct coefs{
    long double a,b,c;
};

long double squaredDistance(pos p1, pos p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}   

coefs getLineCoefficients(pos l1, pos l2){
    coefs co;
    co.a=l1.y-l2.y;
    co.b=l2.x-l1.x;
    co.c=l1.x*l2.y-l2.x*l1.y;
    return co;
}

long double getMinDistLine(pos p,pos l1,pos l2){
    coefs co=getLineCoefficients(l1,l2);

    long double d=(co.a*p.x+co.b*p.y+co.c)*(co.a*p.x+co.b*p.y+co.c)/(co.a*co.a+co.b*co.b);
    pos intersec;
    intersec.x=(co.b*(co.b*p.x-co.a*p.y)-co.a*co.c)/(co.a*co.a+co.b*co.b);
    intersec.y=(co.a*(-co.b*p.x+co.a*p.y)-co.b*co.c)/(co.a*co.a+co.b*co.b);
    if(((l1.x<=intersec.x && l2.x>=intersec.x) || (l1.x>=intersec.x && l2.x<=intersec.x)) &&
    ((l1.y<=intersec.y && l2.y>=intersec.y) || (l1.y>=intersec.y && l2.y<=intersec.y)))
    {
        return d;
    }
    long double dl1=squaredDistance(p,l1);
    long double dl2=squaredDistance(p,l2);
    return min(dl1,dl2);
}

long double calculateMinDist(pos pos1, pos pos2){
    pos origin;
    origin.x=origin.y=0;
    return getMinDistLine(origin,pos1,pos2);
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<fixed;
    cout<<setprecision(12);
    pos a,b,c,d;
    cin>>a.x>>a.y;
    cin>>b.x>>b.y;
    cin>>c.x>>c.y;
    cin>>d.x>>d.y;
    long double frac = squaredDistance(a,b)/squaredDistance(c,d);
    long double ret;
    //cout<<c.x<<" "<<c.y<<" "<<frac<<endl;
    if(frac>1){
        pos aux;
        aux=c;
        c=a;
        a=aux;
        aux=d;
        d=b;
        b=aux;
        frac = squaredDistance(a,b)/squaredDistance(c,d);
    }
    frac=sqrt(frac);

    pos relpos1,relpos2,relpos3;
    relpos1.x=c.x-a.x;
    relpos1.y=c.y-a.y;
    //cout<<relpos1.x<<" "<<relpos1.y<<" "<<frac<<endl;
    relpos2.x=c.x-b.x+(d.x-c.x)*frac;
    relpos2.y=c.y-b.y+(d.y-c.y)*frac;
    //cout<<relpos2.x<<" "<<relpos2.y<<endl;
    relpos3.x = relpos2.x+(d.x-c.x)*(1-frac);
    relpos3.y = relpos2.y+(d.y-c.y)*(1-frac);
    //cout<<relpos3.x<<" "<<relpos3.y<<endl;
    
    ret = calculateMinDist(relpos1,relpos2);
    ret = min(ret,calculateMinDist(relpos2,relpos3));
    cout<<sqrt(ret)<<endl;
    return 0;
}