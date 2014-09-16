#include<bits/stdc++.h>
using namespace std;

#define MAX 30000

int tree[10 * MAX];
bool flag[10 * MAX];

void update( int v, int vl, int vr, int l, int r, int val ) {
    if( l > r ) return;
    if( vl == l && vr == r ) {
        flag[v] = 1;
        tree[v] = val;
        return ;
    }

    if( flag[v] ) {
        tree[v*2] = tree[v*2+1] = tree[v];
        flag[v*2] = flag[v*2+1] = 1;
        flag[v] = 0;
    }

    int mid = (vl+vr) / 2;
    update( v*2, vl, mid, l, min(r,mid), val );
    update( v*2+1, mid+1, vr, max(l,mid+1), r, val );
    return ;
}

int query( int v, int vl, int vr, int i ) {
    if( flag[v] ) return tree[v];
    if( vl >= vr ) return 0;
    int mid = (vl+vr) / 2;
    if( i <= mid ) {
        return query( v*2, vl, mid, i );
    } else {
        return query( v*2+1, mid+1, vr, i );
    }
}

pair<int,int> qlist[MAX];
int vlist[MAX];
int comp[10000007];
bool res[MAX];

int main() {

//    freopen( "input2.txt", "r", stdin );

    int T;
    scanf( "%d", &T );

    while( T-- ) {
        int n;
        scanf( "%d", &n );
        memset( flag, 0, sizeof flag );
        memset( res, 0, sizeof res );
        memset( comp, 0, sizeof comp );

        int ccount = 0;
        for( int i=0; i < n; i++ ) {
            int l , r;
            scanf( "%d %d", &l, &r );
            qlist[i]= make_pair(l,r) ;
            vlist[ccount++] = l;
            vlist[ccount++] = r;
        }

        sort( vlist, vlist + ccount );
        int cood = 1;
        for( int i=0 ; i < ccount ; i++ ) {
            if( comp[ vlist[i] ] == 0 ) {
                comp[ vlist[i] ] = cood++;
            }
        }


        for( int i=0 ; i < n; i++ ) {
            int l = comp[qlist[i].first], r = comp[qlist[i].second];
            update( 1, 1, cood, l, r, i+1 );
        }

        int ans = 0;
        for( int i=1 ; i <= cood ; i++  ) {
            int val = query( 1, 1, cood, i );
            if( !val || res[val] ) continue;
            ans++;
            res[val] = 1;
        }

        printf( "%d\n" , ans );
    }

    return 0;
}

/*

2

5
1 4
2 6
8 10
3 4
7 10

5
1 3
1 3
1 3
1 3
1 3

*/
