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


vector <int> List;  // saves the List
int listSize,N=100101;   // saves the size of List
bool sts[100101];
vector <int> pr;
void prime()
{
    int sqr=sqrt(N);
    for(int i=3; i<=sqr; i+=2)
        if(!sts[i])
            for(int j=i*i; j<=N; j+=(2*i) )
                sts[j]=true;
    pr.push_back(2);
    for(int i=3; i<=N; i+=2)
        if(!sts[i])
            pr.push_back(i);

}
void primeFactorize( int n )
{
    listSize = 0;   // Initially the List is empty, we denote that size = 0
    int sqrtN = int( sqrt(n) ); // find the sqrt of the number
    for( int i = 0; pr[i] <= sqrtN; i++ )   // we check up to the sqrt
    {
        if( n % pr[i] == 0 )   // n is multiple of prime[i]
        {
            // So, we continue dividing n by prime[i] as long as possible
            while( n % pr[i] == 0 )
            {
                n /= pr[i]; // we have divided n by prime[i]
                List.pb(pr[i]); // added the ith prime in the list
                listSize++; // added a prime, so, size should be increased
            }
            // we can add some optimization by updating sqrtN here, since n
            // is decreased. think why it's important and how it can be added
        }
    }
    if( n > 1 )
    {
        // n is greater than 1, so we are sure that this n is a prime
        List.pb(n); // added n (the prime) in the list
        listSize++; // increased the size of the list
    }
}
int a[hi],b[hi],n,x,ar[hi];
const LL md = 1000000007;
int main()
{

#if defined( rifat_pc )
    //Write("out.txt");
    Read("in.txt");
#endif
    prime();

    int tst,cnt=1;
    cin>>tst;
    while(tst--)
    {
        scanf("%d%d",&n,&x);
        rp(i,n)scanf("%d",&ar[i]);
        ms(a,0);
        ms(b,0);
        rp(i,n)
        {

            ar[i]=x-ar[i];
            if(ar[i])
            {
                primeFactorize(ar[i]);
                rp(i,List.size())a[List[i]]++;
                List.clear();
            }
            else a[0]++;
        }

        primeFactorize(x);
        rp(i,List.size())b[List[i]]+=n;
        List.clear();

        rp(i,hi)
        {
            int mn = min(a[i],b[i]);
            a[i]-=mn;
            b[i]-=mn;
        }

        LL ans1 =1,ans2=1;

        rp(i,hi)
        {

            while(a[i])
            {
                a[i]--;
                ans1*=(LL)i;
                ans1%=md;
            }
        }

        rp(i,hi)
        {
            while(b[i])
            {
                b[i]--;
                ans2*=(LL)i;
                ans2%=md;
            }
        }
        printf("Case %d: ",cnt++);
        //if(!ok1)ans1=0;
        //if(!ok2)ans2=0;
        if(ans1)
        {
            //LL gcd = __gcd(ans1,ans2);
            //ans1/=gcd;
            //ans2/=gcd;
            if(ans1==1 && ans2==1)printf("1\n");
            else printf("%lld/%lld\n",ans1,ans2);
        }
        else printf("0\n");
    }


    return 0;
}
