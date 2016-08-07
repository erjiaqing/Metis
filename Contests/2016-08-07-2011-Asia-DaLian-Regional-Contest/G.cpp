#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

const int maxl = 1e6 + 5;
const int maxm = 105;
const int maxs = 1 << 10;
const int maxn = 1e3 + 5;
const int inf = 1e9;

int n, m;
char str[maxl];
int f[2][maxn][maxs], val[15], ans;

struct trie{
	
	int size, indx[maxn][4], word[maxn], fail[maxn];
	bool jump[maxn];
	queue<pii> que[2];
	
	void clear(){
		size = 0;
		memset(indx, 0, sizeof indx);
		memset(word, 0, sizeof word);
		memset(fail, 0, sizeof fail);
		memset(jump, 0, sizeof jump);
		while(!que[0].empty()) que[0].pop();
		while(!que[1].empty()) que[1].pop();
	}
	
	int idx(char ch){
		if(ch == 'A') return 0;
		if(ch == 'T') return 1;
		if(ch == 'C') return 2;
		if(ch == 'G') return 3;
	}
	
	void insert(char s[], int id){
		int u = 0;
		for(int i = 0; s[i]; ++i){
			int k = idx(s[i]);
			if(!indx[u][k]) indx[u][k] = ++size;
			u = indx[u][k];
		}
		word[u] = id;
		jump[u] = true;
	}
	
	void build(){
		queue<int> que;
		while(!que.empty()) que.pop();
		que.push(0);
		while(!que.empty()){
			int u = que.front();
			//printf("u %d\n", u);
			que.pop();
			for(int k = 0; k < 4; ++k){
				int v = indx[u][k];
				if(!v) continue;
				int p = fail[u];
				while(p && !indx[p][k]) p = fail[p];
				if(indx[p][k] && indx[p][k] != v) p = indx[p][k];
				fail[v] = p;
				jump[v] |= jump[p];
				que.push(v);
			}
		}
	}
	
	void dp(int ut){
		int vt = !ut;
		while(!que[ut].empty()){
			int u_node = que[ut].front().first;
			int u_mask = que[ut].front().second;
			int uf = f[ut][u_node][u_mask];
			que[ut].pop();
			for(int k = 0; k < 4; ++k){
				int v_node = u_node;
				int v_mask = u_mask;
				int vf = uf;
				while(v_node && !indx[v_node][k]) v_node = fail[v_node];
				v_node = indx[v_node][k];
				int v = v_node;
				while(jump[v]){
					if(word[v] == 0){
						v = fail[v];
						continue;
					}
					if((v_mask & (1 << (word[v] - 1))) == 0) vf += val[word[v]];
					v_mask |= 1 << (word[v] - 1);
					v = fail[v];
				}
				if(f[vt][v_node][v_mask] == -inf) que[vt].push(make_pair(v_node, v_mask));
				f[vt][v_node][v_mask] = max(f[vt][v_node][v_mask], vf);
				//printf("f[%d][%d][%d] = %d\n", vt, v_node, v_mask, f[vt][v_node][v_mask]);
				//if(vt == m) ans = max(ans, f[vt][v_node][v_mask]);
			}
			f[ut][u_node][u_mask] = -inf;
		}
	}
}dict;

void work(){
	
	dict.clear();
	
	str[0] = 'A', str[1] = 0;
	dict.insert(str, 0);
	str[0] = 'T', str[1] = 0;
	dict.insert(str, 0);
	str[0] = 'C', str[1] = 0;
	dict.insert(str, 0);
	str[0] = 'G', str[1] = 0;
	dict.insert(str, 0);
	for(int i = 1; i <= n; ++i){
		scanf("%s", str);
		dict.insert(str, i);
		scanf("%d", &val[i]);
	}
	dict.build();
	
	ans = -inf;
	for(int i = 0; i <= 1; ++i)
		for(int j = 0; j <= dict.size; ++j)
			for(int k = 0; k < (1 << n); ++k)
				f[i][j][k] = -inf;
	f[0][0][0] = 0;
	dict.que[0].push(make_pair(0, 0));
	for(int i = 0; i < m; ++i) dict.dp(i & 1);
	for(int j = 0; j <= dict.size; ++j)
		for(int k = 0; k < (1 << n); ++k)
			ans = max(ans, f[m&1][j][k]);
	if(ans < 0) puts("No Rabbit after 2012!");
	else printf("%d\n", ans);
}

int main(){
	
	while(scanf("%d%d", &n, &m) == 2) work();

	return 0;
}
