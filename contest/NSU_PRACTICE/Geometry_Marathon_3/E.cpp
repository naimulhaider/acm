#include<bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
const double EPS = 1e-6;
#define MAX 2500

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

double dist( point p1, point p2 ) {
    return hypot( p1.x-p2.x, p1.y-p2.y );
}

double det(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}
double dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }
//double angle(const point &a, const point &b) { return atan2(det(a, b), dot(a, b)); }

double angle( const point&a, const point&b ) {
    point c( b.x -a.x, b.y - a.y );
    if( c.y == 0 && c.x > 0 ) return 0;
    if( c.y == 0 && c.x < 0  ) return PI;
    if( c.x ==0 && c.y > 0  ) return PI / 2;
    if( c.x == 0 && c.y < 0 ) return 6 * PI / 4;
    double ang = atan2( fabs(c.y), fabs(c.x) );
    if( c.x > 0 && c.y > 0 ) {
        return ang;
    } else if( c.x <0 && c.y > 0 ) {
        return PI - ang;
    } else if( c.x < 0 && c.y < 0 ) {
        return PI + ang;
    }
    return 2 * PI - ang;
}

double norm( double x, double y ) {
    double ret = x * x + y * y;
    return sqrt( ret );
}

double heron( double sa, double sb, double sc ) {
    double s = 0.5 * (sa + sb + sc);
    double ret = s * (s-sa) * (s-sb) * (s-sc);
    return sqrt( ret );
}

struct circle {
    point o;
    double r;

    circle(const point o, double r): o(o), r(r) {}

    circle(const point a, const point b, const double R) {
        double d = dist( a,b );
        double area = heron( d, R ,R );
        double h = (2 * area) / d;
        double mx = (a.x + b.x) / 2, my = (a.y + b.y) / 2;
        double vx = a.x - b.x , vy = a.y - b.y;
        vx /= d, vy /= d;
        vx *= h , vy *= h;
        vx *= -1;
        o.x = ( mx + vy );
        o.y = (my + vx);
        r = R;
    }

    bool contains(const point &p) const{
        return norm( p.x-o.x, p.y-o.y ) < r + EPS;
    }
};

point pts[MAX];
int N, R;

int solve(  ) {

    int ret = 1;
    pair<double, point> plist[MAX];
    for( int i=0 ; i< N; i++ ) {
        int index = 0;
        for( int j=0;  j < N; j++ ) {
            if( i == j ) continue;
            if( dist( pts[i] , pts[j] ) <= 2 * R + EPS  ) {
                plist[index++] = make_pair( angle( pts[i] , pts[j] ) , pts[j] );
            }
        }
        if( index == 0 ) continue;
        sort( plist, plist+index );

        int left = 0, right=0;
        circle c ( pts[i] , plist[0].second, R );
        int cnt = 1; // current pivot counted!
         // initialize with containing points
        for( int j=0; j < index; j++ ) {
            point k = plist[j].second;
            if( c.contains( k ) ) {
                ++cnt;
                right = j;
            }
        }
        ret = max( cnt, ret );
        left++;
        right++;
        cnt--;
        while( left < index ) {
            int cright = right;
            circle cc( pts[i] , plist[left].second , R );
            while( right < index && cc.contains( plist[right].second ) ) {
                cnt++;
                right++;
            }
            ret = max( ret, cnt );
            left++;
            cnt--;
        }
    }
    return ret;
}

int main() {

//    circle c( point(1,1) , point(5,5) , 5 );
//    cout << c.o.x << " " << c.o.y << " " << c.r << endl;
//    cout << dist( c.o , point(1,1) ) << endl;
//    cout << dist( c.o , point(5,5) ) << endl;

    while( scanf( "%d%d", &N, &R ) == 2 ) {
        if( N==0 && R==0 ) break;
        for( int i=0; i < N; i++ ) {
            int x, y;
            scanf( "%d%d",&x,&y );
            pts[i] = point(x,y) ;
        }

        if( R == 0 ) {
            printf( "It is possible to cover 0 points.\n" );
            continue;
        }

        if( N == 1 ) {
            printf( "It is possible to cover 1 points.\n" );
            continue;
        }
        int res = solve(  );
        printf( "It is possible to cover %d points.\n", res );
    }


//    cout << angle( point(3,3) , point(8,2) ) << endl;
//    cout << angle( point(3,3) , point(5,3) ) << endl;
//    cout << angle( point(3,3) , point(7,5) ) << endl;
//    cout << angle( point(3,3) , point(5,4) ) << endl;
//    cout << angle( point(3,3) , point(4,5) ) << endl;
//    cout << angle( point(3,3) , point(1,4) ) << endl;
//    cout << angle( point(3,3) , point(1,2) ) << endl;
//    cout << angle( point(3,3) , point(2,1) ) << endl;
//    cout << angle( point(3,3) , point(3,0) ) << endl;
//    cout << angle( point(3,3) , point(5,1) ) << endl;



    return 0;
}
