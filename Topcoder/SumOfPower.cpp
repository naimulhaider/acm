#include<bits/stdc++.h>
using namespace std;
class SumOfPower{
public:
    int findSum(vector <int> array){

        int res = 0;
        for( int i=0 ; i <array.size() ; i++ ) {
            for( int j =0 ; j  < array.size(); j++ ) {
                if( j + i >= array.size() ) break;
                for( int k = j; k <= j + i; k++ ) {
                    res += array[k];
                }
            }
        }

        return int(res);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, findSum(Arg0)); }
	void test_case_1() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, findSum(Arg0)); }
	void test_case_2() { int Arr0[] = {3,14,15,92,65}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1323; verify_case(2, Arg1, findSum(Arg0)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1210; verify_case(3, Arg1, findSum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    SumOfPower ___test;
    ___test.run_test(-1);
}
// END CUT HERE
