#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 250;
const double eps = 1e-8;
int n, m;
double r;

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x) , y(y) {}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend Point operator / (const Point &a, double k) {
		return Point(a.x / k, a.y / k);
	}
	friend double dis(const Point &a, const Point &b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
} a[N], O;

int sgn(double x) {
	return (x < -eps) ? -1 : (x > eps);
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}
double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

Point get_circumcenter(const Point &a, const Point &b, const Point &c) {
	Point p = b - a, q = c - a, s(dot(p, p) / 2, dot(q, q) / 2);
	double d = det(p, q);
	return a + Point(det(s, Point(p.y, q.y)), det(Point(p.x, q.x), s)) / d;
}

bool check() {
	int in_cir, out_cir, clr;
	in_cir = out_cir = -1;
	clr = 0;

	for (int i = 1; i <= n + m; i++) {
		if (i > n) clr = 1;
		int t = sgn(dis(O, a[i]) - r);
		if (t == 1) {
			if (out_cir == -1) out_cir = clr;
			if (out_cir != clr || in_cir == clr) return 0; 
		}
		else if (t == -1) {
			if (in_cir == -1) in_cir = clr;
			if (in_cir != clr || out_cir == clr) return 0;
		}
	}

	return 1;
}

bool solve() {
	for (int i = 1; i <= n + m; i++)
		for (int j = i + 1; j <= n + m; j++)
			if (i != j) {
				//printf("%d %d\n", i, j);
				O = (a[i] + a[j]) / 2;
				r = dis(O, a[i]);
				if (check()) return 1;
			}
	
	for (int i = 1; i <= n; i++)
		for (int j = n + 1; j <= n + m; j++)
			for (int k = i + 1; k <= n + m; k++)
				if (k <= n || k > j) {
					if (sgn(det(a[i] - a[k], a[j] - a[k])) == 0) continue;
					//printf("%d %d %d\n", i, j, k);
					O = get_circumcenter(a[i], a[j], a[k]);
					r = dis(O, a[i]);
					if (check()) return 1;
				}
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[i].x = x; a[i].y = y;
	}
	for (int i = n + 1; i <= n + m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[i].x = x; a[i].y = y;
	}
	
	if (solve()) {
		puts("YES");
		printf("%.8f %.8f %.8f\n", O.x, O.y, r);
	}
	else puts("NO");
	return 0;
}
