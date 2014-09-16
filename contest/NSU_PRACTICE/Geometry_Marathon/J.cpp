#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> v[110];

int solve(  ){
    int cx = 0, cy = 0, cz = 0;
    int dx = 5000, dy = 5000, dz = 5000;
    for( int i=0; i<6; i++ ){
        for( int j=0; j<n; j++ ){
            switch( i ){
                case 0:
                    cx = max( cx, v[j][i] );
                    break;
                case 1:
                    cy = max( cy, v[j][i] );
                    break;
                case 2:
                    cz = max( cz, v[j][i] );
                    break;
                case 3:
                    dx = min( dx, v[j][i] );
                    break;
                case 4:
                    dy = min( dy, v[j][i] );
                    break;
                case 5:
                    dz = min( dz, v[j][i] );
                    break;
            }
        }
    }

    for( int i=0; i<n; i++ ){
        if( cx >= v[i][0] && cy >= v[i][1] && cz >= v[i][2]
           && dx <= v[i][3] && dy <= v[i][4] && dz <= v[i][5] ) continue;
        return -1;
    }

    int fx = dx - cx;
    int fy = dy - cy;
    int fz = dz - cz;
    return fx*fy*fz;
}

int main(){
    //freopen( "input.txt", "r", stdin );
    int kase;
    cin >> kase;
    for( int z=1; z<=kase; z++ ){
        for( int i=0; i<110; i++ ) v[i].clear();
        cin >> n;
        for( int i=0; i<n; i++ ){
            int ax, ay, az, bx, by, bz;
            cin >> ax >> ay >> az >> bx >> by >> bz;
            v[i].push_back( ax );
            v[i].push_back( ay );
            v[i].push_back( az );
            v[i].push_back( bx );
            v[i].push_back( by );
            v[i].push_back( bz );
        }
        int res = solve();
        cout << "Case " << z <<": ";
        if( res<=0 ) cout << "0" << endl;
        else cout << res << endl;

    }

    return 0;
}
