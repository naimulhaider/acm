#include<bits/stdc++.h>
using namespace std;

string s;
vector<int> v;
int filled;
bool memo[1100000][21][2];
bool vis[1100000][21][2];

void update( int &mask, int tm ) {
    for( int i=0 ; i < v.size(); i++ ) {
        if( v[i] < tm ) mask = mask | (1<<i);
    }
}

bool rec( int mask , int tm, int player ) {

    if( (mask == (1<<(filled) )-1) || (tm >= v.size()) ) {
        if( player==0 ) return 0;
        return 1;
    }

    if( vis[mask][tm][filled] ) return memo[mask][tm][filled];

    bool ret = 0;
    int nmask = mask;
    update( nmask , tm );
    for( int i=0 ; i < v.size(); i++ ) {
        if( v[i] < tm ) continue;
        if( nmask & (1<<i) ) continue;
        ret |= rec ( nmask | (1<<i) , tm+1, player==0?1:0 );
    }

    vis[mask][tm][filled] = 1;
    return memo[mask][tm][filled] = ret;
}

int main() {

    int kase;
    cin >> kase;

    while( kase-- ) {
        v.clear();
        int n;
        cin >> n;
        cin >> s;
        memset( memo, false, sizeof memo );
        memset( vis, false, sizeof vis );
        for( int i=0; i < s.size(); i++ ) {
            if(s[i]=='1') v.push_back( i );
        }
        filled = v.size();
        bool res = rec( 0, 0, 0 );
        if( res ) {
            cout << "Adam" << "\n";
        } else {
            cout << "Betka" << "\n";
        }
    }

    return 0;
}
