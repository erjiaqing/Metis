int scc, top, cnt;
int dfn[maxn], low[maxn], stck[maxn], bel[maxn];
bool inst[maxn];
void tarjan(int u){
	
	dfn[u] = low[u] = ++cnt;
	stck[++top] = u;
	inst[u] = true;
	
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l].v;
		if(mp[u][l].flag) continue;
		mp[u][l].flag = mp[v][mp[u][l].r].flag = true;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(inst[v]) low[u] = min(low[u], dfn[v]);
	}
	
	if(dfn[u] == low[u]){
		++scc;
		int v;
		do{
			v = stck[top--];
			bel[v] = scc;
			inst[v] = false;
			++sz[scc];
		} while(v != u);
	}
}
