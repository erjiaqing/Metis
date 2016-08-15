#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const long long p = 1e9 + 7;

int n, m;

long long powmod(long long a, int x){
	long long rtn = 1;
	while(x){
		if(x & 1) rtn *= a, rtn %= p;
		a *= a, a %= p;
		x = x >> 1;
	}
	return rtn;
}

void work(){
	
	scanf("%d%d", &n, &m);
	long long ans = powmod(m, n) * (powmod(m - 1, p - 2) + 1) % p;
	ans -= powmod(m - 1, p - 2);
	ans %= p;
	ans += ans < 0 ? p : 0;
	//printf("%lld\n", ans);
	printf("%I64d\n", ans);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();
	
	return 0;
}
