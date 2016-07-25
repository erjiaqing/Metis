#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n, a[25];
long long f[25][25][2000][2];

long long dfs(int pos, int pivot, int value, bool free){
	
	//printf("%d %d %d %d\n", pos, pivot, value, free);
	
	if(value < 0) return f[pos][pivot][value][free] = 0;
	if(f[pos][pivot][value][free] != -1) return f[pos][pivot][value][free];
	if(pos > n){
		if(value == 0) return 1;
		else return 0;
	}
	
	long long rtn = 0;
	if(free){
		for(int i = 0; i <= 9; ++i)
			rtn += dfs(pos + 1, pivot, value + i * (pivot - pos), true);
	} else{
		for(int i = 0; i < a[pos]; ++i)
			rtn += dfs(pos + 1, pivot, value + i * (pivot - pos), true);
		rtn += dfs(pos + 1, pivot, value + a[pos] * (pivot - pos), false);
	}
	
	//printf("%d %d %d %d : %lld\n", pos, pivot, value, free, rtn);
	
	return f[pos][pivot][value][free] = rtn;
}

long long calc(long long x){
	
	memset(f, -1, sizeof f);
	if(x < 10) return x + 1;
	
	long long rtn = 0;
	for(n = 0; x; x /= 10) a[++n] = x % 10;
	for(int i = 1, j = n; i < j; ++i, --j) swap(a[i], a[j]);
	for(int p = 1; p <= n; ++p)
		rtn += dfs(1, p, 0, false);// - (n - 1);
	
	//for(int i = 1; i <= n; ++i) printf("%d", a[i]); puts("");
	
	//printf("rtn %lld\n", rtn);
	
	return rtn - (n - 1);
}

void work(){
	
	long long left, rght;
	cin >> left >> rght;
	//cout<<calc(rght)<<" " <<calc(left - 1)<<endl;
	cout << calc(rght) - calc(left - 1) << endl;
}

int main(){

	
	int t;
	scanf("%d", &t);
	while(t--) work();
	
	return 0;
}
« Back
