
#include<bits/stdc++.h>
using namespace std;

int main() {

//    freopen( "c2.in", "r", stdin );
//    freopen( "a2.out", "w", stdout );

    int mx = 0;
    int n;
    while( cin >> n ) {
        mx = max( mx , n );
    }

    cout << mx << endl;

    return 0;
}
