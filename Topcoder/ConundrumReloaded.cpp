#include<bits/stdc++.h>
using namespace std;

const int INF = 1000000007;

int n;
vector<int> v;
int memo[2][51][2];

int rec( int l, int i , int shudbe ) {

    if( i == n-1 ) {
        if( shudbe == l ) return 0;
        return INF;
    }

    if( memo[l][i][shudbe] != -1 ) return memo[l][i][shudbe];

    int res = INF;

    if(shudbe) res = min( res , rec( l, i+1, v[i] ) );
    else res = min( res, 1+rec(l,i+1,!v[i]) );

    return memo[l][i][shudbe] = res;

}

class ConundrumReloaded{
public:
    int minimumLiars(string answers){
        v.clear();
        n = answers.size();

        for( int i=0 ; i<answers.size(); i++ ) {
            if( answers[i] == 'L' ) v.push_back(0);
            else v.push_back(1);
        }

        memset(memo, -1, sizeof memo );
        int res = INF;
        res = min( res , rec( 0, 0, !v[n-1] ) );
        res = min( res , rec( 1, 0, v[n-1] ) );

        if( res == INF ) return -1;
        return int( res );
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "LLH"; int Arg1 = 1; verify_case(0, Arg1, minimumLiars(Arg0)); }
	void test_case_1() { string Arg0 = "?????"; int Arg1 = 0; verify_case(1, Arg1, minimumLiars(Arg0)); }
	void test_case_2() { string Arg0 = "LHLH?"; int Arg1 = 2; verify_case(2, Arg1, minimumLiars(Arg0)); }
	void test_case_3() { string Arg0 = "??LLLLLL??"; int Arg1 = 3; verify_case(3, Arg1, minimumLiars(Arg0)); }
	void test_case_4() { string Arg0 = "LLL"; int Arg1 = -1; verify_case(4, Arg1, minimumLiars(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ConundrumReloaded ___test;
    ___test.run_test(-1);
}
// END CUT HERE
