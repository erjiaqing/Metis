#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxp = 20;
const int p = 14641;

long long left, rght;
long long f[maxp][p][2][2];
int n, a[maxp], init, k;

long long dfs(int pos, int stat, bool free, bool beg){
	
	//printf("%d %d %d %d %d\n", pos, stat, free, beg, stat % 11);
	if(f[pos][stat][free][beg] != -1) return f[pos][stat][free][beg];
	if(pos == 0) return f[pos][stat][free][beg] = beg;
	
	long long rtn = 0;
	if(!beg){
		rtn += dfs(pos - 1, stat, free || a[pos] != 0, false);
		for(int i = 1; i <= 9; ++i){
			if(!free && i > a[pos]) continue;
			rtn += dfs(pos - 1, (stat * 11) % p + i, free || i < a[pos], true);
		}
	}else{
		for(int i = 0; i <= 9; ++i){
			if(!free && i > a[pos]) continue;
			int tmp = stat;
			bool can = true;
			//printf("%d\n", tmp % 11);
			//printf("k %d\n", k);
			for(int j = 1; j < k; ++j){
				if(i == (tmp % 11)) can = false;
				tmp /= 11;
			}
			if(!can) continue;
			//printf("can %d\n", can);
			//printf("i %d\n", i);
			if(!free && i == a[pos]) rtn += dfs(pos - 1, (stat * 11) % p + i, false, true);
			else rtn += dfs(pos - 1, (stat * 11) % p + i, true, true);
		}
	}
	return f[pos][stat][free][beg] = rtn;
}

long long calc(long long x){
	
	if(x == 0) return 0;
	memset(f, -1, sizeof f);
	memset(a, 0, sizeof a);
	n = 0;
	while(x) a[++n] = x % 10, x /= 10;
	//printf("%d\n", n);
	//for(int i = n; i >= 1; --i) printf("%d ", a[i]); puts("");
	//for(int i = 1, j = n; i < j; ++i, --j) swap(a[i], a[j]);
	//for(int i = n; i >= 1; --i) printf("%d ", a[i]); puts("");
	//puts("done");
	return dfs(n, p - 1, false, false);
}

void work(){
	
	printf("%I64d\n", calc(rght) - calc(left - 1));
	//printf("%lld\n", calc(rght) - calc(left - 1));
}

int main(){
	
	for(int i = 1; i <= 5; ++i) init *= 11, init += 10;
	while(scanf("%I64d%I64d%d", &left, &rght, &k) == 3) work(); // I64d
	//while(scanf("%lld%lld%d", &left, &rght, &k) == 3) work(); // I64d

	return 0;
}
