// POJ 2449
/******************************************
K短路 用dijsktra+A*启发式搜索
当点v第K次出堆的时候，这时候求得的路径是k短路。
A*算法有一个启发式函数f(p)=g(p)+h(p), 即评估函数=当前值+当前位置到终点的最短距离
g(p):当前从s到p点所走的路径长度，h(p)就是点p到目的点t的最短距离。
f(p)就是当前路径从s走到p在从p到t的所走距离。
步骤：
1>求出h(p)。将有向边反向，求出目的点t到所有点的最短距离，用dijkstra算法
2>将原点s加入优先队列中
3>优先队列取出f(p)最小的一个点p
如果p==t,并且出来的次数恰好是k次，那么算法结束
否则，如果p出来的次数多余k次，就不用再进入队列中
否则遍历p相邻的边，加入优先队列中
注意:如果s==t，那么求得k短路应该变成k++;
******************************************/
#define MAXN 1005
#define MAXM 200100
struct Node{
       int v,c,nxt;
}Edge[MAXM];
int head[MAXN], tail[MAXN], h[MAXN];
struct Statement{
       int v,d,h;
       bool operator <( Statement a )const
       {    return a.d+a.h<d+h;   }
};
void addEdge( int u,int v,int c,int e ){
     Edge[e<<1].v=v; Edge[e<<1].c=c; Edge[e<<1].nxt=head[u]; head[u]=e<<1;
     Edge[e<<1|1].v=u; Edge[e<<1|1].c=c; Edge[e<<1|1].nxt=tail[v]; tail[v]=e<<1|1;
}

void Dijstra( int n,int s,int t ){
     bool vis[MAXN];
     memset( vis,0,sizeof(vis) );
     memset( h,0x7F,sizeof(h) );
     h[t]=0;
     for( int i=1;i<=n;i++ ){
          int min=0x7FFF;
          int k=-1;
          for( int j=1;j<=n;j++ ){
               if( vis[j]==false && min>h[j] )
                   min=h[j],k=j;
          }
          if( k==-1 )break;
          vis[k]=true;
          for( int temp=tail[k];temp!=-1;temp=Edge[temp].nxt ){
               int v=Edge[temp].v;
               if( h[v]>h[k]+Edge[temp].c )
                   h[v]=h[k]+Edge[temp].c;
          }
     }
}
int Astar_Kth( int n,int s,int t,int K ){
    Statement cur,nxt;
    //priority_queue<Q>q;
    priority_queue<Statement>FstQ;
    int cnt[MAXN];
    memset( cnt,0,sizeof(cnt) );
    cur.v=s; cur.d=0; cur.h=h[s];
    FstQ.push(cur);
    while( !FstQ.empty() ){
           cur=FstQ.top();
           FstQ.pop();
           cnt[cur.v]++;
           if( cnt[cur.v]>K ) continue;
           if( cnt[t]==K )return cur.d;
           for( int temp=head[cur.v];temp!=-1;temp=Edge[temp].nxt ){
                int v=Edge[temp].v;
                nxt.d=cur.d+Edge[temp].c;
                nxt.v=v;
                nxt.h=h[v];
                FstQ.push(nxt);
           }
    }
    return -1;
}
int main()
{
    int n,m;
    while( scanf( "%d %d",&n,&m )!=EOF ){
           int u,v,c;
           memset( head,0xFF,sizeof(head) );
           memset( tail,0xFF,sizeof(tail) );
           for( int i=0;i<m;i++ ){
                scanf( "%d %d %d",&u,&v,&c );
                addEdge( u,v,c,i );
           }
           int s,t,k;
           scanf( "%d %d %d",&s,&t,&k );
           if( s==t ) k++;
           Dijstra( n,s,t );
           printf( "%d\n",Astar_Kth( n,s,t,k ) );
    }
    return 0;
}