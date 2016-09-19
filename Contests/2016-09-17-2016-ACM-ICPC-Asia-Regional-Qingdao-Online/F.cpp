#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
const int M = 1e6 + 10;
int n, m, a[N], d[N], tot, ans;
bool vis[N];
int id[M], lst[N], nxt[M];

void Add(int x, int y) {
    id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot;
}

void dfs(int x) {
    tot++;
    vis[x] = 1;
    for (int i = lst[x]; i; i = nxt[i]) {
        int y = id[i];
        if (!vis[y]) dfs(y);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        tot = 0; memset(lst, 0, sizeof(lst));
        memset(d, 0, sizeof(d));
        
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            Add(x, y); Add(y, x);
            d[x]++; d[y]++;
        }
        
        bool ok = 1;
        memset(vis, 0, sizeof(vis));
        tot = 0;
        for (int i = 1; i <= n; i++)
            if (d[i] == 0) tot++;
        /*if (tot == n) {
            int ans = 0;
            for (int i = 1; i <= n; i++)
                if (a[i] > ans) ans = a[i];
            printf("%d\n", ans);
            continue;
        }*/
        
        for (int i = 1; i <= n; i++)
            if (d[i]) {
                dfs(i);
                break;
            }
        if (tot < n) ok = 0;
        
        tot = 0;
        for (int i = 1; i <= n; i++)
            if (d[i] & 1) tot++;
        if (tot > 2) ok = 0;
        
        if (!ok) puts("Impossible");
        else {
            ans = 0;
            for (int i = 1; i <= n; i++) {
                int t = (d[i] + 1) / 2;
                if (t & 1) ans ^= a[i];
            }
            
            if (tot == 0) {
                int cans = ans;
                ans = 0;
                for (int i = 1; i <= n; i++)
                    if (d[i]) {
                        int tmp = cans ^ a[i];
                        if (tmp > ans) ans = tmp;
                    }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
