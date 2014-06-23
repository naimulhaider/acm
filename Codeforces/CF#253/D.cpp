#include<bits/stdc++.h>
using namespace std;

vector<double> v;

double rec ( int p , int kept ) {

    if( p >= v.size() ) {
        return 0.0;
    }

    double ret = 0.0;
    if(kept==0) ret = max ( ret, rec( p+1, kept ) );

    if( kept ) {
        ret = max( ret, rec( p+1, 1 ) );
        ret = max ( ret, (1.0-v[p]) * rec(p+1,1) );
        ret=  max( ret, 1.0 - v[p] );
    } else {
        ret = max ( ret, ( v[p] * rec( p+1, 1 ) ) );
        ret = max ( ret, v[p] );
    }
    return ret;
}

int main () {

    int n;
    cin >> n;

    for( int i=0;  i< n; i++ ) {
        double x;
        cin >> x;
        v.push_back(x);
    }


    double res = rec( 0, 0 );
    cout << res << endl;

    return 0;
}

