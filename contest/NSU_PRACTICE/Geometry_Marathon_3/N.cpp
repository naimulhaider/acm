#include<bits/stdc++.h>
using namespace std;

#define MAXC 10000007
int N = MAXC;
int data[MAXC];

void update(int at, int by) {
    while (at < N) {
        data[at] += by;
        at |= (at + 1);
    }
}

int ask(int at) {
    int res = 0;
    while (at >= 0) {
        res += data[at];
        at = (at & (at + 1)) - 1;
    }
    return res;
}

struct query{
    int cat , pos, val;
    int x, y, inv;
    query(){}
    query( int cat, int x, int y, int val ) : cat(cat), x(x), y(y), val(val) {}
    query( int cat, int x, int y, int inv, int pos ):
        cat(cat),x(x),y(y),inv(inv), pos(pos) {}
};

bool cmp ( query a , query b ) {
    if( a.y < b.y ) return 1;
    if( a.y == b.y ) {
        return a.cat < b.cat;
    }
    return 0;
}

query v[300005];
int res[100005];

int main() {

    int T;
    scanf( "%d", &T );

    while( T-- ){
        int n;
        scanf( "%d", &n );
        int ind = 0;
        for( int i=0; i < n; i++ ) {
            int x, y, val;
            scanf( "%d%d%d", &x, &y, &val );
            v[ind++] = query(2,x,y,val);
        }
        int R;
        scanf( "%d" , &R );
        for( int i=0; i < R; i++ ) {
            int x1, y1, x2, y2;
            scanf( "%d%d%d%d", &x1, &y1, &x2, &y2 );
            v[ind++] = query( 1,x1,y1,x2,i );
            v[ind++] = query( 3,x2,y2,x1,i );
        }

        sort( v , v + ind, cmp );
        memset( res , 0 ,sizeof res );

        memset( data,  0, sizeof data );
        for( int i=0; i < ind; i++ ) {
            query &cur = v[i];
            if( cur.cat == 2 ) {
                update( cur.x, cur.val );
            } else if ( cur.cat == 1 ) {
                res[ cur.pos ] -= ( ask( cur.inv ) - ask( cur.x-1 ) );
            } else {
                res[ cur.pos ] += ( ask(cur.x) - ask( cur.inv - 1 ) );
            }
        }

        for( int i=0 ; i < R; i++ ) {
            printf( "%d\n", res[i] );
        }
    }

    return 0;
}
