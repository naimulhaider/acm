#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct point {
    double x, y;
    point() {}
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

double norm_sq( double x , double y ) {
    return x * x  + y  * y;
}

double norm( double x, double y ) {
    double ret = x * x + y * y;
    return sqrt( ret );
}

double det(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}

point circumcenter(point a, point b, point c){
    b = point( b.x-a.x, b.y-a.y );
    c = point( c.x-a.x, c.y-a.y );
    double d = 2.0 * det(b, c);
    point p = point( norm_sq( b.x , b.y ) , norm_sq( c.x,c.y ) );
    point ret( det(p, point(b.y, c.y)), det(point(b.x, c.x), p) );
    ret.x /= d, ret.y /=d;
    ret.x += a.x, ret.y += a.y;
    return ret;
}

struct circle {
    point o;
    double r;

    circle(const point o, double r): o(o), r(r) {}

    circle(const point a, const point b) {
            o = point( a.x + b.x , a.y + b.y );
            o.x *= 0.5, o.y *= 0.5;
            r = 0.5 * norm(a.x-b.x,a.y-b.y);
        }

    circle(const point a, const point b, const point c):
        o(circumcenter(a, b, c)) {
            r = ( norm(a.x-o.x, a.y-o.y)
                 + norm(b.x-o.x, b.y-o.y )
                + norm(c.x-o.x, c.y-o.y) ) / 3.0;
    }

    bool contains(const point &p) const{
        return norm( p.x-o.x, p.y-o.y ) < r + EPS;
    }
};

double my_round(double x) {
    return floor(x * 100 + 0.5) / 100;
}

int main () {

    double x1,y1,x2,y2,x3,y3;
    while( scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3)==6 ){
        circle c ( point(x1,y1),point(x2,y2),point(x3,y3) );
        double res = 2 * acos(-1) * c.r;
        res = my_round( res );
        printf( "%.2lf\n", res );
    }

    return 0;
}
