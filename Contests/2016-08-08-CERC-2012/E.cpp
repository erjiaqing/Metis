#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

const int N = 2005;
map<int, int> ind;
char s[50], a[N][10], b[2005];
int p, l;
int n, p1[N], p2[N], len[N];
bool mark[N];
int tot, id[N * 2], lst[N], nxt[N * 2], d[N];
int f[N][2005];
queue<int> Q;

void Add(int x, int y) {
    id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot; d[y]++;
}

int get(int &p) {
    while (p <= l && (s[p] < 'A' || s[p] > 'Z')) p++;
    int t = 0;
    while (p <= l && s[p] >= 'A' && s[p] <= 'Z') {
        t = t * 27 + s[p] - 'A' + 1;
        p++;
    }
    if (!ind[t]) ind[t] = ++n;
    return ind[t];
}

void readin() {
    gets(s + 1);
    l = strlen(s + 1);
    int tp = 0, x, y, z;
    for (int i = 1; i <= l; i++)
        if (s[i] == '+') tp = 1;
    
    if (tp == 0) {
        p = 1;
        x = get(p);
        mark[x] = 1;
        Q.push(x);
        
        while (s[p] < 'a' || s[p] > 'z') p++;
        int t = 0;
        while (s[p] >= 'a' && s[p] <= 'z') {
            a[x][t++] = s[p];
            p++;
        }
        len[x] = t;
        /*printf("%d = ", x);
         for (int i = 0; i < len[x]; i++) printf("%c", a[x][i]);
         puts("");*/
    }
    else {
        p = 1;
        z = get(p);
        x = get(p);
        y = get(p);
        //printf("%d = %d + %d\n", z, x, y);
        Add(x, z);
        Add(y, z);
        p1[z] = x;
        p2[z] = y;
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (mark[i]) {
            for (int j = 1; j <= l; j++) {
                int p = j;
                for (int k = 0; k < len[i]; k++) {
                    if (a[i][k] == b[p]) p++;
                    if (p > l) break;
                }
                f[i][j] = p;
            }
        }
        f[i][l + 1] = l + 1;
    }
    
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        //cerr<<"...."<<x<<endl;
        for (int i = lst[x]; i; i = nxt[i]) {
            int y = id[i];
            d[y]--;
            if (d[y] == 0) {
                Q.push(y);
                for (int j = 1; j <= l; j++) {
                    f[y][j] = f[p2[y]][f[p1[y]][j]];
                }
            }
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        n = 0; ind.clear();
        memset(mark, 0, sizeof(mark));
        tot = 0; memset(lst, 0, sizeof(lst));
        while (!Q.empty()) Q.pop();
        memset(d, 0, sizeof(d));
        
        int m; scanf("%d", &m); getchar();
        for (int i = 1; i <= m; i++) {	
            readin();
        }
        
        gets(s + 1);
        l = strlen(s + 1);
        p = 1;
        int tar = get(p);
        gets(b + 1);
        l = strlen(b + 1);
        solve();
        if (f[tar][1] == l + 1) puts("YES");
        else puts("NO");
    }
    return 0;
}