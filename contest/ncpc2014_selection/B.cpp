#include<bits/stdc++.h>
using namespace std;

char line[1010];
int memo[1010][30];
int len;
int MOD = 100009;

int rec ( int p, int prev ) {

    if( p >= len ) return 0;
    if( memo[p][prev] != -1 ) return memo[p][prev];
    if( line[p] == prev + 'a' ) {
        return memo[p][prev] = rec(p+1, prev)% MOD;
    }

    int ret = 1;
//    for( int i=p+1; i<len ; i++ ) {
//        if( line[i] != line[p] ) {
//            ret = ( ret + rec( i, line[p] - 'a' )  ) % MOD ;
//        }
//    }
    ret = ( ret + rec(p+1,line[p]-'a') ) % MOD;
    ret = ( ret + rec(p+1, prev) )% MOD;
    return memo[p][prev] = ret;
}


int main () {

    int T;
    scanf( "%d", &T );
    int kase =1;
    while( T-- ) {
        scanf( "%s", line );
        len = strlen( line );
        memset( memo, -1, sizeof memo );
        int res = rec ( 0, 29 );
        printf( "Case %d: %d\n", kase++, res+1  );
    }

    return 0;
}

/*
1
jlfjflkjdsafewlrjoiweuroiweuoiwqjdlkasjdlksnvdsnvkjsdafkjahfwqjdwqjoidqjdlksjlkfdajlkfdhldjfoijvoidsajvcoiajoiwjedoiqwjdoiwqjdoiqjwdoijaslkjclkacnlknclksndlcksdkajflkdsjflkdsajflkjdsaflkjslfaaa

correct: 92916
loss: 41512
*/
