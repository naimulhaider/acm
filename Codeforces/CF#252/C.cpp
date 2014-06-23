#include<bits/stdc++.h>
using namespace std;

vector<int> cood[100000];

int main() {

    int n , m , no;
    cin >> n >> m >> no;

    int sz = (n*m) / no;

    int grid[400][400];
    memset( grid, 0, sizeof grid );

    int tubeNo = 1;
    int i = 0, j=0, k=0;
    while( i < n ) {
        j = 0;
        while( j < m ) {
            k = sz;
            if( j + k <= m ) {
                while(k--) grid[i][j] = tubeNo, j++;
                tubeNo++;
            } else j++;
        }
        i++;
    }
    j = 0;
    while( j < m ) {
        i = 0;
        while( i < n ) {
            k = sz;
            if( i + k <= n && grid[i][j] == 0 ) {
                while(k--) grid[i][j] = tubeNo, i++;
                tubeNo++;
            } else i++;
        }
        j++;
    }

//    for( int i=0 ; i< n; i++ ) {
//        for( int j=0; j < m; j++ ) {
//            cout << grid[i][j] ;
//        }
//        cout << endl;
//    }

    for( i=0; i < n; i++ ) {
        for( j=0 ; j < m; j++ ) {
            cood[ grid[i][j] ].push_back( i+1 );
            cood[ grid[i][j] ].push_back( j+1 );
        }
    }

    for( i=1; i <= tubeNo; i++ ) {
        cout << cood[i].size() / 2;
        for( j=0; j < cood[i].size(); j++ ) {
            cout << " ";
            cout << cood[i][j];
        }
        cout << endl;
    }

    return 0;
}
