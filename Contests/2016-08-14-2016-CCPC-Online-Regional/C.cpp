#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5 + 5;

vector<pii> mp[maxn];
void add_edge(int u, int v, int d){
	mp[u].push_back(make_pair(v, d));
	mp[v].push_back(make_pair(u, d));
}

int n;
int val[maxn];
int f[maxn], g[maxn], ans[maxn];
int h[maxn], fir[maxn], sec[maxn];

void calc(int u, int fa){
	
	g[u] = val[u];
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].first;
		int d = mp[u][l].second;
		if(v == fa) continue;
		calc(v, u);
		h[v] = f[v] - d - (g[v] - 2 * d > 0 ? g[v] - 2 * d : 0);
		g[u] += (g[v] - 2 * d > 0 ? g[v] - 2 * d : 0);
		if(h[v] > fir[u]) sec[u] = fir[u], fir[u] = h[v];
		else if(h[v] > sec[u]) sec[u] = h[v];
	}
	f[u] = g[u] + fir[u];
}

void set_root(int u, int fa){
	
	ans[u] = f[u];
	int rec_fu = f[u], rec_gu = g[u], rec_hu = h[u];
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].first;
		int d = mp[u][l].second;
		if(v == fa)	continue;
		int rec_fv = f[v], rec_gv = g[v], rec_hv = h[v];
		int rec_fir = fir[v], rec_sec = sec[v];
		
		g[u] -= (g[v] - 2 * d > 0 ? g[v] - 2 * d : 0);
		g[v] += (g[u] - 2 * d > 0 ? g[u] - 2 * d : 0);
		if(h[v] == fir[u]) f[u] = g[u] + sec[u];
		else f[u] = g[u] + fir[u];
		h[u] = f[u] - d - (g[u] - 2 * d > 0 ? g[u] - 2 * d : 0);
		if(h[u] > fir[v]) sec[v] = fir[v], fir[v] = h[u];
		else if(h[u] > sec[v]) sec[v] = h[u];
		f[v] = g[v] + fir[v];
		set_root(v, u);
		
		f[u] = rec_fu, g[u] = rec_gu, h[u] = rec_hu;
		f[v] = rec_fv, g[v] = rec_gv, h[v] = rec_hv;
		fir[v] = rec_fir, sec[v] = rec_sec;
	}
}

void work(){
	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
	for(int i = 1; i < n; ++i){
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		add_edge(u, v, d);
	}
	
	calc(1, 0);
	//for(int i = 1; i <= n; ++i) printf("%d : %d %d\n", i, f[i], g[i]);
	set_root(1, 0);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	
	for(int i = 1; i <= n; ++i) mp[i].clear();
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	memset(fir, 0, sizeof fir);
	memset(sec, 0, sizeof sec);
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int cs = 1; cs <= t; ++cs){
		printf("Case #%d:\n", cs);
		work();
	}

	return 0;
}
