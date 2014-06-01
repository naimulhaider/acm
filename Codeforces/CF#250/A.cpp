#include<bits/stdc++.h>
using namespace std;

bool cmp ( pair<int,int> a, pair<int,int> b ) {
    return a.first < b.first;
}

int main () {

    vector< pair<int,int> > sizes;
    for( int i=0; i<4; i++ ) {
        string s;
        cin >> s;
        sizes.push_back( make_pair(s.size()-2, i ) );
    }

    sort( sizes.begin(), sizes.end(), cmp );
    int ans = 2;
    bool case1 = 0, case2 = 0;
    if( sizes[0].first <= sizes[1].first / 2 ) {
        case1 = 1;
        ans = sizes[0].second;
    }
    if( sizes[3].first/2 >= sizes[2].first ){
        case2 = 1;
        ans = sizes[3].second;
    }

    if( case1 && case2 ) ans = 2;

    char res = 'A' + ans;
    cout << res << endl;
    return 0;
}
