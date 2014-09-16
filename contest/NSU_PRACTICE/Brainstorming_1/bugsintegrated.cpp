#include<cstdio>
#include<algorithm>
#include<cstring>
#include<utility>
using namespace std;

/*
Keep 3 states
1. row
2. column
3. configuration of current row / mask

Either i can fill a 2 x 3 and jump to col+3 th column
or i can fill a 2 x 3 and jump to row + 2 th row
or i can fill a 3 x 2 and jump to next col+2 th column
or i can fill a 3 x 2 and jump to row + 2 th row
*/

bool plate[10][200][20];
pair<int,int> sz[10];
int curPlate;
int memo[200][20][2100];

bool free2by3 ( int& p, int& r, int& c, int& mask ) {
//    cout << "at free2by3 " << r << " " << c << " " << mask<< endl;
    if( r + 1 >= sz[p].first ) return 0;
    if( c + 2 >= sz[p].second ) return 0;
    if( mask & (1<<c) ) return 0;
    if( mask & (1<<(c+1)) ) return 0;
    if( mask & (1<<(c+2)) ) return 0;
//    if(r==0&&c==2)cout << "here r=0 c=2 " << endl;
    for( int i=r; i < r+2; i++ ) {
        for( int j=c; j < c+3; j++ ) {
            if( plate[p][i][j] ) return 0;
        }
    }
//    cout << "got1" << endl;
    return 1;
}

bool free3by2 ( int& p, int& r, int& c,int &mask ) {
    if( r + 2 >= sz[p].first ) return 0;
    if( c + 1 >= sz[p].second ) return 0;
    if( mask & (1<<c) ) return 0;
    if( mask & (1<<(c+1)) ) return 0;
    for( int i=r; i < r+3; i++ ) {
        for( int j=c; j < c+2; j++ ) {
            if( plate[p][i][j] ) return 0;
        }
    }
//    cout << "got 1" << endl;
    return 1;
}

int rec( int row , int col , int mask, int mask2 ) {

    if( row >= sz[curPlate].first ) return 0;
    if( col >= sz[curPlate].second ) return 0;
//    if( memo[row][col][mask] != -1 ) {
//        return memo[row][col][mask];
//    }
    int res = 0;
    int i = col;
    // remember to check if row is free by mask
    if( free2by3(curPlate,row,i,mask) ) {
        // fill 2 x 3 jump to col + 3
        res = max( res, 1 + rec(row,i+3,mask,mask2) );
        //or i can fill a 2 x 3 and jump to row + 2 th row
        res = max( res, 1 + rec(row+2,0,mask2,0) );
    }

    if( free3by2(curPlate,row,i,mask) ) {
        int nmask = mask2;
        nmask |= (1<<i);
        nmask |= (1<<(i+1));
        // or i can fill a 3 x 2 and jump to next col+2 th column
        res = max( res, 1 + rec(row,i+2,mask,nmask) );
        // or i can fill a 3 x 2 and jump to row + 2 th row
        res = max( res, 1 + rec(row+2,0,nmask,0) );
        res = max( res, 1 + rec(row+1,i+2,nmask,0 ) );
    }


    if(col==0) res = max( res , rec(row+1,0,0,0) );
    res = max( res, rec(row,col+1,mask,mask2) );
    return memo[row][col][mask] = res;

}

int main() {

    memset( plate, 0 , sizeof plate );

    int D;
    scanf( "%d", &D );
    for( int i=0; i < D; i++ ) {
        int N, M, K;
        scanf( "%d%d%d", &N, &M, &K );
        sz[i] = make_pair( N, M );
        for( int j=0 ; j< K; j++ ) {
            int x, y;
            scanf( "%d %d" , &x, &y );
            plate[i][y-1][x-1] = 1;
        }
    }

    for( int i=0 ; i < D; i++ ) {
        curPlate = i;
        memset( memo, -1 , sizeof memo );
        int res = rec( 0, 0 , 0, 0 );
        printf( "%d\n" , res );
    }

    return 0;
}


/*

00000X
00000X
00X000
00000X
000000

1
3 3 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3

1
6 5 9
4 5
2 2
4 3
1 3
5 1
1 1
2 1
4 3
1 4

*/
