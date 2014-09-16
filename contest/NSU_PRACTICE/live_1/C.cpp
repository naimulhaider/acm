#include<bits/stdc++.h>
using namespace std;

int sol( string& s ) {

    int ret = 0;
    for( int i=0; i < s.size() ; i++ ) {
        if( s[i] == 'l' ) ret = max( ret , 1 );
        if( i+1 < s.size() && s[i] == 'l'  && s[i+1] == 'o' ) ret = max( ret,  2 );
        if( i+2 < s.size() && s[i] == 'l' && s[i+1] == 'o' && s[i+2] == 'l' ) ret=  max( ret, 3 );
        if( s[i] == 'o' ) ret=  max( ret, 1 );
        if( i+1 < s.size() && s[i] == 'o' && s[i+1] == 'l' ) ret=  max( ret , 2 );
        if( i+1 < s.size() && s[i] == 'l' && s[i+1] == 'l' ) ret = max( ret, 2 );
        if( i +2 < s.size() && s[i] == 'l' && s[i+2] == 'l' ) ret = max( ret, 2 );
    }

    return ret;
}

int main() {

    int T;
    cin >> T;

    while( T-- ) {

        string s;
        cin >>s;
        int res = sol( s );
        int ans = 3 - res;
        cout << ans << "\n";
    }

    return 0;
}
