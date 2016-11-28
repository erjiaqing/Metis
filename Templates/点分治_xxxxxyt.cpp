// POJ 1741
/*询问树上有多少对pair距离不超过k
 每次找重心 经过一些容斥
 求经过重心与不经过重心pair数*/
const int maxn = 1e4 + 5;
vector<pii> edge[maxn];
void add_edge(int u, int v, int d){}
int n, ans, limit, gra, min_maxx, sz[maxn];
bool flag[maxn];
vector<int> vec;
void get_gra(int u, int fa, int nowsize){
	sz[u] = 1; int maxx = 0;
	for(int l = 0; l < edge[u].size(); ++l){
		int v = edge[u][l].first;
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
	for(int l = 0; l < edge[u].size(); ++l){
		int v = edge[u][l].first;
		if(v == fa || flag[v]) continue;
		get_dist(v, u, d + edge[u][l].second);
	}
}
int calc(int u, int delta){
	int rtn = 0; vec.clear();
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
	ans += calc(u, 0); // 加上经过重心的答案
	for(int l = 0; l < edge[u].size(); ++l){ // 容斥
		int v = edge[u][l].first;
		if(flag[v]) continue;
		ans -= calc(v, edge[u][l].second * 2);
		devide(v, sz[v] > sz[u] ? nowsize - sz[u] : sz[v]);
	}
}
void work(){
	memset(flag, 0, sizeof flag);
	for(int i = 1, u, v, d; i < n; ++i)
		scanf("%d%d%d", &u, &v, &d),
		add_edge(u, v, d);
	devide(1, n);
	printf("%d\n", ans);
}
