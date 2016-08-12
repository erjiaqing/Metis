#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6 + 5;

int n, ans;
long long a[maxn], s[maxn];

void work(){
	
	for(int i = 1; i <= n; ++i){
		int x;
		scanf("%d", &x);
		a[i] = 1LL * x;
	}
	s[n+1] = 0;
	for(int i = n; i >= 1; --i) s[i] = s[i+1] + a[i];
	ans = 0;
	for(int i = n, lst = n + 1; i >= 1; --i){
		if(s[i] - s[lst] >= 0){
			++ans;
			lst = i;
		}
	}
	printf("%d\n", ans);
}

int main(){
	
	while(scanf("%d", &n) == 1) work();

	return 0;
}
