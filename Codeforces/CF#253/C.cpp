#include<bits/stdc++.h>
using namespace std;

int main () {

    int n;
    cin >> n;
    map<char,int> m;
    m['R'] = 0;
    m['G'] = 1;
    m['B'] = 2;
    m['Y'] = 3;
    m['W'] = 4;

    int cols[6], vals[6];
    memset( cols , 0 , sizeof cols );
    memset( vals , 0 , sizeof vals );
    for( int i=0; i < n; i++ ) {
        string s;
        cin >> s;
        int col = m[ s[0] ];
        int val = s[1] - '0';
        cols[col]++;
        vals[val]++;
    }

    int cnt = 0;
    for( int i=0 ; i< 5; i++ ) {
        if( cols[i] > 0 ) ++cnt;
    }
    if( cnt >= 1 ) cnt--;


    int cnt2 = 0;
    for( int i=0 ; i< 5; i++ ) {
        if( vals[i] > 0 ) ++cnt2;
    }
    if( cnt2 >= 1 ) cnt2--;

    cout << max( cnt , cnt2 ) << "\n";

    return 0;
}



