#include<bits/stdc++.h>
using namespace std;

/* *** GEOMETRY NOTES ***

Triangles:
The largest circle in a triangle is centered at the in-center of the triangle. Known three sides,
the radius can be found by the formula r = 2 * a / p, where a is the area(heron) and p is the perimeter.


*** END NOTES *** */

const double EPS = 1e-6;
const double PI = acos(-1);

/*** ALGEBRAIC METHODS ****/
// the area of a triangle given three sides
double heron( double sa, double sb, double sc ) {
    double s = 0.5 * (sa + sb + sc);
    double ret = s * (s-sa) * (s-sb) * (s-sc);
    return sqrt( ret );
}

// sector area of circle given radius and angle
double sectorArea( double r, double theta ) {
    return (r * r * theta) / 2.0;
}

// returns the angle thetaA having known three sides
double cosineAngle( double a, double b, double c ) {
    return acos( (b*b + c * c - a*a) / (2 * b * c) );
}

/** Geometry Data Structures and Functions **/

int signum(double x) { return x < -EPS? -1: x > EPS; }

double my_round(double x) {
    return floor(x * 1000 + 0.5) / 1000;
}

struct point_i {
    int x, y;
    point_i( int _x, int _y) : x(_x), y(_y){}
};

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

// euclidean distance
double dist( point p1, point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
}

double toRadian( double deg ) {
    return acos(-1.0) * deg / 180.0;
}

double toDegree( double rad ) {
    return 180.0 * rad / acos(-1.0);
}

// rotate p by theta CCW wrt origin
point rotate( point p , double theta ) {
    double rad = toRadian(theta);
    return point( p.x * cos(rad) - p.y * sin(rad) ,
        p.x * sin(rad) + p.y * cos(rad) );
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

// check if lines are same
bool areSame( line l1 , line l2 ) {
    return areParallel(l1,l2) && ( fabs(l1.c-l2.c) < EPS );
}

// returns true if they intersect, and point is updated
// note that lines here extend to infinity ( not segments )
bool areIntersect( line l1, line l2, point& p ) {
    if( areParallel(l1,l2) ) return 0;
    p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
    if( fabs(l1.b>EPS) ) p.y = -( l1.a*p.x + l1.c );
    else p.y = -( l2.a*p.x + l2.c );
    return 1;
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

/** POLYGON **/

// polygon area
double area( const vector<point> &p ) {
    double result = 0.0, x1, y1, x2, y2;
    for( int i=0 ; i < (int) p.size(); i++ ) {
        x1 = p[i].x , x2 = p[i+1].x;
        y1 = p[i].y , y2 = p[i+1].y;
        result += (x1*y2 - x2*y1);
    }
    return fabs(result) / 2.0;
}

// check convexity of polygon
bool isConvex ( const vector<point> &p ) {
    int sz = (int) p.size();
    if( sz <= 3 ) return false;
    bool isLeft = ccw(p[0],p[1],p[2]);
    for( int i=1; i<sz-1; i++ ) {
        if( ccw( p[i], p[i+1], p[ (i+2)==sz?1:i+2 ] ) != isLeft ) {
            return false;
        }
    }
    return true;
}

// check if point is inside polygon
// note that first point and last point must be same
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

// line_segment pq intersect with line ab
point lineIntersectSeg( point p , point q, point A, point B ) {
    double a = B.y - A.y, b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs( a * p.x + b * p.y + c );
    double v = fabs( a * q.x + b * q.y + c );
    return point( (p.x*v+q.x*u) / (u+v) , (p.y*v+q.y*u) / (u+v) );
}

// cuts polygon Q along the line formed by point a -> point b
// note that the last point must be same as the first point
vector<point> cutPolygon( point a, point b, const vector<point> &Q ) {
    vector<point> P;
    for( int i=0 ; i < (int) Q.size(); i++ ) {
        double left1 = cross( toVec(a,b) , toVec(a,Q[i]) ), left2 = 0;
        if( i != (int) Q.size() - 1  ) left2 = cross( toVec(a,b) , toVec(a,Q[i+1]) );
        if( left1 > -EPS ) P.push_back( Q[i] );
        if( left1 * left2 < -EPS ) {
            P.push_back( lineIntersectSeg(Q[i] , Q[i+1], a, b) );
        }
    }

    if( !P.empty() && !( P.back() == P.front() ) ) {
        P.push_back( P.front() );
    }
    return P;
}

// returns distance from point p to line ( a, b )
// c = closest point in the line from p
// note that AB is not line segment, means it extends to infinity
double distToLine( point p, point a, point b, point& c ) {
    // c = a + u * ab;
    vec ap = toVec(a,p), ab = toVec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    c = translate( a, scale(ab,u) );
    return dist( p , c );
}

// in case of line segment, end points are considered
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
            r = ( norm(a.x-o.x, a.y - o.y)
                 + norm(b.x-o.x, b.y-o.y )
                + norm(c.x-o.x, c.y-o.y) ) / 3.0;
    }

    // two points & radius
    circle(const point a, const point b, const double R) {
        double d = dist( a,b );
        double area = heron( d, R ,R );
        double h = (2 * area) / d;
        double mx = (a.x + b.x) / 2, my = (a.y + b.y) / 2;
        double vx = a.x - b.x , vy = a.y - b.y;
        vx /= d, vy /= d;
        vx *= h , vy *= h;
        vx *= -1; // for left hand point
        // cur vx *= -1 and do vy *= -1 for right hand point
        o.x = ( mx + vy );
        o.y = (my + vx);
        r = R;
    }

    bool contains(const point &p) const{
        return norm( p.x-o.x, p.y-o.y ) < r + EPS;
    }
};

