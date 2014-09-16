#include<bits/stdc++.h>
using namespace std;

typedef long double vtype;

const vtype EPS = 1e-10;
const vtype PI = acos(-1);

struct point {
    vtype x, y;
    point() { x =0.0, y = 0.0; }
    point( vtype _x, vtype _y ) : x(_x) , y(_y){}

    bool operator < (point other) const {
        if( fabs(x-other.x) > EPS )
            return x < other.x;
        return y < other.y;
    }

    bool operator == (point other) const{
        return ( fabs(x-other.x) < EPS && fabs((y-other.y)) < EPS );
    }
};

vtype norm( vtype x, vtype y ) {
    vtype ret = x * x + y * y;
    return sqrt( ret );
}

struct circle {
    point o;
    vtype r;

    circle(const point o, vtype r): o(o), r(r) {}

    circle(const point a, const point b) {
            o = point( a.x + b.x , a.y + b.y );
            o.x *= 0.5, o.y *= 0.5;
            r = 0.5 * norm(a.x-b.x,a.y-b.y);
        }

    bool contains(const point &p) const{
        return norm( p.x-o.x, p.y-o.y ) < r + EPS;
    }
};

vtype dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }

bool operator ==(const circle &a, const circle &b){
    return a.o == b.o && a.r == b.r;
}

vtype norm_sq( vtype x , vtype y ) {
    return x * x  + y  * y;
}

point project( point from, point a, point b) {
    point p = from;
    point k ( b.x - a.x, b.y - a.y );
    vtype nrm = norm_sq( a.x - b.x, a.y - b.y );
    vtype dt = dot( point(p.x-a.x,p.y-a.y), point(b.x-a.x,b.y-a.y) );
    vtype dtbnrm = dt / nrm;
    k.x *= dtbnrm;
    k.y *= dtbnrm;
    return point( a.x + k.x , a.y + k.y );
}

vtype det(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}

vtype point_to(point &from , point &a, point &b) {
    point p = from;
    return fabs(det( point(p.x-a.x,p.y-a.y) , point(p.x-b.x,p.y-b.y) ) / norm(a.x-b.x,a.y-b.y) );
}

point intersect_cir_line( circle &c, point &a, point &b) {
    vtype x = sqrt(c.r*c.r - point_to(c.o,a,b) * point_to(c.o,a,b) );
    vtype normalizer = norm ( a.x - b.x , a.y - b.y );
    point ret ( (a.x - b.x)/normalizer , (a.y - b.y)/normalizer );
    ret.x *= x;
    ret.y *= x;
    point prj = project( c.o , a, b );
    return point( ret.x + prj.x , ret.y + prj.y );
}

vtype angle(const point &a, const point &b) { return atan2(det(a, b), dot(a, b)); }

vtype intersect(circle c, point a, point b){
    a.x -= c.o.x, a.y -= c.o.y;
    b.x -= c.o.x , b.y -= c.o.y;
    c.o = point();
    if (c.contains(b)) swap(a, b);
    if (c.contains(a) && c.contains(b)) {
//        cout << "section " << 1 << endl;
        return 0.5 * fabs(det(a, b)); // 1. the area of the triangle
    }
    if (c.contains(a)) {
//        cout << "section " << 2 << endl;
        point p = intersect_cir_line(c, b, a);
        cout << "1 pt " << p.x << " " << p.y << endl;
        return 0.5 * ( fabs(det(a, p)) + fabs( c.r*c.r * angle(p, b) ) ); // 2. one point inside
    }
    if ( point_to(c.o,a, b) >= c.r - EPS){
//        cout << "section " << 3 << endl;
        return 0.5 * fabs(c.r*c.r * angle(a, b)); // 3. Both outside and line doesnt intersect
    }
    // 4. Both Outside & Line Intersects circle at 2 points
    point p = intersect_cir_line(c, a, b);
    point q = intersect_cir_line(c, b, a);
    cout << "2 pts " << " (" << p.x << " " <<p.y << ") (" << q.x << " " << q.y <<")"<< endl;
//    cout << p.x << " " << p.y << " " << q.x << " " << q.y << endl;
//    cout << withA.x << " " << withA.y << " " << withB.x << " " << withB.y << endl;
//    cout << "section " << 4 << " " << p.x << " " << p.y << " " << q.x << " " << q.y << endl;
//    cout << angle(p,q) << endl;
    return 0.5 * ( fabs(c.r*c.r*angle(a,p)) + fabs( det(p,q) ) + fabs(c.r*c.r*angle(q,b)) ); // seems fine
//    return 0;
//    return 0.5 * (fabs(det(a, p)) + fabs(c.r*c.r * angle(p, q)) + fabs(det(q, b)));
}

