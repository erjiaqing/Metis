#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int MAXN = 1e5 + 5;
const ull MAGIC = 999991;

int n, m, ques;
int ed[MAXN][2], d[MAXN], clr[MAXN];
map<ull, int> mp;

vector<int> edge[MAXN];
void add_edge(int u, int v) {
	
	edge[u].push_back(v);
	edge[v].push_back(u);
}

int ance[MAXN][20], dpth[MAXN];
int lca(int u, int v) {
	
	if(dpth[u] < dpth[v]) swap(u, v);
    int p = dpth[u] - dpth[v];
    for(int i = 0; i < 20; ++i)
        if(p & (1 << i)) u = ance[u][i];

    if(u == v) return u;
    for(int i = 19; i >= 0; --i) {
        if(ance[u][i] == ance[v][i]) continue;
        u = ance[u][i];
        v = ance[v][i];
    }
    return ance[u][0];
}

int dist(int u, int v) {
	
	int g = lca(u, v);
	return dpth[u] + dpth[v] - dpth[g] * 2;
}

void updata(int u, int c) {
	
	if(ed[c][0] == 0) {
		ed[c][0] = ed[c][1] = u;
		return;
	}
	int tmp = d[c], t1 = ed[c][0], t2 = ed[c][1];
	if(dist(u, ed[c][0]) > tmp) {
		tmp = dist(u, ed[c][0]);
		t1 = u;
		t2 = ed[c][0];
	}
	if(dist(u, ed[c][1]) > tmp) {
		tmp = dist(u, ed[c][1]);
		t1 = u;
		t2 = ed[c][1];
	}
	d[c] = tmp;
	ed[c][0] = t1;
	ed[c][1] = t2;
}

void dfs(int u, int fa) {
	
	dpth[u] = dpth[fa] + 1;
	ance[u][0] = fa;
	for(int i = 1; i < 20; ++i) ance[u][i] = ance[ance[u][i-1]][i-1];
	updata(u, clr[u]);
	
	for(int l = 0; l < edge[u].size(); ++l){
		int v = edge[u][l];
		if(v == fa) continue;
		dfs(v, u);
	}
}

char str[10000];
ull hsh() {
	
	ull rtn = 0;
	int l = strlen(str);
	for(int j = 0; j < l; ++j) rtn *= MAGIC, rtn += str[j];
	return rtn;
}

void work() {
	
	for(int i = 1; i <= n; ++i) {
		scanf("%s", str);
		ull h = hsh();
		if(mp.find(h) == mp.end()) ++m, mp[h] = m;
		clr[i] = mp[h];
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	
	dfs(1, 0);
	for(int i = 1; i <= ques; ++i) {
		int c[2];
		for(int j = 0; j < 2; ++j) {
			scanf("%s", str);
			ull h = hsh();
			c[j] = mp.find(h) == mp.end() ? 0 : mp[h];
		}
		if(1LL * c[0] * c[1] == 0LL) {
			puts("-1");
			continue;
		}
		int ans = 0;
		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
				ans = max(ans, dist(ed[c[0]][j], ed[c[1]][k]));
		printf("%d\n", ++ans);
	}
	
	for(int i = 1; i <= n; ++i) edge[i].clear();
	for(int i = 1; i <= n; ++i) ed[i][0] = ed[i][1] = 0;
	for(int i = 1; i <= n; ++i) d[i] = 0;
	mp.clear();
}

int main() {
	
	//freopen("E.txt", "r", stdin);
	
	while(scanf("%d%d", &n, &ques) == 2) work();

	return 0;
}
