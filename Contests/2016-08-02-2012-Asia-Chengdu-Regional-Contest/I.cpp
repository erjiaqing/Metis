#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1005;
const int P = 1e9 + 7;
vector<int> Q[N];
int n, f[N][N], ans[N];

int main() {
	n = 1000;
	memset(f, 0, sizeof(f));
	f[1][1] = 1;
	for(int i = 1; i <= n; i++) Q[i].clear();
	Q[1].push_back(1);
	
	for (int i = 1; i <= n; i++) {
		for (int p = 0; p < (int)Q[i].size(); p++) {
			int j = Q[i][p];
			for (int k = j; i + k <= n; k += j) {
				if (f[i + k][k] == 0) Q[i + k].push_back(k);
				f[i + k][k] += f[i][j];
				f[i + k][k] %= P;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		ans[i] = 0;
		for	(int j = 1; j <= n; j++)
			ans[i] += f[i][j], ans[i] %= P;
	}
	
	int cases = 0;
	while (scanf("%d", &n) == 1) {
		cases++;
		printf("Case %d: %d\n", cases, ans[n]);
	}
	return 0;
}
