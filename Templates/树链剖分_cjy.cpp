const int N = 800005;
int n, m, Max, b[N], edge_pos[N], path[N];
int fa[N], siz[N], dep[N], hvy[N], top[N], pos[N];
void dfs1(int x, int Fa) {
	fa[x] = Fa;
	siz[x] = 1;
	dep[x] = dep[Fa] + 1;
	int max_size = 0;
	for (int i = lst[x]; i; i = nxt[i]) {
		int y = id[i];
		if (y != Fa) {
			path[y] = i; //-----------------
			dfs1(y, x);
			if (siz[y] > max_size) {
				max_size = siz[y];
				hvy[x] = y;
			}
			siz[x] += siz[y];
		}
	}
}
void dfs2(int x, int Top) {
	top[x] = Top;
	pos[x] = ++m;
	b[m] = val[path[x]]; //b[m] = val[x];
	edge_pos[path[x] / 2] = m; //when change only one edge's value
	if (hvy[x]) dfs2(hvy[x], Top); //heavy son need to be visited first
	for (int i = lst[x]; i; i = nxt[i]) {
		int y = id[i];
		if (y == fa[x] || y == hvy[x]) continue;
		dfs2(y, y);
	}
}
void work(int x, int y) {
	int X = top[x], Y = top[y];
	if (X == Y) {
		if (dep[x] < dep[y]) Negate(1, pos[x] + 1, pos[y]);
		else if (dep[x] > dep[y]) Negate(1, pos[y] + 1, pos[x]);
		//if (dep[x] <= dep[y]) Negate(1, pos[x], pos[y]);
		//else Negate(1, pos[y], pos[x]);
		return ;
	}
	if (dep[X] >= dep[Y]) {
		Negate(1, pos[X], pos[x]);
		work(fa[X], y);
	} else {
		Negate(1, pos[Y], pos[y]);
		work(x, fa[Y]);
	}
}
int main() {
	tot = 1; memset(lst, 0, sizeof(lst)); //!!!tot = 1;
	memset(hvy, 0, sizeof(hvy));
	(Add_edge) //val[] = value
	dep[0] = 0; dfs1(1, 0); //the root is 1
	m = 0; dfs2(1, 1);
	build(1, 1, n);
	Change(1, edge_pos[x], y); //change one edge's valve directly in Tree
	work(x, y); //change value of a chain
}
