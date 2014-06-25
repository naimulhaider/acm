#include<bits/stdc++.h>
using namespace std;

#define MAX 1000006

int par[MAX], mx[MAX];;
pair<int,int> memo[MAX];

void rec ( int u ) {
    int p = par[u];
    if( p == -1 ) return;
    if( memo[p].first < mx[u] ) {
        memo[p].second = memo[p].first;
        memo[p].first=  mx[u];
    } else memo[p].second = max(memo[p].second,mx[u]);

    if( max(memo[p].first, memo[p].second + 1) == mx[p] ) return;
    mx[p] = max( memo[p].first, memo[p].second + 1 );
    rec( p );
    return;
}

int main() {

    int n;
    scanf( "%d", &n );
    memset( par, -1 ,sizeof par );
    for(int i=0;i <MAX; i++) {
        memo[i].first=memo[i].second=0;
        mx[i] = 0;
    }

    for( int i=2;  i<= n+1; i++ ) {
        int x;
        scanf( "%d", &x );
        par[i] = x;
        mx[i] = 1;
        rec( i );
        if( i != 2 ) printf(" ");
        printf( "%d", memo[1].first );
    }

    return 0;
}
