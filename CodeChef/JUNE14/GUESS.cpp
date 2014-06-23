#include<bits/stdc++.h>
using namespace std;

int main () {

    int T;
    cin >> T;

    while( T-- ) {
        unsigned long long n , m;
        cin >> n >> m;
        unsigned long long oddA = n/2, oddB=m/2, evenA=n/2, evenB=m/2;
        if(n%2) oddA++;
        if(m%2) oddB++;
        unsigned long long num = (oddA*evenB) + (evenA*oddB);
        unsigned long long den = n * m;
        unsigned long long div = __gcd( num, den );
        num /= div;
        den /= div;
        cout << num << "/" << den << endl;
    }

    return 0;
}
