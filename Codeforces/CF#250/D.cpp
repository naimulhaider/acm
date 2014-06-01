#include<bits/stdc++.h>
using namespace  std;

vector<int> v;

int main() {

    int n, m;
    cin >> n >> m;
    for( int i=0; i < n; i++ ) {
        int x;
        cin >> x;
        v.push_back( x );
    }

    for( int i=0; i < m; i++ ) {
        int u, v;
        cin >> u >> v;
    }

    sort( v.begin(), v.end() );
    double res = 0.0;
    int cur = n-1;
    for( int i=0 ; i  < v.size(); i++ ) {
        res += double( v[i] * cur );
        cur--;
    }

    res = res * 2;
    res = res / double( n * (n-1) );

    printf( "%.6lf\n", res );

    return 0;
}
