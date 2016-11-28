// 针对无向图：求双联通分量（按割边缩点），求割点和桥
vector<pii> edge[N]; // pii => pair<int, int>
bool vist[M]; // 去掉vist判定及加单向边就是求强连通分量
void add_edge(int u, int v, int id){
	edge[u].push_back(make_pair(v, id));
	edge[v].push_back(make_pair(u, id));
}
int top, cnt, scc;
int dfn[N], low[N], stck[N], bel[N];
bool brg[M], inst[N], cut[N]; // brg => bridge
void tarjan(int u, int rt){
	dfn[u] = low[u] = ++cnt;
	stck[++top] = u;
	inst[u] = true;
	int son = 0, good_son = 0; //
	for(int l = 0; l < edge[u].size(); ++l){
		int id = edge[u][l].second;
		if(vist[id]) continue;
		vist[id] = true; ++son; // 
		int v = edge[u][l].first;
		if(!dfn[v]){
			tarjan(v, rt);
			low[u] = min(low[u], low[v]);
			if(dfn[u] < low[v]) brg[id] = true;
		}else if(inst[v]) low[u] = min(low[u], dfn[v]);
		if(dfn[u] <= low[v]) ++good_son; //
	}
	if(u == rt){if(son >= 2) cut[u] = true;}
	else if(good_son > 0) cut[u] = true;
	if(dfn[u] == low[u]){
		++scc; int v;
		do{
			v = stck[top--];
			bel[v] = scc;
			inst[v] = false;
		}while(v != u);
	}
}

// 针对无向图：求双联通分量（按割点缩点并建出森林）
int totedge, hd[N], th[M], nx[M];
void addedge(int x, int y){
	th[++totedge] = y; nx[totedge] = hd[x]; hd[x] = totedge;
	th[++totedge] = x; nx[totedge] = hd[y]; hd[y] = totedge;
}
int tottree, thd[N * 2], tth[M * 2], tnx[M * 2];
void addtree(int x, int y){
	tth[++tottree] = y; tnx[tottree] = thd[x]; thd[x] = tottree;
	tth[++tottree] = x; tnx[tottree] = thd[y]; thd[y] = tottree;
}
bool mark[M];
int part, ind, top;
int dfn[N], low[N], st[N], root[N];
void tarjan(int x, int cur){
	dfn[x] = low[x] = ++ind;
	for(int i = hd[x]; i; i = nx[i]){
		if(mark[i]) continue;
		mark[i] = mark[i ^ 1] = true;
		st[++top] = i;
		int v = th[i];
		if(dfn[v]){
			low[x] = min(low[x], low[v]);
			continue;
		}
		tarjan(v, cur);
		low[x] = min(low[x], low[v]);
		if(low[v] >= dfn[x]){
			++part; int k;
			do{ //cur:=联通块里点双联通分量标号最小值
				k = st[top--];
				root[th[k]] = root[th[k ^ 1]] = cur; 
				addtree(part, th[k]); //part为点双联通分量的标号
				addtree(part, th[k ^ 1]);
			}while(th[k ^ 1] != x);
		}
	}
}
int main(){
	part = n;
	for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i, part + 1);
}
