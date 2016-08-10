#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

char a[505][15];
int len[505];
int n, m;
int f[30][30], d[30];
queue<int> Q;
bool bo;

void Add(int x, int y) {
	if (!f[x][y]) d[y]++;
	f[x][y] = 1;
}

void work(int l, int r, int k) {
	//printf("%d %d %d\n", l, r, k);
	if (!bo) return ;
	if (l == r) return ;
	while (l <= r && k > len[l]) l++;
	if (l >= r) return ;
	int lst = l;
	for (int i = l + 1; i <= r; i++) {
		if (k > len[i]) {
			bo = 0;
			return ;
		}
		if (a[i][k] != a[i - 1][k]) {
			Add(a[i - 1][k] - 'a' + 1, a[i][k] - 'a' + 1);
			work(lst, i - 1, k + 1);
			lst = i;
		}
	}
	work(lst, r, k + 1);
}

void bfs() {
	while (!Q.empty()) Q.pop();
	for (int i = 1; i <= 26; i++)
		if (d[i] == 0) Q.push(i);
	while (!Q.empty()) {
		int x = Q.front();
		m--; Q.pop();
		for (int i = 1; i <= 26; i++)
			if (f[x][i] && d[i]) {
				d[i]--;
				if (d[i] == 0) Q.push(i);
			}
	}
}

int main() {
	while (true) {
		memset(f, 0, sizeof(f));
		memset(d, 0, sizeof(d));
	
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++) {
			scanf("%s", a[i] + 1);
			len[i] = strlen(a[i] + 1);
		}
		bo = 1;
		work(1, n, 1);
		//cerr<<bo<<endl;
		/*for (int i = 1; i <= 26; i++) {
			for (int j = 1; j <= 26; j++)
				printf("%d", f[i][j]);
			puts("");
		}*/
		if (!bo) {
			puts("no");
			continue;
		}
		m = 26;
		bfs();
		if (m) puts("no"); else puts("yes");
	}
	return 0;
}
