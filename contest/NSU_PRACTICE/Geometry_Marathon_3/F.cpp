#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
const double EPS = 1e-6;

int n , m;
int v[MAX];

double dist ( double x, double y ) {
    return fabs( x- y );
}

int getCover ( double d ) {
    int i = 0, cnt=0;
    while( cnt < n ) {
        double curPos = v[i] + d;
        cnt++;
        while( i < m ) {
            if( dist( v[i] , curPos ) > d ){
                break;
            }
            i++;
        }
    }
    return i;
}

int main() {

    int T;
    scanf( "%d", &T );

    while( T-- ) {
        scanf( "%d %d", &n, &m );
        for( int i=0 ; i< m; i++ ) scanf( "%d", &v[i] );
        sort( v , v + m );
        double l = 0.0, r = 1000000.0;
        while( fabs(l-r) > EPS ) {
            double mid = (l + r) / 2.0;
            if( getCover(mid) == m ) {
                r = mid;
            } else l = mid;
        }
        printf( "%.1lf\n" , r );
    }

    return 0;
}

/*

4

1 2
1
5

2 2
1 5

2 4
1
3
10000
10002

1 2
1
6

*/
