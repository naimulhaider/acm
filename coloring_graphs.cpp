/*
Problem: C. Coloring Graphs NCPC 2014 Preliminary
Date: 28 May, 2014
*/

#include <bits/stdc++.h>
using namespace std;

#define M 110
const long long INF = 1000000007LL;
const long long MOD = 1000000007LL;

long long mat[M][M];
long long _mat[11][M][M];

template<int d>
class Matrix {
    public:
    long long v[d][d];
    Matrix () {
        memset( v, 0 , sizeof v );
    }

    Matrix<d> mul ( const Matrix<d>& b ) {
        Matrix<d> r;
        for( int k=0; k<d; k++ )
            for( int i=0; i<d; i++ )
                for( int j=0; j<d; j++ )
                    r.v[i][j] = ( r.v[i][j] + v[i][k] * b.v[k][j] ) % MOD;
        return r;
    }

    Matrix<d> modpow( long long p, long long m ) {
        Matrix<d> r, b = *this;
        for( int i=0; i<d; i++ ) r.v[i][i] = 1LL;
        for( ; p ; p /= 2 ) {
            if( p % 2 ) {
                r = r.mul( b ).mod ( m );
            }
            b = b.mul( b );
            b = b.mod( m );
        }
        return r;
    }

    Matrix<d> mod( long long m ) {
        Matrix<d> r;
        for( int i=0; i<d; i++ )
            for( int j=0; j<d; j++ )
                r.v[i][j] = v[i][j] % m;
        return r;
    }
 };

int main () {

    freopen( "input.txt", "r", stdin );

    int T;
    scanf("%d", &T);
    int kase = 1;

    while( T-- ) {
        int n, m, r , p;
        scanf( "%d %d %d %d", &n, &m, &r, &p );
        long long ini[M];
        for( int i=0; i<n; i++ ) {
            scanf( "%lld", &ini[i] );
        }
        for( int i=0; i<n; i++ )
            for( int j=0; j<n; j++ )
                if( i == j ) mat[i][j] = 0;
                else mat[i][j] = INF;

        for( int i=0; i<m; i++ ) {
            int u ,v;
            scanf( "%d %d", &u, &v );
            mat[u][v] = 1;
            mat[v][u] = 1;
        }

        // finding all pair shortest path
        for( int k=0; k<n; k++ )
            for( int i=0; i<n; i++ )
                for( int j=0; j<n;j++ )
                    mat[i][j] = min( mat[i][j], mat[i][k] + mat[k][j]);

        memset( _mat, 0 , sizeof _mat );

        // seperate into r matrices
        for( int k = 1; k <= r; k++ ) {
            for( int i=0; i<n; i++ ) {
                for( int j=0; j<n; j++ ) {
                    if( i == j || mat[i][j] == k ) _mat[k][i][j] = 1;
                }
            }
        }

        int pw = p / r;
        int rem = p % r;

        Matrix<100> trans ;

        for( int i=0; i<n; i++ ) {
            for( int j=0; j<n; j++ )
                trans.v[i][j] = _mat[1][i][j];
        }

        // multiply for the final transition Matrix
        for( int i=2; i <= r; i++ ) {
            Matrix<100> cur;
            for( int j=0; j<n; j++ )
                for( int k=0; k<n; k++ )
                    cur.v[j][k] = _mat[i][j][k];
            trans = trans.mul( cur );
            trans = trans.mod( MOD );
        }

        // power the transition matrix
        trans = trans.modpow( pw, MOD );

         // multiplying the remaining
        for( int i=1; i<=rem; i++ ) {
            Matrix<100> cur;
            for( int j=0; j<n; j++ )
                for( int k=0; k<n; k++ )
                    cur.v[j][k] = _mat[i][j][k];
            trans = trans.mul( cur );
            trans = trans.mod( MOD );
        }


        // the resultant Matrix
//        Matrix<100> res;
//        for( int i=0; i<n; i++ ) {
//            res.v[i][0] = ini[i];
//        }
//
//        res = res.mul( trans );
//        res = res.mod( MOD );

//        for( int i=0; i<n; i++ ) {
//            for( int j=0; j<n; j++ ) {
//                cout << trans.v[i][j] << " ";
//            }
//            cout << endl;
//        }

        long long res[M];
        memset( res, 0 ,sizeof res );
        for( int i =0 ; i < n; i++ ) {
            for( int j=0; j < n; j++ ) {
                res[i] = ( res[i] + trans.v[i][j] * ini[j] ) % MOD;
            }
        }

//        for( int i=0; i<n; i++ ) {
//            for( int j=0; j<n; j++ ) {
//                cout << res.v[i][j] << " ";
//            }
//            cout << endl;
//        }

        printf( "Case %d: ", kase++);
        for( int i=0; i<n ; i++ ) {
            if( i != 0 ) printf( " " );
            printf( "%lld", res[i] );
        }

    }

    return 0;
}
