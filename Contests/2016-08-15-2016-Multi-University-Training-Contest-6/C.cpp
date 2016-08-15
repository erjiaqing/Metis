#include <set>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e6 + 5;

int n, a[maxn];

int main(){
		
	int t;
	scanf("%d", &t);
	for(int cs = 1; cs <= t; ++cs){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for(int i = 1; i <= n; ++i){
			if(a[i] % 8 == 0) a[i]--;
			else if(a[i] % 8 == 7) a[i]++;
			//printf("%d ", a[i]);
		}
		long long ans = 0;
		for(int i = 1; i <= n; ++i) ans ^= 1LL * a[i];
		if(ans) puts("First player wins.");
		else puts("Second player wins.");
	}

	return 0;
}
