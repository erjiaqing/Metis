#include <bits/stdc++.h>
using namespace std;

const long double PI = 3.1415926535897932384626433832795;

long long sqr(long long x){
	
	return x * x;
}

const int maxn = 1e6 + 5;

typedef complex<long double> cpb;

int N;
cpb a[maxn], aa[maxn];
cpb b[maxn], bb[maxn];
cpb c[maxn], cc[maxn];
long long anss, va[maxn], vb[maxn];
long double ans[maxn];

void fft(cpb x[], cpb xx[], int n, int step, int type){
	
	if(n == 1){
		xx[0] = x[0];
		return;
	}
	
	int m = n >> 1;
	fft(x, xx, m, step << 1, type);
	fft(x + step, xx + m, m, step << 1, type);
	
	cpb w = exp(cpb(0., PI * type / m));
	cpb t = 1.;
	for(int i = 0; i < m; ++i){
		cpb t0 = xx[i];
		cpb t1 = xx[i+m];
		xx[i] = t0 + t * t1;
		xx[i+m] = t0 - t * t1;
		t *= w;
	}
}

void work(){
	
	int n, x;
	anss = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d", &x), a[i] = cpb(x, 0.), va[i] = x;
	for(int i = 0; i < n; ++i) scanf("%d", &x), b[i] = cpb(x, 0.), vb[i] = x;
	for(int i = 0, j = n - 1; i < j; ++i, --j) swap(b[i], b[j]);
	for(N = 1; N < n + n; N <<= 1);
	
	fft(a, aa, N, 1, 1);
	fft(b, bb, N, 1, 1);
	for(int i = 0; i < N; ++i) cc[i] = aa[i] * bb[i];
	fft(cc, c, N, 1, -1);
	for(int i = 0; i < N; ++i) ans[i] = round(c[i].real()) / N;
	
	long double maxx = 0;
	int pos = -1;
	N = 2 * n;
	for(int i = n; i < N; ++i){
		if(ans[i] + ans[i-n] > maxx){
			maxx = ans[i] + ans[i-n];
			pos = -(i - n + 1);
		}
	}
	//printf("pos %d\n", pos);
	anss = 0;
	for(int i = 0; i < n; ++i){
		int j = i + n + pos; j %= n;
		anss += sqr(va[i] - vb[j]);
	}
	cout << anss << endl;
	
	for(int i = 0; i < N; ++i) a[i] = b[i] = cpb(0., 0.);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
