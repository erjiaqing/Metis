#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6 + 5;
const long long p = 1e9 + 7;

char str[maxn*2];
int n, mx[maxn*2];
long long tagl[maxn], tagr[maxn];
long long cntl[maxn], cntr[maxn], tcntl[maxn], tcntr[maxn];
long long ansl[maxn], ansr[maxn];

void work(){
	
	n = strlen(str);
	for(int i = n; i >= 0; --i){
		str[i*2+2] = str[i];
		str[i*2+1] = '#';
	}
	str[0] = '*';
	for(int i = 2, id = 0; i < 2 * n + 1; ++i){
		if(mx[id] + id > i) mx[i] = min(mx[2*id-i], mx[id] + id - i);
		else mx[i] = 1;
		while(str[i-mx[i]] == str[i+mx[i]]) ++mx[i];
		if(id + mx[id] < i + mx[i]) id = i;
		
		int left, rght;
		if(str[i] == '#'){
		
			left = i / 2 - (mx[i] - 1) / 2 + 1;
			rght = i / 2 + (mx[i] - 1) / 2;
			//printf("%d %d\n", left, rght);
			
			tagr[left] += i / 2;
			tagr[left] %= p;
			cntr[left] ++;
			tcntr[left] ++;
			tagr[i/2+1] -= i / 2 - p;
			tagr[i/2+1] %= p;
			cntr[i/2+1] --;
			tcntr[i/2+1] --;
			
			tagl[rght] += i / 2 + 1;
			tagl[rght] %= p;
			cntl[rght] ++;
			tcntl[rght] ++;
			tagl[i/2] -= i / 2 + 1 - p;
			tagl[i/2] %= p;
			cntl[i/2] --;
			tcntl[i/2] --;
			
		}else{
		
			left = i / 2 - (mx[i] - 1) / 2;
			rght = i / 2 + (mx[i] - 1) / 2;
			//printf("%d %d\n", left, rght);
			
			tagr[left] += i / 2;
			tagr[left] %= p;
			cntr[left] ++;
			tagr[i/2+1] -= i / 2 - p;
			tagr[i/2+1] %= p;
			cntr[i/2+1] --;
			
			tagl[rght] += i / 2;
			tagl[rght] %= p;
			cntl[rght] ++;
			tagl[i/2-1] -= i / 2 - p;
			tagl[i/2-1] %= p;
			cntl[i/2-1] --;
		}
	}
	
	for(int i = 1; i <= n; ++i){
		cntr[i] += cntr[i-1];
		tagr[i] += tagr[i-1];
		tagr[i] %= p;
		tcntr[i] += tcntr[i-1];
		//printf("%d : %lld %lld\n", i, tagr[i], cntr[i]);
		ansr[i] += tagr[i] * 2 - cntr[i] * i;
		ansr[i] += tcntr[i];
		ansr[i] %= p;
		ansr[i] += ansr[i] < 0 ? p : 0;
		//printf("%d : %lld\n", i, ansr[i]);
	}
	for(int i = n; i >= 1; --i){
		cntl[i] += cntl[i+1];
		tagl[i] += tagl[i+1];
		tagl[i] %= p;
		tcntl[i] += tcntl[i+1];
		//printf("%d : %lld %lld\n", i, tagl[i], cntl[i]);
		ansl[i] += tagl[i] * 2 - cntl[i] * i;
		ansl[i] -= tcntl[i];
		ansl[i] %= p;
		ansl[i] += ansl[i] < 0 ? p : 0;
		//printf("%d : %lld\n", i, ansl[i]);
	}
	long long ans = 0;
	for(int i = 1; i < n; ++i){
		ans += ansl[i] * ansr[i+1];
		ans %= p;
	}
	cout << ans << endl;
	
	memset(tagl, 0, sizeof tagl);
	memset(cntl, 0, sizeof cntl);
	memset(ansl, 0, sizeof ansl);
	memset(tagr, 0, sizeof tagr);
	memset(cntr, 0, sizeof cntr);
	memset(ansr, 0, sizeof ansr);
	memset(tcntl, 0, sizeof tcntl);
	memset(tcntr, 0, sizeof tcntr);
}

int main(){
	
	while(scanf("%s", str) != EOF) work();

	return 0;
}
