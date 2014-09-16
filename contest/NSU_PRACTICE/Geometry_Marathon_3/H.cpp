#include<bits/stdc++.h>
using namespace std;

#define LOGSZ 8

class BIT {
public:
    int N = (1<<LOGSZ);
    int dataMul[ (1<<LOGSZ) + 1 ] , dataAdd[ (1<<LOGSZ) + 1 ];

    BIT( ) {
        CLR();
    }

    void CLR( ) {
        memset( dataMul, 0, sizeof dataMul );
        memset( dataAdd, 0, sizeof dataAdd );
    }

    void internalUpdate(int at, int mul, int add) {
        while (at < N) {
            dataMul[at] += mul;
            dataAdd[at] += add;
            at |= (at + 1);
        }
    }

    void updateRange(int left, int right, int by) {
        internalUpdate(left, by, -by * (left - 1));
        internalUpdate(right, -by, by * right);
    }

    int queryOfRange(int at) {
        int mul = 0;
        int add = 0;
        int start = at;
        while (at >= 0) {
            mul += dataMul[at];
            add += dataAdd[at];
            at = (at & (at + 1)) - 1;
        }
        return mul * start + add;
    }
};

vector<BIT> xcood(300);

int main () {

    int T, kase=1;
    scanf( "%d", &T );

    while( T-- ) {

        for( int i=0; i < 300; i++ ) xcood[i].CLR();

        int n;
        scanf( "%d", &n );

        int ans = 0;
        for( int i=0; i < n; i++ ) {
            int x1, y1, x2, y2;
            scanf( "%d%d%d%d",&x1,&y1,&x2,&y2 );
            x1+=102,y1+=102,x2+=102,y2+=102;
            int area = abs( (x2 - x1)  * (y2 - y1) );
            bool hasRect = 0;
            for( int j=x1+1; j<=x2; j++ ) {
                int sum = xcood[j].queryOfRange( y2 ) - xcood[j].queryOfRange( y1 );
                if( sum > 0 ) {
                    hasRect = 1;
                    break;
                }
            }

            if( !hasRect ) {
                ans += area;
                for( int j=x1+1; j <= x2; j++ ) {
                    xcood[j].updateRange( y1+1, y2, 1 );
                }
            }

        }

        printf( "Case %d: %d\n" , kase++, ans );
    }

    return 0;
}

/*

5

3
-1 -1 1 1
0 0 10 10
1 0 2 2


3
0 0 1 1
1 1 2 2
2 2 3 3


5
0 0 1 1
0 0 2 2
1 1 5 5
4 4 5 5
5 5 6 6


5
0 0 1 1
3 0 4 1
0 3 1 4
3 3 4 4
1 1 3 3


10
0 0 1 1
3 0 4 1
0 3 1 4
3 3 4 4
1 1 3 3
1 0 3 1
1 3 3 4
0 0 4 4
2 2 3 3
3 4 4 5

res:
6
3
18
8
13

*/
