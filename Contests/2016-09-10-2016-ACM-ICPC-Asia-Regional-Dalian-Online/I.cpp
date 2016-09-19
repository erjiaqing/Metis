#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

const int N = 400005;
const int M = 400050;

set<int> h, ch;
int n, m, S, Ans[N];
int d[N], q[N];
bool vis[N];
int tot, id[M], nxt[M], lst[N];

void Add(int x, int y) {
	id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot;
}

void solve() {
	memset(vis, 1, sizeof(vis)); vis[S] = 0;
	int rst = n - 1, m, ans;
	set<int>::iterator it;
	for (int i = lst[S]; i; i = nxt[i]) vis[id[i]] = 0;
	
	m = 0; ans = 1;
	h.clear();
	for (int i = 1; i <= n; i++)
		if (i != S) h.insert(i);
	
	for (int i = 1; i <= n; i++)
		if (vis[i]) {
			h.erase(i);
			q[++m] = i;
			Ans[i] = ans;
			rst--;
		}
	if (m == 0) return;	
	while (rst) {
		ans++;
		for (it = h.begin(); it != h.end(); it++) d[*it] = 0;
		for (int i = 1; i <= m; i++) {
			int x = q[i];
		//printf("%d\n", i);
			for (int j = lst[x]; j; j = nxt[j]) {
				int y = id[j];// printf(",,,%d\n", y);
				if (!vis[y]) d[y]++;
			}
		}
			
		//for (int i = 1; i <= n; i++) printf("%d ", d[i]); puts("");
		int cm = m; m = 0; //cout<<'.'<<cm<<endl;
		ch.clear();
		//cout<<ans<<endl;
		for (it = h.begin(); it != h.end(); it++) {
			int x = *it;
			if (d[x] < cm) {
			//cout<<x<<endl;
				//h.erase(x);
				vis[x] = 1;
				q[++m] = x;
				Ans[x] = ans;
				rst--;
			} else ch.insert(x);
		}
		h = ch;
		
		if (m == 0) return;
		//cout<<ans<<endl;
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		tot = 0; memset(lst, 0, sizeof(lst));
	
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y); Add(y, x);
		}
		scanf("%d", &S);
		
		memset(Ans, -1, sizeof(Ans));
		solve();
		int tot = 0;
		for (int i = 1; i <= n; i++)
			if (i != S) printf("%d%c", Ans[i], " \n"[++tot == n - 1]);
	}
	return 0;
}
