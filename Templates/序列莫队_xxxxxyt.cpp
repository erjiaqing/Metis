#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const int maxn = 50005;
const int maxb = 233;

int n, m, cnt[maxn], a[maxn];
long long answ[maxn], ans;
int bk, sz, bel[maxn];
int lf[maxn], rh[maxn], rnk[maxn];

bool cmp(int i, int j){
	if(bel[lf[i]] != bel[lf[j]]) return bel[lf[i]] < bel[lf[j]];
	else return bel[rh[i]] < bel[rh[j]];
}

void widden(int i){ans += cnt[a[i]]++;}
void shorten(int i){ans -= --cnt[a[i]];}

long long gcd(long long a, long long b){
	if(b == 0) return a;
	else return gcd(b, a % b);
}

int main(){

	scanf("%d%d", &n, &m);
	bk = sqrt(n); sz = n / bk;
	while(bk * sz < n) ++bk;
	for(int b = 1, i = 1; b <= bk; ++b)
		for(; i <= b * sz && i <= n; ++i) bel[i] = b;
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= m; ++i) scanf("%d%d", &lf[i], &rh[i]);
	for(int i = 1; i <= m; ++i) rnk[i] = i;
	sort(rnk + 1, rnk + 1 + m, cmp);
	
	lf[0] = rh[0] = 1; widden(1);
	for(int i = 1; i <= m; ++i){
		int k = rnk[i], kk = rnk[i-1];
		for(int j = lf[k]; j < lf[kk]; ++j) widden(j);
		for(int j = rh[k]; j > rh[kk]; --j) widden(j);
		for(int j = lf[kk]; j < lf[k]; ++j) shorten(j);
		for(int j = rh[kk]; j > rh[k]; --j) shorten(j);
		answ[k] = ans;
	}
	
	for(int i = 1; i <= m; ++i){
		if(answ[i] == 0){
			puts("0/1");
			continue;
		}
		int lnth = rh[i] - lf[i] + 1;
		long long t = 1LL * lnth * (lnth - 1) / 2;
		long long g = gcd(answ[i], t);
		printf("%lld/%lld\n", answ[i] / g, t / g);
	}
	
	return 0;
}
