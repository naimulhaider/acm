#include<bits/stdc++.h>
using namespace std;

int allzero( string &s, int i, int j ) {
    if( i > j ) return 1;
    for( int k=i; k<=j; k++ )
        if( s[k] != '0' ) return 0;
    return 1;
}

int check ( string& s ) {
    int dot = 0;
    int i=0;
    for(  ; i < s.size(); i++ ) {
        if( s[i] == '.' ) {
            return allzero( s, i+1, s.size() -1 );
        }
        if( s[i] < '0' || s[i] > '9' ) return 0;
    }
    return 1;
}

string rstr = "";

int sol( string& s ) {

    int i = 0;
    while( s[i] == ' ' ) {
        i++;
    }
    string s1 = "";
    int j = s.size()-1;
    while( s[j] == ' ' ) {
        j--;
    }

    while( s[i] == '0' ) i++;
    if( i > j ) {
        rstr = "0";
        return 1;
    }

    for( int k = i ; k <= j; k++ ) s1 += s[k];
    rstr = s1;
    if( !check(s1) ) return -1;

}

int main() {

    int T;
    cin >> T;
    string dump;
    getline( cin, dump );
    while( T-- ) {
        string s;
        getline( cin, s );
        int res = sol( s );
        if( res == -1 ) cout << "invalid input" << "\n";
        else {
            if( rstr.size() == 0 || rstr[0] == '.' ) {
                cout << "0" << "\n";
            } else {
                for( int i=0; i < rstr.size(); i++ ) {
                if( rstr[i] == '.' ) break;
                    cout << rstr[i] ;
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
