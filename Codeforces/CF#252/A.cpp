#include<bits/stdc++.h>
using namespace std;

int main () {

    int n , v;
    cin >> n >> v;
    int res = 0;
    vector<int> ans;
    for( int i=0 ; i< n; i++ ) {
        int N;
        cin >> N;
        int mn = 1000000007;
        for( int j=0 ;j < N; j++ ) {
            int x;
            cin >> x;
            mn = min( mn, x );
        }
        if( mn < v ) {
            ++res;
            ans.push_back( i+1 );
        }
    }
    cout << res << endl;
    if( res ) {

        for( int i=0 ;i < ans.size(); i++ ) {
            if( i ) cout << " ";
            cout << ans[i] ;
        }
    }

    return 0;
}
