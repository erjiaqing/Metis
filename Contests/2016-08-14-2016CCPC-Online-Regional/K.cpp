#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n, c[500], ans;
char s[N];

int main() {
	int T; scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%s", s);
		n = strlen(s);
		memset(c, 0, sizeof(c));
		ans = 0;
		for (int i = 0; i < n; i++) {
			if (!c[s[i]]) ans++;
			c[s[i]]++;
		}
		printf("Case #%d: %d\n", cs, ans);
	}
	return 0;
}
