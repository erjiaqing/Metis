#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3 + 5;
const int mod  = 1e9 + 7;

int n, s, w[maxn];
int f[maxn][maxn][3][3];

void add(int &x, int y){
	x += y;
	x -= x >= mod ? mod : 0;
}

void work(){
	
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
	memset(f, 0, sizeof f);
	f[0][0][0][0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= s; ++j)
			for(int s1 = 0; s1 <= 2; ++s1)
				for(int s2 = 0; s2 <= 2; ++s2){
					add(f[i][j][s1][s2], f[i-1][j][s1][s2]);
					if(s2 >= 1) add(f[i][j][s1][s2], f[i-1][j][s1][s2-1]);
					if(j >= w[i]){
						add(f[i][j][s1][s2], f[i-1][j-w[i]][s1][s2]);
						if(s1 >= 1) add(f[i][j][s1][s2], f[i-1][j-w[i]][s1-1][s2]);
					}
				}
	int ans = 0;
	for(int i = 0; i <= s; ++i) add(ans, f[n][i][2][2]);
	cout << 4LL * ans % mod  << endl;
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