bool operator ==(const circle &a, const circle &b){
    return a.o == b.o && a.r == b.r;
}

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

// 0 => doesn't intersect
// 1 => intersects
// 2 => infinite intersections
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


// The minimum circle that bounds all the points
circle mincircle(point points[], int n){
    circle result(point(0.0, 0.0), 0.0);
    for (int i = 0; i < n; ++i){
        if (!result.contains(points[i])){
            result = circle(points[i], 0.0);
            for (int j = 0; j < i; ++ j){
                if (!result.contains(points[j])){
                    result = circle(points[i], points[j]);
                    for (int k = 0; k < j; ++k){
                        if (!result.contains(points[k])){
                            result =circle(points[i], points[j], points[k]);
                        }
                    }
                }
            }
        }
    }
    return result;
}

double dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }

// line point distance
double point_to(point &from , point &a, point &b) {
    point p = from;
    return fabs(det( point(p.x-a.x,p.y-a.y) , point(p.x-b.x,p.y-b.y) ) / norm(a.x-b.x,a.y-b.y) );
}


point project( point from, point a, point b) {
    point p = from;
    point k ( b.x - a.x, b.y - a.y );
    double nrm = norm_sq( a.x - b.x, a.y - b.y );
    double dt = dot( point(p.x-a.x,p.y-a.y), point(b.x-a.x,b.y-a.y) );
    double dtbnrm = dt / nrm;
    k.x *= dtbnrm;
    k.y *= dtbnrm;
    return point( a.x + k.x , a.y + k.y );
}

point intersect_cir_line( circle &c, point &a, point &b) {
    double x = sqrt(c.r*c.r - point_to(c.o,a,b) * point_to(c.o,a,b) );
    double normalizer = norm ( a.x - b.x , a.y - b.y );
    point ret ( (a.x - b.x)*x/normalizer , (a.y - b.y)*x/normalizer );
    point prj = project( c.o , a, b );
    return point( ret.x + prj.x , ret.y + prj.y );
}

double angle(const point &a, const point &b) { return atan2(det(a, b), dot(a, b)); }


bool onSegment(point& p, point& a, point& b){
    point pa ( p.x-a.x, p.y-a.y );
    point pb ( p.x - b.x , p.y - b.y );
    return ( signum( det(pa,pb) ) == 0 && signum( dot(pa,pb) ) <= 0 );
}

