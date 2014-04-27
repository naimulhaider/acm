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

    int n , lim;
    cin >> n >> lim;
    VI v;
    REP(i,n){
        int x;
        cin >> x;
        v.pb(x);
    }


    int res = -1000000007;
    REP(i,sz(v)){
        FOR(j,i,sz(v)-1){
            VI inner, outer;
            REP(k,sz(v)){
                if(k>=i&&k<=j) inner.pb(v[k]);
                else outer.pb(v[k]);
            }
            int clim = lim;
            sort(ALL(inner));
            sort(ALL(outer));
            reverse( ALL(outer) );
            int outerInd = 0;
            REP(z,sz(inner)){
                if( outerInd < sz(outer) && inner[z]<outer[outerInd] && clim ){
                    inner[z] = outer[outerInd];
                    outerInd++;
                    clim--;
                }
            }
            int sum = 0;
            REP(z,sz(inner)){
                sum += inner[z];
            }
            res = max( res, sum );
        }
    }

    cout << res << endl;

    return 0;
}
