#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

long long n;

void work(){
	
	long long ans = 0;
	for (long long i = 1; i * i * i <= n; i++)
		for (long long j = i; i * j * j <= n; j++) {
			long long k = n / (i * j);
			//cerr<<i<<' '<<j<<' '<<k<<endl;
			long long tmp = (k - j) * 6;
			if (i == j) tmp /= 2, ans += 1;
			else ans += 3;
			ans += tmp;
		}
	cout << ans << endl;
}

int main(){
	int cases = 0;
	while(scanf("%lld", &n) == 1)
	{
		cases++;
		printf("Case %d: ", cases);
		work();
	}

	return 0;
}
