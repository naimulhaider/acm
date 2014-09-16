#include<bits/stdc++.h>
using namespace std;

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
        double a, b, c, d;
        scanf( "%lf %lf %lf %lf", &a, &b, &c, &d );
        if( c < a ) swap( a ,c );
        double k = c-a ;
        double h = heron( d, b, k ) / (0.5 * k);
        double res = ( (a + c) / 2.0 ) * h;
        printf( "Case %d: %.8lf\n", kase++ , res );
    }

    return 0;
}
