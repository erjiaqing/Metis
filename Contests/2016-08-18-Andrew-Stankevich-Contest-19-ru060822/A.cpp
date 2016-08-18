#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 50;
int n, a[N];
long long ans;
char s[N];

bool check(int x) {
	for (int i = x; i <= n; i++)
		if (a[n + 1 - i] > a[i]) return false;
		else if (a[n + 1 - i] < a[i]) return true;
	return true;
}

int main() {
	while (1) {
		scanf("%s", s + 1);
		if (s[1] == '0') break;
		
		n = strlen(s + 1);
		for (int i = 1; i <= n; i++)
			a[i] = s[i] - '0';
		
		if (n == 1) {
			printf("%d\n", a[1]);
			continue;
		}
		
		ans = 9;
		long long tmp = 1; 
		for (int i = 2; i < n; i++) {
			if (i % 2 == 0) ans += 9LL * tmp * (1 + i / 2 * 9);
			else {
				ans += 9LL * tmp * 10 * (1 + i / 2 * 9);
				tmp *= 10;
			}
		}
		
		//cout<<"///"<<s + 1<<endl;
		//cout<<"ans="<<ans<<" tmp="<<tmp<<endl;
		long long x = 0;
		for (int i = 1; i <= n / 2; i++)
			x = x * 10 + a[i];
			
		if (n % 2 == 0)
			ans += (x - tmp) * (1 + n / 2 * 9);
		
		if (n % 2 == 1) {
			ans += (x - tmp) * 10 * (1 + n / 2 * 9);
			ans += a[n / 2 + 1] * (1 + n / 2 * 9);
		}
		
		for (int i = (n + 1) / 2 + 1; i <= n + 1; i++) {
			if (i == n + 1) {
				ans++;
				break;
			}
			int p = n + 1 - i;
			if (a[p] > a[i]) {
				ans += a[i];
				if (check(i + 1)) ans++;
				break;
			}
			else if (a[p] < a[i]) {
				ans += a[i] - 1;
				ans += 1 + 9 * (n - i);
				if (check(i + 1)) ans++;
				break;
			} else ans += a[i];
		}
		
		cout << ans << endl;
	}
	return 0;
}
