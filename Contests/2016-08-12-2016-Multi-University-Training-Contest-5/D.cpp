#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 4005;

struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x) , y(y) {}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
} ;

int n, now, a[N];
Point b[N], c[N];
long long cnt;
double d[N];

long long dot(const Point &a, const Point &b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
long long det(const Point &a, const Point &b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}
bool operator == (const Point &a, const Point &b) {
	return a.x == b.x && a.y == b.y;
}

bool cmp(int i, int j) {
	return d[i] < d[j];
}

void work() {
	int m = 0;
	for (int i = 1; i <= n; i++) {
		if (i == now) continue;
		b[++m] = c[i] - c[now];
		d[m] = atan2(b[m].y, b[m].x);
	}
	for (int i = 1; i <= n; i++) a[i] = i;
	sort(a + 1, a + m + 1, cmp);
	for (int i = 1; i <= m; i++)
		a[i + m] = a[i];
	//for (int i = 1; i <= m + m; i++)
	//printf("..%d %d\n", b[i].x, b[i].y);
	
	int r = 1;
	long long DET, DOT;	
	for (int i = 1; i <= m; i++) {
		if (r == i) r++;
		DET = det(b[a[i]], b[a[r]]);
		DOT = dot(b[a[i]], b[a[r]]);
		while (r < i + m && DOT > 0 && (DET > 0 || DET == 0 && r <= m)) {
			r++;
			DET = det(b[a[i]], b[a[r]]);
			DOT = dot(b[a[i]], b[a[r]]);
		}
		//printf("%d %d\n", i , r);
		cnt += r - i - 1;
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			c[i] = Point(x, y);
		}
		
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			now = i;
			work();
		}
		long long t = 1LL * n * (n - 1) * (n - 2) / 3;
		cout << cnt - t << endl;
	}
	return 0;
}
