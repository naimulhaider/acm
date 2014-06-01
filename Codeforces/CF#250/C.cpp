#include<bits/stdc++.h>
using namespace std;

int v[1010];
int mat[1010][1010];
bool rem[1010];

int main () {

    int n , m;
    cin >> n >> m;

    for( int i=0; i<n; i++ ) cin >> v[i];

    memset( mat, 0 , sizeof mat );
    for( int i=0; i<m; i++ ) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }

    vector< pair<int,int> > res;
    for( int i=0; i < n; i++ ) {
        res.push_back( make_pair( v[i], i ) );
    }

    memset( rem, false, sizeof rem );

    sort( res.begin(), res.end() );
    reverse( res.begin(), res.end() );

    int ans = 0;
    for( int i=0; i < res.size(); i++ ) {
        int w = res[i].first;
        int u = res[i].second;
        int sum = 0;
        for( int j=0; j < n; j++ ) {
            if( u == j ) continue;
            if( mat[u][j] && !rem[j] ) sum += v[ j ];
        }
        rem[u] = 1;
        ans += sum;
    }

    cout << ans << endl;

    return 0;
}
