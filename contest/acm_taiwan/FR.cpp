#include<bits/stdc++.h>
using namespace std;

const int INF = 1000000007;

const int MAXN = 2010; //maximum number of nodes
const int MAXE = 5010; //maximum number of edges

struct Edge
{
    int u,v,nxt;
    int cap;
} edge[MAXE*2];

int cnt,head[MAXN],dep[MAXN];
int src,snk;

void init( int _src, int _snk )
{
    cnt=0;
    memset(head,-1,sizeof(head));
    src=_src, snk=_snk;
}
void add(int cu,int cv,int cw)
{
    edge[cnt].u=cu;
    edge[cnt].v=cv;
    edge[cnt].cap=cw;
    edge[cnt].nxt=head[cu];
    head[cu]=cnt++;
    edge[cnt].u=cv;
    edge[cnt].v=cu;
    edge[cnt].cap=0;
    edge[cnt].nxt=head[cv];
    head[cv]=cnt++;
}
int BFS()
{
    queue<int> q;
    while(!q.empty()) q.pop();
    memset(dep,-1,sizeof(dep));
    dep[src]=0;
    q.push(src);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i=head[u]; i!=-1; i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(edge[i].cap>0 && dep[v]==-1)
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[snk]!=-1;
}

int DFS(int u,int fl)
{
    if(u==snk) return fl;
    int ret;
    for(int i=head[u]; i!=-1; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(edge[i].cap>0 && dep[v]==dep[u]+1 &&
                (ret=DFS(v,min(fl,edge[i].cap))))
        {
            edge[i].cap-=ret;
            edge[i^1].cap+=ret;
            return ret;
        }
    }
    dep[u]=-1;
    return 0;
}

int Dinic()
{
    int ret = 0, delta;
    while(BFS())
    {
        while(1)
        {
            delta=DFS(src,INF);
            if(delta==0) break;
            ret+=delta;
        }
    }
    return ret;
}

int deg[2010];

int main() {

    int n , c;
    while ( scanf( "%d %d", &n, &c ) == 2 ) {
        init(1100, 1200);
        memset(deg,0,sizeof deg);
        for(int i=0;i<n-1;i++){
            int u, v, w;
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
            deg[u]++;
            deg[v]++;
        }
        add( 1100, c, INF );
        for(int i=1;i<=n;i++) {
            if(i!=c&&deg[i]==1) {
//                cout<<i<<endl;
                add(i,1200,INF);
            }
        }
        printf("%d\n",Dinic());
    }

    return 0;
}

/*

3 1
2 1 5
1 3 4
7 7
7 6 10
7 5 10
6 4 1
6 3 1
5 2 1
5 1 2

*/
