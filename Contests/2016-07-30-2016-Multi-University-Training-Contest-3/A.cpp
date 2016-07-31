 
#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

const int maxl = 1e2 + 5;

const long long inf = 1e16;

char str[maxl];

int calc(long long x){
	
	int rtn = 0;
	long long t;
	while(x > 1){
		t = x;
		x = sqrt(x);
		if((x + 1) * (x + 1) <= t) x = x + 1;
		if(x * x > t) x = x - 1;
		//cout << x << endl;
		++rtn;
	}
	return rtn;
}

int main(){
	
	while(gets(str)){
		long long x = 0;
		int n = strlen(str);
		bool able = true;
		for(int i = 0; i < n; ++i){
			x *= 10;
			x += str[i] - '0';
			if(x >= inf){
				able = false;
				break;
			}
		}
		if(!able) puts("TAT");
		else{
			if(x == 0){
				puts("TAT");
				continue;
			}
			int ans = calc(x);
			if(ans <= 5) printf("%d\n", ans);
			else puts("TAT");
		}
	}
	
	return 0;
}
