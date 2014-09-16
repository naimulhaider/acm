#include<bits/stdc++.h>
using namespace std;

const double EPSILON = 1e-8;
int signum(double x)
{
    return x < -EPSILON? -1: x
           > EPSILON;
}



double sqr( double x ) {
    return x * x;
}
struct Point
{
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x),
        y(y) {}
    Point &operator +=(const Point &o)
    {
        return x
               += o.x, y += o.y, *this;
    }
    Point &operator -=(const Point &o)
    {
        return x
               -= o.x, y -= o.y, *this;
    }
    Point &operator *=(double k)
    {
        return x *= k,
                    y *= k, *this;
    }
    Point &operator /=(double k)
    {
        return x /= k,
                    y /= k, *this;
    }
    Point rotate() const
    {
        return Point(-y, x);
    }
    double norm2() const;
    double norm() const;
    Point normalize() const;
    Point project(const Point &a, const Point &b) const;
    double to(const Point &a, const Point &b) const;
    double arg() const
    {
        return atan2(y, x);
    }
};
Point operator ==(const Point &a, const Point &b)
{
    return signum(a.x - b.x) == 0 && signum(a.y -
                                            b.y) == 0;
}
Point operator +(Point a, const Point &b)
{
    return
        a += b;
}
Point operator -(Point a, const Point &b)
{
    return
        a -= b;
}
Point operator *(Point a, double k)
{
    return a *=
               k;
}
Point operator *(double k, Point a)
{
    return a *=
               k;
}
Point operator /(Point a, double k)
{
    return a /=
               k;
}
double det(const Point &a, const Point &b)
{
    return a.x * b.y - b.x * a.y;
}
double dot(const Point &a, const Point &b)
{
    return
        a.x * b.x + a.y * b.y;
}
double angle(const Point &a, const Point &b)
{
    return atan2(det(a, b), dot(a, b));
}
double Point::norm2() const
{
    return dot(*this,
               *this);
}
double Point::norm() const
{
    return
        sqrt(norm2());
}
Point Point::normalize() const
{
    return *this /
           norm();
}

Point Point::project(const Point &a, const Point &b) const {
Point p = *this;
return a + dot(p - a, b - a) / (a - b).norm2() * (b - a);
}

double Point::to(const Point &a, const Point &b)
const {
    Point p = *this;
    return abs(det(p - a, p - b) / (a -
    b).norm());
}

struct Circle
{
    Point o;
    double r;
    Circle(const Point &o, double r): o(o), r(r)
    {}
    Circle(const Point &a, const Point &b): o(0.5
                * (a + b)), r(0.5 * (a - b).norm()) {}

    bool contains(const Point &p) const
    {
        return (p - o).norm() < r + EPSILON;
    }
};

Point intersect_cir_line(const Circle &c, const Point &a, const Point &b) {
    double x = sqrt(sqr(c.r) - sqr(c.o.to(a,b)));
    return c.o.project(a, b) + (a-b).normalize() * x;
}

double intersect(Circle c, Point a, Point b) {
    a -= c.o, b -= c.o, c.o = Point();
    if (c.contains(b)) { swap(a, b); }
    if (c.contains(a) && c.contains(b)) {
        return 0.5 * abs(det(a, b)); // ok
    }
    if (c.contains(a)) {
        Point p = intersect_cir_line(c, b, a);
        Point q=  intersect_cir_line( c, b, Point(0,0) );
        return 0.5 * (abs(det(a, p)) + abs(sqr(c.r) * angle(p, q)));
    }
    if (c.o.to(a, b) >= c.r - EPSILON) {
        return 0.5 * abs(sqr(c.r) * angle(a, b)); // ok
    }
    // both points are outside circle
    Point p = intersect_cir_line(c, a, b);
    Point q = intersect_cir_line(c, b, a);
//    Point withA = intersect_cir_line( c,  a , Point(0,0) );
//    Point withB = intersect_cir_line( c, b,  Point(0,0) );
    cout << p.x << " " << p.y << " " << q.x << " " << q.y << endl;
//    cout << withA.x << " " << withA.y << " " << withB.x << " " << withB.y << endl;

//    cout << angle(p,q) << endl;
    return 0.5 * ( fabs(c.r*c.r*angle(a,p)) + fabs( det(p,q) ) + fabs(c.r*c.r*angle(q,b)) );

//                return 0.5 * (abs(det(a, p))
//                + abs(sqr(c.r) * angle(p, q))
//                + abs(det(q, b)));
}

