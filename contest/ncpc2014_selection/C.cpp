#include<bits/stdc++.h>
using namespace std;

int ini[110];
int mat[110][110];
int dist[110][110];
vector<int> v[110][110];
int dp[110][110];

const int INF = 1000000007;
const int MOD = 1000000007;

int main ( ) {

//    freopen( "in.txt", "r", stdin );

    int T;
    scanf( "%d", &T );
    int kase = 1;
    while( T-- ) {

        for( int i = 0 ; i <110; i++ ) {
            for( int j=0; j<110; j++ ) {
                v[i][j].clear();
            }
        }

        int n , m, r, p;
        scanf( "%d %d %d %d", &n, &m, &r, &p );
        for( int i=0; i<n; i++ ) {
            scanf( "%d", &ini[i] );
        }

        for( int i=0; i<110; i++ ) {
            for( int j=0; j<110; j++ ) {
                dist[i][j] = INF;
            }
        }

        for( int i=0; i<m; i++ ) {
            int u, v;
            scanf( "%d %d", &u, &v );
            mat[u][v] = 1;
            dist[u][v] = 1;
            mat[v][u] = 1;
            dist[v][u] = 1;
        }

        // doing floyd
        for( int k = 0; k < n; k++ ) {
            for( int i =0; i<n; i++ ) {
                for( int j=0; j<n; j++ ) {
                    dist[i][j] = min( dist[i][j] , dist[i][k] + dist[k][j] );
                }
            }
        }

        // find nodes at kth distance from each node
        for( int j=0; j<n;j++ ) {
            for( int k = 0; k < n; k++ ) {
                if( j == k ) continue;
                if( dist[j][k] == INF ) continue;
                v[j][ dist[j][k] ].push_back( k );
            }
        }

        memset( dp, 0 , sizeof dp );
        for( int i=0; i< n; i++ ) dp[i][0] = ini[i];
        for( int i=1; i<=p; i++ ) {
            for( int j = 0; j<n; j++ ) {
                dp[j][i] = dp[j][i-1] ;
                int fd = ( (i-1) % r) + 1;
                for( int k = 0; k < v[j][fd].size(); k++ ) {
                    dp[j][i] += dp[ v[j][fd][k] ] [ i-1 ];
                    dp[j][i] %= MOD;
                }
            }
        }

        printf( "Case %d: ", kase++ );
        for( int i = 0; i < n; i++ ) {
            if( i != 0 ) printf(" ");
            printf( "%d", dp[i][p] );
        }
        printf("\n");

    }

    return 0;
}