// CIRCLE - TRIANGLE INTERSECTION
double intersect(circle c, point a, point b){
    if ( a == c.o || b == c.o ) {
        return 0.0;
    }
    if( signum( det(a,b) ) == 0 ) {
        return 0.0;
    }

    a.x -= c.o.x, a.y -= c.o.y;
    b.x -= c.o.x , b.y -= c.o.y;
    c.o = point();
    if (c.contains(b)) swap(a, b);
    if (c.contains(a) && c.contains(b)) {
        return 0.5 * fabs(det(a, b)); // 1. the area of the triangle
    }
    if (c.contains(a)) {
        point p = intersect_cir_line(c, b, a);
        return 0.5 * ( fabs(det(a, p)) + fabs( c.r*c.r * angle(p, b) ) ); // 2. one point inside
    }
    if ( point_to(c.o,a, b) >= c.r - EPS){
        return 0.5 * fabs(c.r*c.r * angle(a, b)); // 3. Both outside and line doesnt intersect
    }
    // 4. Both Outside & Line Intersects circle at 2 points
    point p = intersect_cir_line(c, a, b);
    point q = intersect_cir_line(c, b, a);

    point prj = project( point(0,0) , a, b );

    double totSector = fabs( c.r * c.r * angle(a,b) ) / 2;
    double triangle = fabs( det(p,q) ) / 2;
    double smallSector = fabs( c.r * c.r * angle(p,q) ) / 2;

    if( onSegment( prj , a, b ) ) {
        return totSector - ( smallSector - triangle ) ;
    }

    return totSector ;

}

//Triangle Centroid
point centroid(const point &a, const point &b, const point &c){
    point ret ( a.x+b.x+c.x , a.y+b.y+c.y );
    ret.x /= 3.0, ret.y /= 3.0;
    return ret;
}

//Triangle In - Center
point incenter(const point &a, const point &b,const point &c){
    double nrmab = norm( a.x-b.x, a.y-b.y ),
        nrmbc = norm(b.x-c.x,b.y-c.y), nrmca = norm( c.x-a.x,c.y-a.y );
    double p = nrmab + nrmbc + nrmca;
    double retx = (a.x * nrmbc + b.x * nrmca + c.x * nrmab)/p;
    double rety = (a.y * nrmbc + b.y * nrmca + c.y * nrmab)/p;
    return point( retx, rety );
}

//Triangle Orthocenter
point orthocenter(const point &a, const point &b, const point &c){
    point ret ( a.x + b.x + c.x, a.y + b.y + c.y );
    point cc = circumcenter(a, b, c);
    cc.x *= 2.0, cc.y *= 2.0;
    ret.x -= cc.x;
    ret.y -= cc.y;
    return ret;
}

/* *** 3D Geometry *** */
struct point3d{
    double x,y,z;
    point3d operator-(point3d v){
        return (point3d){
            x-v.x, y-v.y, z-v.z
        };
    }
};

double trip(point3d a, point3d b, point3d c){
    return a.x * ( b.y * c.z - b.z * c.y )
           - a.y * ( b.x * c.z - b.z * c.x )
           + a.z * ( b.x * c.y - b.y * c.x );
}

