
// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#define FOR(I,A,B) for(int I = (A); I < (B); ++I)
#define REP(I,N)   FOR(I,0,N)
#define ALL(A)     (A).begin(), (A).end()

using namespace std;

// }}}

class HouseBuilding
{
public:
	int getMinimum(vector <string> area)
	{
        vector<int> v;
        for ( int i=0;i<area.size();i++){
            for( int j=0;j<area[i].size();j++){
                v.push_back ( area[i][j] - '0' );
            }
        }
        int res  = 1000000000;
        for( int i=0; i<10; i++ ) {
            int cost = 0;
            for ( int j=0;j<int(v.size());j++){
                if ( v[j] < i ) {
                    cost += ( abs(i-v[j]) );
                    continue;
                }
                if ( abs(v[j]-i) <= 1 ) continue;
                cost += abs( i-v[j] ) - 1;
            }
            res = min ( res , cost );
        }
        
		return int(res);
	}
};

