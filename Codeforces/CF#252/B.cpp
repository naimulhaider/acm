#include<bits/stdc++.h>
using namespace std;

int main(){

    int n , v;
    cin >> n >> v;

    int fruit[4000], fruitx[4000];
    memset( fruit, 0 , sizeof fruit );
    memset( fruitx, 0 , sizeof fruitx );
    for( int i=0 ; i < n; i++ ) {
        int a, b;
        cin >> a >> b;
        fruit[a] += b;
    }

    for( int i=1 ; i <= 3200; i++ ) {
        if( fruit[i] + fruitx[i] > v ) {
            int diff = v - fruitx[i];
            diff = max( 0, diff );
            if( fruit[i] > diff ) {
                fruitx[i] += diff;
                fruitx[i+1] += ( fruit[i] - diff );
            } else fruitx[i] += fruit[i];
        } else {
            fruitx[i] += fruit[i];
        }

    }

    int res = 0;
    for( int i=1; i <= 3200; i++ ) {
        if( fruitx[i] < v ) res += fruitx[i];
        else res += v;
    }

    cout << res << endl;

    return 0;
}

/*

5 10
1 20
3 20
5 20
7 20
9 20

*/
