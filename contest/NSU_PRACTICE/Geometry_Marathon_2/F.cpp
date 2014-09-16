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

struct vec {
    double x , y;
    vec(double _x, double _y) : x(_x) , y(_y) {}
};

vec toVec( point a, point b ) {
    return vec( b.x - a.x , b.y - a.y );
}

vec scale( vec v, double s ) {
    return vec( v.x * s, v.y * s );
}

point translate(point p, vec v) {
    return point( p.x + v.x , p.y + v.y );
}

double dot( vec a , vec b ) {
    return ( a.x*b.x + a.y*b.y );
}

double norm_sq( vec v ) {
    return v.x * v.x + v.y * v.y;
}

double dist( point p1, point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
}

double distToLine( point p, point a, point b, point& c ) {
    // c = a + u * ab;
    vec ap = toVec(a,p), ab = toVec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    c = translate( a, scale(ab,u) );
    return dist( p , c );
}

vector<point> vp;

int main ( ) {

    int n, q;
    scanf( "%d %d", &n, &q );

    double sum_x = 0.0, sum_y = 0.0;
    for( int i=0 ; i< n; i++ ) {
        double x, y;
        scanf( "%lf %lf", &x, &y );
        sum_x += x;
        sum_y += y;
        vp.push_back( point(x,y) );
    }

    double pt_x = sum_x / n, pt_y = sum_y / n;

    for( int i=0 ; i < q; i++ ) {
        double ax ,bx ,ay, by;
        scanf( "%lf %lf %lf %lf", &ax, &ay, &bx, &by );
        double grad = (by-ay) / (bx-ax);
        double x = -pt_x;
        double y = ( grad * x ) - (grad * pt_x) + pt_y;
        double res = 0.0;
        point k;
        point A( x, y ), B( pt_x, pt_y );
        for( int j=0 ; j < vp.size(); j++ ) {
            res += distToLine( vp[j] , A, B, k );
        }
        res = round( res );
        printf( "Case %d: %.0lf\n" , i + 1, res );
    }

    return 0;
}
