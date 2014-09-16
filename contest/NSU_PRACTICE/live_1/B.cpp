#include<bits/stdc++.h>
using namespace std;

int n ,m;

char board[55][55];

struct data {
    int x, y;
    int s, tm;
    data( int a, int b, int c, int d ) : x(a) , y(b) , s(c) , tm(d){}
};

int dr[]  = {-1,1,0,0};
int dc[] = {0,0,-1,1};

int memo[55][55][2600];

int sol ( int sx , int sy, int inboard ) {
    memset( memo, -1 , sizeof memo );
    queue<data> q;
    q.push( data(sx,sy,0,0) );
    int ret = 1000000007;
    while( !q.empty() ) {
        data u = q.front();
        q.pop();
        int has = 0;
        if( board[u.x][u.y] == '#' ) ++has;
        int ctm = u.tm;
        cout << u.x << " " << u.y << endl;
        for( int i=0 ; i < 4; i++ ) {
            int x = dr[i] + u.x;
            int y = dc[i] + u.y;
            if( x >= n || y >= m || x < 0 || y < 0 ) continue;
            if( board[x][y] == 'X' ) continue;
            if( memo[x][y][ctm+1] < u.s + has && ctm < 2510 ) {
                memo[x][y][ctm+1] = u.s + has;
                if( u.s + has == inboard ) ret=  min( ret, ctm );
                q.push( data(x,y,u.s+has,ctm+1) );
            }
        }
    }
    return ret + inboard;
}

int main() {

    freopen( "input.txt" , "r" , stdin );
    freopen( "output.txt" , "w" , stdout );

    int T;
    cin >> T;

    while( T-- ) {

        cin >> n >> m;

        int sheep = 0;
        int stx, sty;
        for( int i=0; i < n; i++ ) {
            for( int j=0; j < m; j++ ) {
                cin >> board[i][j];
                if( board[i][j] == 'U' ) stx = i, sty= j;
                if( board[i][j] == '#' ) ++sheep;
            }
        }

        int res = sol( stx ,sty, sheep );
        if( res >= 1000000000  ) cout << "impossible" << endl;
        else cout << res << "\n";

    }

    return 0;
}
