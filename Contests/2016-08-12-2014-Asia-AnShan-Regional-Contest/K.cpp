#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 55;
const long long p = 1e9 + 7;
const double eps = 1e-8;

struct pit{
	
	double x, y;
	pit(double x = 0.00, double y = 0.00) : x(x), y(y) {}
	pit friend operator + (pit A, pit B){return pit(A.x + B.x, A.y + B.y);}
	pit friend operator - (pit A, pit B){return pit(A.x - B.x, A.y - B.y);}
	void rotate(double theta){
		double cs = cos(theta), sn = sin(theta);
		double tx = x * cs - y * sn;
		double ty = x * sn + y * cs;
		x = tx, y = ty;
	}
	bool friend operator == (pit A, pit B){
		if(fabs(A.x - B.x) > eps) return false;
		if(fabs(A.y - B.y) > eps) return false;
		//printf("%lf %lf %lf %lf\n", A.x, A.y, B.x, B.y);
		return true;
	}
}P[maxn], Q[maxn], cnt;

int n, m, c;
int fa[maxn], h[maxn], mp[maxn][maxn];

int get_fa(int u){
	if(fa[u] == u) return u;
	else return fa[u] = get_fa(fa[u]);
}
vector<int> vec;

void calc(){
	
	for(int i = 1; i <= n; ++i) h[i] = 0;
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j){
			if(Q[i] == P[j]) h[i] = j;
			else continue;
			int fai = get_fa(i);
			int faj = get_fa(j);
			fa[fai] = faj;
			//puts("ok");
		}
	for(int i = 1; i <= n; ++i) if(!h[i]) return;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(mp[i][j]) if(!mp[h[i]][h[j]]) return;
	//for(int i = 1; i <= n; ++i) printf("%d ", h[i]); puts("");
	//for(int i = 1; i <= n; ++i) printf("%d ", fa[i]); puts("");
	int sz = 0;
	for(int i = 1; i <= n; ++i) if(fa[i] == i) ++sz;
	vec.push_back(sz);
}

long long powmod(long long a, int x){
	long long rtn = 1;
	while(x){
		if(x & 1) rtn *= a, rtn %= p;
		a *= a, a %= p;
		x = x >> 1;
	}
	return rtn;
}

void work(){
	
	scanf("%d%d%d", &n, &m, &c);
	cnt = pit(0.00, 0.00);
	for(int i = 1; i <= n; ++i) scanf("%lf%lf", &P[i].x, &P[i].y), cnt = cnt + P[i];
	//for(int k = 1; k <= n; ++k) printf("%lf %lf\n", P[k].x, P[k].y); puts("------------");
	cnt.x /= 1.00 * n, cnt.y /= 1.00 * n;
	//printf("%lf %lf\n", cnt.x, cnt.y);
	memset(mp, 0, sizeof mp);
	for(int i = 1; i <= m; ++i){
		int u, v;
		scanf("%d%d", &u, &v);
		mp[u][v] = mp[v][u] = true;
	}
	vec.push_back(n);
	pit T;
	for(int i = 1; i <= n; ++i) if(!(P[i] == cnt)) T = P[i];
	//printf("%lf %lf\n", T.x, T.y);
	for(int j = 1; j <= n; ++j){
		if(P[j] == cnt || P[j] == T) continue;
		//printf("%lf %lf\n", P[j].x, P[j].y);
		double alpha = atan2(T.y - cnt.y, T.x - cnt.x);
		double beta = atan2(P[j].y - cnt.y, P[j].x - cnt.x);
		double theta = beta - alpha;
		//printf("%lf %lf %lf\n", alpha, beta, theta);
		for(int k = 1; k <= n; ++k) Q[k] = P[k] - cnt;
		//for(int k = 1; k <= n; ++k) printf("%lf %lf\n", Q[k].x, Q[k].y); puts("------------");
		for(int k = 1; k <= n; ++k) Q[k].rotate(theta);
		for(int k = 1; k <= n; ++k) Q[k] = Q[k] + cnt;
		//for(int k = 1; k <= n; ++k) printf("%lf %lf\n", Q[k].x, Q[k].y); puts("------------");
		calc();
	}
	long long ans = 0;
	int G = vec.size();
	//printf("%d\n", G);
	for(int i = 0; i < G; ++i) ans += powmod(c, vec[i]), ans %= p;//, printf("vec %d\n", vec[i]);
	ans *= powmod(G, p - 2), ans %= p;
	cout << ans << endl;
	vec.clear();
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
