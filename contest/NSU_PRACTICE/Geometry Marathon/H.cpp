#include<bits/stdc++.h>
using namespace std;

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

int main () {

    int T;
    scanf( "%d", &T );

    while( T-- ) {
        double r1, r2, r3;
        scanf( "%lf %lf %lf", &r1, &r2, &r3 );
        double sa = r2 + r3, sb = r1 + r3, sc = r1 + r2;
        double thetaA = cosineAngle( sa, sb, sc );
        double thetaB = cosineAngle( sb, sa, sc );
        double thetaC = acos(-1) - (thetaA + thetaB);
        double totSector = sectorArea( r1, thetaA );
        totSector += sectorArea( r2, thetaB );
        totSector += sectorArea( r3, thetaC );
        double triangleArea = heron( sa, sb, sc );
        double res = triangleArea - totSector;
        printf( "%.6lf\n", res );
    }

    return 0;
}
