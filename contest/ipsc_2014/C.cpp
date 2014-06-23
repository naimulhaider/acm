#include<bits/stdc++.h>
using namespace std;

bool mark[1000000];
vector<int> res;

int main() {

    freopen( "c2.in", "r", stdin );
    freopen( "c2.out", "w", stdout );

    int kase;
    cin >> kase;

    for( int i=0 ; i < kase; i++ ) {
        memset( mark , false, sizeof mark );
        res.clear();
        int n;
        cin >> n;
        for( int i=0 ; i <n; i++ ) {
            int x;
            cin >> x;
            if( !mark[x] ) res.push_back(x);
            mark[x] = 1;
        }

        for( int i=0 ; i< res.size(); i++ ) {
            if( i != 0 ) cout << " ";
            cout << res[i];
        }
        cout << "\n";
    }

    return 0;
}
