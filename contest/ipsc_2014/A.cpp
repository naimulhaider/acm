#include<bits/stdc++.h>
using namespace std;

int main() {

//    freopen( "a2.in", "r", stdin );
//    freopen( "a2.out", "w", stdout );

    int T;
    cin >> T;

    while( T-- ) {

        string p, q;
        cin >> p >> q;

        int mInd = -1;
        for( int i=0 ; i < p.size(); i++ ) {
            if( i > q.size() ) break;
            if( p[i] != q[i] ) {
                mInd = i;
                break;
            }
        }

        string res = "";
        if( mInd == -1 ) {
            if( p.size() > q.size() ) {
                for( int i=q.size(); i < p.size(); i++) {
                    res += p[i];
                }
            } else {
                if( q.size() - p.size() <= p.size() ) {
                    for( int i=0; i < q.size()-p.size(); i++) {
                        res += "<";
                    }
                } else {
                    res += "*";
                    for( int i=0 ; i<p.size(); i++ ) res+=p[i];
                }
            }
        } else {
            int onLeft = mInd, onRight = q.size() - mInd - 1;
            if( onLeft > onRight ) { // use backspace
                for( int i=0 ; i < onRight + 1; i++ )
                    res += "<";
                for( int i=mInd; i < p.size(); i++ )
                    res += p[i];
            } else { // delete whole pass
                res += "*";
                for( int i=0 ; i < p.size(); i++ ) {
                    res += p[i];
                }
            }
        }

        res += "*";
        cout << res << "\n";

    }

    return 0;
}

/*

asd
asdfgx

*/
