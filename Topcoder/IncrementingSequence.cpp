#include<bits/stdc++.h>
using namespace std;
class IncrementingSequence{
public:
    string canItBeDone(int k, vector <int> A){

        sort( A.begin() , A.end() );
        bool mark[100];
        memset( mark , false, sizeof mark );
        bool possible = 1;

        for( int i = 1;  i<= A.size(); i++ ) {

            bool found = 0;
            // try to find
            for( int j=0; j<A.size(); j++ ) {
                if( mark[j] ) continue;
                if( A[j] == i ) {
                    mark[j] = 1;
                    found = 1;
                    break;
                }
            }

            if( found ) continue;
            bool flag = 0;

            for( int j=A.size()-1 ; j >=0 ; j-- ) {
                if( mark[j] ) continue;
                int x = i - A[j];
                x /= k;
                if( x > 0 && (A[j]+(x*k)==i) ) {
                    mark[j] = 1;
                    flag=1;
                    break;
                }
            }
            if( flag ) continue;

            possible = 0;
            break;
        }


        if( !possible ) return "IMPOSSIBLE";

        return string("POSSIBLE");
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {1,2,4,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "POSSIBLE"; verify_case(0, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(1, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arr1[] = {1,1,1,1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "POSSIBLE"; verify_case(2, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; int Arr1[] = {5,3,3,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(3, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 9; int Arr1[] = {1,2,3,1,4,5,6,7,9,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "POSSIBLE"; verify_case(4, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 2; int Arr1[] = {1,1,1,1,1,1,2,2,2,2,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "POSSIBLE"; verify_case(5, Arg2, canItBeDone(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 1; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "POSSIBLE"; verify_case(6, Arg2, canItBeDone(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    IncrementingSequence ___test;
    ___test.run_test(-1);
}
// END CUT HERE