vector<point> monster;

vtype calculateArea( vtype r ) {
    circle c( point(0,0) , r );
    int sz = (int)monster.size();
    vtype ret = 0.0;
    for( int i=0 ; i < monster.size(); i++ ) {
        ret += intersect( c, monster[i] , monster[ (i + 1 ) % sz ] );
    }
    return ret;
}

int main () {
//    vtype chk = intersect ( circle( point(0,0) , 5.0 ) , point(10,10) , point(-10,10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,10) , point(-10,-10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,-10) , point(10,-10) );
//    chk += intersect ( circle( point(0,0) , 5.0 ) , point(-10,10) , point(10,10) );
//    cout << chk << endl;

//    vtype chk = intersect ( circle( point(0,0) , 5.0 ) , point(6,0) , point(0,6) );
//    cout << chk << endl;

//    point k = project( point(5,5), point(2,2), point(7,3) );
//    cout << k.x << " " << k.y <<endl;

//    double x = 1256962.12;
//    printf( "%lf\n" , acos(-1) * x * x );
    //4963571160346.043000

//    double y = 1880631.95;
//    printf( "%lf\n" , acos(-1) * y * y );
    //11111111168311.887000

    // R = 11111111111111;

    int n;
    int kase = 1;
    while( cin >> n ) {
        if( n == 0 ) break;
        vtype R;
        cin >> R;
        monster.clear();
        for( int i=0 ; i < n; i++ ) {
            vtype x, y;
//            scanf( "%lf %lf", &x, &y );
            cin >> x >> y;
            monster.push_back( point(x,y) );
        }

        vtype l = 0.0 , r = 1e10;
        while( fabs(r - l) > EPS ) {
            vtype mid = ( l + r ) / 2.0;
            vtype AR = calculateArea( mid );
            cout << "when radius is " << mid << " area is " << AR << endl;
            if( AR >= R ) {
                r = mid;
            } else l = mid;
        }
        vtype res = (l+r) / 2.0;
//        printf( "Case %d: %.2lf\n" , kase++, res );
        cout << "Case " << kase++ << ": " << fixed << setprecision(2) << res << "\n";
    }


    return 0;
}

/*

5 3423.64
-45982 -45982
46000 -50000
90000 80456
0 100000
-67986 45687

5 3874537587245.12
-459824726572 -459824726572
460004726572 -500004726572
900004726572 804564726572
0 1000004726572
-679864726572 456874726572

*****

7 11111111111111
-23984837342 2193824857342
0 81273857128342
387342 943894342
582342 334877342
19827342 -2138757342
0 -78437878217342
-1238783274342 -1238782342

// 1880631.95

*****

7 355252
-239 219
0 500
382 435
565 334
198 -213
0 -784
-123 -123

4 5000
-20 100
20 100
20 -100
-20 -100

6 8000
0 100
50 50
60 0
60 -50
40 -100
-50 90

3 2000
-100 0
0 100
100 0

3 0
5 15
10 10
15 5


3 0
-1 -1
1 -1
0 1
0

4 150
10 0
0 10
-10 0
0 -10

*/
