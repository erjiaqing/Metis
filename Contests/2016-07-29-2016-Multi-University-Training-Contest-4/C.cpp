#include <vector>
#include <queue>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 25;
const int maxs = 2e6;
const int maxm = 500;

int n, m, s;
int f[maxs], u[maxm], v[maxm], connect[maxn];


void work(){
	
	memset(f, 0, sizeof f);
	memset(connect, 0, sizeof connect);
	scanf("%d%d", &n, &m);
	s = 1 << n;
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", &u[i], &v[i]);
		connect[u[i]] |= (1 << v[i]);
		connect[v[i]] |= (1 << u[i]);
	}

	for(int mask = 0; mask < s; ++mask){
		int t = mask & -mask;
		if((mask == t) && mask) f[mask] = 1;
		else f[mask] = 0;
	}

	for(int mask = 0; mask < s; ++mask)
		for(int i = 0; i < n; ++i) if(mask & (1 << i))
			f[mask] |= bool(connect[i] & (mask ^ (1 << i))) && f[mask^(1<<i)];

	for(int mask = 0; mask < s; ++mask) f[mask] = f[mask] & f[mask^(s-1)];

	for(int i = 0; i < n; ++i)
	for(int mask = 0; mask < s; ++mask)
			if(mask & (1 << i)) f[mask] += f[mask^(1<<i)];

	for(int i = 1; i <= m; ++i){
		int ans = 0;
		ans += f[(s-1)^(1<<u[i])];
		ans += f[(s-1)^(1<<v[i])];
		ans -= 2 * f[(s-1)^(1<<u[i])^(1<<v[i])];
		printf("%d%c", ans / 2, " \n"[i==m]);
	}
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case #%d: ", tt);
		work();
	}
	
	return 0;
}
