#include<bits/stdc++.h>
using namespace std;

struct data {
    int sh, sm, eh, em;
    data(){}
    data ( int a, int b, int c, int d ) : sh(a),sm(b),eh(c),em(d){}
} v[200];

bool cmp ( data a, data b ) {
    if( a.sh < b.sh ) return 1;
    if( a.sh == b.sh ) {
        return a.sm < b.sm;
    }
    return 0;
}

int diff( data a , data b ) {
    if( a.eh == b.sh ) return b.sm - a.em;
    return (60-a.em) + 60*(b.sh - a.eh -1) + b.sm;
}

int main () {

    int n, day = 1;
    while( cin >> n ) {
        int sh , sm, eh, em;
        bool hasst = 0 , hased = 0;
        for( int i=0 ; i< n; i++ ) {
            scanf( "%d:%d %d:%d", &sh, &sm, &eh, &em );
            v[i] = data(sh,sm,eh,em);
            string line;
            getline( cin, line );
            if( sh == 10 && sm == 0 ) hasst = 1;
            if( eh == 18 && em == 0 ) hased = 1;
        }

        if( !hasst )  v[n] = ( data(10,0,10,0) ), n++;
        if( !hased ) v[n] = ( data(18,0,18,0) ), n++;

        sort( v, v+n, cmp );

//        for( int i=0 ; i< n; i++ ) {
//            cout << v[i].sh << " " << v[i].sm << " " << v[i].eh << " " << v[i].em << endl;
//        }

        int res = 0, resh, resm;
        for( int i=0 ; i <n-1; i++ ) {
            int mins = diff( v[i], v[i+1] );
//            cout << "mins " << mins << endl;
//            cout << between << v[i].eh << " " << v[i].em << " " <<
            if( mins > res ) {
                res = mins;
                resh = v[i].eh;
                resm = v[i].em;
            }
        }

        if( res < 60 ){
            printf( "Day #%d: the longest nap starts at %02d:%02d and will last for %d minutes.\n", day++, resh, resm,  res );
        } else {
            int hr = res / 60;
            int mn = res - ( hr * 60 );
            printf( "Day #%d: the longest nap starts at %02d:%02d and will last for %d hours and %d minutes.\n", day++, resh, resm, hr, mn );
        }

    }

    return 0;
}
