#include<bits/stdc++.h>
using namespace std;

int main () {

    freopen( "output.txt" , "w" ,stdout );
    double n;
    while(cin>> n) {
        if( n == 0 ) continue;
//        cout << n - 100000000 << endl;
        printf( "%lf\n", n - 1000000000000 );
    }

    return 0;
}

/*

7
11111011111111.000000
-24084837342.000000
2193724857342.000000
81273757128342.000000
-99612658.000000
843894342.000000
-99417658.000000
234877342.000000
-80172658.000000
-2238757342.000000
-78437978217342.000000
-1238883274342.000000
-1338782342.000000


*/