#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 5005;
int a[N], id[N], n, m;
long long c[N];
int top;

void rotate(int x) {
	int t = a[x];
	for (int j = x; j > 1; j--)
		a[j] = a[j - 1];
	a[1] = t;
}

void work() {
	char s[10];
	int x;
	scanf("%s", s);
	scanf("%d", &x);
	if (s[0] == 'A') {
		for (int i = 1; i <= m; i++)
			if (id[a[i]] == x) {
				printf("same priority");
				return ;
			}
		n++, m++;
		a[m] = n;
		id[n] = x;
		c[n] = 0;
		printf("success");
	}
	else if (s[0] == 'C' && s[1] == 'l') {
		for (int i = 1; i <= m; i++)
			if (id[a[i]] == x) {
				printf("close %d with %I64d", x, c[a[i]]);
				if (top == x) top = 0;
				for (int j = i; j < m; j++)
					a[j] = a[j + 1];
				m--;
				return ;
			}
		printf("invalid priority");
	}
	else if (s[0] == 'C' && s[1] == 'h' && s[2] == 'a') {
		if (m == 0) printf("empty");
		else {
			printf("success");
			if (top) {
				for (int i = 1; i <= m; i++)
					if (id[a[i]] == top) {
						c[a[i]] += x;
						return ;
					}
			}
			else c[a[1]] += x;
		}
	}
	else if (s[0] == 'R') {
		if (x < 1 || x > m) {
			printf("out of range");
			return ;
		}
		printf("success");
		rotate(x);
	}
	else if (s[0] == 'P') {
		if (m == 0) printf("empty");
		else {
			printf("success");
			int mx = 1;
			for (int i = 1; i <= m; i++)
				if (id[a[i]] > id[a[mx]]) mx = i;
			rotate(mx);
		}
	}
	else if (s[0] == 'C' && s[1] == 'h' && s[2] == 'o') {
		for (int i = 1; i <= m; i++)
			if (id[a[i]] == x) {
				rotate(i);
				printf("success");
				return ;
			}
		printf("invalid priority");
	}
	else if (s[0] == 'T') {
		for (int i = 1; i <= m; i++)
			if (id[a[i]] == x) {
				printf("success");
				top = x;
				return ;
			}
		printf("invalid priority");
	}
	else if (s[0] == 'U') {
		if (!top) printf("no such person");
		else printf("success"), top = 0;
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int op;
		scanf("%d", &op);
		n = m = 0;
		top = 0;
		for (int i = 1; i <= op; i++) {
			printf("Operation #%d: ", i);
			work();
			printf(".\n");
		}
		if (top) {
			for (int i = 1; i <= m; i++)
				if (id[a[i]] == top) {
					if (c[a[i]]) printf("Bye %d: %I64d\n", id[a[i]], c[a[i]]);
					break;
				}
		}
		for (int i = 1; i <= m; i++)
			if (c[a[i]] && id[a[i]] != top) printf("Bye %d: %I64d\n", id[a[i]], c[a[i]]);
	}
	return 0;
}
