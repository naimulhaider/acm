#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct point {
    double x, y;
    point() { x =0.0, y = 0.0; }
    point( double _x, double _y ) : x(_x) , y(_y){}

    bool operator < (point other) const {
        if( fabs(x-other.x) > EPS )
            return x < other.x;
        return y < other.y;
    }

    bool operator == (point other) const{
        return ( fabs(x-other.x) < EPS && fabs((y-other.y)) < EPS );
    }
};

int main() {

    double x1, y1, x2, y2, x3, y3, x4, y4;
    while( scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4) == 8 ){
        point a(x1,y1), b(x2,y2),c(x3,y3),d(x4,y4);
        if(b==c) c = d;
        point r = c;
        if(a.x<b.x) r.x-=fabs(a.x-b.x);
        else r.x+=fabs(a.x-b.x);
        if(a.y<b.y)r.y-=fabs(a.y-b.y);
        else r.y+=fabs(a.y-b.y);
        printf("%.3lf %.3lf\n", r.x , r.y );
    }

    return 0;
}
