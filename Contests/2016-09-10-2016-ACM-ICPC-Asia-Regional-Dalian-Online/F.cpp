#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 5;

int n;
int a[maxn], s[maxn];

void work(){
	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; ++i) s[i] = s[i-1] + a[i];
	bool flag = false;
	if(s[n] != n * (n - 1)) flag = true;
	for(int i = 2; i <= n; ++i) if(s[i] < i * (i - 1)) flag = true;
	if(flag) puts("F");
	else puts("T");
}

int main(){
	
	int t;
	while(scanf("%d", &t) == 1){
		while(t--) work();
	}

	return 0;
}
