//O(n^0.5*m)
/*最小点覆盖数 = 最大匹配数
最大独立数 = 最大匹配数 (选取最多的点，使任意所选两点均不相连)
(DAG)最小路径覆盖数 = 顶点数 - 最大匹配数*/
int matchx[N], matchy[N], d[N];
bool dfs(int x) {
	for (int i = lst[x], y; i; i = nxt[i]) {
		y = id[i];
		int t = matchy[y];
		if (t == -1 || d[x] + 1 == d[t] && dfs(t)) {
			matchx[x] = y; matchy[y] = x;
			return true;
		}
	}
	d[x] = -1;
	return false;
}
int solve() {
	memset(matchx, -1, sizeof(matchx));
	memset(matchy, -1, sizeof(matchy));
	for (int ans = 0; ; ) {
		while (!Q.empty()) Q.pop();
		for (int i = 1; i <= n; i++)
			if (matchx[i] == -1) {
				d[i] = 0;
				Q.push(i);
			} else d[i] = -1;
		while (!Q.empty()) {
			int x = Q.front(); Q.pop();
			for (int i = lst[x], y; i; i = nxt[i]) {
				y = id[i];
				int t = matchy[y];
				if (t != -1 && d[t] == -1) {
					d[t] = d[x] + 1;
					Q.push(t);
				}
			}
		}
		int delta = 0;
		for (int i = 1; i <= n; i++)
			if (matchx[i] == -1 && dfs(i)) delta++;
		if (delta == 0) return ans;
		ans += delta;
	}
} 