//int main() {
//
//    Point p(5,5);
//    Point k = p.project( Point(2,2) , Point(7,3) );
//    cout << k.x << " " << k.y << endl;
//
//    return 0;
//}

vector<Point> monster;

double calculateArea( double r ) {
    Circle c( Point(0.0,0.0) , r );
    int sz = (int)monster.size();
    double ret = 0.0;
    for( int i=0 ; i < sz; i++ ) {
        ret += intersect( c, monster[i] , monster[ (i + 1 ) % sz ] );
    }
    return ret;
}

double heron( double sa, double sb, double sc ) {
    double s = 0.5 * (sa + sb + sc);
    double ret = s * (s-sa) * (s-sb) * (s-sc);
    return sqrt( ret );
}

double dist( Point p1, Point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
}

int main () {


//    cout << intersect( Circle( Point(0,0) , 3 ) , Point(-5,2) , Point(5,2) ) << endl;

//
//    cout << heron( dist( Point(5,10), Point(10,5) ), dist( Point(0,0), Point(10,5) ), dist( Point(0,0), Point(5,10) ) ) << endl;
//    cout << det( Point(5,10), Point(10,5) ) / 2 << endl;

//    double chk = intersect ( circle( point(0,0) , 5.0 ) , point(10,10) , point(-10,10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,10) , point(-10,-10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,-10) , point(10,-10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,10) , point(10,10) );
//    cout << chk << endl;

//    double chk = intersect ( circle( point(0,0) , 5.0 ) , point(6,0) , point(0,6) );
//    cout << chk << endl;

//    point k = project( point(5,5), point(2,2), point(7,3) );
//    cout << k.x << " " << k.y <<endl;
//
    int n;
    int kase = 1;
    while( scanf( "%d", &n ) == 1 ) {
        if( n == 0 ) break;
        double R;
        scanf( "%lf", &R );
        monster.clear();
        for( int i=0 ; i < n; i++ ) {
            double x, y;
            scanf( "%lf %lf", &x, &y );
            monster.push_back( Point(x,y) );
        }

        double l = 0.0 , r = 100000000.0;
        while( fabs(r - l) > EPSILON ) {
            double mid = (l + r) / 2.0;
            double ar = calculateArea( mid );
//            cout << ar << endl;
            if( ar < R ) {
                l = mid;
            } else r = mid;
        }
        double res = r;
        printf( "Case %d: %.2lf\n" , kase, res);
    }

//        monster.push_back( Point(-1,-1) );
//        monster.push_back( Point(1,-1) );
//        monster.push_back( Point(0,1) );

//        cout << calculateArea( 100 ) << endl;
//        cout << calculateArea( 0.93 );

//        Circle k( Point(0,0) , 1.5 );
//        double area = intersect( k , Point(-1,-1), Point(1,-1) );
//        cout << area << endl;
//        double area2 = intersect( k , Point(0,2), Point(2,0)  );
//        area += intersect( k , Point(-1,-1), Point(1,-1) );
//        cout << area << endl;
//        cout << area2 << endl;
//
//        cout << heron( 1, sqrt(2), sqrt(5) );
//
//        Circle k( Point(0,0) , 100 );
//        double area = intersect( k , Point(0,10), Point(10,0) );
//        cout << area << endl;
//        double area2 = intersect( k , Point(0,1), Point(1,-1)  );

    return 0;
}
