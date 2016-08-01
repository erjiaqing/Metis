#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 35;
const int M = 2000000;
const int dx[5] = {-1, 1, 0, 0, 0};
const int dy[5] = {0, 0, -1, 1, 0};

struct status {
	int x1, y1, x2, y2, now;
	status() {}
	status(int x1, int y1, int x2, int y2, int now) : x1(x1), y1(y1), x2(x2), y2(y2), now(now) {}
} h[M];

queue<int> Q;
char mp[N][N];
int n, m, f[M], deg[M];
int Id[N][N][N][N][2];
int Ax, Ay, Qx, Qy;

void pretreat() {
	memset(deg, 0, sizeof(deg));
	int cnt = 0;
	for (int x1 = 1; x1 <= n; x1++)
	for (int y1 = 1; y1 <= m; y1++)
	if (mp[x1][y1] != '#')
		for (int x2 = 1; x2 <= n; x2++)
		for (int y2 = 1; y2 <= m; y2++)
		if (mp[x2][y2] != '#') 
			for (int now = 0; now < 2; now++) {
				Id[x1][y1][x2][y2][now] = ++cnt;
				h[cnt] = status(x1, y1, x2, y2, now);
				if (now == 0) f[cnt] = 0; else f[cnt] = 4;
				
				if (x1 == x2 && y1 == y2) { //catch
					f[cnt] = 3;
					Q.push(cnt);
					continue;
				}
				
				if (now == 1 && mp[x2][y2] == 'E') { //escape
					f[cnt] = 1;
					Q.push(cnt);
					continue;
				}
				
				for (int i = 0; i < 5; i++)
					if (now == 0) {
						int x = x1 + dx[i];
						int y = y1 + dy[i];
						if (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#')
							deg[cnt]++;
					}
					else {
						int x = x2 + dx[i];
						int y = y2 + dy[i];
						if (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#')
							deg[cnt]++;
					}
			}
}

void bfs() {
	while (!Q.empty()) {
		int cur = Q.front(); Q.pop();
		int x1 = h[cur].x1, y1 = h[cur].y1, x2 = h[cur].x2, y2 = h[cur].y2, now = h[cur].now;
		//cerr<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<now<<" "<<f[cur]<<endl;
		
		for (int i = 0; i < 5; i++)
			if (now == 1) {
				int x = x1 + dx[i];
				int y = y1 + dy[i];
				if (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#') {
					int pre = Id[x][y][x2][y2][now ^ 1];
					if (f[pre] == 3 || deg[pre] == 0) continue;
					//if(pre == 4) cerr<<" hhh "<<deg[pre]<<" "<<f[pre]<<endl;
					f[pre] = max(f[pre], f[cur]);
					deg[pre]--;
					if (f[pre] == 3 || deg[pre] == 0) Q.push(pre); 
				}
			}
			else {
				int x = x2 + dx[i];
				int y = y2 + dy[i];
				if (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#') {
					int pre = Id[x1][y1][x][y][now ^ 1];
					if (f[pre] == 1 || deg[pre] == 0) continue;
					//if(pre == 4) cerr<<" hhhh "<<deg[pre]<<" "<<f[pre]<<endl;
					f[pre] = min(f[pre], f[cur]);
					deg[pre]--;
					if (f[pre] == 1 || deg[pre] == 0) Q.push(pre);
				}
			}
	}
}

int main() {
	while (true) {
		scanf("%d%d", &m, &n);
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				cin >> mp[i][j];
				if (mp[i][j] == 'A') Ax = i, Ay = j;
				if (mp[i][j] == 'Q') Qx = i, Qy = j;
			}
		pretreat();
		bfs();
		if (deg[Id[Ax][Ay][Qx][Qy][1]] && f[Id[Ax][Ay][Qx][Qy][1]] != 1)
			puts("Queen can not escape and Army can not catch Queen.");
		else if (f[Id[Ax][Ay][Qx][Qy][1]] == 3)
			puts("Army can catch Queen.");
		else if (f[Id[Ax][Ay][Qx][Qy][1]] == 1)
			puts("Queen can escape.");
	}
	return 0;
}
