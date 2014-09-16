#include<bits/stdc++.h>
using namespace std;

int main () {
    freopen( "input2.txt" , "w", stdout );
    int inps = 10000;
    cout << 1 << endl;
    cout << inps << endl;
    for( int i=0 ; i< 1000; i++ ) {
        int a = rand() % 10000000, b=rand() % 10000000;
        if( b < a ) swap(a,b);
        cout << a << " " << b << endl;
    }

    return 0;
}
