#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
#define VMAX 300005

struct data{
    int l , orgIndex;
    bool entry;
    data() {}
    data(int l1, int orgIndex1 , bool entry1 = false) {
        l = l1 , entry = entry1;
        orgIndex = orgIndex1;
    }
} v[2*MAX];

struct mdata{
    int l , r , v;
    mdata(){}
    mdata( int l1 , int v1 , int r1 ):l(l1),r(r1), v(v1){}
} org[MAX];

bool cmp( data a, data b ) {
    if( a.l < b.l ) return 1;
    if( a.l == b.l ) {
        return !b.entry;
    }
    return 0;
}

int tree[10 * VMAX ], lazy[10 * VMAX], mxIndex[10 * VMAX];
bool pending[10 * VMAX];
int maxpos=0, curmax = 0;

inline void push_down( int& node ) {
    if( !pending[node] ) return;
    tree[node] += lazy[node];
    pending[node] = 0;
    lazy[node<<1] += lazy[node];
    lazy[(node<<1)+1] += lazy[node];
    lazy[node] = 0;
    pending[node<<1] = pending[(node<<1)+1] = 1;
}

void build( int node , int l, int r ) {
    if( l > r ) return;
    if( l == r ) {
        mxIndex[node] = l;
        return;
    }
    mxIndex[node] = l;
    int mid = (l + r) >> 1;
    build( node<<1, l , mid  );
    build( (node<<1)+1, mid+1 ,r );
    return;
}

void update( int node, int l, int r, int ll, int rr, int val ) {

    if( ll > rr ) return;
    if( l == ll && r == rr ) {
//        cout << "adding " << val << " to range " << ll << " " << rr << endl;
        lazy[node] += val;
        pending[node] = 1;
        push_down( node );
        return;
    }
    int mid = ( l + r ) / 2;
    int nodeL = (node << 1), nodeR = (node<<1) + 1;
    push_down( node );
    update( nodeL, l , mid , ll, min(mid,rr), val );
    update( nodeR, mid+1, r, max(mid+1,ll), rr, val );
    push_down(nodeL);
    push_down(nodeR);
    if( tree[nodeL] > tree[nodeR] ) {
        tree[node] = tree[nodeL];
        mxIndex[node] = mxIndex[nodeL];
    } else {
        tree[node] = tree[nodeR];
        mxIndex[node] = mxIndex[nodeR];
    }
    return;
}

//void printTree( int node, int l , int r ) {
//
//    if( l > r ) return;
//    if( l == r && l >= 0 && l <= 16 ) {
//        cout << l << " has value " << tree[node] << endl;
//        return;
//    }
//    if( l == r ) return;
//    int mid = (l + r ) / 2;
//    if( l >= 0 && r <= 16 ) {
//        cout << "range " << l << " to " << r <<
//        " has value " << tree[node] ;
//        if( pending[node] ) {
//            cout << " has pending " << lazy[node] ;
//        }
//        cout << endl;
//    }
//    printTree( node * 2, l , mid );
//    printTree ( node * 2 +1 , mid + 1, r );
//    return;
//}

int res[MAX] , rescnt=0;

int main() {

//    freopen( "input.in" , "r", stdin );

    int n;
    scanf( "%d", &n );
    for(int i=0; i < n; i++) {
        int l , r , val;
        scanf( "%d %d %d", &l, &val, &r );
        org[i] = mdata( l , val, r );
        v[i] = data( l, i , 1 );
        v[i+n] = data( val, i , 0 );
    }

    sort( v , v + 2*n, cmp );

    memset( lazy , 0 , sizeof lazy );
    memset( tree, 0 , sizeof tree );
    memset( pending, 0 , sizeof pending );

    build( 1, 0, VMAX-1 );

    int resL = 0, resR = 0;
    for( int i=0 ; i<2*n; i++ ) {
        int ii = v[i].orgIndex;
        if( v[i].entry ) {
            update( 1, 0, VMAX-1,  org[ii].v, org[ii].r, 1 );
        } else {
            update( 1, 0, VMAX-1,  org[ii].v, org[ii].r, -1 );
        }
        if( tree[1] > curmax ) {
            curmax = tree[1];
            resL = org[ii].l , resR = mxIndex[1];
        }

//        cout << "***************printing tree "<< org[ii].v <<" "<<org[ii].r<< " *********" << endl;
//        printTree( 1, 0, VMAX-1 );
//        cout << "***************finished printing tree*********" << endl;
//        cout << "tree[1] " << tree[1] << endl;

//        // debug
//        if( v[i].entry ) {
//            cout << "added " << org[ii].l << " " << org[ii].v << " " << org[ii].r;
//            cout << " count is " <<  tree[1] << endl;
//        }
//
//        else if( !v[i].entry ) {
//            cout << "removed " << org[ii].l << " " << org[ii].v << " " << org[ii].r;
//            cout << " count is " <<  tree[1] << endl;
//        }
    }

//    cout << "result range: " << resL << " " << resR << endl;

    for( int i=0; i < n; i++ ) {
        int l = org[i].l ,  v = org[i].v, r = org[i].r;
        if( l <= resL && v >= resL && v <= resR && r >= resR ) {
            res[rescnt++] = i + 1;
        }
    }

    printf( "%d\n" , rescnt );
    for( int i=0; i < rescnt; i++ ) {
        if ( i != 0 ) printf( " " );
        printf( "%d", res[i] );
    }

    return 0;
}
