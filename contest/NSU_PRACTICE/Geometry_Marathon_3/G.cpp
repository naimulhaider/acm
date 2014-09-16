#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double PI = acos(-1);

struct point {
    double x, y;
    point() { x =0.0, y = 0.0; }
    point( double _x, double _y ) : x(_x) , y(_y){}

    bool operator < (const point& other) const {
        if( fabs(x-other.x) > EPS )
            return x < other.x;
        return y < other.y;
    }

    bool operator == (const point& other) const{
        return ( fabs(x-other.x) < EPS && fabs((y-other.y)) < EPS );
    }
};

double norm_sq( const double& x , const double& y ) {
    return x * x  + y  * y;
}

double norm( const double& x, const double& y ) {
    double ret = x * x + y * y;
    return sqrt( ret );
}

double det(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}

struct circle {
    point o;
    double r;
    circle(){}
    circle(const point o, double r): o(o), r(r) {}
};

bool operator ==(const circle &a, const circle &b){
    return a.o == b.o && a.r == b.r;
}

int signum(const double& x) { return x < -EPS? -1: x > EPS; }

point intersect(const circle &a, const circle &b){
    point r = point (b.o.x - a.o.x, b.o.y-a.o.y);
    double normalizer = norm ( r.x , r.y );
    r.x /= normalizer , r.y /= normalizer;
    double d = norm (b.o.x - a.o.x, b.o.y - a.o.y);
    double x = 0.5 * ((a.r*a.r - b.r*b.r) / d + d);
    double h = sqrt(a.r*a.r - x*x);
    point ret = point( a.o.x , a.o.y );
    ret.x += ( r.x * x );
    ret.y += ( r.y * x );
    ret.x += ( -r.y * h );
    ret.y += ( r.x * h );
    ret;
}

circle circles[2000];
double result[2000];
pair< double , int > events[5000];
int ecnt;

void countArea( int n ) {
    for (int i = 0; i < n; ++i) {
        circle &a = circles[i];
        ecnt = 0;
        events[ecnt++] = make_pair(-PI, 0);
        events[ecnt++] = make_pair(PI, 0);
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                circle &b = circles[j];
                if (a == b) {
                    if (i < j) {
                        events[ecnt++] = make_pair(-PI, 1);
                        events[ecnt++] = make_pair(PI, -1);
                    }
                } else {
                    double d = norm( a.o.x - b.o.x , a.o.y - b.o.y );
                    if (signum(a.r - b.r) < 0 && signum(d - (b.r - a.r)) <= 0) {
                        events[ecnt++] = make_pair(-PI, 1);
                        events[ecnt++] = make_pair(PI, -1);
                    } else if (signum(d - (a.r + b.r)) < 0) {
                        point ints1 = intersect(b, a);
                        point ints2 = intersect(a, b);
                        double x = atan2( ints1.y, ints1.x );
                        double y = atan2( ints2.y, ints2.x );
                        if (signum(x - y) <= 0) {
                            events[ecnt++] = make_pair(x, 1);
                            events[ecnt++] = make_pair(y, -1);
                        } else {
                            events[ecnt++] = make_pair(x, 1);
                            events[ecnt++] = make_pair(PI, -1);
                            events[ecnt++] = make_pair(-PI, 1);
                            events[ecnt++] = make_pair(y, -1);
                        }
                    }
                }
            }
        }
        sort( events, events + ecnt );
        int counter = events[0].second;
        for (int j = 1; j < ecnt; ++j) {
            double delta = events[j].first - events[j - 1].first;
            result[counter] += 0.5 * a.r * a.r * (delta - sin(delta));
            point k1 = (point(cos(events[j - 1].first)*a.r, sin(events[j - 1].first)*a.r) );
            point k2 = (point(cos(events[j].first)*a.r, sin(events[j].first)*a.r) );

            point p = point( a.o.x + k1.x , a.o.y + k1.y );
            point q = point( a.o.x + k2.x , a.o.y + k2.y );
            result[counter] += 0.5 * det(p, q);
            counter += events[j].second;
        }
    }
}

int main () {

//    freopen( "input3.txt", "r", stdin );

    int n;
    scanf( "%d", &n);

    for( int i=0; i < n; i++ ) {
        double x, y, r;
        scanf("%lf %lf %lf", &x, &y, &r);
        circles[i].o.x = x;
        circles[i].o.y = y;
        circles[i].r = r;
    }
    memset(result, 0, sizeof(result));
    countArea( n );
    printf( "%.3lf\n" , result[0] );

    return 0;
}
