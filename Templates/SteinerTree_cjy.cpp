const int N = 100005;
const int M = 200005;
const int P = 8;
const int inf = 0x3f3f3f3f;
int n, m, p, status, idx[P], f[1 << P][N];
//int top, h[N];
priority_queue<pair<int, int> > q;
bool vis[N];
int tot, lst[N], nxt[M], id[M], len[M];
void Add(int x, int y, int z) {
	id[++tot] = y; nxt[tot] =lst[x]; lst[x] = tot; len[tot] = z;
}
void dijkstra(int dis[]) {
	while(!q.empty()) {
		int x = q.top().second; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = lst[x]; i; i = nxt[i]) {
			int y = id[i];
			if (dis[x] + len[i] < dis[y]) {
				dis[y] = dis[x] + len[i];
				if (!vis[y]) q.push(make_pair(-dis[y], y));
			}
		}
	}
}
void Steiner_Tree() {
	for (int i = 1; i < status; i++) {
		//top = 0;
		while (!q.empty()) q.pop();
		memset(vis, 0, sizeof(vis));
		for (int j = 1; j <= n; j++) {
			for (int k = i & (i - 1); k; (--k) &= i)
				f[i][j] = min(f[i][j], f[k][j] + f[i ^ k][j]);
			if (f[i][j] != inf) {
				//h[++top] = j, vis[j] = 1;
				q.push(make_pair(-f[i][j], j));
			}
		}
		//SPFA(f[i]);
		dijkstra(f[i]);
	}
}
int main() {
	while (scanf("%d%d%d", &n, &m, &p) == 3) {
		status = 1 << p;
		tot = 0; memset(lst, 0, sizeof(lst));
		/*求最小生成森林
		  每棵生成树中至少选择一个点，点权为代价
		  新开一个空白关键点作为源
          for (int i = 1; i <= n; i++) {
           scanf("%d", &val[i]);
           Add(0, i, val[i]); Add(i, 0, val[i]);
          }*/
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			Add(x, y, z); Add(y, x, z);
		}
		for (int i = 1; i <= p; i++) scanf("%d", &idx[i]);
		memset(f, 0x3f, sizeof(f));
		for (int i = 1; i <= n; i++) f[0][i] = 0;
		for (int i = 1; i <= p; i++)
			f[1 << (i - 1)][idx[i]] = 0;
		Steiner_Tree();
		int ans = inf;
		for (int i = 1; i <= n; i++) ans = min(ans, f[status - 1][i]);
		printf("%d\n", ans);
	} 
	return 0;
}
