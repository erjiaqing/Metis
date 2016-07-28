#include <queue>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_vist = 1e2;
const int maxn = 305;

double ans, exp, f[maxn][maxn];
int vist[maxn][maxn];

void dfs(int a, int b, int step, double p){
	
	printf("%d %d %lf\n", a, b, p);
	
	if(vist[a][b] > max_vist) return;
	//if(vist[a][b]) return;
	++vist[a][b];
	f[a][b] += p;
	if(a == 0 || b == 0) exp += p * step;
	if(b == 0) ans += p;
	if(a == 0 || b == 0) return;
	
	int d = min(a, b);
	dfs(a + d, b - d, step + 1, p * 0.50);
	dfs(a - d, b + d, step + 1, p * 0.50);
}

const int max_step = 1e4;

queue<pair<pair<int, int>, pair<int, double> > > que;
void bfs(int a, int b){
	
	que.push(make_pair(make_pair(a, b), make_pair(0, 1.00)));
	int tot = 0;
	while(!que.empty() && tot < max_step){
	
		int aa = que.front().first.first;
		int bb = que.front().first.second;
		int dd = min(aa, bb);
		int step = que.front().second.first;
		double p = que.front().second.second;
		que.pop();
		++tot;
		
		if(aa == 0 || bb == 0) exp += p * step;
		if(bb == 0) ans += p;
		if(aa == 0 || bb == 0) continue;
		
		que.push(make_pair(make_pair(aa - dd, bb + dd), make_pair(step + 1, p * 0.50)));
		que.push(make_pair(make_pair(aa + dd, bb - dd), make_pair(step + 1, p * 0.50)));
	}
}

void work(){
	
	int a, b;
	scanf("%d%d", &a, &b);
	ans = exp = 0.00;
	memset(vist, 0, sizeof vist);
	for(int i = 0; i <= 300; ++i)
		for(int j = 0; j <= 300; ++j)
			f[i][j] = 0.00;
	//dfs(a, b, 0, 1.00);
	bfs(a, b);
	//puts("done");
	printf("%.6f %.6f\n", exp, ans);
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
