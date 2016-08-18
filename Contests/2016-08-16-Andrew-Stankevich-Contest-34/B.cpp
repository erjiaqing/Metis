#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;
int n, m, a[N];
char s[N];

int main() {
	while (true) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		if (s[1] == '0') break;
		
		if (n % 2 == 1) {
			n = n + 1;
			m = n / 2;
			printf("1");
			for (int i = 2; i <= m; i++) printf("0");
			for (int i = m + 1; i < n; i++) printf("1");
			printf("0\n");
			continue;
		}
		
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
			a[i] = s[i] - '0';
		a[n]++;
		int p = n;
		while (a[p] == 10) {
			a[p] = 0;
			a[--p]++;
		}
		if (p == 0) {
			n = n + 2;
			m = n / 2;
			printf("1");
			for (int i = 2; i <= m; i++) printf("0");
			for (int i = m + 1; i < n; i++) printf("1");
			printf("0\n");
			continue;
		}
		
		m = n / 2;
		int t = m + 1;
		while (t <= n) {
			if (a[t] == a[n + 1 - t]) {
				a[t]++;
				for (int i = t + 1; i <= n; i++)
					a[i] = 0;
			}
			//for (int i = 1; i <= n; i++) printf("%d", a[i]); puts("");
			if (a[t] < 10) {
				t++;
				continue;
			}
			while (a[t] == 10) {
				a[t] = 0;
				a[--t]++;
			}
			if (t == 0) {
				n = n + 2;
				m = n / 2;
				printf("1");
				for (int i = 2; i <= m; i++) printf("0");
				for (int i = m + 1; i < n; i++) printf("1");
				printf("0\n");
				break;
			}
			
			if (t <= m) t = m + 1;
		}
		
		if (t == 0) continue;
		for (int i = 1; i <= n; i++) printf("%d", a[i]);
		printf("\n");
	}
	return 0;
}
« Back
