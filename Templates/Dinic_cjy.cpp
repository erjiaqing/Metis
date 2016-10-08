#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 20000;
const int inf = 100000;
int tot, id[N], nxt[N], lst[N], cap[N];
int d[N];
queue<int> Q;

void Add(int x, int y, int z) {
	id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot; cap[tot] = z;
	id[++tot] = x; nxt[tot] = lst[y]; lst[y] = tot; cap[tot] = 0;
}

bool bfs() {
	while (!Q.empty()) Q.pop();
	Q.push(S);
	memset(d, 0, sizeof(d)); d[S] = 1;
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		for (int i = lst[x]; i; i = nxt[i]) {
			int y = id[i];
			if (cap[i] && !d[y]) {
				d[y] = d[x] + 1;
				if (y == T) return true;
				Q.push(y);
			}
		}
	}
	return false;
}

int find(int x, int flow) {
	if (x == T) return flow;
	int res = 0;
	for (int i = lst[x]; i; i = nxt[i]) {
		int y = id[i];
		if (cap[i] && d[y] == d[x] + 1) {
			int now = find(y, min(flow - res, cap[i]));
			res += now;
			cap[i] -= now, cap[i ^ 1] += now;
		}
	}
	if (!res) d[x] = -1;
	return res;
} 

int dinic() {
	int ans = 0;
	while (bfs())
		ans += find(S, inf);
	return ans; 
}

int main() {
	tot = 1; memset(lst, 0, sizeof(lst));
	
	printf("%d\n", dinic());
	return 0;
}
