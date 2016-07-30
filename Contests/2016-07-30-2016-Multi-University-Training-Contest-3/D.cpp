#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxr = 50;
const int maxn = 1000;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int r, c, w[maxr][maxr], a[maxn][maxn], n;

int id(int i, int j){
	
	if(i < 1 || i > r) return 0;
	if(j < 1 || j > c) return 0;
	return j + c * (i - 1);
}

void gauss(){

		
	for(int i = 1; i <= n; ++i){
		int t = i;
		for(int j = i; j <= n; ++j) if(a[j][i]){t = j; break;}
		for(int j = i; j <= n; ++j) swap(a[i][j], a[t][j]); swap(a[i][0], a[t][0]);
		
		int inv = a[i][i];
		for(int j = i + 1; j <= n; ++j){
		if(a[j][i] != 0)
		{
			int t = a[j][i] * inv % 3;
			for(int k = i; k <= n; ++k){
				a[j][k] -= a[i][k] * t - 6;
				a[j][k] %= 3;
			}
			a[j][0] -= a[i][0] * t - 6;
			a[j][0] %= 3;
			}
		}
	}
	
	for(int i = n; i >= 1; --i){
		int inv = a[i][i];
		for(int j = i + 1; j <= n; ++j){
			a[i][0] -= a[i][j] * a[j][0] - 6;
			a[i][0] %= 3;
		}
		a[i][0] = a[i][0] * inv % 3;
	}
}

pair<int, int> trans(int x){
	int j = x % c ? x % c : c;
	int i = (x - j) / c + 1;
	return make_pair(i, j);
}

vector<pair<int, int> > ans;

void work(){
	
	scanf("%d%d", &r, &c);
	n = r * c;
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j){
			scanf("%d", &w[i][j]);
			int u = id(i, j);
			//printf("u : %d %d\n", i, j);
			a[u][0] = 6 - w[i][j];
			a[u][0] %= 3;
			a[u][u] = 2;
			for(int k = 0; k < 4; ++k){
				int v = id(i + dx[k], j + dy[k]);
				if(!v) continue;
				//printf("    v : %d %d\n", i + dx[k], j + dy[k]);
				a[u][v] = 1;
			}
		}
	
	/*for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			printf("%d%c", a[i][j], " \n"[j==n]);*/
	
	gauss();
	ans.clear();
	for(int i = 1; i <= n; ++i){
		//printf("%d : %d\n", i, a[i][0]);
		for(int j = 1; j <= a[i][0]; ++j)
			ans.push_back(trans(i));
	}
	printf("%d\n", ans.size());
	memset(a, 0, sizeof a);
	int A = ans.size();
	for(int i = 0; i < A; ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
