#include<bits/stdc++.h>
using namespace std;

int main () {

    int n;
    cin >> n;

    int res = 0;
    int cnt = 0;
    for( int i=0; i < n; i++ ) {

        int x;
        cin >> x;
        if( x ) ++cnt;
        if( !x ) cnt = 0;
        res = max( res, cnt );
    }

    res = max( res, cnt );
    cout << res << "\n";

    return 0;
}
