#include<iostream>
#include<bits/stdc++.h>
#include<math.h>
#define MAX 100001
using namespace std;

struct vec{
    long double x,y;
    long double arg;
    int i;
};

int n;
long double PI;
vector<vec> vecs;

long double arg(long double x, long double y){
    long double ret=atan2(y,x);
    return ret;
}

bool vec_sorter(vec const& v1, vec const& v2) {
    return v1.arg < v2.arg;
}


int main(){
    PI=atan2(0,-1);
    scanf("%d",&n);
    long double x,y;
    for(int i=1;i<=n;i++){
        scanf("%Lf %Lf",&x,&y);
        vec v;
        long double absVal=sqrt(x*x+y*y);
        v.x=x/absVal;
        v.y=y/absVal;
        v.i=i;
        v.arg=arg(v.x,v.y);
        vecs.push_back(v);  
    }
    sort(vecs.begin(),vecs.end(), &vec_sorter);
    int i1,i2;
    long double minAng=10;
    for(int i=1;i<=n;i++){
        vec v1=vecs[i-1];
        vec v2=i<n? vecs[i] : vecs[0];
        long double ang=abs(v2.arg-v1.arg);
        if(ang>PI)ang=2*PI-ang;
        if(minAng>ang){
            minAng=ang;
            i1=v1.i;
            i2=v2.i;
        }

    }
    cout<<i1<<" "<<i2<<endl;
    return 0;
}