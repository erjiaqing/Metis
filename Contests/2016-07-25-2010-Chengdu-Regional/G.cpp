#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1e4 + 5;

vector<int> mp[maxn];
void add_edge(int u, int v){
	//printf("%d -> %d\n", u, v);
	mp[u].push_back(v);
}

int n, m, id[maxn][2];
int a[maxn], b[maxn], c[maxn];

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

bool check(int mid){
	
	top = scc = cnt = 0;
	for(int i = 1; i <= 2 * n; ++i) mp[i].clear();
	for(int i = 1; i <= 2 * n; ++i) dfn[i] = low[i] = bel[i] = 0;
	for(int i = 1; i <= 2 * n; ++i) inst[i] = false, stck[i] = 0;
	
	for(int i = 1; i <= mid; ++i){
		
		if(c[i] == 0){
			//add_edge(id[a[i]][1], id[b[i]][0]);
			//add_edge(id[b[i]][1], id[a[i]][0]);
			
			add_edge(id[a[i]][0], id[b[i]][1]);
			add_edge(id[b[i]][0], id[a[i]][1]);
			
			//add_edge(id[a[i]][1], id[b[i]][1]);
			//add_edge(id[b[i]][0], id[a[i]][0]);
		}
		if(c[i] == 1){
			add_edge(id[a[i]][0], id[b[i]][0]);
			add_edge(id[b[i]][1], id[a[i]][1]);
			
			add_edge(id[a[i]][1], id[b[i]][1]);
			add_edge(id[b[i]][0], id[a[i]][0]);
		}
		if(c[i] == 2){
			add_edge(id[a[i]][1], id[b[i]][0]);
			add_edge(id[b[i]][1], id[a[i]][0]);
		}
	}
	
	for(int i = 1; i <= 2 * n; ++i) if(!dfn[i]) tarjan(i);
	//tarjan(1);
	//for(int i = 1; i <= 2 * n; ++i) printf("bel[%d] = %d\n", i, bel[i]);
	
	for(int i = 1; i <= n; ++i) if(bel[id[i][0]] == bel[id[i][1]]) return false;
	return true;
}

int binary(int left, int rght){

	while(left < rght){
		int mid = (left + rght + 1) >> 1;
		if(check(mid)) left = mid;
		else rght = mid - 1;
	}
	return left;
}

void work(){
	
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]), ++a[i], ++b[i];
	for(int i = 1; i <= n; ++i)	id[i][0] = i, id[i][1] = i + n;
	printf("%d\n", binary(0, m));
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
