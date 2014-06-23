#include<bits/stdc++.h>
using namespace std;

map<char, char> hsh;
vector<char> v;
string s;

int main() {

    int T;
    cin >> T;

    while( T-- ) {
        int n;
        cin >> n;

        hsh.clear();
        v.clear();

        for( int i=0; i < n; i++ ) {
            char c ,p;
            cin >> c >> p;
            hsh[c] = p;
        }

        cin >> s;

        for( int i=0; i < s.size(); i++ ) {
            if( hsh[ s[i] ] == 0 ) v.push_back( s[i] );
            else v.push_back( hsh [s[i]] );
        }


        reverse( v.begin(), v.end() );
        while( int(v.size()) > 0 && v[ v.size() - 1 ] == '0' ) v.pop_back();
        reverse( v.begin(), v.end() );

        while( int(v.size()) > 0 && v[ v.size() - 1 ] == '0' ) v.pop_back();
        if( int(v.size()) > 0 && v[ v.size() - 1 ] == '.' ) v.pop_back();

        for( int i=0; i < v.size(); i++ ) {
            cout << v[i];
        }
        if( v.empty() ) {
            cout << "0";
        }
        cout << "\n";
    }

    return 0;
}
