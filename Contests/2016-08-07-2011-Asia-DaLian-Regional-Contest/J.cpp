#include <ctime>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxh = 2e3 + 5;
const int maxn = 2e2 + 5;
const int inf = 1e9;

int h, w, n, m, t, ans, a, b;
char mp[maxh][maxh];
int s[maxh][maxh];

vector<int> edge[maxn];
void add_edge(int u, int v){
	edge[u].push_back(v);
}

int nowtime;
int lnk[maxn], inq[maxn];
bool mark1[maxn], mark2[maxn];
bool find(int u){
	if(mark1[u]) return false;
	for(int l = 0; l < edge[u].size(); ++l){
		int v = edge[u][l];
		if(mark2[v]) continue;
		if(inq[v] != nowtime){
			inq[v] = nowtime;
			if(lnk[v] == 0 || find(lnk[v])){
				lnk[v] = u;
				return true;
			}
		}
	}
	return false;
}

int calc(){
	
	int rtn = 0;
	for(int i = 1; i <= n + 1; ++i)	mark1[i] = false;
	for(int i = 1; i <= m + 1; ++i) mark2[i] = false;
	for(int i = 1; i <= n + 1; ++i) edge[i].clear();
	for(int i = 1, x = b + 1; i <= n; ++i, x += a + b)
		for(int j = 1, y = b + 1; j <= m; ++j, y += a + b){
			int sum = s[x+a-1][y+a-1] - s[x+a-1][y-1] - s[x-1][y+a-1] + s[x-1][y-1];
			if(sum != a * a) ++rtn;
		}
	for(int i = 1, x = 1; i <= n + 1; ++i, x += a + b)
		for(int j = 1, y = 1; j <= m + 1; ++j, y += a + b){
			int sum = s[x+b-1][y+b-1] - s[x+b-1][y-1] - s[x-1][y+b-1] + s[x-1][y-1];
			if(sum != 0) add_edge(i, j), ++cnt;
		}
	for(int i = 1, x = 1; i <= n + 1; ++i, x += a + b)
		for(int  j = 1, y = b + 1; j <= m; ++j, y += a + b){
			int sum = s[x+b-1][y+a-1] - s[x+b-1][y-1] - s[x-1][y+a-1] + s[x-1][y-1];
			if(sum != 0) mark1[i] = true, ++cnt;
		}
	for(int i = 1, x = b + 1; i <= n; ++i, x += a + b)
		for(int j = 1, y = 1; j <= m + 1; ++j, y += a + b){
			int sum = s[x+a-1][y+b-1] - s[x+a-1][y-1] - s[x-1][y+b-1] + s[x-1][y-1];
			if(sum != 0) mark2[j] = true, ++cnt;
		}
	
	for(int i = 1; i <= n + 1; ++i)	if(mark1[i]) ++rtn;
	for(int i = 1; i <= m + 1; ++i) if(mark2[i]) ++rtn;
	for(int i = 1; i <= m + 1; ++i) lnk[i] =  0;
	for(int i = 1; i <= n + 1; ++i){
		++nowtime;
		if(find(i)) ++rtn;
	}
	return rtn * t;
}

bool exist(){
	bool found = false;
	for(b = 1; b * (n + 1) < h && b * (m + 1) < w; ++b){
		if((h - (n + 1) * b) % n != 0) continue;
		a = (h - (n + 1) * b) / n;
		if(a < b) continue;
		if((m + 1) * b + m * a != w) continue;
		found = true;
		ans = min(ans, calc());
	}
	return found;
}

void work(){
	
	ans = inf;
	char ch = getchar();
	for(int i = 1; i <= h; ++i) gets(mp[i] + 1);
	for(int i = 1; i <= h; ++i)
		for(int j = 1; j <= w; ++j)
			s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + mp[i][j] - '0';
	if(exist()) printf("%d\n", ans);
	else puts("-1");
}

int main(){
	
	while(scanf("%d%d%d%d%d", &h, &w, &n, &m, &t) == 5) work();
	
	return 0;
}
