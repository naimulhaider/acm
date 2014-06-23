#include<bits/stdc++.h>
using namespace std;

vector<double> v;

double getSum ( int l , int r ) {

    double ret = 0.0;
    for( int i=l ; i <= r; i++  ) {
        double cret = v[i];
        for( int j=l; j<=r; j++ ) {
            if( j == i ) continue;
            cret *= (1.0 - v[j] );
        }
        ret += cret;
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

    sort( v.begin() , v.end() );
    reverse( v.begin(), v.end() );

    double res = 0.0;
    // take max and go hi to lo

    for( int i=0;  i< v.size(); i++ ) {
        res = max( res , getSum( 0, i ) );
    }

    printf( "%.12lf\n",  res );

    return 0;
}


