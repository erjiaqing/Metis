#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std;
const double INF = 1e7;
const int maxn = 2e4 + 10;
const int maxm = 2e5 + 10;
int h[maxn], head[maxn], nex[maxm], to[maxm], last[maxn], lastedge[maxn], tot, s, t;
int gap[maxn], cur[maxn], d[maxn], n;
double maxflow;
double flow[maxm];
void clear(){
	rep(i, 1, tot) head[i] = 0;
	tot = 1;
	maxflow = 0;
}
void add(int l, int r, double f){
	nex[++tot] = head[l]; head[l] = tot; to[tot] = r; flow[tot] = f;
	nex[++tot] = head[r]; head[r] = tot; to[tot] = l; flow[tot] = 0;
}
void augment(){
	double f = INF;
	for(int pos = t; pos != s; pos = last[pos])
		if(flow[lastedge[pos]] < f) f = flow[lastedge[pos]];
	for(int pos = t; pos != s; pos = last[pos])
		flow[lastedge[pos]] -= f, flow[lastedge[pos] ^ 1] += f;
	maxflow += f;
}
void isap(){
	int pos = s;
	rep(i, 1, t) gap[i] = 0;
	gap[0] = t;
	rep(i, 1, t) cur[i] = head[i], d[i] = 0;
	while(d[s] < t){
		if(pos == t){augment(); pos = s;}
		bool flag = 0;
		for(int u = cur[pos]; u; u = nex[u])
			if(flow[u] > 0 && d[to[u]] + 1 == d[pos]){
				flag = 1;
				cur[pos] = u;
				last[to[u]] = pos;
				lastedge[to[u]] = u;
				pos = to[u];
				break;
			}
		if(!flag){
			int f = t - 1;
			for(int u = head[pos]; u; u = nex[u])
				if(flow[u] > 0  && d[to[u]] < f) f = d[to[u]];
			if(!--gap[d[pos]]) break;
			gap[d[pos] = f + 1] ++;
			cur[pos] = head[pos];
			if(pos != s) pos = last[pos];
		}
	}
}
bool check(double v){
	clear();
	int sum = n;
	rep(i, 2, n)
		rep(j, 1, i - 1)
			if(h[j] > h[i]) {
                add(++sum, i, INF);
				add(sum, j, INF);
			}
	s = sum + 1;
	t = s + 1;
	rep(i, n + 1, sum) add(s, i, 1.0);
	rep(i, 1, n) add(i, t, v);
	isap();
	return sum - n - maxflow > 1e-10;
}
int main(){
	int T;
	cin >> T;
	rep(cas, 1, T){
		printf("Case #%d: ", cas);
		cin >> n;
		rep(i, 1, n) scanf("%d", &h[i]);
		double l = 0, r = n, ans = 0;
		while(r - l > 1e-9){
			double mid = (l + r) / 2;
			if(check(mid)){
				if(mid > ans) ans = mid;
				l = mid;
			}
			else r = mid;
		}	
		printf("%.8f\n", ans);
	}
	return 0;
}

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
	if(u == T || nowflow < eps) return nowflow;
	double tempflow, deltaflow = 0.00;
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		double flow = mp[u][l].flow;
		if(flow > eps && dist[u] == dist[v] + 1){
			tempflow = sap(v, min(flow, nowflow - deltaflow));
			mp[u][l].flow -= tempflow;
			mp[v][mp[u][l].r].flow += tempflow;
			deltaflow += tempflow;
			if(deltaflow == nowflow || dist[S] == T) return deltaflow;
		}
	}
	disq[dist[u]]--;
	if(!disq[dist[u]]) dist[S] = T;
	dist[u]++;
	disq[dist[u]]++;
	return deltaflow;
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