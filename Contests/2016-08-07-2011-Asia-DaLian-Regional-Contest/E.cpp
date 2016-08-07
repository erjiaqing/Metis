#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3 + 5;
const int p = 1e9 + 7;

int n, f[maxn][maxn], s[maxn][maxn];
char str[maxn];

void work(){
	
	n = strlen(str) + 1;
	f[1][1] = s[1][1] = 1;
	for(int i = 2; i <= n; ++i){
		if(str[i-2] == 'I'){
			f[i][i] = s[i-1][i-1];
			for(int j = 1; j < i; ++j)
				f[i][j] = s[i-1][j-1];
		}
		if(str[i-2] == 'D'){
			f[i][i] = 0;
			for(int j = 1; j < i; ++j)
				f[i][j] = s[i-1][i-1] - s[i-1][j-1], f[i][j] += f[i][j] < 0 ? p : 0;
		}
		if(str[i-2] == '?'){
			for(int j = 1; j <= i; ++j)
				f[i][j] = s[i-1][i-1];
		}
		for(int j = 1; j <= i; ++j) s[i][j] = s[i][j-1] + f[i][j], s[i][j] -= s[i][j] >= p ? p : 0;
	}
	printf("%d\n", s[n][n]);
	
	memset(f, 0, sizeof f);
	memset(s, 0, sizeof s);
	memset(str, 0, sizeof str);
}

int main(){
	
	while(gets(str)) work();

	return 0;
}
