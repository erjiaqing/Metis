/******************************
  询问树上有多少对pair距离不超过k
  每次找重心 经过一些容斥
  求经过重心与不经过重心pair数
 ******************************/

#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e4 + 5;

vector<pii> mp[maxn];
void add_edge(int u, int v, int d){
	mp[u].push_back(make_pair(v, d));
	mp[v].push_back(make_pair(u, d));
}

int n, ans, limit, gra, min_maxx;
int sz[maxn];
bool flag[maxn];
vector<int> vec;
void get_gra(int u, int fa, int nowsize){
	sz[u] = 1;
	int maxx = 0;
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].first;
		if(v == fa || flag[v]) continue;
		get_gra(v, u, nowsize);
		sz[u] += sz[v];
		maxx = max(maxx, sz[v]);
	}
	maxx = max(maxx, nowsize - sz[u]);
	if(maxx < min_maxx) min_maxx = maxx, gra = u;
}
void get_dist(int u, int fa, int d){
	vec.push_back(d);
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].first;
		if(v == fa || flag[v]) continue;
		get_dist(v, u, d + mp[u][l].second);
	}
}
int calc(int u, int delta){
	int rtn = 0;
	vec.clear();
	get_dist(u, 0, 0);
	sort(vec.begin(), vec.end());
	int m = vec.size();
	for(int i = 0, j = m - 1; i < j; ++i){
		while(i < j && vec[i] + vec[j] + delta > limit) --j;
		rtn += j - i;
	}
	return rtn;
}
void devide(int u, int nowsize){
	min_maxx = maxn;
	get_gra(u, 0, nowsize);
	flag[u=gra] = true;
	ans += calc(u, 0);
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].first;
		if(flag[v]) continue;
		ans -= calc(v, mp[u][l].second * 2);
		devide(v, sz[v] > sz[u] ? nowsize - sz[u] : sz[v]);
	}
}

void init(){
	ans = 0;
	for(int i = 1; i <= n; ++i) mp[i].clear();
	memset(flag, 0, sizeof flag);
}
void work(){
	
	init();
	for(int i = 1; i < n; ++i){
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		add_edge(u, v, d);
	}
	devide(1, n);
	printf("%d\n", ans);
}

int main(){
	while(true){
		scanf("%d%d", &n, &limit);
		if(n == 0) break;
		work();
	}
	return 0;
}
