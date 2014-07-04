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

// euclidean distance
double dist( point p1, point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
}

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



// check if lines are parallel
bool areParallel( line l1, line l2 ) {
    return ( fabs(l1.a-l2.a) < EPS && ( fabs(l1.b-l2.b) < EPS ) );
}

struct vec {
    double x , y;
    vec(double _x, double _y) : x(_x) , y(_y) {}
};

// create vector from two points
vec toVec( point a, point b ) {
    return vec( b.x - a.x , b.y - a.y );
}

vec scale( vec v, double s ) {
    return vec( v.x * s, v.y * s );
}

// translate p according to v
point translate(point p, vec v) {
    return point( p.x + v.x , p.y + v.y );
}

double dot( vec a , vec b ) {
    return ( a.x*b.x + a.y*b.y );
}

double norm_sq( vec v ) {
    return v.x * v.x + v.y * v.y;
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


double distToLineSegment( point p, point a, point b, point& c ) {
    vec ap = toVec(a,p), ab = toVec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    if( u < 0.0 ) {
        c = point(a.x , a.y);
        return dist( p, a );
    }
    if( u > 1.0 ) {
        c = point(b.x, b.y);
        return dist( p, b );
    }
    return distToLine( p, a, b, c );
}

// the segments are on top of one another, crosses at infinite points
bool segmentsOverlap( point a, point b, point c, point d ) {
    if( areParallel( line(a,b) , line(c,d) ) ) {
        if( a == c || a == d || b == c || b == d ) return 0; // joined at endpoints
        point k;
        double distA = distToLineSegment( c, a, b, k );
        double distB = distToLineSegment( d, a, b, k );
        if( distA < EPS || distB < EPS ) return 1;
    }
    return 0;
}

// two lines with fixed endpoints intersect?
bool segmentsIntersect( point a, point b, point c, point d ) {
    if( segmentsOverlap( a, b, c, d ) ) return 1;
    line l1(a,b) , l2(c,d);
    point k;
    if( areIntersect( l1, l2, k ) ) {
        point pt;
        return ( distToLineSegment( k, a, b, pt ) < EPS && distToLineSegment( k, c, d, pt ) < EPS );
    }
    return 0;
}


double cross( vec a , vec b ) {
    return a.x * b.y - a.y * b.x;
}

bool ccw( point p , point q, point r ) {
    return cross( toVec(p,q) , toVec(p,r) ) > 0;
}

bool collinear( point p, point q, point r ) {
    return fabs( cross(toVec(p,q), toVec(p,r)) ) < EPS;
}

double angle( point a, point o, point b ) {
    vec oa = toVec(o,a), ob = toVec(o,b);
    return acos( dot(oa,ob)/sqrt(norm_sq(oa)*norm_sq(ob)) );
}

bool inPolygon( point pt, const vector<point> &p ) {
    if( (int)p.size() == 0 ) return 0;
    double sum = 0;
    for( int i=0 ; i < (int)p.size()-1; i++ ) {
        if( ccw( pt, p[i], p[i+1] ) )
            sum += angle( p[i] , pt, p[i+1] );
        else sum -= angle( p[i] , pt, p[i+1] );
    }
    return fabs( fabs(sum) - 2 * acos(-1) ) < EPS;
}

int main () {


//    freopen("input.in", "r" ,stdin);

    int T;
    cin >> T;
    while( T-- ) {
        double x1, y1, x2, y2, x3, y3 ,x4, y4;
        cin >> x3>>y3>>x4>>y4>>x1>>y1>>x2>>y2;
        point r1(x1,y1), r2(x2,y2), r3(x1,y2), r4(x2,y1);
        point l1(x3,y3), l2(x4,y4);
        bool res = 0;
        point k;

        res |= segmentsIntersect( r1, r4, l1 ,l2 );
        res |= segmentsIntersect( r1, r3, l1 ,l2 );
        res |= segmentsIntersect( r3, r2, l1 ,l2 );
        res |= segmentsIntersect( r2, r4, l1 ,l2 );
        // check if totally within bounding box
        vector<point> pts;
        pts.push_back( r1 );
        pts.push_back( r3 );
        pts.push_back( r2 );
        pts.push_back( r4 );
        pts.push_back( r1 );

        res |= inPolygon( l1, pts );
        res |= inPolygon( l2, pts );

        if( res  ) cout << "T\n";
        else cout << "F\n";
    }

    return 0;
}
