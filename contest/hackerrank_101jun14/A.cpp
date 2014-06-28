#include<bits/stdc++.h>
using namespace std;

int main () {

    int t;
    cin >> t;

    while( t-- ) {
        int n;
        cin >> n;
        vector<int> v;
        for( int i=0 ; i < n; i++ ) {
            int x;
            cin >> x;
            v.push_back ( x );
        }

        sort( v.begin() , v.end() );

        bool res = false;
        for( int i=0 ; i < v.size(); i++ ) {
            for( int j=i+1; j < v.size(); j++  ) {
                if( __gcd( v[i], v[j] ) == 1 ) res = 1;
            }
        }

        if( res || v[0] == 1 ) cout << "YES" << "\n";
        else cout << "NO" << "\n";
    }

    return 0;
}
