#include <ctime>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxr = 4e3 + 5;

int n;
char str[maxr];

bool A[maxr][maxr], B[maxr][maxr], C[maxr][maxr];
int P[maxr], Q[maxr], F[maxr];

void scan(bool T[][maxr]){
	
	for(int i = 1; i <= n; ++i){
		scanf("%s", str);
		//puts(str);
		for(int j = 1, p = 0; str[p]; j += 4, ++p){
			//printf("j %d\n", j);
			int x = str[p] - '0';
			if(str[p] >= 'A' && str[p] <= 'Z') x = str[p] - 'A' + 10;
			for(int k = 3; k >= 0; --k){
				T[i][j+k] = x % 2;
				x /= 2;
			}
		}
	}
}

int main(){
	
	srand(131);
	scanf("%d", &n);
	//printf("%d\n", n);
	scan(A); scan(B); scan(C);
	//puts("done");
	//A.print();
	
	int nowtime = 0;
	while(clock() <= 1500000){
	//while(++nowtime <= 15){
		for(int i = 1; i <= n; ++i) P[i] = rand() & 1;
		for(int i = 1; i <= n; ++i) Q[i] = P[i];
		
		memset(F, 0, sizeof F);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j){
				F[i] += P[j] * A[j][i];
				F[i] -= F[i] >= 2 ? 2 : 0;
			}
		memcpy(P, F, sizeof F);
		memset(F, 0, sizeof F);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j){
				F[i] += P[j] * B[j][i];
				F[i] -= F[i] >= 2 ? 2 : 0;
			}
		memcpy(P, F, sizeof F);
		
		memset(F, 0, sizeof F);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j){
				F[i] += Q[j] * C[j][i];
				F[i] -= F[i] >= 2 ? 2 : 0;
			}
		memcpy(Q, F, sizeof F);
		
		for(int i = 1; i <= n; ++i)
			if(P[i] != Q[i]){
				puts("NO");
				return 0;
			}
	}
	puts("YES");

	return 0;
}
