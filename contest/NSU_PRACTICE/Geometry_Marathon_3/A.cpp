#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

#define MAX 100005

pii v[MAX];
int memo[MAX], n;

bool cmp ( pii a, pii b ) {
    return a.first < b.first;
    if( a.first == b.first ) {
        return a.second < b.second;
    }
    return 0;
}

int rec ( int ind ) {
    if( ind >= n ) return 0;
    if( memo[ind] != -1 ) return memo[ind];
    int l = ind , r = n-1;
    while( l <= r ) {
        int mid = ( l +r) / 2;
        if( v[ind].second <= v[mid].first ) {
            r = mid - 1;
        } else l = mid + 1;
    }

    int next = r + 1;
    int ret = 0;
    ret = max ( 1 + rec(next), rec(ind+1) );
    return memo[ind] = ret;
}

int main() {

    int T;
    scanf( "%d", &T );

    while( T-- ) {

        scanf( "%d", &n );
        for( int i=0 ;i < n; i++ ) {
            int l, r;
            scanf( "%d %d" , &l, &r );
            v[i] = make_pair( l , r );
        }
        sort( v , v + n, cmp );
        memset( memo , -1 , sizeof memo );
        int ans = rec( 0 );
        printf( "%d\n" , ans );
    }

    return 0;
}
