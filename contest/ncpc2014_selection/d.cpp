//#include <bits/stdc++.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <numeric>
#include <stack>
#include <functional>
#include <bitset>
#include <iomanip>

#include <ctime>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <cstring>
#include <cstdlib>

#define _ ios_base::sync_with_stdio(0);
#define ms(ar,val) memset(ar,val,sizeof(ar))
#define all(s) (s).begin(),(s).end()
#define rp1(i,s,n) for(int i=s;i<n;++i)
#define rp(i,n) rp1(i,0,n)
#define abs(x) (((x)< 0) ? (-(x)) : (x))
#define pb push_back
#define LL long long
#define Read(x) freopen(x,"r",stdin)
#define Write(x) freopen(x,"w",stdout)
#define st(N,pos) (sts[N]=sts[N] | (1<<pos))
#define check(N,pos) ((bool)(sts[N] & (1<<pos)))
#define i_s(num)  static_cast<ostringstream*>( &(ostringstream() << num) )->str();
#define __lcm(a,b)  ((a*b)/(__gcd(a,b)))
#define inf INT_MAX
#define mp(a,b) make_pair(a,b)
#define pii pair<int,int>
#define PQ priority_queue
#define GSORT(x) sort(ALL(x), greater<typeof(*((x).begin()))>())
#define UNIQUE(v) Sort(v); (v).resize(unique(ALL(v)) - (v).begin())
#define F first
#define S second
#define bits(n) __builtin_popcount(n)
#define EPS 1e-11
#define hi 100010

///int month[]={31,28,31,30,31,30,31,31,30,31,30,31}; //month

using namespace std;

const LL md = 1000000007L;

LL ar[hi];
int main()
{
     #if defined( rifat_pc )
        //Write("out.txt");
        Read("in.txt");
    #endif
    LL n,x;
    int tst,cnt=1;
    cin>>tst;
    while(tst--){
        scanf("%I64d %I64d ",&n,&x);
        rp(i,n)scanf("%I64d",&ar[i]);
        LL ans1 = 1;
        LL ans2 = 1;
        rp(i,n){
            ans2*=x;
            ans2%=md;
        }
        rp(i,n){
            ar[i]=x-ar[i];
            ans1*=ar[i];
            ans1%=md;
        }
        printf("Case %d: ",cnt++);
        if(ans1){
            LL gcd = __gcd(ans1,ans2);
            ans2/=gcd;
            ans1/=gcd;
            if(ans1 == 1  && ans2==1){

                printf("1\n");
            }else printf("%I64d/%I64d\n",ans1,ans2);

        }else {
            printf("0\n");
        }

    }

    return 0;
}




