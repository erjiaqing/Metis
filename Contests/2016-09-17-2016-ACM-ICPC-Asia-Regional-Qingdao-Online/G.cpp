#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

int n;
long long limt;
long long a[maxn], b[maxn];

bool check(int mid){
	
	int flag = (n - 1) % (mid - 1) == 0 ? 0 : (n - 1) % (mid - 1) + 1;
	//printf("flag %d\n", flag);
	int tot = 0, apos = 0, bpos = 0, cnt;
	
	long long t = 0;
	while(tot - bpos + n - apos > 1){
		
		if(flag > 0) cnt = flag, flag = 0;
		else cnt = mid;
		
		long long tmp = 0;
		while(cnt--){
			if(tot - bpos == 0 || (n - apos > 0 && a[apos+1] < b[bpos+1])) ++apos, tmp += a[apos];
			else ++bpos, tmp += b[bpos];
		}
		
		//printf("pos %d %d\n", apos, bpos);
		//for(int i = 1; i <= tot; ++i) printf("%lld%c", b[i], " \n"[i==tot]);
		
		t += tmp;
		b[++tot] = tmp;
	}
	//printf("%d %lld\n", mid, t);
	return t <= limt;
}

int binary(int left, int rght){
	
	while(left < rght){
		int mid = (left + rght) >> 1;
		if(check(mid)) rght = mid;
		else left = mid + 1;
	}
	return rght;
}

void work(){
	
	scanf("%d%I64d", &n, &limt);
	for(int i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
	sort(a + 1, a + 1 + n);
	printf("%d\n", binary(2, n));
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
