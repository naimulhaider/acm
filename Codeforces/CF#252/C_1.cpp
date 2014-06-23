#include<bits/stdc++.h>
using namespace std;

vector<int> cood[100000];

int main(){

    int n , m , k;
    cin >> n >> m >> k;

    int sz = ( n * m ) / k;

    int i = 0 , j = 0;

    int grid[400][400];

    int dir = 0, cnt = 0;
    int tubeNo = 1;
    while( i < n ) {

        if( i == 0 || i % 2 == 0 ) dir = 0, j = 0;
        else dir = 1, j = m-1;

        if( !dir ){
            while( j < m ) {

                if( cnt >= sz ) {
                    cnt = 0;
                    tubeNo++;
                }

                grid[i][j] = tubeNo;
                cood[ tubeNo ].push_back(i+1);
                cood[ tubeNo ].push_back(j+1);
                ++cnt;
                j++;
            }
        } else {
            while( j >= 0 ) {

                if( cnt >= sz ) {
                    cnt = 0;
                    tubeNo++;
                }

                grid[i][j] = tubeNo;
                cood[ tubeNo ].push_back(i+1);
                cood[ tubeNo ].push_back(j+1);
                ++cnt;
                j--;
            }
        }
        i++;
    }

//    for( int i=0 ; i< n; i++ ) {
//        for( int j=0; j < m; j++ ) {
//            cout << grid[i][j] ;
//        }
//        cout << endl;
//    }

//    for( i=0; i < n; i++ ) {
//        for( j=0 ; j < m; j++ ) {
//            cood[ grid[i][j] ].push_back( i+1 );
//            cood[ grid[i][j] ].push_back( j+1 );
//        }
//    }

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
