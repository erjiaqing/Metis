#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 2e4 + 5;
const int inf = 1e9;

struct edge{
	int v, flow, r;
	edge(int v = 0, int flow = 0, int r = 0) : v(v), r(r), flow(flow) {}
};
vector<edge> mp[maxn];
void add_edge(int u, int v, int flow){
	mp[u].push_back(edge(v, flow, mp[v].size()));
	mp[v].push_back(edge(u, 0, mp[u].size() - 1));
}

int n, S, T, x[maxn], a[maxn], b[maxn], w[105][105], sx[105], sy[105], maxx, ans;
char str[maxn];

int dd[maxn], v[maxn];
int sap(int u, int flow){
	
	if(u == T) return flow;
	int now = 0;
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		if(mp[u][l].flow > 0 && dd[u] == dd[v] + 1){
			int t = sap(v, min(flow - now, mp[u][l].flow));
			mp[u][l].flow -= t;
			mp[v][mp[u][l].r].flow += t;
			now += t;
			if(now == flow) return now;
			if(dd[S] >= T) return now;
		}
	}
	
	--v[dd[u]];
	if(!v[dd[u]]) dd[S] = T;
	++dd[u];
	++v[dd[u]];
	return now;
}

void work(){
	
	scanf("%d", &n);
	scanf("%s", str);
	for(int i = 0; i < n; ++i) x[i+1] = str[i] - '0';
	for(int i = 0; i <= 9; ++i) scanf("%d%d", &a[i], &b[i]);
	maxx = ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j){
			scanf("%d", &w[i][j]);
			sx[i] += w[i][j];
			sy[j] += w[i][j];
			maxx = max(maxx, w[i][j]);
			ans += w[i][j];
		}
	
	S = n + n * n + 10 + 1, T = S + 1;
	for(int i = 1; i <= n; ++i){
		add_edge(S, i, a[x[i]] + maxx);
		add_edge(i, T, sx[i] + sy[i] + maxx);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j){
			int k = j + n * i;
			add_edge(S, k, maxx);
			add_edge(k, T, maxx - w[i][j]);
			add_edge(k, i, inf);
			add_edge(k, j, inf);
		}
	for(int i = 0; i <= 9; ++i){
		int k = n * n + n + i + 1;
		add_edge(S, k, b[i] - a[i] + maxx);
		add_edge(k, T, maxx);
		for(int j = 1; j <= n; ++j) if(x[j] == i) add_edge(k, j, inf);
	}
	
	while(dd[S] < T) ans -= sap(S, inf);
	ans += maxx * (S - 1);
	printf("%d\n", ans);
	
	for(int i = 0; i <= T; ++i) mp[i].clear();
	for(int i = 0; i <= T; ++i) dd[i] = v[i] = 0;
	for(int i = 0; i <= n; ++i) sx[i] = sy[i] = 0;
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case #%d: ", tt);
		work();
	}

	return 0;
}
