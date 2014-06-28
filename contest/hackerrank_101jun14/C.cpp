/*

Hacker rank 101 hack june 14
UNSOLVED!!!

*/

#include<bits/stdc++.h>
using namespace std;

#define M 100005
typedef long long LL;
const int MOD = 1000000007;

LL a[M];
LL oddsum[M], evensum[M], sum[M];

LL xorsum( int l, int r ) {
    return sum[r] ^ sum[l - 1];
}

LL getoddsum( int l , int r ) {
    return oddsum[r] ^ oddsum[l - 1];
}

LL getevensum( int l , int r ) {
    return evensum[r] ^ evensum[l - 1];
}

int main() {

    freopen( "input.in" , "r", stdin );

    int n;
    scanf( "%d", &n );

    memset( oddsum, 0 , sizeof oddsum );
    memset( evensum, 0 , sizeof evensum );
    memset( sum, 0 , sizeof sum );

    for( int i=1 ; i <= n; i++ ) {
        scanf( "%d", &a[i] );
    }

    LL cursum = 0;
    for( int i=1 ; i <=n; i++  ) {
        cursum ^= a[i];
        sum[i] = cursum;
        if( sum[i] > MOD ) sum[i] %= MOD;
    }

    cursum = 0;
    for( int i= 1;  i <=n ; i++ ) {
        if( i % 2 != 0 ) {
            cursum ^= a[i];
        }
        oddsum[i] = cursum;
        if( oddsum[i] > MOD ) oddsum[i] %= MOD;
    }

    cursum = 0;
    for( int i=1;  i <=n ; i++ ) {
        if( i % 2 == 0 ) {
            cursum ^= a[i];
        }
        evensum[i] = cursum;
        if( evensum[i] > MOD ) evensum[i] %= MOD;
    }

    int m;
    scanf( "%d", &m );

    for( int i=0 ; i < m; i++ ) {

        int k, p, r;
        scanf( "%d %d %d", &k, &p, &r );
        long long res = 0;
        res ^= k;
        res ^= xorsum( p, r-1 );
        int len = (r - p + 1);
//        if( len % 2 && r%2==0 ) {
//            res ^= getoddsum( p+1, r );
//        } else if( len%2==0 && r%2==0 ) {
//            res ^= getoddsum( p+1, r );
//        } else {
//            res ^= getevensum( p+1, r );
//        }
        res ^= getevensum( p+1, r );
        printf( "%d\n", res );
    }

    return 0;
}
