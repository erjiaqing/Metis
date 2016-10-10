// POJ 2449
/******************************************
描述一下怎样用启发式搜索来解决K短路。
A*的基础公式：f(x)=g(x)+h(x)
其中g(x)为s到x已有代价，h(x)为x到t最短路
每次取出队头的f(x)最小的节点对其他节点进行拓展
对当前节点的拓展次数++
若当前节点的拓展次数超过K，则不进行拓展
若对t节点的拓展次数恰好为K，则找到答案
对当前节点的拓展次数即为到当前节点的第几短路
找到需要节点的K短路后，返回g(t)即可
******************************************/

#include<iostream>
#include<cstdio>
#include<queue>
#define MAXN 1005
#define MAXM 200100
using namespace std;

struct Node{
       int v,c,nxt;
}Edge[MAXM];

int head[MAXN];
int tail[MAXN];
int h[MAXN];

struct Statement
{
       int v,d,h;
       bool operator <( Statement a )const
       {    return a.d+a.h<d+h;   }
};

void addEdge( int u,int v,int c,int e )
{
     Edge[e<<1].v=v;
     Edge[e<<1].c=c;
     Edge[e<<1].nxt=head[u];
     head[u]=e<<1;
     
     Edge[e<<1|1].v=u;
     Edge[e<<1|1].c=c;
     Edge[e<<1|1].nxt=tail[v];
     tail[v]=e<<1|1;
     return ;
}

void Dijstra( int n,int s,int t )
{
     bool vis[MAXN];
     memset( vis,0,sizeof(vis) );
     memset( h,0x7F,sizeof(h) );
     h[t]=0;
     for( int i=1;i<=n;i++ )
     {
          int min=0x7FFF;
          int k=-1;
          for( int j=1;j<=n;j++ )
          {
               if( vis[j]==false && min>h[j] )
                   min=h[j],k=j;
          }
          if( k==-1 )break;
          vis[k]=true;
          for( int temp=tail[k];temp!=-1;temp=Edge[temp].nxt )
          {
               int v=Edge[temp].v;
               if( h[v]>h[k]+Edge[temp].c )
                   h[v]=h[k]+Edge[temp].c;
          }
     }
}

int Astar_Kth( int n,int s,int t,int K )
{
    Statement cur,nxt;
    //priority_queue<Q>q;
    priority_queue<Statement>FstQ;
    
    int cnt[MAXN];
    memset( cnt,0,sizeof(cnt) );
    cur.v=s;
    cur.d=0;
    cur.h=h[s];
    
    FstQ.push(cur);
    
    while( !FstQ.empty() )
    {
           cur=FstQ.top();
           FstQ.pop();
           
           cnt[cur.v]++;
           if( cnt[cur.v]>K ) continue;
           if( cnt[t]==K )return cur.d;
           
           for( int temp=head[cur.v];temp!=-1;temp=Edge[temp].nxt )
           {
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
    while( scanf( "%d %d",&n,&m )!=EOF )
    {
           int u,v,c;
           memset( head,0xFF,sizeof(head) );
           memset( tail,0xFF,sizeof(tail) );
           
           for( int i=0;i<m;i++ )
           {
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
