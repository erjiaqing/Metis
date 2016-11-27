int first[maxn],nxt[maxn],u[maxn],v[maxn],vis[maxn],rear;
void add(int from, int to){
	nxt[++rear] = first[from];
	first[from] = rear;
	u[rear] = from;
	v[rear] = to;
	nxt[++rear] = first[to];
	first[to] = rear;
	u[rear] = to;
	v[rear] = from;
}
bool tree_div(int x){
	int h = 1, t = 2;
	que[h] = x,pre[x] = -1,vis[x] = 1;
	while (h < t){
		int sta = que[h++];
		size[sta] = 1;
		for (int i = first[sta]; i != -1; i = nxt[i]){
			if(!vis[v[i]]){
				vis[v[i]] = true;
				pre[v[i]] = sta;
				que[t++] = v[i];
			}
		}
	}
	for (int i = t - 1; i >= 1; --i){
		size[pre[que[i]]] += size[que[i]];
		vis[que[i]] = 0;
	}
	int max_size = 0x7fffffff;
	int root = -1;
	for (int i = 1; i < t; ++i){
		int tmp = 0;
		for (int j = first[que[i]]; ~j; j = nxt[j]){
			if (v[j] != pre[que[i]]){
				tmp = max(tmp,size[v[j]]);
			}
		}
		tmp = max(tmp, t - 1 - size[que[i]]);
		if (tmp < max_size){
			max_size = tmp;
			root = que[i];
		}
	}
	if  (solve(root))return 1;
	vis[root] = 1;
	for (int j = first[root]; j != -1; j = nxt[j]) {
		int y = v[j];
		if (!vis[y]){
			if (tree_div(y)){
				return 1;
			}
		}		
	}
	return 0;	
}
