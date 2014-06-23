/* LOJ: Partitioning Game (1199)
Cat: Game Theory */

#include<bits/stdc++.h>
using namespace std;

int v[110];
int memo[10005];

int grundy( int pile ) {
    if( pile== 0 || pile == 1 || pile == 2 ) return 0;
    if( memo[pile] != -1 ) return memo[pile];
    set<int> s;
    for( int i=1; i<=pile/2; i++ ) {
        if( i == pile-i ) continue;
        s.insert( grundy(i) ^ grundy(pile-i) );
    }
    int i = 0;
    while( s.find(i) != s.end() ) i++;
    return memo[pile] = i;
}

int main () {

    int T;
    cin >> T;
    int kase = 1;
    memset( memo, -1 , sizeof memo );
    while( T-- ) {
        int n;
        cin >> n;
        for( int i=0; i < n; i++ ) {
            cin >> v[i];
        }
        int res = 0;
        for( int i=0; i < n; i++ ) {
            res ^= grundy( v[i] );
        }
        cout << "Case " << kase++ << ": ";
        if( res ) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }

    return 0;
}

/*

6
1
16
1
169
3
648 247 294
4
403 761 116 99
5
18 20 18 15 15
6
916 590 341 139 626 515

Case 1: Alice
Case 2: Alice
Case 3: Alice
Case 4: Bob
Case 5: Bob
Case 6: Alice
*/
