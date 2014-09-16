#include<bits/stdc++.h>
using namespace std;

#define MAXC 200005
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

query v[MAXC];
int res[MAXC];
int xcood[MAXC];
map<int,int> map_x;

int main() {

    int T, kase = 1;
    scanf( "%d", &T );

    while( T-- ){
        int p, q;
        scanf( "%d %d", &p , &q );
        int ind = 0;
        int xind = 0;
        for( int i=0; i < p; i++ ) {
            int x, y;
            scanf( "%d%d", &x, &y );
            xcood[xind++] = x;
            v[ind++] = query(2,x,y,1);
        }

        for( int i=0; i < q; i++ ) {
            int x1, y1, x2, y2;
            scanf( "%d%d%d%d", &x1, &y1, &x2, &y2 );
            xcood[xind++] = x1;
            xcood[xind++] = x2;
            v[ind++] = query( 1,x1,y1,x2,i );
            v[ind++] = query( 3,x2,y2,x1,i );
        }

        sort( xcood, xcood + xind );
        map_x.clear();

        for( int i=0; i < xind; i++ ) {
            if( map_x[ xcood[i] ] != 0 ) continue;
            map_x[ xcood[i] ] = i;
        }

        sort( v , v + ind, cmp );
        memset( res , 0 ,sizeof res );

        memset( data,  0, sizeof data );
        for( int i=0; i < ind; i++ ) {
            query &cur = v[i];
            if( cur.cat == 2 ) {
                update( map_x[cur.x], cur.val );
            } else if ( cur.cat == 1 ) {
                res[ cur.pos ] -= ( ask( map_x[cur.inv] ) - ask( map_x[cur.x]-1 ) );
            } else {
                res[ cur.pos ] += ( ask( map_x[cur.x] ) - ask( map_x[cur.inv]-1 ) );
            }
        }
        printf( "Case %d:\n" , kase++ );
        for( int i=0 ; i < q; i++ ) {
            printf( "%d\n", res[i] );
        }
    }

    return 0;
}

