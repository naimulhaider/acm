#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

double sectorArea( double r, double theta ) {
    return (r * r * theta) / 2.0;
}

double cosineAngle( double a, double b, double c ) {
    return acos( (b*b + c * c - a*a) / (2 * b * c) );
}

double heron( double sa, double sb, double sc ) {
    double s = 0.5 * (sa + sb + sc);
    double ret = s * (s-sa) * (s-sb) * (s-sc);
    return sqrt( ret );
}

int main() {

    int T;
    scanf( "%d", &T );
    int kase = 1;
    while( T-- ) {
        double c1x, c1y, r1, c2x, c2y, r2;
        scanf( "%lf%lf%lf%lf%lf%lf", &c1x,&c1y,&r1,&c2x,&c2y,&r2 );
        if( r1 < r2 ) {
            swap( c1x , c2x );
            swap( c1y , c2y );
            swap( r1 , r2 );
        }
        double dist = hypot( c1x-c2x, c1y-c2y );
        if( (r1+r2 < dist) || fabs(r1+r2-dist) < EPS ) {
            printf( "Case %d: %.8lf\n", kase++, 0.0 );
            continue;
        }

        if( dist + r2 < r1 || fabs( dist+r2-r1 ) < EPS ) {
            printf( "Case %d: %.8lf\n", kase++, acos(-1) * r2 * r2 );
            continue;
        }

        double theta1 = 2 * cosineAngle( r2, dist, r1 );
        double theta2 = 2 * cosineAngle( r1, dist, r2 );
        double area1 = 0.5 * r1 * r1 * theta1;
        area1 -= ( 0.5 * r1 * r1 * sin(theta1) );
        double area2 = 0.5 * r2 * r2 * theta2;
        area2 -= ( 0.5 * r2 * r2 * sin(theta2) );
        printf( "Case %d: %.8lf\n", kase++, area1 + area2 );
    }

    return 0;
}
