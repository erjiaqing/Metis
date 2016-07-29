#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 7e5 + 5;

long long ans;
int n, nxt[maxn];
char str[maxn], ch;

int rk[maxn], sa[maxn];

int sum[maxn], tsa[maxn], trk[maxn];
void get_sa(int j){
	
	memset(sum, 0, sizeof sum);
	for(int i = 1; i <= n; ++i) ++sum[rk[i+j]];
	for(int i = 1; i <= n; ++i) sum[i] += sum[i-1];
	for(int i = n; i >= 1; --i) tsa[sum[rk[i+j]]--] = i;
	memset(sum, 0, sizeof sum);
	for(int i = 1; i <= n; ++i) ++sum[rk[i]];
	for(int i = 1; i <= n; ++i) sum[i] += sum[i-1];
	for(int i = n; i >= 1; --i) sa[sum[rk[tsa[i]]]--] = tsa[i];
}

void calc_sa(){
	
	memset(rk, 0, sizeof rk);
	memset(sum, 0, sizeof sum);
	for(int i = 1; i <= n; ++i) ++sum[str[i]];
	for(int i = 1; i <= 256; ++i) sum[i] += sum[i-1];
	for(int i = n; i >= 1; --i) sa[sum[str[i]]--] = i;
	rk[sa[1]] = 1;
	for(int i = 2, p = 1; i <= n; ++i){
		if(str[sa[i]] != str[sa[i-1]]) ++p;
		rk[sa[i]] = p;
	}
	for(int j = 1; j <= n; j <<= 1){
		get_sa(j);
		trk[sa[1]] = 1;
		for(int i = 2, p = 1; i <= n; ++i){
			if(rk[sa[i]] != rk[sa[i-1]] || rk[sa[i]+j] != rk[sa[i-1]+j]) ++p;
			trk[sa[i]] = p;
		}
		for(int i = 1; i <= n; ++i) rk[i] = trk[i];
	}
}

int hght[maxn];
void calc_hght(){
	
	for(int i = 1, j = 0; i <= n; ++i){
		if(rk[i] == 1) continue;
		while(i + j <= n && sa[rk[i]-1] + j <= n && str[i+j] == str[sa[rk[i]-1]+j]) ++j;
		hght[rk[i]] = j;
		if(j > 0) --j;
	}
}

void work(){
	
	ch = getchar();
	ch = getchar();
	scanf("%s", str + 1);
	n = strlen(str + 1);
	//puts(str + 1);
	for(int i = n, lst = n + 1; i >= 1; --i){
		if(str[i] == ch) lst = i;
		nxt[i] = lst - i + 1;
	}
	calc_sa();
	calc_hght();
	/*
	puts("");
	for(int i = 1; i <= n; ++i){
		for(int j = sa[i]; j <= n; ++j) putchar(str[j]);
		printf(" %d\n", hght[i]);
	}
	*/
	ans = 0;
	for(int i = 1; i <= n; ++i){
		int ii = rk[i];
		int d = max(nxt[sa[i]] - 1, hght[i]);
		ans += n - sa[i] - d + 1;
	}
	cout << ans << endl;
	memset(str, 0, sizeof str);
	memset(rk, 0, sizeof rk);
	memset(sa, 0, sizeof sa);
	memset(hght, 0, sizeof hght);
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
