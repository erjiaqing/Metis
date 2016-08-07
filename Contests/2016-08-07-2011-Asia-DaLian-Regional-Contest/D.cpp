#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxl = 5e3 + 5;

void trans_addr(int x){
	
	int tmp[4];
	memset(tmp, 0, sizeof tmp);
	for(int i = 0; i < 4; ++i){
		tmp[i] = x % 16;
		x /= 16;
	}
	for(int i = 3; i >= 0; --i){
		if(tmp[i] >= 10) putchar('a' + tmp[i] - 10);
		else printf("%d", tmp[i]);
	}
}

void trans_dump(int x){
	
	if(!x){
		printf("  ");
		return;
	}
	
	int tmp[2];
	memset(tmp, 0, sizeof tmp);
	for(int i = 0; i < 2; ++i){
		tmp[i] = x % 16;
		x /= 16;
	}
	for(int i = 1; i >= 0; --i){
		if(tmp[i] >= 10) putchar('a' + tmp[i] - 10);
		else printf("%d", tmp[i]);
	}
}

void print_row(int addr, char s[]){
	
	trans_addr(addr);
	printf(": ");
	for(int i = 0; i < 16; ++i){
		trans_dump(s[addr+i]);
		if(i & 1) putchar(' ');
	}
	for(int i = 0; i < 16 && s[addr+i]; ++i){
		int j = addr+i;
		if(s[j] >= 'a' && s[j] <= 'z') s[j] -= 32;
		else if(s[j] >= 'A' && s[j] <= 'Z') s[j] += 32;
		putchar(s[j]);
	}
	putchar('\n');
	if(!s[addr+16]) return;
	else print_row(addr + 16, s);
}

char str[maxl];

int main(){
	
	while(gets(str)){
		print_row(0, str);
		memset(str, 0, sizeof str);
	}
	
	return 0;
}