double len(point3d a){
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

point3d cross(point3d a, point3d b){
    return (point3d){
        a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
    };
}

double dot(point3d a, point3d b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


/** Computational Geometry **/
typedef long long LL;

struct Point {
    LL x,y;
    Point() {}
    Point( LL _x, LL _y ) : x(_x), y(_y){}
    bool operator<(const Point &p)const {
        return(x==p.x) ? y<p.y : x<p.x;
    }
};

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
LL cross(const Point &O, const Point &A, const Point &B){
    return (A.x-O.x) * (B.y-O.y) - (A.y-O.y) * (B.x-O.x);
}
// Returns a list of convex hull in counterclockwise order.
// In case of collinear points, only end-points are taken (not middle).
// The last point is the same as the first one.
vector<Point> ConvexHull(vector<Point> P){
    int n = P.size(), k = 0;
    vector<Point> H(2*n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; i++){
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--){
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}

/** 3D Convex Hull **/
#define MAXN 1010
typedef long long vtype;
/* Basic 3D vector implementation */
struct vec3 {
  vec3() { X[0] = X[1] = X[2] = 0; }
  vec3(vtype x, vtype y, vtype z) { X[0] = x; X[1] = y; X[2] = z; }
  /* 3D cross product */
  vec3 operator*(const vec3& v) const {
    return vec3(X[1] * v.X[2] - X[2] * v.X[1],
                X[2] * v.X[0] - X[0] * v.X[2],
                X[0] * v.X[1] - X[1] * v.X[0]);
  }
  vec3 operator-(const vec3& v) const {
    return vec3(X[0] - v.X[0], X[1] - v.X[1], X[2] - v.X[2]);
  }
  vec3 operator-() const {return vec3(-X[0], -X[1], -X[2]);}
  vtype dot(const vec3& v) const {
      return X[0] * v.X[0] + X[1] * v.X[1] + X[2] * v.X[2];
  }
  vtype X[3];
};

/* Original points in the input. */
vec3 A[MAXN];
/* E[i][j] indicates which (up to two) other points combine with the edge i and j
to make a face in the hull.  Only defined when i < j. */
struct twoset {
  void insert(int x) { (a == -1 ? a : b) = x; }
  bool contains(int x) { return a == x || b == x; }
  void erase(int x) { (a == x ? a : b) = -1; }
  int size() { return (a != -1) + (b != -1); }
  int a, b;
} E[MAXN][MAXN];

struct face {
  vec3 norm;
  vtype disc;
  int I[3];
};
/* Compute the half plane {x : c^T norm < disc}
 * defined by the three points A[i], A[j], A[k] where
 * A[inside_i] is considered to be on the 'interior' side of the face. */
face make_face(int i, int j, int k, int inside_i) {
  E[i][j].insert(k); E[i][k].insert(j); E[j][k].insert(i);
  face f;
  f.I[0] = i; f.I[1] = j; f.I[2] = k;
  f.norm = (A[j] - A[i]) * (A[k] - A[i]);
  f.disc = f.norm.dot(A[i]);
  if(f.norm.dot(A[inside_i]) > f.disc) {
    f.norm = -f.norm;
    f.disc = -f.disc;
  }
  return f;
}

vector<face> getFaces( int N ) {
    /* Initially construct the hull as containing only the first four points. */
    face f;
    vector<face> faces;
    memset(E, -1, sizeof(E));
    for(int i = 0; i < 4; i++)
    for(int j = i + 1; j < 4; j++)
    for(int k = j + 1; k < 4; k++) {
      faces.push_back(make_face(i, j, k, 6 - i - j - k));
    }

    /* Now add a point into the hull one at a time. */
    for(int i = 4; i < N; i++) {
      /* Find and delete all faces with their outside 'illuminated' by this
       * point. */
      for(int j = 0; j < faces.size(); j++) {
        f = faces[j];
        if(f.norm.dot(A[i]) > f.disc) {
          for(int a = 0; a < 3; a++) for(int b = a + 1; b < 3; b++) {
            int c = 3 - a - b;
            E[f.I[a]][f.I[b]].erase(f.I[c]);
          }
          faces[j--] = faces.back();
          faces.resize(faces.size() - 1);
        }
      }
      /* Now for any edge still in the hull that is only part of one face
       * add another face contaning the new point and that edge to the hull. */
      int nfaces = faces.size();
      for(int j = 0; j < nfaces; j++) {
        f = faces[j];
        for(int a = 0; a < 3; a++) for(int b = a + 1; b < 3; b++) {
          int c = 3 - a - b;
          if(E[f.I[a]][f.I[b]].size() == 2) continue;
          faces.push_back(make_face(f.I[a], f.I[b], i, f.I[c]));
        }
      }
    }
    return faces;
}
/**
int main() {
  int N;
  for(cin >> N; N; cin >> N) {
    for(int i = 0; i < N; i++) {
      cin >> A[i].X[0] >> A[i].X[1] >> A[i].X[2];
    }

    vector<face> faces = getFaces( N ) ; // get the convex hull
    //Answer each of the queries.  Compute the minimum distance of each query
    //point to each face of the apple.
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
      vec3 v; cin >> v.X[0] >> v.X[1] >> v.X[2];

      double dist = 1e300;
      for(int i = 0; i < faces.size(); i++) {
        vtype d = faces[i].disc - faces[i].norm.dot(v);
        dist = min(dist, 1. * d / sqrt(faces[i].norm.dot(faces[i].norm)));
      }
      printf("%.4f\n", dist);
    }
  }
}
**/

/** Closest Pair **/
#define px second
#define py first
typedef pair<long long, long long> pairll;
int n;
pairll pnts [100000];
set<pairll> box;
double best;
int compx(pairll a, pairll b){
    return a.px<b.px;
}

double getClosestPair(  ) {
    sort(pnts, pnts+n, compx);
    best = 1500000000; // INF
    box.insert(pnts[0]);
    int left = 0;
    for (int i=1; i<n; ++i){
        while (left<i && pnts[i].px-pnts[left].px > best) box.erase(pnts[left++]);
        for (typeof(box.begin())
                it=box.lower_bound(make_pair(pnts[i].py-best, pnts[i].px-best)); it!=box.end() &&
                pnts[i].py+best>=it->py; it++){
            best = min(best, sqrt(pow(pnts[i].py- it->py, 2.0)+pow(pnts[i].px - it->px, 2.0)));
        }
        box.insert(pnts[i]);
        printf("%.2f\n", best);
    }
}

/**
int main (){
    scanf("%d", &n);
    for (int i=0; i<n; ++i)
        scanf("%lld %lld", &pnts[i].px, &pnts[i].py);

    double res = getClosestPair();
    return 0;
}
**/

/** Area of Union of Triangles **/
struct segment {int x1, y1, x2, y2;};
//struct point {double x, y;};
struct item { double y1, y2;int triangle_id;};
//struct line {int a, b, c;};
//const double EPS = 1E-7;
void intersect (segment s1, segment s2, vector<point> & res) {
	line l1 ( s1.y1-s1.y2, s1.x2-s1.x1, l1.a*s1.x1+l1.b*s1.y1 ),
		l2 ( s2.y1-s2.y2, s2.x2-s2.x1, l2.a*s2.x1+l2.b*s2.y1 );
	double det1 = l1.a * l2.b - l1.b * l2.a;
	if (abs (det1) < EPS)  return;
	point p ( (l1.c * 1.0 * l2.b - l1.b * 1.0 * l2.c) / det1,
		(l1.a * 1.0 * l2.c - l1.c * 1.0 * l2.a) / det1 );
	if (p.x >= s1.x1-EPS && p.x <= s1.x2+EPS && p.x >= s2.x1-EPS && p.x <= s2.x2+EPS)
		res.push_back (p);
}
double segment_y (segment s, double x) {
	return s.y1 + (s.y2 - s.y1) * (x - s.x1) / (s.x2 - s.x1);
}
bool eq (double a, double b) {return abs (a-b) < EPS;}
vector<item> c;
bool cmp_y1_y2 (int i, int j) {
	const item & a = c[i];
	const item & b = c[j];
	return a.y1 < b.y1-EPS || abs (a.y1-b.y1) < EPS && a.y2 < b.y2-EPS;
}
vector<segment> a (n*3);
double getUnionArea() {
    for (size_t i=0; i<a.size(); ++i) if (a[i].x1 > a[i].x2)
			swap (a[i].x1, a[i].x2),  swap (a[i].y1, a[i].y2);
	vector<point> b; b.reserve (n*n*3);
	for (size_t i=0; i<a.size(); ++i) for (size_t j=i+1; j<a.size(); ++j)
			intersect (a[i], a[j], b);
	vector<double> xs (b.size());
	for (size_t i=0; i<b.size(); ++i) xs[i] = b[i].x;
	sort (xs.begin(), xs.end());
	xs.erase (unique (xs.begin(), xs.end(), &eq), xs.end());
	double res = 0;
	vector<char> used (n); vector<int> cc (n*3); c.resize (n*3);
	for (size_t i=0; i+1<xs.size(); ++i) {
		double x1 = xs[i],  x2 = xs[i+1];
		size_t csz = 0;
		for (size_t j=0; j<a.size(); ++j) if (a[j].x1 != a[j].x2)
				if (a[j].x1 <= x1+EPS && a[j].x2 >= x2-EPS) {
					item it = { segment_y (a[j], x1), segment_y (a[j], x2), (int)j/3 };
					cc[csz] = (int)csz; c[csz++] = it;
				}
		sort (cc.begin(), cc.begin()+csz, &cmp_y1_y2);
		double add_res = 0;
		for (size_t j=0; j<csz; ) {
			item lower = c[cc[j++]];
            used[lower.triangle_id] = true; int cnt = 1;
			while (cnt && j<csz) {
				char & cur = used[c[cc[j++]].triangle_id]; cur = !cur;
				if (cur)  ++cnt;  else  --cnt;
			}
			item upper = c[cc[j-1]];
			add_res += upper.y1 - lower.y1 + upper.y2 - lower.y2;
		} res += add_res * (x2 - x1) / 2;
	}
//	cout.precision (8); cout << fixed << res;
    return res;
}

void addTriangle( int i, int x1, int y1, int x2, int y2, int x3, int y3 ) {
    segment s1 = { x1,y1,x2,y2 }; segment s2 = { x1,y1,x3,y3 };
    segment s3 = { x2,y2,x3,y3 };
    a[i*3] = s1; a[i*3+1] = s2; a[i*3+2] = s3;
}

/**
int main() {
	int n;cin >> n;
    a.clear();
	for (int i=0; i<n; ++i) {
		int x1, y1, x2, y2, x3, y3;
		scanf ("%d%d%d%d%d%d", &x1,&y1,&x2,&y2,&x3,&y3);
        addTriangle( i, x1,y1,x2,y2,x3,y3 );
	}
    double area = getUnionArea();
}
**/

/** UNION OF RECTANGLES **/

inline int cmp(double x, double y){
    if (x < y-EPS) return -1;
    else if (x > y+EPS) return +1;
    else return 0;
}
bool cmp_eq(double x, double y){
    return cmp(x,y) == 0;
}
bool cmp_lt(double x, double y){
    return cmp(x,y) < 0;
}

struct segtree {
    int B, E, C;
    segtree *L, *R;
    double len;
    int a, lbd, rbd;
    segtree(int b, int e): B(b), E(e), len(0), C(0), a(0), lbd(0), rbd(0) {
    if (E - B > 1) {
        int M = (B + E) / 2;
        L = new segtree(B, M);
        R = new segtree(M, E);
    } else if (E - B == 1) {
        L = new segtree(B, B);
        R = new segtree(E, E);
    } else L = R = NULL;
}

    ~segtree() { delete L; delete R; }

    void insert(int b, int e) {
        if (e <= B || E <= b || B == E) return;
        if (b <= B && E <= e) C++;
        else { L->insert(b, e); R->insert(b, e); }
        update();
    }

    void erase(int b, int e) {
        if (e <= B || E <= b || B == E) return;
        if (b <= B && E <= e) C--;
        else { L->erase(b, e); R->erase(b, e); }
        update();
    }
    void update();
};

struct rect {
    double x1, y1, x2, y2;
    rect(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0):
    x1(x1), y1(y1), x2(x2), y2(y2) {}
};

const int TAM = 110;
double y[2 * TAM];

void segtree::update() {
    if (C) {
        len = y[E] - y[B];
        a = 2;
        lbd = rbd = 1;
    } else {
        len = L->len + R->len;
        a = L->a + R->a - 2 * L->rbd * R->rbd;
        lbd = L->lbd; rbd = R->rbd;
    }
}

double union_area(vector<rect>& R) {
    int n = R.size(); if (n == 0) return 0;
    vector< pair<double, int> > E;
    int m = 0;
    for (int i = 0; i < n; i++) {
        E.push_back(make_pair(R[i].x1, i));
        E.push_back(make_pair(R[i].x2, ~i));
        y[m++] = R[i].y1;
        y[m++] = R[i].y2;
    }
    sort( E.begin(), E.end() ); sort(y, y + m); m = unique(y, y + m, cmp_eq) - y;
    double last = E[0].first, r = 0;
    segtree T(0, m-1);
    for (int i = 0; i < E.size(); i++) {
        int k = E[i].second; bool in = (k >= 0); if (!in) k = ~k;
        double dx = E[i].first - last, dy = T.len;
        r += dx * dy;
        int a = lower_bound(y, y + m, R[k].y1, cmp_lt) - y;
        int b = lower_bound(y, y + m, R[k].y2, cmp_lt) - y;
        if (in) T.insert(a, b);
        else T.erase(a, b);
        last += dx;
    }
    return r;
}

double union_perimeter(vector<rect>& R) {
    int n = R.size(); if (n == 0) return 0;
    vector< pair<double, int> > E;
    int m = 0;
    for (int i = 0; i < n; i++) {
        E.push_back(make_pair(R[i].x1, i));
        E.push_back(make_pair(R[i].x2, ~i));
        y[m++] = R[i].y1;
        y[m++] = R[i].y2;
    }
    sort( E.begin() , E.end() ); sort(y, y + m); m = unique(y, y + m, cmp_eq) - y;
    double last = E[0].first, r = 0, dy = 0;
    segtree T(0, m-1);
    for (int i = 0; i < 2*n; i++) {
        int k = E[i].second; bool in = (k >= 0); if (!in) k = ~k;
        double dx = E[i].first - last;
        r += dx * T.a;
        int a = lower_bound(y, y + m, R[k].y1, cmp_lt) - y;
        int b = lower_bound(y, y + m, R[k].y2, cmp_lt) - y;
        if (in) T.insert(a, b);
        else T.erase(a, b);
        r += fabs(dy - T.len);
        dy = T.len;
        last += dx;
    }
    return r;
}

/** Area of Union of Circles **/
/**
struct Point
{
    double x,y;
    Point(double a=0.0,double b=0.0){x=a;y=b;}
    Point operator+(const Point&a)const{return Point(x+a.x,y+a.y);}
    Point operator-(const Point&a)const{return Point(x-a.x,y-a.y);}
    Point operator*(const double&a)const{return Point(x*a,y*a);}
    Point operator/(const double&a)const{return Point(x/a,y/a);}
    double operator*(const Point&a)const{return x*a.y-y*a.x;}
    double operator/(const Point&a)const{return sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y));}
    double operator%(const Point&a)const{return x*a.x+y*a.y;}
}po[1005];

double r[1005];
const double eps = 1e-7;
const double pi=acos(-1.0);
inline int sgn(double x)
{return fabs(x)<eps?0:(x>0.0?1:-1);}

pair<double,bool>arg[2005];
double cir_union(Point c[],double r[],int n)
{
    double sum=0.0,sum1=0.0,d,p1,p2,p3;
    for(int i=0;i<n;i++)
    {
        bool f=1;
        for(int j=0;f&&j<n;j++)
            if(i!=j&&sgn(r[j]-r[i]-c[i]/c[j])!=-1)f=0;
        if(!f)swap(r[i],r[--n]),swap(c[i--],c[n]);
    }
    for(int i=0;i<n;i++)
    {
        int k=0,cnt=0;
        for(int j=0;j<n;j++)
            if(i!=j&&sgn((d=c[i]/c[j])-r[i]-r[j])<=0)
            {
                p3=acos((r[i]*r[i]+d*d-r[j]*r[j])/(2.0*r[i]*d));
                p2=atan2(c[j].y-c[i].y,c[j].x-c[i].x);
                p1=p2-p3;p2=p2+p3;
                if(sgn(p1+pi)==-1)p1+=2*pi,cnt++;
                if(sgn(p2-pi)==1)p2-=2*pi,cnt++;
                arg[k++]=make_pair(p1,0);arg[k++]=make_pair(p2,1);
            }
        if(k)
        {
            sort(arg,arg+k);
            p1=arg[k-1].first-2*pi;
            p3=r[i]*r[i];
            for(int j=0;j<k;j++)
            {
                p2=arg[j].first;
                if(cnt==0)
                {
                    sum+=(p2-p1-sin(p2-p1))*p3;
                    sum1+=(c[i]+Point(cos(p1),sin(p1))*r[i])*(c[i]+Point(cos(p2),sin(p2))*r[i]);
                }
                p1=p2;
                arg[j].second?cnt--:cnt++;
            }
        }
        else sum+=2*pi*r[i]*r[i];
    }
    return (sum+fabs(sum1))*0.5;
}

int main() {
//    freopen( "input.txt", "r", stdin );
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%lf%lf%lf",&po[i].x,&po[i].y,r+i);
    printf("%.3f\n",cir_union(po,r,n));
    return 0;
}
**/

int main() {

    return 0;
}
