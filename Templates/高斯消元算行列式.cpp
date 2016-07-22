 #include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n, r, t;
const int pp=10007;
int e[333][333];
int fa[333];

struct Point{
    int x, y;
    int num;
    Point() {}
    Point(int x, int y, int num = -1) : x(x), y(y), num(num) {}
};
Point p[333];
int dist2(const Point &p) {
    return p.x * p.x + p.y * p.y;
}
Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

int dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int find(int x) {
    if (fa[x] == x) return x;
    else {
        fa[x] = find(fa[x]);
        return fa[x];
    }
}

void addedge(int x, int y) {
    e[x][x]++;
    e[x][y] = -1;
    int fax=find(fa[x]);
    int fay=find(fa[y]);
    if (fax != fay) fa[fax] = fay;
}

int P(int x, int k) {
    if (k == 0) return 0;
    if (k == 1) return x;
    int ret = P(x, k / 2);
    ret = ret *ret % pp;
    if (k & 1) ret = ret * x % pp;
    return ret;
}

void Guass() {
    --n;
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int pos = i; int mx = 0;
        for (int j = i; j <= n; j++)
            if (abs(e[j][i])>mx) {
                mx = abs(e[j][i]);
                pos = j;
            }
        if (pos != i) {
            for (int j = 1; j <= n; j++) {
                swap(e[i][j], e[pos][j]);
            }
            ans *= -1;
        }
        int inv = P(e[i][i], pp - 2);
        for (int j = i+1;j <= n; j++) {
            int t = inv * e[j][i] % pp;
            for (int k = i; k <= n; k++)
                e[j][k] = (e[j][k] - t*e[i][k]) % pp;
        }
    }
    for (int i = 1; i <= n; i++)
        ans = ans * e[i][i] % pp;
    if (ans < 0) ans += pp;
    cout << ans << endl;
}

void doit(int k) {
    Point a[333];
    int m = 0;
    for (int i = 1;i <= n; i++)
        if (i != k && dist2(p[i] - p[k]) <= r*r) {
            bool flag = 1;
            for (int j = 1;j <= n ; j++)
                if (j != k && j !=i) {
                    if (cross(p[j] - p[k],p[i] - p[k]) ==0 && dot(p[j] - p[k],p[i] - p[k]) >0 && dist2(p[j] - p[k]) < dist2(p[i] - p[k])) {
                        flag = 0;
                        break;
                    }
                }
            if (flag) addedge(k, i);
        }
}

void solve() {
    cin >> n >> r;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    for (int i = 1;i <=n; i++) fa[i] = i;
    memset(e, 0, sizeof(e));
    for (int i = 1;i <= n; i++)
        doit(i);
    for (int i = 2;i <= n; i++)
        if (find(i) != find(i-1)) {
            puts("-1");
            return;
        }
    Guass();		  
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) solve();
    return 0;
}
