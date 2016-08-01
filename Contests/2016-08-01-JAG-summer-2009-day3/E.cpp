#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int dr[] = {0, 4, 1, 2, 3, 8, 5, 6, 7};
const int du[] = {0, 4, 3, 7, 8, 1, 2, 6, 5};
const int dx[] = {0, 5, 1, 4, 8, 6, 2, 3, 7};

const int maxn = 10;
const int maxg = 100;
const int maxl = 200;
const int n = 8;

int G, a[maxn], trans[maxg][maxn];
bool uniq[maxg];
map<int, bool> gg;

void rotate(int r, int u, int x){
	
	int t[maxn];
	for(int i = 1; i <= r; ++i){
		memset(t, 0, sizeof t);
		for(int j = 1; j <= n; ++j) t[j] = a[dr[j]];
		memcpy(a, t, sizeof t);
	}
	for(int i = 1; i <= u; ++i){
		memset(t, 0, sizeof t);
		for(int j = 1; j <= n; ++j) t[j] = a[du[j]];
		memcpy(a, t, sizeof t);
	}
	for(int i = 1; i <= x; ++i){
		memset(t, 0, sizeof t);
		for(int j = 1; j <= n; ++j) t[j] = a[dx[j]];
		memcpy(a, t, sizeof t);
	}
}

int fa[maxn], sz[maxn];
int getfa(int u){
	if(fa[u] == u) return u;
	else return fa[u] = getfa(fa[u]);
}
void pre(){
	
	for(int x = 0; x < 4; ++x)
		for(int r = 0; r < 4; ++r)
			for(int u = 0; u < 4; ++u){
				int id = x * 16 + r * 4 + u;
				for(int i = 1; i <= n; ++i) a[i] = i;
				rotate(r, u, x);
				for(int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
				for(int i = 1; i <= n; ++i){
					int j = getfa(i);
					int k = getfa(a[i]);
					if(j != k){
						fa[j] = k;
						sz[k] += sz[j];
					}
				}
				for(int i = 1; i <= n; ++i) if(fa[i] == i) trans[id][++trans[id][0]] = sz[i];
				int zip = 0;
				for(int i = 1; i <= n; ++i) zip *= 10, zip += a[i];
				if(!gg[zip]) uniq[id] = true, ++G;
				gg[zip] = true;
			}
}

int color[maxn];
int dfs(int pos, int id){
	
	if(pos > trans[id][0]) return 1;
	int rtn = 0;
	for(int i = 1; i <= color[0]; ++i){
		if(color[i] < trans[id][pos]) continue;
		color[i] -= trans[id][pos];
		rtn += dfs(pos + 1, id);
		color[i] += trans[id][pos];
	}
	return rtn;
}

char str[maxl];
string tmp;
map<string, int> mp;
map<string, int> ::iterator it;
void work(){
	
	int l = strlen(str);
	tmp = "";
	mp.clear();
	for(int i = 0; i < l; ++i){
		if(str[i] == ' ' || str[i] == '\n'){
			mp[tmp]++;
			tmp = "";
			continue;
		}
		tmp += str[i];
	}
	mp[tmp]++;
	color[0] = 0;
	for(it = mp.begin(); it != mp.end(); ++it) color[++color[0]] = (*it).second;
	
	int ans = 0;
	for(int i = 0; i < maxg; ++i) if(uniq[i]) ans += dfs(1, i);
	printf("%d\n", ans / G);
	mp.clear();
}

int main(){
	
	pre();
	while(gets(str)) work();
	
	return 0;
}
