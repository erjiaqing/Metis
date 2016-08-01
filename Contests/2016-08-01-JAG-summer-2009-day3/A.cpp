#include <cstring>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 1e3 + 5;
const long double inf = 1e18;
const int M = 256;

long double ans;
int N, S, A, C;
int I[maxn], R[maxn], O[maxn], cnt[M];

void work(){
	
	for(int i = 1; i <= N; ++i) scanf("%d", &I[i]);

	bool mark = 0;	
	ans = inf;
	for(int tS = 0; tS <= 15; ++tS)
		for(int tA = 0; tA <= 15; ++tA)
			for(int tC = 0; tC <= 15; ++tC){
				R[0] = tS;
				for(int i = 1; i <= N; ++i){
					R[i] = tA * R[i-1] + tC;
					R[i] %= M;
				}
				memset(cnt, 0, sizeof cnt);
				for(int i = 1; i <= N; ++i) O[i] = (I[i] + R[i]) % M, ++cnt[O[i]];
				//for(int i = 1; i <= N; ++i) printf("%d%c", O[i], " \n"[i==N]);
				
				long double t = 0.00;
				for(int i = 0; i < M; ++i) if(cnt[i]) t -= 1.00 * cnt[i] / N * (log(1.00 * cnt[i]) - log(N));
				if(!mark || t < ans) mark = 1, ans = t, S = tS, A = tA, C = tC;
				//printf("%d %d %d : %lf\n", tS, tA, tC, t);
			}
	printf("%d %d %d\n", S, A, C);
}

int main(){

	while(true){
		scanf("%d", &N);
		if(!N) break;
		work();
	}
	
	return 0;
}
