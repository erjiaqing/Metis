#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 305;
const int M = 1e9 + 7;

int n, f[N][2005], ans;
long long a[N];

int m, prime[2000];
bool is_prime[2005];
void get_prime() {
	m = 0;
	memset(is_prime, 1, sizeof(is_prime));
	for (int i = 2; i <= 2000; i++) {
		if (is_prime[i]) prime[++m] = i;
		for (int j = i + i; j <= 2000; j += i) {
			is_prime[j] = 0;
		}
	}
}

void Gauss() {
	ans = 1;
	int p = 1;
	for (int i = 1; i <= n; i++) {
		int k = 0;
		for (int j = p; j <= m; j++)
			if (f[j][i]) {
				k = j;
				break;
			}
			
		if (k == 0) {
			ans = (ans * 2) % M;
			continue;
		}
		
		if (k != p) {
			for (int j = i; j <= n + 1; j++)
				swap(f[p][j], f[k][j]);
		}
		
		for (int j = p + 1; j <= m; j++) {
			if (!f[j][i]) continue;
			for (int h = i; h <= n + 1; h++)
				f[j][h] ^= f[p][h];
		}
		
		p++;
	}
}

int main() {
	get_prime();	

	int T; scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d:\n", cs);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%I64d", &a[i]);
			
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				int t = 0;
				while (a[j] % prime[i] == 0) {
					t ^= 1;
					a[j] /= prime[i];
				}
				f[i][j] = t;
			}
			f[i][n + 1] = 0;
		}

		Gauss();
		printf("%d\n", (ans - 1 + M) % M);
	}
	return 0;
}
