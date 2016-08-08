#include <set>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 105;
const int maxm = 5e4 + 5;

set<string> st;

int n, m, tot, ans;
long long a[maxn], b[maxn], c[maxn];
long long x[maxm], y[maxm];

char check(int i, int j){
	long long rtn = a[i] * x[j] + b[i] * y[j] + c[i];
	if(rtn < 0) return '1';
	else return '0';
}

void work(){
	
	tot = 1;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	for(int i = 1; i <= m; ++i) scanf("%lld%lld", &x[i], &y[i]);
	for(int i = 1; i <= n; ++i){
		++tot;
		for(int j = 1; j < i; ++j)
			if(1LL * a[i] * b[j] - 1LL * a[j] * b[i]) ++tot;
	}
	
	st.clear();
	ans = 0;
	for(int i = 1; i <= m; ++i){
		string tmp = "";
		for(int j = 1; j <= n; ++j) tmp += check(j, i);
		if(st.find(tmp) == st.end()) ++ans;
		st.insert(tmp);
	}
	if(tot == ans) puts("PROTECTED");
	else puts("VULNERABLE");
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
