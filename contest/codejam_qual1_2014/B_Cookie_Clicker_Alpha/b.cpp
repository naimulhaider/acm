// author: naimulhaider
// task:
// algo:
// date: 2014-04-12

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

double c, f, x;
double rec ( double rate ) {
    double tFarm = c / rate, tEnd = x / rate;
    if ( rate >= 10*x ) return tEnd;
    return min( tFarm+rec(rate+f), tEnd );
}

int main(){

    int T;
    cin >> T;
    int kase = 1;
    while( T-- ){
        cin >> c >> f >> x;
        double res = rec ( 2.0 ) ;
        printf( "Case #%d: %.7f\n", kase++, res );
    }

    return 0;
}

