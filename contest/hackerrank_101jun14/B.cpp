#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
const int MOD = 1000000007;

long long a[MAX], b[MAX], c[MAX];
long long mul[MAX];

int main () {

//    freopen( "input.in" , "r", stdin );

    int n, m;
    scanf( "%d %d", &n, &m );

    for( int i=1; i <= n; i++ ) {
        scanf( "%lld", &a[i] );
    }

    for( int i=1 ; i<=m; i++ ) {
        scanf( "%lld", &b[i] );
    }

    for( int i=1 ; i<=m; i++ ) {
        scanf( "%lld", &c[i] );
    }

    for( int i=0 ; i< MAX; i++ ) mul[i] = 1;

    for( int i=1 ; i <= m; i++ ) {
        mul[ b[i] ] *= c[i];
        if( mul[ b[i] ] > MOD ) mul[ b[i] ] %= MOD;
    }

    for( int i=1 ; i <= n; i++ ) { // b[i] maximum n
        if( mul[i] > 1 ) {
            for( int j=i; j <= n ; j+=i ) {
                    a[j] *= mul[i];
                    if( a[j] > MOD ) a[j] %= MOD;
            }
        }
    }

    for( int i=1 ; i<=n; i++ ) {
        if( i != 1 ) printf( " " );
        printf( "%lld", a[i] );
    }

    return 0;
}
