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
    ret.x += a.x, ret.y += a.y;
    ret.x /= d, ret.y /=d;
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

    circle(const point a, const point b, const
           point c): o(circumcenter(a, b, c)) {
        r = ( norm(a.x-o.x, a.y - o.y) + norm(b.x-o.x, b.y-o.y )
             + norm(c.x-o.x, c.y-o.y) ) / 3.0;
    }

    bool contains(const point &p) const{
        return norm( p.x-o.x, p.y-o.y ) < r + EPS;
    }
};


struct line{
    double a, b, c;
    line ( double _a , double _b, double _c ) : a(_a), b(_b), c(_c){}
    line( point p1, point p2 ) {
        if( fabs(p1.x-p2.x) < EPS ) {
            a = 1.0, b = 0.0, c = -p1.x;
        } else {
            a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
            b = 1.0;
            c = -(double) (a*p1.x) - p1.y;
        }
    }
};

void circleLineIntersection( circle cir, line l, vector<point>& ret ) {
    double a = l.a;
    double b = l.b;
    double c = l.c + cir.o.x * a + cir.o.y * b;
    double r = cir.r;
    double aabb = a * a + b * b;
    double d = c * c / aabb - r * r;
    if (d > EPS) return;
    double x0 = -a * c / aabb;
    double y0 = -b * c / aabb;
    if (d > -EPS) {
      ret.push_back( point(x0 + cir.o.x, y0 + cir.o.y) );
      return;
    }
    d /= -aabb;
    double k = sqrt(d < 0 ? 0 : d);
    ret.push_back( point(x0 + k * b + cir.o.x, y0 - k * a + cir.o.y) );
    ret.push_back( point(x0 - k * b + cir.o.x, y0 + k * a + cir.o.y) );
}

int circlecircleIntersection( circle c1, circle c2 , vector<point>& pts ) {
    if ( hypot(c1.o.x - c2.o.x, c1.o.y - c2.o.y) < EPS ) {
      if ( fabs(c1.r - c2.r) < EPS) return 2;
      return 0;
    }
    double dx = c2.o.x - c1.o.x;
    double dy = c2.o.y - c1.o.y;
    double A = -2 * dx;
    double B = -2 * dy;
    double C = dx * dx + dy * dy + c1.r * c1.r - c2.r * c2.r;
    circleLineIntersection( circle( point(0,0), c1.r), line(A, B, C), pts );
    for( int i=0 ; i < pts.size(); i++ ) {
        pts[i].x += c1.o.x;
        pts[i].y += c1.o.y;
    }
    if( pts.size() > 0 ) return 1;
    return 0;
}

double my_round(double x) {
    return floor(x * 1000 + 0.5) / 1000;
}

int main () {

//    freopen("input.in", "r" ,stdin);

    double x1, y1 , r1, x2 , y2, r2;
    while( scanf("%lf %lf %lf %lf %lf %lf", &x1,&y1,&r1,&x2,&y2,&r2) == 6 ) {
        point c1(x1,y1), c2(x2,y2);
        circle cir1( c1, r1 ), cir2( c2, r2 );
        if( (fabs(cir1.o.x-cir2.o.x)<EPS) && (fabs(cir1.o.y-cir2.o.y)<EPS) && ( fabs(cir1.r) < EPS ) && ( fabs(cir2.r) < EPS) ) {
            printf( "(%.3lf,%.3lf)\n", cir1.o.x, cir1.o.y );
            continue;
        }
        vector<point> ints;
        int res = circlecircleIntersection( cir1, cir2, ints );
        if( res == 0 ) {
            cout << "NO INTERSECTION\n";
        } else if ( res == 2 ) {
            cout << "THE CIRCLES ARE THE SAME\n";
        } else {
            sort( ints.begin() , ints.end() );
            for( int i=0 ;i < ints.size(); i++ ) {
                printf( "(%.3lf,%.3lf)", my_round(ints[i].x), my_round(ints[i].y) );
            }
            printf( "\n" );
        }
    }
    return 0;
}

/*

*/
