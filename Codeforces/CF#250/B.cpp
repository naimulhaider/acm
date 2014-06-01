#include<bits/stdc++.h>
using namespace std;

int toPow( int base, int pow ) {
    if( !pow ) return 1;
    int ret = base;
    for( int i=1; i<pow; i++ ) {
        ret = ret * base;
    }
    return ret;
}

int toLowBit( int x ) {
    int pos = 0, p = 0;
    while( x > 0 ) {
        int c = x % 2;
        x /= 2;
        if( c == 1 ) {
            pos = p;
            break;
        }
        p++;
    }
    return toPow( 2, pos );
}

int main() {

    int sum, lim;
    cin >> sum >> lim;
    vector< pair<int,int> > v;
    for( int i=1; i<=lim; i++ ) {
        v.push_back( make_pair( toLowBit(i), i ) );
    }

    sort( v.begin(), v.end() );
    reverse( v.begin(), v.end() );
    int cursum = 0;
    int i = 0;
    vector<int> resSet;
    while( cursum < sum && i < v.size() ) {
        if( cursum + v[i].first <= sum  ) {
            cursum += v[i].first;
            resSet.push_back( v[i].second );
        }
        i++;
    }

    if( cursum == sum ) {
        cout << resSet.size() << endl;
        for( int j=0; j < resSet.size(); j++ ) {
            if( j != 0 ) cout << " ";
            cout << resSet[j] ;
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
