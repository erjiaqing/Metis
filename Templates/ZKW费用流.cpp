#include <bits/stdc++.h>
using namespace std;

const int N = 4e3 + 5;
const int M = 2e6 + 5;
const long long INF = 1e18;

struct eglist{
	int sum;
	int other[M], succ[M], last[N];
	long long cap[M], cost[M];
	void clear(){
		memset(last, -1, sizeof last);
		sum = 0;
	}
	void _addEdge(int a, int b, long long c, long long d){
		other[sum] = b;
		succ[sum] = last[a];
		last[a] = sum;
		cost[sum] = d;
		cap[sum++] = c;
	}
	void add_edge(int a, int b, long long c, long long d){
		_addEdge(a, b, c, d);
		_addEdge(b, a, 0, -d);
	}
}e;

int st, ed;
long long tot_flow, tot_cost;
long long dist[N], slack[N];
int vist[N], cur[N];

int modlable(){
	long long delta = INF;
	for(int i = 1; i <= ed; ++i){
		if(!vist[i] && slack[i] < delta)
			delta = slack[i];
		slack[i] = INF;
		cur[i] = e.last[i];
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
	for(int i = cur[x]; ~i; i = e.succ[i])
		if(e.cap[i] > 0 && !vist[e.other[i]]){
			int y = e.other[i];
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
	for(int i = 1; i <= ed; ++i) cur[i] = e.last[i];
	do{
		do{
			fill(vist + 1, vist + 1 + ed, 0);
		}while(dfs(st, INF));
	}while(!modlable());
}

int n, m, q, k;
long long r, t;

int main(){
	
	e.clear();
	scanf("%d%d%I64d%I64d%d", &n, &m, &r, &t, &q);
	k = min(1LL * m, t / r);
	st = n + n + m + 1;
	ed = n + n + m + 2;
	for(int i = 1; i <= n; ++i) e.add_edge(st, i, m, 0);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= k; ++j)
			e.add_edge(i, n + i, 1, r * j);
	for(int i = 1; i <= m; ++i) e.add_edge(n + n + i, ed, 1, 0);
	for(int qq = 1, i, j; qq <= q; ++qq){
		scanf("%d%d", &i, &j);
		e.add_edge(n + i, n + n + j, 1, 0);
	}
	minCost();
	printf("%I64d %I64d\n", tot_flow, tot_cost);
	for(int i = 1; i <= n; ++i){
		long long tmp = 0;
		int u = n + i;
		for(int l = e.last[u]; ~l; l = e.succ[l]){
			int j = e.other[l] - n - n;
			if(j <= 0) continue;
			if(e.cap[l]) continue;
			printf("%d %d %I64d\n", i, j, tmp);
			tmp += r;
		}
	}

	return 0;
}
