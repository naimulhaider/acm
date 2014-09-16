#include<bits/stdc++.h>
using namespace std;

inline int cmp(int x, int y){
    if (x < y) return -1;
    else if (x > y) return +1;
    else return 0;
}
bool cmp_eq(int x, int y){
    return cmp(x,y) == 0;
}
bool cmp_lt(int x, int y){
    return cmp(x,y) < 0;
}

struct segtree {
    int B, E, C;
    segtree *L, *R;
    int len;
    int a, lbd, rbd;
    segtree(int b, int e): B(b), E(e), len(0), C(0), a(0), lbd(0), rbd(0) {
    if (E - B > 1) {
        int M = (B + E) / 2;
        L = new segtree(B, M);
        R = new segtree(M, E);
    } else if (E - B == 1) {
        L = new segtree(B, B);
        R = new segtree(E, E);
    } else L = R = NULL;
}

    ~segtree() { delete L; delete R; }

    void insert(int b, int e) {
        if (e <= B || E <= b || B == E) return;
        if (b <= B && E <= e) C++;
        else { L->insert(b, e); R->insert(b, e); }
        update();
    }

    void erase(int b, int e) {
        if (e <= B || E <= b || B == E) return;
        if (b <= B && E <= e) C--;
        else { L->erase(b, e); R->erase(b, e); }
        update();
    }
    void update();
};

struct rect {
    int x1, y1, x2, y2;
    rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0):
    x1(x1), y1(y1), x2(x2), y2(y2) {}
};

const int TAM = 10000;
int y[2 * TAM];

void segtree::update() {
    if (C) {
        len = y[E] - y[B];
        a = 2;
        lbd = rbd = 1;
    } else {
        len = L->len + R->len;
        a = L->a + R->a - 2 * L->rbd * R->rbd;
        lbd = L->lbd; rbd = R->rbd;
    }
}

int union_perimeter(vector<rect>& R) {
    int n = R.size(); if (n == 0) return 0;
    vector< pair<int, int> > E;
    int m = 0;
    for (int i = 0; i < n; i++) {
        E.push_back(make_pair(R[i].x1, i));
        E.push_back(make_pair(R[i].x2, ~i));
        y[m++] = R[i].y1;
        y[m++] = R[i].y2;
    }
    sort( E.begin() , E.end() ); sort(y, y + m); m = unique(y, y + m, cmp_eq) - y;
    int last = E[0].first, r = 0, dy = 0;
    segtree T(0, m-1);
    for (int i = 0; i < E.size(); i++) {
        int k = E[i].second; bool in = (k >= 0); if (!in) k = ~k;
        int dx = E[i].first - last;
        r += dx * T.a;
        int a = lower_bound(y, y + m, R[k].y1, cmp_lt) - y;
        int b = lower_bound(y, y + m, R[k].y2, cmp_lt) - y;
        if (in) T.insert(a, b);
        else T.erase(a, b);
        r += fabs(dy - T.len);
        dy = T.len;
        last += dx;
    }
    return r;
}

int main() {

//    freopen( "input.in" , "r" , stdin );

    int n;
    while( scanf( "%d", &n ) == 1 ) {
        vector<rect> v;
        for( int i=0 ;i < n; i++ ) {
            int x1, y1, x2, y2;
            scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );
            v.push_back( rect(x1,y1,x2,y2) );
        }
        printf( "%d\n" , union_perimeter( v ) );
    }

    return 0;
}
