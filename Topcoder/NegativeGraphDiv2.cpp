#include<bits/stdc++.h>
using namespace std;

const long long INF = 1000000007;

#define M 55
vector<int> edges[M], weights[M];
int n;

struct data{
    int node , strength;
    long long cost;
    data( int a , long long b, int c ) {
        node = a, cost = b , strength = c;
    }
};

long long solve( int charges ) {

    queue<data> q ;
    q.push( data(1,0LL,charges) );
    long long memo[M];
    for( int i=0 ; i < M; i++ ) memo[i] = INF;
    memo[1] = 0;

    while( !q.empty() ) {
        data u = q.front();
        q.pop();
//        if( u.node == n && u.strength == 0  ) return u.cost;
        for( int i=0 ; i < edges[ u.node ].size(); i++ ) {
            int uu = u.node , vv = edges[u.node][i];
            if( memo[vv] > u.cost + weights[uu][i] ) {
                memo[vv] = u.cost + weights[uu][i];
                q.push( data(vv, memo[vv] , u.strength) );
            }
            if( u.strength && ( memo[vv] > u.cost + (-weights[uu][i]) )  ) {
                memo[vv] = u.cost + (-weights[uu][i]);
                q.push( data( vv, memo[vv] , u.strength-1 ) );
            }
        }
    }

    return memo[n];

}

class NegativeGraphDiv2{
public:
    long long findMin(int N, vector <int> s, vector <int> t, vector <int> weight, int charges){

//        priority_queue<data> q;
//        q.push( data(0,4,0) );
//        q.push( data(0,1,0) );
//        q.push( data(0,6,0) );
//        q.push( data(0,34,0) );
//        q.push( data(0,77,0) );
//        q.push( data(0,2,0) );
//
//        while( !q.empty() ) {
//            data u = q.top();
//            q.pop();
//            cout << u.cost << endl;
//        }

        n = N;

        for( int i= 0; i < M; i++ ) {
            edges[i].clear();
            weights[i].clear();
        }

        for( int i=0 ; i < s.size(); i++ ) {
                edges[ s[i] ] . push_back ( t[i] );
                weights[ s[i] ]. push_back( weight[i] );
        }

        long long res = solve(charges);
        return res;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {1,1,2,2,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,1,3,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,5,1,10,1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; long long Arg5 = -9LL; verify_case(0, Arg5, findMin(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 1; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {100}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1000; long long Arg5 = -100000LL; verify_case(1, Arg5, findMin(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 2; int Arr1[] = {1,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6,1,4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; long long Arg5 = -9LL; verify_case(2, Arg5, findMin(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 2; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {98765}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 100; long long Arg5 = -98765LL; verify_case(3, Arg5, findMin(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    NegativeGraphDiv2 ___test;
    ___test.run_test(-1);
}
// END CUT HERE
