#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int maxl = 105;

int n, ans;
char str[maxl];

int main(){
	
	int cs = 0;
	while(scanf("%d", &n) == 1){
		++cs;
		ans = 0;
		char ch = getchar();
		for(int i = 1; i <= n; ++i){
			int t = 0;
			gets(str);
			int m = strlen(str);
			for(int j = 0; j < m; ++j) t += str[j];
			ans = max(ans, t);
		}
		printf("Case %d: %d\n", cs, ans);
	}

	return 0;
}
