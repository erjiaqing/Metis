#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3 + 5;

int n, m, a[maxn], b[maxn], ind[maxn];
int mp[maxn][maxn], f[maxn][maxn];
bool mr[maxn][maxn], ls[maxn][maxn];
bool team[maxn];

queue<int> que;
bool inq[maxn];
bool topsort(int s[], bool type, int tot){
	
	int k = 0;
	memset(inq, 0, sizeof inq);
	while(!que.empty()) que.pop();
	for(int i = 1; i <= n + m; ++i){
		if(team[i] != type) continue;
		if(ind[i] != 0) continue;
		que.push(i);
		s[++k] = i;
		inq[i] = true;
	}
	while(!que.empty()){
		int u = que.front();
		que.pop();
		for(int v = 1; v <= n + m; ++v){
			if(team[v] != type) continue;
			if(!mp[u][v]) continue;
			--ind[v];
			if(ind[v] == 0 && inq[v] != true){
				que.push(v);
				s[++k] = v;
				inq[v] = true;
			}
		}
	}
	
	return k == tot;
}

char str[maxn*10];
void work(){
	
	memset(ind, 0, sizeof ind);
	char ch = getchar();
	for(int i = 1; i <= n; ++i){
		gets(str);
		int l = strlen(str);
		for(int j = 1, k = 0; k < l; ++j, k += 2)
			mp[i][j] = str[k] - '0';
	}
	memset(team, 0, sizeof team);
	for(int i = 1, j; i <= m; ++i) scanf("%d", &j), team[j] = true;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(mp[i][j] && team[i] == team[j]) ++ind[j];
	n = n - m; swap(n, m);
	
	//puts("done");
	if(!topsort(a, true, n) || !topsort(b, false, m)){
		puts("NO");
		return;
	}
	
	//for(int i = 1; i <= n; ++i) printf("%d ", a[i]); puts("");
	//for(int i = 1; i <= m; ++i) printf("%d ", b[i]); puts("");
	
	memset(mr, 0, sizeof mr);
	memset(ls, 0, sizeof ls);
	for(int j = 1; j <= m; ++j){
		ls[j][0] = mr[j][n+1] = true;
		for(int i = 1; i <= n; ++i) ls[j][i] = ls[j][i-1] && mp[a[i]][b[j]];
		for(int i = n; i >= 1; --i) mr[j][i] = mr[j][i+1] && mp[b[j]][a[i]];
		//for(int i = 0; i <= n + 1; ++i) printf("mr[%d][%d] = %d, ls[%d][%d] = %d\n", j, i, mr[j][i], j, i, ls[j][i]);
	}
	memset(f, 0, sizeof f);
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j){
			if(i > 0) f[i][j] = max(f[i][j], f[i-1][j]);
			if(j > 0) f[i][j] = max(f[i][j], f[i][j-1]);
			if(j > 0 && ls[j][i] && mr[j][i+1]) f[i][j] = max(f[i][j], f[i][j-1] + 1);
		}
	printf("YES %d\n", f[n][m]);
}

int main(){
	
	//freopen("C.in", "r", stdin);
	//freopen("wrong.out", "w", stdout);
	
	while(scanf("%d%d", &n, &m) == 2){
		if(n + m == 0) break;
		work();
	}

	return 0;
}
