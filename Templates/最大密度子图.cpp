#include<iostream>
#include<cstdio>
#include<cstring>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std;
const double INF = 1e7;
const int maxn = 2e4 + 10;
const int maxm = 2e5 + 10;
int h[maxn], head[maxn], nex[maxm], to[maxm], last[maxn], lastedge[maxn], tot, s, t;
int gap[maxn], cur[maxn], d[maxn], n;
double maxflow;
double flow[maxm]; 

void clear(){
	rep(i, 1, tot) head[i] = 0;
	tot = 1;
	maxflow = 0;
}

void add(int l, int r, double f){
	nex[++tot] = head[l]; head[l] = tot; to[tot] = r; flow[tot] = f;
	nex[++tot] = head[r]; head[r] = tot; to[tot] = l; flow[tot] = 0;
}
void augment(){
	double f = INF;
	for(int pos = t; pos != s; pos = last[pos])
		if(flow[lastedge[pos]] < f) f = flow[lastedge[pos]];
	for(int pos = t; pos != s; pos = last[pos])
		flow[lastedge[pos]] -= f, flow[lastedge[pos] ^ 1] += f;
	maxflow += f;
}
void isap(){
	int pos = s;
	rep(i, 1, t) gap[i] = 0;
	gap[0] = t;
	rep(i, 1, t) cur[i] = head[i], d[i] = 0;
	while(d[s] < t){
		if(pos == t){augment(); pos = s;}
		bool flag = 0;
		for(int u = cur[pos]; u; u = nex[u])
			if(flow[u] > 0 && d[to[u]] + 1 == d[pos]){
				flag = 1;
				cur[pos] = u;
				last[to[u]] = pos;
				lastedge[to[u]] = u;
				pos = to[u];
				break;
			}
		if(!flag){
			int f = t - 1;
			for(int u = head[pos]; u; u = nex[u])
				if(flow[u] > 0  && d[to[u]] < f) f = d[to[u]];
			if(!--gap[d[pos]]) break;
			gap[d[pos] = f + 1] ++;
			cur[pos] = head[pos];
			if(pos != s) pos = last[pos];
		}
	}
}
bool check(double v){
	clear();
	int sum = n;
	
	rep(i, 2, n)
		rep(j, 1, i - 1)
			if(h[j] > h[i]) {
		//		printf("add(%d %d %d)\n", sum, i, j);
				add(++sum, i, INF);
				add(sum, j, INF);
			}
	s = sum + 1;
	t = s + 1;
	//printf("sum = %d\n", sum);
	rep(i, n + 1, sum) add(s, i, 1.0);
	rep(i, 1, n) add(i, t, v);
	isap();
	//printf("maxflow = %f\n", maxflow);
	return sum - n - maxflow > 1e-10;
}
int main(){
	int T;
	cin >> T;
	rep(cas, 1, T){
		printf("Case #%d: ", cas);
		cin >> n;
		rep(i, 1, n) scanf("%d", &h[i]);
		double l = 0, r = n, ans = 0;
		while(r - l > 1e-9){
			double mid = (l + r) / 2;
			//printf("l = %.8f r = %.8f\n", l, r);
			if(check(mid)){
				if(mid > ans) ans = mid;
				l = mid;
			}
			else r = mid;
		}	
		printf("%.8f\n", ans);
	}
	return 0;
}
