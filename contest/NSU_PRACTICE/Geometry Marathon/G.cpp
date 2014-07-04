#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

double heron( double sa, double sb, double sc ) {
    double s = 0.5 * (sa + sb + sc);
    double ret = s * (s-sa) * (s-sb) * (s-sc);
    return sqrt( ret );
}

double my_round(double x) {
    return floor(x * 1000 + 0.5) / 1000;
}

int main () {

    double a, b, c;
    while( scanf("%lf%lf%lf",&a,&b,&c) == 3 ){
        double area;
        if( a < EPS || b < EPS || c < EPS ) {
            printf( "The radius of the round table is: %.3lf\n", 0.0 );
            continue;
        }
        area = heron( a, b, c );
        printf( "The radius of the round table is: %.3lf\n", my_round( 2.0 * area / (a+b+c) ) );

    }

    return 0;
}
