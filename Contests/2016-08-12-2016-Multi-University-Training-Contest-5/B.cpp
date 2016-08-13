#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;

const int maxn = 1e4 + 5;

int n, fail[2][maxn];
char s[2][maxn], ans[maxn];
bitset<maxn> all_fail[2][maxn], mrch[2][maxn];

void get_fail(int k){
	
	memset(fail[k], 0, sizeof fail[k]);
	for(int i = 0; i <= n; ++i) all_fail[k][i] = 0;
	if(k == 0) all_fail[k][1][n] = all_fail[k][0][n] = all_fail[k][1][n-1] = 1;
	else all_fail[k][1][0] = all_fail[k][0][0] = all_fail[k][1][1] = 1;
	for(int i = 2, j = 0; i <= n; ++i){
		while(j && s[k][i] != s[k][j+1]) j = fail[k][j];
		if(s[k][i] == s[k][j+1]) ++j;
		fail[k][i] = j;
		if(k == 0){
			all_fail[k][i] = all_fail[k][j];
			all_fail[k][i][n-i] = 1;
		}else{
			all_fail[k][i] = all_fail[k][j];
			all_fail[k][i][i] = 1;
		}
	}
}

void march(int k){
	
	for(int i = 1, j = 0; i <= n; ++i){
		while(j && s[k][i] != s[!k][j+1]) j = fail[!k][j];
		if(s[k][i] == s[!k][j+1]) ++j;
		mrch[k][i] = all_fail[!k][j];
		if(j == n) j = fail[!k][j];
	}
}

void work(){
	
	scanf("%s", s[1] + 1);
	n = strlen(s[1] + 1);
	for(int i = 0; i < 2; ++i) get_fail(i);
	for(int i = 0; i < 2; ++i) march(i);
	for(int i = 1; i <= n; ++i){
		if((mrch[0][i] & (mrch[1][i] >> (n - i))).count()) ans[i-1] = '1';
		else ans[i-1] = '0';
	}
	puts(ans);
	memset(ans, 0, sizeof ans);
}

int main(){
	
	while(scanf("%s", s[0] + 1) != EOF) work();

	return 0;
}
