#include <bits/stdc++.h>
using namespace std;
const int N = 4e3 + 5;
const int M = 2e6 + 5;
const long long INF = 1e18;
struct eglist{
	int tot_edge;
	int dstn[M], nxt[M], lst[N];
	long long cap[M], cost[M];
	void clear(){
		memset(lst, -1, sizeof lst);
		tot_edge = 0;
	}
	void _addEdge(int a, int b, long long c, long long d){
		dstn[tot_edge] = b;
		nxt[tot_edge] = lst[a];
		lst[a] = tot_edge;
		cost[tot_edge] = d;
		cap[tot_edge++] = c;
	}
	void add_edge(int a, int b, long long c, long long d){
		_addEdge(a, b, c, d);
		_addEdge(b, a, 0, -d);
	}
}e;
int st, ed, vist[N], cur[N];
long long tot_flow, tot_cost, dist[N], slack[N];
int modlable(){
	long long delta = INF;
	for(int i = 1; i <= ed; ++i){
		if(!vist[i] && slack[i] < delta)
			delta = slack[i];
		slack[i] = INF;
		cur[i] = e.lst[i];
	}
	if(delta == INF) return 1;
	for(int i = 1; i <= ed; ++i)
		if(vist[i])
			dist[i] += delta;
	return 0;
}
long long dfs(int x, long long flow){
	if(x == ed){
		tot_flow += flow;
		tot_cost += flow * (dist[st] - dist[ed]);
		return flow;
	}
	vist[x] = 1;
	long long left = flow;
	for(int i = cur[x]; ~i; i = e.nxt[i])
		if(e.cap[i] > 0 && !vist[e.dstn[i]]){
			int y = e.dstn[i];
			if(dist[y] + e.cost[i] == dist[x]){
				long long delta = dfs(y, min(left, e.cap[i]));
				e.cap[i] -= delta;
				e.cap[i ^ 1] += delta;
				left -= delta;
				if(!left) return flow;
			}else slack[y] = min(slack[y], dist[y] + e.cost[i] - dist[x]);
		}
	return flow - left;
}
void minCost(){
	tot_flow = 0, tot_cost = 0;
	fill(dist + 1, dist + 1 + ed, 0);
	for(int i = 1; i <= ed; ++i) cur[i] = e.lst[i];
	do{
		do{
			fill(vist + 1, vist + 1 + ed, 0);
		}while(dfs(st, INF));
	}while(!modlable());
}
int main(){
	e.clear(); minCost();
}
