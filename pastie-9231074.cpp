#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<cctype>
#include<cstdio>
#include<string>
#include<sstream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<iterator>
#include<iostream>
#include<algorithm>
#include<cassert>
#include<ctime>

using namespace std;

#pragma comment(linker,"/STACK:16777216")
#pragma warning(disable:4786)

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define myabs(a) ((a)<0?(-(a)):(a))
#define pi acos(-1.0)
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a) memset(a,-1,sizeof(a))
#define pb push_back
#define all(a) a.begin(),a.end()
#define ff first
#define ss second
#define eps 1e-9
#define root 1
#define lft 2*idx
#define rgt 2*idx+1
#define cllft lft,st,mid,s,e
#define clrgt rgt,mid+1,ed,s,e
#define inf (1<<29)
#define i64 long long
#define MX 105
#define MAX_LIMIT 1000000000
#define MOD 1000000007

typedef pair<int,int> pii;

int w[MX][MX],n,col[MX],rcol[MX];

struct matrix{
    i64 mat[MX][MX];
    matrix operator *(const matrix &a){
        matrix ret;
        int i,j,k;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                ret.mat[i][j]=0;
                for(k=0;k<n;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+mat[i][k]*(i64)a.mat[k][j])%MOD;
                }
            }
        }
        return ret;
    }
}m[12],mm;

void warshall(){
    int i,j,k;
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
            }
        }
    }
}

void build_matrices(int r){
    int i,j,k;
    for(k=1;k<=r;k++){
        CLR(m[k].mat);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i==j || w[i][j]==k)m[k].mat[i][j]=1;
            }
        }
    }
    mm=m[r];
    for(i=r-1;i>=1;i--)mm=mm*m[i];
}

void find_color(int tm,int r){
    int x=tm/r,y=tm%r,i,j;

    matrix res;
    CLR(res.mat);
    for(i=0;i<n;i++)res.mat[i][i]=1;

    for(i=y;i>=1;i--)res=res*m[i];

    while(x){
        if(x&1)res=res*mm;
        mm=mm*mm;
        x>>=1;
    }

//		 for( int i=0; i<n; i++ ) {
//            for( int j=0; j<n; j++ ) {
//                cout << res.mat[i][j] << " ";
//            }
//            cout << endl;
//        }

    for(i=0;i<n;i++){
        rcol[i]=0;
        for(j=0;j<n;j++){
            rcol[i]=(rcol[i]+res.mat[i][j]*(i64)col[j])%MOD;
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);

	double st = clock();


	int cs,t=1,i,j,m,r,tm,x,y;
	scanf("%d",&cs);
	while(cs--){

		scanf("%d %d %d %d",&n,&m,&r,&tm);

		for(i=0;i<n;i++)scanf("%d",&col[i]);

		memset(w,3,sizeof(w));
		while(m--){
		    scanf("%d %d",&x,&y);
		    w[x][y]=w[y][x]=1;
		}
		//printf("1");
		warshall();

        //printf("2");
		build_matrices(r);
        //printf("3");
		find_color(tm,r);
        //printf("4");
		printf("Case %d:",t++);
		for(i=0;i<n;i++){
		    printf(" %d",rcol[i]);
		    assert(rcol[i]>=0 && rcol[i]<MOD);
		}
		puts("");
	}

	double en = clock();
	fprintf(stderr, "Time = %f\n", (en-st)/CLOCKS_PER_SEC);
	return 0;
}


