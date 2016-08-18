#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 5;

vector<int> mp[maxn];
void add_edge(int u, int v){
	mp[u].push_back(v);
	mp[v].push_back(u);
}

int n, sz[maxn], ans;
bool flag[maxn];

void dfs(int u, int fa){
	
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l];
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
	if(sz[u] == 0) sz[u] = 1, ++ans;
	if(sz[u] >= 2) sz[u] = 0, --ans;
}

int main(){
	
	scanf("%d", &n);
	for(int i = 1; i < n; ++i){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	
	dfs(1, 0);
	printf("%d\n", ans);

	return 0;
}
