#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxm = 1e3 + 5;
const int maxl = 15;

int n, m, l, fail[maxl];
double f[maxm][maxl], w[50];
char str[maxl];

void get_fail(){
	
	for(int i = 2, j = 0; i <= l; ++i){
		while(j && str[i] != str[j+1]) j = fail[j];
		if(str[i] == str[j+1]) ++j;
		fail[i] = j;
	}
}

void work(){
	
	for(int i = 0; i < 26; ++i) w[i] = 0.00;
	for(int i = 1; i <= n; ++i){
		char ch = getchar();
		ch = getchar();
		scanf("%lf", &w[ch-'a']);
	}
	scanf("%s", str + 1);
	//puts(str + 1);
	l = strlen(str + 1);
	get_fail();
	
	for(int i = 0; i <= m; ++i)
		for(int j = 0; j <= l; ++j)
			f[i][j] = 0.00;
	f[0][0] = 1.00;
	for(int i = 0; i < m; ++i){
		f[i+1][l] += f[i][l];
		for(int j = 0; j < l; ++j)
			for(int k = 0; k < 26; ++k){
				int jj = j;
				char ch = k + 'a';
				while(jj && str[jj+1] != ch) jj = fail[jj];
				if(str[jj+1] == ch) ++jj;
				f[i+1][jj] += f[i][j] * w[k];
			}
	}
	printf("%.2f%c\n", f[m][l] * 100.00, '%');
}

int main(){
	
	while(true){
		
		scanf("%d%d", &n, &m);
		if(n + m == 0) break;
		work();
	}

	return 0;
}
