#include<bits/stdc++.h>
using namespace std;

int main () {

    set<char> st;

    string s;
    getline( cin , s );
    for( int i=0 ; i < s.size(); i++ ) {
        if( s[i] >='a' && s[i] <= 'z' ) {
            st.insert( s[i] );
        }
    }

    cout << st.size() << endl;

    return 0;
}
