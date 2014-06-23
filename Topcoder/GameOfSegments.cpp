#include<bits/stdc++.h>
using namespace std;

int memo[1010];
int nimber( int n ) {
    if( n == 0 || n == 1 ) return 0;
    if( memo[n] != -1 ) return memo[n];
    set<int> mex ;
    for( int i=0; i <= n-2; i++ ) {
        mex.insert( nimber( i ) ^ nimber( n - 2 - i ) );
    }
    for( int i=0; i <=n ; i++ ) if( mex.find(i) == mex.end() ) return memo[n] = i;
    return -1;
}

class GameOfSegments{
public:
    int winner(int N){

        memset( memo, -1, sizeof memo );
        int res = nimber( N );
        if( res ) return 1;
        return int( 2 );
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; verify_case(0, Arg1, winner(Arg0)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; verify_case(1, Arg1, winner(Arg0)); }
	void test_case_2() { int Arg0 = 15; int Arg1 = 2; verify_case(2, Arg1, winner(Arg0)); }
	void test_case_3() { int Arg0 = 191; int Arg1 = 2; verify_case(3, Arg1, winner(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    GameOfSegments ___test;
    ___test.run_test(-1);
}
// END CUT HERE
