#include<bits/stdc++.h>
using namespace std;

int main () {

    string s;
    cin >> s;
    int k;
    cin >> k;

    for( int i=0 ; i< k; i++ ) s += '?';

    int res = 0;
    for( int i=0 ; i<s.size(); i++ ) {
        for( int j=i+1 ; j < s.size(); j++ ) {
            int len = j - i + 1;
            if( len == 0 || len % 2 ) continue;
            int n = len / 2;
            bool ok = 1;
            for( int k = i; k<i+n; k++ ) {
                if( s[k] == '?' || s[k+n] == '?' ) continue;
                if( s[k] != s[k+n] ) {
                    ok = 0;
                    break;
                }
            }
            if( ok ) res = max( res, len );
        }
    }

     cout << res << "\n";

    return 0;
}
