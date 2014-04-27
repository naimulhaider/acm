// author: naimulhaider
// task:
// algo:
// date: 2014-04-27

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
#define REP(i,n) for(int i=0, _e(n); i<_e; i++)
#define FOR(i,a,b) for(int i(a), _e(b); i<=_e; i++)
#define FORD(i,a,b) for(int i(a), _e(b); i>=_e; i--)
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define SET(t,v) memset((t), (v), sizeof(t))
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize( unique( ALL(c) ) - (c).begin() )
#define pb push_back
#define sz(t) ((int)((t).size()))
#define mp make_pair
typedef pair<int,int> ii;
typedef vector<int> VI;
typedef vector< vector<int> > VVI;
typedef long long LL;
#define D(x) if(1) cout << __LINE__ <<" "<< #x " = " << (x) << endl;
#define D2(x,y) if(1) cout << __LINE__ <<" "<< #x " = " << (x)  <<", " << #y " = " << (y) << endl;
#define PRINT(x) FORIT(i,x){if(i!=x.begin())printf(" ");cout<<*i; }printf("\n");

int main(){

    int n, s;
    cin >> n >> s;
    int sum = 0;
    VI v;
    REP(i,n){
        int x;
        cin >> x;
        v.pb(x);
    }
    sort(ALL(v));
    bool ok = 1;
    REP(i,n-1){
        if( i >= sz(v) ){
            ok = 0;
            break;
        }
        sum += v[i];
    }

    if ( sum > s ) ok = 0;

    if ( ok ) {
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }

    return 0;
}
