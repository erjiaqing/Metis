// 点双连通分量缩点 树形dp计数

#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 2e4 + 5;
const long long inf = 1e18;

struct edge{
	int v, w, r, uu, vv;
	bool flag;
	edge(int v = 0, int w = 0, int r = 0, bool flag = false, int uu = 0, int vv = 0) : v(v), w(w), r(r), flag(flag), uu(uu), vv(vv) {}
};
vector<edge> mp[maxn];
void add_edge(int u, int v, int w, int uu, int vv){
	mp[u].push_back(edge(v, w, mp[v].size(), false, uu, vv));
	mp[v].push_back(edge(u, w, mp[u].size() - 1, false, vv, uu));
}

int n, m, a[maxn], sz[maxn];
bool vist[maxn];

int scc, top, cnt;
int dfn[maxn], low[maxn], stck[maxn], bel[maxn];
bool inst[maxn];
void tarjan(int u){
	
	dfn[u] = low[u] = ++cnt;
	stck[++top] = u;
	inst[u] = true;
	
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		if(mp[u][l].flag) continue;
		mp[u][l].flag = mp[v][mp[u][l].r].flag = true;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(inst[v]) low[u] = min(low[u], dfn[v]);
	}
	
	if(dfn[u] == low[u]){
		++scc;
		int v;
		do{
			v = stck[top--];
			bel[v] = scc;
			inst[v] = false;
			++sz[scc];
		} while(v != u);
	}
}

int fa[maxn], rt[maxn];
void dfs(int u, int r){
	
	rt[u] = r;
	vist[u] = true;
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		if(vist[v]) continue;
		fa[v] = u;
		dfs(v, r);
		sz[u] += sz[v];
	}
}

// 在缩点建出的新图上dp 但把f记录在原图上

long long f[maxn];
void calc(int u, long long mid){
	
	vist[u] = true;
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		if(vist[v]) continue;
		calc(v, mid);
		long long w = 1LL * mp[u][l].w * sz[v] * (sz[rt[u]] - sz[v]);
		int uu = mp[u][l].uu;
		int vv = mp[u][l].vv;
		if(f[vv] + w <= mid) f[vv] += w;
		else f[uu] += w;
	}
}

bool check(long long mid){
	
	for(int i = n + 1; i <= scc; ++i) vist[i] = false;
	for(int i = 1; i <= n; ++i) f[i] = a[i];
	for(int i = n + 1; i <= scc; ++i){
		if(vist[i]) continue;
		calc(i, mid);
	}
	for(int i = 1; i <= n; ++i) if(f[i] > mid) return false;
	return true;
}

long long binary(long long left, long long rght){
	
	while(left < rght){
		long long mid = (left + rght) >> 1;
		if(check(mid)) rght = mid;
		else left = mid + 1;
	}
	return rght;
}

void solve(){
	
	scanf("%d%d", &n, &m);
	scc = n;
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= m; ++i){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w, u, v);
	}
	
	for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);
	for(int u = 1; u <= n; ++u){
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].v;
			if(bel[u] != bel[v]) add_edge(bel[u], bel[v], mp[u][l].w, u, v);
		}
	}
	for(int i = n + 1; i <= scc; ++i) if(!vist[i]) dfs(i, i);
	
	printf("%lld\n", binary(0, inf));
	top = cnt = 0;
	for(int i = 1; i <= n; ++i) dfn[i] = 0;
	for(int i = 1; i <= scc; ++i) mp[i].clear();
	for(int i = 1; i <= scc; ++i) sz[i] = 0;
	for(int i = 1; i <= scc; ++i) vist[i] = false;
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case %d: ", tt);
		solve();
	}

	return 0;
}
