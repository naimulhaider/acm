#include<bits/stdc++.h>
using namespace std;

int n, m, r;
int e[1000];

int rec ( int p, int slept, int con ) {

    if( p >= n ) return 0;

    int ret = 0;
    if( con > 1 && con <= r ) {
        ret = max( ret,  e[i] * i + rec(p+1,slept+1,con+1) );
    }

}

int main() {

    int T;
    cin >> T;

    while( T-- ) {
//        int n , m , r;
        cin >> n >> m >> r;

        for( int i=0; i < n;i++ ) {
            cin >> e[i];
        }

        int res = rec( 0, 0 );
        cout << res << endl;

    }

    return 0;
}
