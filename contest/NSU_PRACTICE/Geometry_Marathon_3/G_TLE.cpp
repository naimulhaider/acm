#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double PI = acos(-1);

double sqr(double x) {
return x * x;}

const double EPSILON = 1e-9;
int signum(double x)
{
    return x < -EPSILON? -1: x
           > EPSILON;
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
    double arg() const
    {
        return atan2(y, x);
    }
};

bool operator ==(const Point &a, const Point &b)
{
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
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
    return
        a.x * b.y - b.x * a.y;
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

Point circumcenter(Point a, Point b, Point c)
{
    b -= a, c -= a;
    double d = 2.0 * det(b, c);
    Point p = Point(b.norm2(), c.norm2());
    return a + Point(det(p, Point(b.y, c.y)),
                     det(Point(b.x, c.x), p)) / d;
}

struct Circle
{
    Point o;
    double r;
    Circle(){}
    Circle(const Point &o, double r): o(o), r(r)
    {}
    Circle(const Point &a, const Point &b): o(0.5
                * (a + b)), r(0.5 * (a - b).norm()) {}
    Circle(const Point &a, const Point &b, const
           Point &c): o(circumcenter(a, b, c))
    {
        r = ((a - o).norm() + (b - o).norm() + (c - o).norm()) / 3.0;
    }
    bool contains(const Point &p) const
    {
        return (p - o).norm() < r + EPSILON;
    }
};
bool operator ==(const Circle &a, const Circle &b)
{
    return (a.o == b.o) && (a.r == b.r);
}

Point intersect(const Circle &a, const Circle &b)
{
    Point r = (b. o - a.o).normalize();
    double d = (b.o - a.o).norm();
    double x = 0.5 * ((sqr(a.r) - sqr(b.r)) / d +
                      d);
    double h = sqrt(sqr(a.r) - sqr(x));
    return a.o + r * x + r.rotate() * h;
}


double* count(Circle circles[], int n)
{
    double* result = new double[n + 1];
    memset(result, 0, sizeof(result));
#define ADD(k, v) events.push_back(make_pair(k, v))
#define ADD_PAIR(a, b) ADD(a, 1), ADD(b, -1)
    for (int i = 0; i < n; ++ i)
    {
        Circle &a = circles[i];
        vector <pair <double, int> > events;
        ADD(-PI, 0), ADD(PI, 0);
        for (int j = 0; j < n; ++ j)
        {
            if (i != j)
            {
                Circle &b = circles[j];
                if (a == b)
                {
                    if (i < j)
                    {
                        ADD_PAIR(-PI, PI);
                    }
                }
                else
                {
                    double d = (a.o - b.o).norm();
                    if (signum(a.r - b.r) < 0 && signum(d - (b.r - a.r)) <= 0)
                    {
                        ADD_PAIR(-PI, PI);
                    }
                    else if (signum(d - (a.r + b.r)) < 0)
                    {
                        double x = intersect(b, a).arg();
                        double y = intersect(a, b).arg();
                        if (signum(x - y) <= 0)
                        {
                            ADD_PAIR(x, y);
                        }
                        else
                        {
                            ADD_PAIR(x, PI);
                            ADD_PAIR(-PI, y);
                        }
                    }
                }
            }
        }
        sort(events.begin(), events.end());
        int counter = events.front().second;
#define RADIUS(a, r) (Point(cos(a), sin(a)) * (r))
        for (int j = 1; j < (int)events.size(); ++ j)
        {
            double delta = events[j].first - events[j - 1].first;
            result[counter] += 0.5 * sqr(a.r) * (delta - sin(delta));
            Point p = a.o + RADIUS(events[j - 1].first, a.r);
            Point q = a.o + RADIUS(events[j].first, a.r);
            result[counter] += 0.5 * det(p, q);
            counter += events[j].second;
        }
    }
    return result;
}

Circle circs[2000];

int main ()
{

    freopen( "input.txt", "r", stdin );

    int n;
    scanf( "%d", &n);

    for( int i=0; i < n; i++ )
    {
        double x, y, r;
        scanf("%lf %lf %lf", &x, &y, &r);
        circs[i] = Circle( Point(x,y), r);
    }

    double* res = count( circs, n );
    printf( "%.3lf\n" , res[0] );

    return 0;
}
