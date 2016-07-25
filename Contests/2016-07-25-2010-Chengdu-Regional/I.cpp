#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5e4 + 5;

int T;
LL n, K;
LL m[N], c[N];

bool ok(long long x)
{
	LL res = 0;
	int j = n;
	LL damage = 0;
	LL now = 0, sumlen = 0;
	for(int i = n; i >= 1; --i) {
		if(j > i)
		while((i - j) * (i - j) >= x) {
			now -= c[j];
			damage -= (j - (i + 1)) * (j - (i + 1)) * c[j];
			sumlen -= c[j] * (j - i - 1);
			j--;
		}
				
		damage += now;
		damage += 2 * sumlen;
		sumlen += now;
		
		LL tmp = m[i] - now * x + damage;
		if(tmp < 0) c[i] = 0;
		else c[i] = tmp / x + 1;
		
		res += c[i];
		now += c[i];
	}
	return (res <= K);
}

int main()
{
	cin>>T;
	while(T--) {
		cin>>n>>K;
		int t;
		for(int i = 1; i <= n; ++i) scanf("%d", &t), m[i] = t;
		
		LL l = 1, r = 1e12;
		while(l <= r) {
		//cerr<<l<<" "<<r<<endl;
			LL mid = (l + r) >> 1;
			if(ok(mid)) r = mid - 1;
			else l = mid + 1;
		}
		cout<<l<<endl;
	}
	return 0;
}
