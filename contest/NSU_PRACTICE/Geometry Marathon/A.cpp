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

double dist( point p1, point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
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

struct line{
    double a, b, c;
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

bool areParallel( line l1, line l2 ) {
    return ( fabs(l1.a-l2.a) < EPS && ( fabs(l1.b-l2.b) < EPS ) );
}

bool areIntersect( line l1, line l2, point& p ) {
    if( areParallel(l1,l2) ) return 0;
    p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
    if( fabs(l1.b>EPS) ) p.y = -( l1.a*p.x + l1.c );
    else p.y = -( l2.a*p.x + l2.c );
    return 1;
}

double distToLine( point p, point a, point b, point& c ) {
    // c = a + u * ab;
    vec ap = toVec(a,p), ab = toVec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    c = translate( a, scale(ab,u) );
    return dist( p , c );
}

bool onTop( point a, point b, point c, point d ) {
    if( areParallel( line(a,b) , line(c,d) ) ) {
        point k;
        double distA = distToLine( c, a, b, k );
        double distB = distToLine( d, a, b, k );
        if( distA < EPS || distB < EPS ) return 1;
    }
    return 0;
}

int main () {

    int n;
    cin >> n;

    cout << "INTERSECTING LINES OUTPUT" << "\n";

    for( int i=0 ; i< n; i++ ) {
        int x1, x2, x3, x4, y1, y2, y3, y4;
        scanf("%d %d %d %d %d %d %d %d",
              &x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        point a(x1,y1), b(x2,y2), c(x3,y3), d(x4,y4);
        point inter;
        if( onTop(a,b,c,d) ) {
            cout << "LINE\n";
        } else if ( areIntersect( line(a,b) , line(c,d), inter ) ) {
            printf( "POINT %.2lf %.2lf\n" , inter.x , inter.y );
        } else {
            cout << "NONE\n";
        }
    }

    cout << "END OF OUTPUT\n" ;

    return 0;
}
