#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int p = 1e9 + 7;

const int maxn = 1e5 + 5;

int n, m, fail[maxn], f[maxn];
char str[maxn], pat[maxn];

void get_fail(){
	
	fail[0] = fail[1] = 0;
	for(int i = 2, j = 0; i <= m; ++i){
		while(j && pat[i] != pat[j+1]) j = fail[j];
		if(pat[i] == pat[j+1]) ++j;
		fail[i] = j;
	}
}

void kmp(){
	
	f[0] = 1;
	for(int i = 1, j = 0; i <= n; ++i){
		f[i] = f[i-1];
		while(j && str[i] != pat[j+1]) j = fail[j];
		if(str[i] == pat[j+1]) ++j;
		if(j == m){
			f[i] += f[i-m];
			f[i] %= p;
			j = fail[j];
		}
	}
}

void work(){
	
	scanf("%s", str + 1);
	scanf("%s", pat + 1);
	n = strlen(str + 1);
	m = strlen(pat + 1);
	get_fail();
	kmp();
	printf("%d\n", f[n]);
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
