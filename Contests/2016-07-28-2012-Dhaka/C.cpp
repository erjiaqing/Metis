#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char str[10000];

void work(){
	
	int ans = 0;
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", str);
	//puts(str);
	for(int i = 0; i < n; ++i){
		bool flag = false;
		for(int j = max(0, i - m); j < i; ++j)
			if(str[i] == str[j]) flag = true;
		if(flag) ++ans;
	}
	printf("%d\n", ans);
}

int main(){

	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case %d: ", tt);
		work();
	}
	
	return 0;
}
