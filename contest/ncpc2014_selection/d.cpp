#include<bits/stdc++.h>
using namespace std;

long long v[100009];

const long long MOD = 1000000007;


long long powmod( long long base, long long power ) {
    if( power == 0 ) return 1L;
    long long ret = powmod( base, power/2 );
    ret = ( ret * ret ) % MOD;
    if( power % 2 ) ret = ( ret * base ) %MOD;
    return ret ;
}

long long mod(long long a, long long b) {
    return ((a%b)+b)%b;
}

long long extended_euclid(long long a, long long b, long long &x, long long &y)
{
    long long xx = y = 0;
    long long yy = x = 1;
    while (b)
    {
        long long q = a/b;
        long long t = b;
        b = a%b;
        a = t;
        t = xx;
        xx = x-q*xx;
        x = t;
        t = yy;
        yy = y-q*yy;
        y = t;
    }
    return a;
}

long long mod_inverse(long long a, long long n)
{
    long long x, y;
    long long d = extended_euclid(a, n, x, y);
    if (d > 1) return -1;
    return mod(x,n);
}

int main () {

//    freopen( "in.txt", "r", stdin );

    int T;
    scanf("%d", &T);
    int kase = 1;

    while( T-- ) {

        int n , x;
        scanf( "%d %d", &n, &x );

        for( int i =0 ; i< n; i++ ) {
            scanf( "%lld", &v[i] );
        }

        long long num = 1, den = 1;
        for ( int i=0; i<n; i++ ) {
            num *= ( x - v[i] );
            num %= MOD;
        }

        den = powmod ( x , n );
        den = mod_inverse( den, MOD );
        long long gcd = __gcd ( num , den );
        den = mod_inverse( den, MOD );
//        num /= gcd;
//        den /= gcd;

        printf("Case %d: ",kase++);
        if(num){
            num /= gcd;
            den /= gcd;
            long long gcd2 = __gcd( num, den );
            num /= gcd2;
            den /= gcd2;
            if(num == 1 && den==1){
                printf("1\n");
            }else printf("%lld/%lld\n",num,den);

        }else {
            printf("0\n");
        }


    }

    return 0;
}
