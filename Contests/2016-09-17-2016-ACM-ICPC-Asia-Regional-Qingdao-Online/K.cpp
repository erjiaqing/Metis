#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 1005;
const int M = 20005;
const int inf = 1e8;

int n, m, S, T;
int tot, id[M], nxt[M], lst[N], cap[M];
int Tot, Id[M], Nxt[M], Lst[N], Len[M];
int d[N], q[N], dis[N];

void Add(int x, int y, int z) {
    Id[++Tot] = y; Nxt[Tot] = Lst[x]; Lst[x] = Tot; Len[Tot] = z;
}
void add(int x, int y, int z) {
//printf("%d %d %d\n", x, y, z);
    id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot; cap[tot] = z;
}

void bfs() {
    int S = 1, l, r;
    l = r = 1; q[1] = S;
    memset(d, -1, sizeof(d)); d[S] = 0;
    while (l <= r) {
        int x = q[l++];
        for (int i = Lst[x]; i; i = Nxt[i]) {
            int y = Id[i];
            if (d[y] == -1) {
                d[y] = d[x] + 1;
                if (y == n) return;
                q[++r] = y;
            }
        }
    }
}

void build() {
    int S = n, l, r;
    l = r = 1; q[1] = S;
    memset(dis, -1, sizeof(dis)); dis[S] = 0;
    while (l <= r) {
        int x = q[l++];
        for (int i = Lst[x]; i; i = Nxt[i]) {
            int y = Id[i];
            if (dis[y] == -1) {
                dis[y] = dis[x] + 1;
                q[++r] = y;
            }
            if (dis[x] + 1 + d[y] == d[n]) {
                add(x, y, Len[i]);
                add(y, x, 0);
            }
        }
    }
}

bool Bfs(int S) {
    int l, r;
    l = r = 1; q[1] = S;
    memset(d, -1, sizeof(d)); d[S] = 0;
    while (l <= r) {
        int x = q[l++];
        for (int i = lst[x]; i; i = nxt[i]) {
            int y = id[i];
            if (d[y] == -1 && cap[i]) {
                d[y] = d[x] + 1;
                if (y == T) return 1;
                q[++r] = y;
            }
        }
    }
    return 0;
}

int find(int x, int flow) {
    if (x == T) return flow;
    int res = 0, y;
    for (int i = lst[x]; i; i = nxt[i])
        if (cap[i] && d[y = id[i]] == d[x] + 1) {
            int now = find(y, min(flow - res, cap[i]));
            res += now;
            cap[i] -= now; cap[i ^ 1] += now;
        }
    if (!res) d[x] = -1;
    return res;
}

int Dinic() {
    int ans = 0;
    S = n; T = 1;
    while (Bfs(S)) {
        ans += find(S, inf);
        //printf("%d\n", ans);
    }
    return ans;
}

int main() {
    int Test; scanf("%d", &Test);
    while (Test--) {
        tot = 1; memset(lst, 0, sizeof(lst));
        Tot = 1; memset(Lst, 0, sizeof(Lst));
    
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            Add(x, y, z); Add(y, x, z);
        }
        
        bfs();
        if (d[n] == -1) {
            puts("0");
            continue;
        }
        //for (int i = 1; i <= n; i++) printf("%d ", d[i]); puts("");
        build();
        //for (int i = 1; i <= n; i++) printf("%d ", dis[i]); puts("");
        
        printf("%d\n", Dinic());
    }
    return 0;
}
