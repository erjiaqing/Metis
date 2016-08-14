#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxl = 1e7 + 5;
const int p1 = 73;
const int p2 = 137;

int x1, x2;
char str[maxl];

void work(){
	
	int l = strlen(str);
	x1 = x2 = 0;
	for(int i = 0; i < l; ++i){
		x1 *= 10;
		x1 += str[i] - '0';
		x1 %= p1;
		x2 *= 10;
		x2 += str[i] - '0';
		x2 %= p2;
	}
	if(x1 == 0 && x2 == 0) puts("YES");
	else puts("NO");
}

int main(){
	
	int cs = 0;
	while(scanf("%s", str) != EOF){
		++cs;
		printf("Case #%d: ", cs);
		work();
	}
	
	return 0;
}
