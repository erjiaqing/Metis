const int maxn = 1e2 + 5;
const double eps = 1e-10;
const double d = 1e2;
const double inf = 1e9;
struct edge{
	int r, v;
	double flow;
	edge(int v, int r, double flow) : v(v), r(r), flow(flow) {}
};
vector<edge> mp[maxn];
void add_edge(int u, int v, double flow){
	mp[u].push_back(edge(v, mp[v].size(), flow));
	mp[v].push_back(edge(u, mp[u].size() - 1, 0.00));
}
int n, m, S, T, a[maxn], deg[maxn];
int dist[maxn], disq[maxn];
double sap(int u, double nowflow){
}
double value(){
	double maxflow = 0.00;
	while(dist[S] <= T) maxflow += sap(S, inf);
	return -0.50 * (maxflow - d * n);
}
void build(double g){
	g *= 2.00;
	for(int i = 1; i <= n; ++i) add_edge(S, i, d); // s -> v : INF
	for(int i = 1; i <= n; ++i) add_edge(i, T, d + g - deg[i]); // u -> t : INF + g - deg[u] 其中 deg[u] 为点 u 的度数（双向边）
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j){
			if(a[i] >= a[j]) continue;
			add_edge(i, j, 1.00); // u -> v : 1.00
			add_edge(j, i, 1.00);
		}
}
void clear(){
	memset(dist, 0, sizeof dist);
	memset(disq, 0, sizeof disq);
	for(int i = 1; i <= T; ++i) mp[i].clear();
}
double binary(double left, double rght){ // 猜测答案 g [1 / n, m / 1]
	int step = 0;
	while(left + eps < rght && step <= 50){
		++step;
		double mid = (left + rght) / 2;
		clear();
		build(mid);
		double h = value();
		if(h > eps) left = mid;
		else rght = mid;
	}
	return left;
}
void work(){
	m = 0;
	scanf("%d", &n);
	S = n + 1, T = n + 2;
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) deg[i] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j){
			if(a[i] >= a[j]) continue;
			++m;
			++deg[i];
			++deg[j];
		}
	printf("%.12f\n", binary(0.00, m));
}
int main(){
	int case_number;
	scanf("%d", &case_number);
	for(int cs = 1; cs <= case_number; ++cs){
		printf("Case #%d: ", cs);
		work();
	}
	return 0;
}