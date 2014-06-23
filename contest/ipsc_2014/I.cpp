#include<bits/stdc++.h>
using namespace std;

vector<int> edge[22000];
int val[22000];
int logTable[100000];

void rec( int u ) {
    for( int i=0 ; i < edge[u].size(); i++ ) {
        int v = edge[u][i];
        int childs = edge[u].size();
        if( edge[u].size() == 1 ) {
            val[v] = val[u];
        } else val[v] = val[u] + logTable[childs];
        rec ( v );
    }
}

int makeLog( int v ) {
    int pw = 0;
    while( v > 1 ) {
        pw++;
        if( v % 2 ) v++;
        v /= 2;
    }
    return pw;
}

int main() {

//    freopen( "i1.in", "r", stdin );
//    freopen( "i1.out", "w", stdout );

    logTable[1] = 0;
    for( int i=2 ; i < 100000; i++ ) {
        logTable[i] = makeLog( i );
    }

    for( int i=1; i <= 65; i++ )
        cout << i << " " << logTable[i] << endl;

    int kase;
    cin >> kase;

    while( kase-- ) {

        for( int i=0 ; i < 22000; i++ ) edge[i].clear();
        int n;
        cin >> n;
        for( int i=2 ; i <= n; i++ ) {
            int x;
            cin >> x;
            edge[x].push_back ( i );
        }

        memset( val, 0 , sizeof val );

        rec( 1 );

        int res = 0;
        for( int i=1; i <= n; i++ ) res += val[i];
        cout << res << "\n";
    }

    return 0;
}
