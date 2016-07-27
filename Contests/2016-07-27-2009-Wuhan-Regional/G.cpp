#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 305;
const int inf = 1e9;

int v1, v2, n, f[2][505][60][2];
int s[maxn], p[maxn], h[maxn];

void work(){
	
	for(int i = 1; i <= n; ++i) scanf("%d%d%d", &p[i], &h[i], &s[i]);
	for(int i = 0; i <= v1; ++i)
		for(int j = 0; j <= v2; ++j)
			for(int k = 0; k < 2; ++k)
				for(int l = 0; l < 2; ++l)
					f[k][i][j][l] = -inf;
	
	f[0][0][0][0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= v1; ++j)
			for(int k = 0; k <= v2; ++k){
				int ii = i & 1;
				if(s[i]){
					f[ii][j][k][1] = f[ii^1][j][k][0] + h[i];
					f[ii][j][k][0] = -inf;
					if(j >= p[i]) f[ii][j][k][0] = max(f[ii][j][k][0], f[ii^1][j-p[i]][k][0] + h[i]);
					if(k >= p[i]) f[ii][j][k][0] = max(f[ii][j][k][0], f[ii^1][j][k-p[i]][0] + h[i]);
					if(j >= p[i]) f[ii][j][k][1] = max(f[ii][j][k][1], f[ii^1][j-p[i]][k][1] + h[i]);
					if(k >= p[i]) f[ii][j][k][1] = max(f[ii][j][k][1], f[ii^1][j][k-p[i]][1] + h[i]);
				} else{
					f[ii][j][k][0] = f[ii^1][j][k][0];
					f[ii][j][k][1] = f[ii^1][j][k][1];
					f[ii][j][k][1] = max(f[ii][j][k][1], f[ii^1][j][k][0] + h[i]);
					if(j >= p[i]) f[ii][j][k][0] = max(f[ii][j][k][0], f[ii^1][j-p[i]][k][0] + h[i]);
					if(k >= p[i]) f[ii][j][k][0] = max(f[ii][j][k][0], f[ii^1][j][k-p[i]][0] + h[i]);
					if(j >= p[i]) f[ii][j][k][1] = max(f[ii][j][k][1], f[ii^1][j-p[i]][k][1] + h[i]);
					if(k >= p[i]) f[ii][j][k][1] = max(f[ii][j][k][1], f[ii^1][j][k-p[i]][1] + h[i]);
				}
				//printf("f[%d][%d][%d][%d] = %d\n", i, j, k, 0, f[i&1][j][k][0]);
				//printf("f[%d][%d][%d][%d] = %d\n", i, j, k, 1, f[i&1][j][k][1]);
			}
	
	int ans = 0;
	for(int i = 0; i <= v1; ++i)
		for(int j = 0; j <= v2; ++j)
			ans = max(ans, max(f[n&1][i][j][0], f[n&1][i][j][1]));
	if(ans <= 0) puts("-1");
	else printf("%d\n", ans);
}

int main(){

	int t = 0;
	while(true){
		scanf("%d%d%d", &v1, &v2, &n);
		if(v1 + v2 + n == 0) break;
		++t;
		printf("Case %d: ", t);
		work();
		puts("");
	}

	return 0;
}
