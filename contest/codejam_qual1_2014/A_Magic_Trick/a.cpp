// author: naimulhaider
// task: Code Jam Qualification Round 1 - 2014 (Problem - A)
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

int main(){

    int kase;
    cin >> kase;
    int t = 1;
    while( kase-- ){
       int ans1;
       cin >> ans1;

       vector<int> row1, row2;
       for( int i =0; i<4;i++){
           for( int j=0;j<4;j++){
               int x;
               cin >> x;
               if( i==ans1-1) row1.push_back( x );
           }
       }

       int ans2;
       cin >> ans2;
       for( int i =0; i<4;i++){
           for( int j=0;j<4;j++){
               int x;
               cin >> x;
               if(i==ans2-1) row2.push_back(x);
           }
       }
    
       vector<int> equals;
       for( int i=0;i<row1.size();i++)
           for( int j=0;j<row2.size();j++)
               if( row1[i] == row2[j] )
                   equals.push_back( row1[i] );
        
       cout << "Case #" << t++ << ": " ;
       if( equals.size() == 1 ) cout << equals[0] << "\n";
       else if ( equals.size() > 1 ) cout << "Bad magician!\n";
       else {
           cout << "Volunteer cheated!\n";
       }

    }


    return 0;
}
