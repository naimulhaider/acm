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

int n, m;
vector<int> mat[101];

int ok ( ){
    int cur = n;
    int res = n;
    while ( 1 ){
        cur = cur/2;
        if (  cur == 0) return 1;
        REP( i, cur){
            REP(j,m){
                if ( mat[i][j] != mat[(cur*2)-i-1][j] ) {
                    return res;     
                }
            }
        }
        res = cur;
    }
    return res;
}

int main(){
 
    cin >> n >> m;
    REP(i,n){
        REP(j,m){
            int x;
            cin >> x;
            mat[i].pb(x);
        }
    }

    if ( n % 2 ){
        cout << n << endl;
    }else {
        cout << ok() << endl;
    }

    return 0;
}
