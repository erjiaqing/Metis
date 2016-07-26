int cnt, top, scc;
int bel[maxn], dfn[maxn], low[maxn], stck[maxn];
bool inst[maxn];
void tarjan(int u){
	
	dfn[u] = low[u] = ++cnt;
	stck[++top] = u;
	inst[u] = true;
	
	for(int l = 0; l < mp[u].size(); ++l){
		int v = mp[u][l];
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
		} while(v != u);
	}
}

