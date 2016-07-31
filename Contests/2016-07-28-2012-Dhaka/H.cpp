#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 50;
const int maxs = 2e7;
const double inf = 1e9;

int n, m, k, a[maxn], limit;
double f[maxs][2], w[maxn][maxn];
bool need[maxn], vist[maxs][2];

void expand(int s){
	for(int i = n; i >= 1; --i) a[i] = s % 16, s /= 16;
	//for(int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i==n]);
}
int zip(){
	int rtn = 0;
	for(int i = 1; i <= n; ++i) rtn *= 16, rtn += a[i];
	//for(int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i==n]);
	return rtn;
}

double dfs(int s, bool pre){
	
	if(vist[s][pre]) return f[s][pre];
	vist[s][pre] = true;
	
	expand(s);
	int pos = 0;
	for(int i = 1; i <= n; ++i) pos += a[i]; ++pos;
	if(pos > m){
		int mx = 0, mn = m;
		for(int i = 1; i <= n; ++i) mx = max(mx, a[i]), mn = min(mn, a[i]);
		if(mx - mn > 1) return f[s][pre] = -inf;
		else return f[s][pre] = 0.00;
	}
	
	f[s][pre] = -inf;
	for(int i = 1; i <= n; ++i){
		++a[i];
		//printf("a lim %d %d\n", a[i], limit);
		if(a[i] > limit){--a[i]; continue;} // !!!
		int ss = zip();
		if(need[pos] && !pre) f[s][pre] = max(f[s][pre], dfs(ss, false));
		else{
			double t = 0.00;
			t += w[i][pos] * (dfs(ss, true) + 1.00);
			t += (1.00 - w[i][pos]) * dfs(ss, false);
			f[s][pre] = max(f[s][pre], t);
		}
		--a[i];
	}
	
	return f[s][pre];
}

void work(){
	
	scanf("%d%d", &n, &m);
	limit = m / n + (m % n != 0); // !!!
	scanf("%d", &k);
	for(int i = 1, j; i <= k; ++i) scanf("%d", &j), need[j] = true;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%lf", &w[i][j]);
	printf("%.4f\n", dfs(0, false));
	memset(vist, 0, sizeof vist);
	memset(need, 0, sizeof need);
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case %d: ", tt);
		work();
	}

	return 0;
}
