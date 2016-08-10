#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e3 + 5;
const int maxm = 1e4 + 5;

int n, m, fa[maxn];
vector<int> ans;

struct edge{
	int u, v, lnth;
}e[maxm];

bool cmp(edge i, edge j){
	return i.lnth < j.lnth;
}

int getfa(int u){
	if(fa[u] == u) return u;
	else return fa[u] = getfa(fa[u]);
}

void work(){
	
	ans.clear();
	for(int i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].lnth);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	sort(e + 1, e + 1 + m, cmp);
	for(int i = 1; i <= m; ++i){
		int u = e[i].u;
		int v = e[i].v;
		int fau = getfa(u);
		int fav = getfa(v);
		if(fau != fav){
			ans.push_back(e[i].lnth);
			fa[fau] = fav;
		}
	}
	sort(ans.begin(), ans.end());
	m = ans.size();
	int i, j;
	for(i = 0, j = m - 1; i < j; ++i, --j);
	if((ans[i] + ans[j]) % 2 == 0) printf("%d\n", (ans[i] + ans[j]) / 2);
	else printf("%.1f\n", 1.00 * (ans[i] + ans[j]) / 2.00);
}

int main(){
	
	while(true){
		scanf("%d%d", &n, &m);
		if(n + m == 0) break;
		work();
	}
	
	return 0;
}
