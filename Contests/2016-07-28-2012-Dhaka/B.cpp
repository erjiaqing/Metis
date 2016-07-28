#include <vector>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1005;

char str[maxn];
vector<int> mp[maxn];
void add_edge(int u, int v){
	mp[u].push_back(v);
	mp[v].push_back(u);
}

bool flag[maxn], in[maxn];

int top;
int stck[maxn];

int id(char ch){
	return ch - 'A' + 1;
}

void work(){
	
	top = 0;
	memset(flag, 0, sizeof flag);
	memset(in, 0, sizeof in);
	scanf("%s", str);
	int n = strlen(str);
	for(int i = 0; i < n; ++i){
		int j = id(str[i]);
		in[j] = true;
		
		//printf("%d stck:\n", i + 1);
		//for(int k = 1; k <= top; ++k) printf("%d ", stck[k]); puts("");
		
		if(flag[j]) --top;
		else{
			if(top > 0) add_edge(stck[top], j);
			stck[++top] = j;
			flag[j] = true;
		}
	}
	for(int i = 1; i <= 26; ++i){
		if(in[i]) printf("%c = %d\n", 'A' + i - 1, (int)mp[i].size());
		//for(int l = 0; l < mp[i].size(); ++l) printf("%d ", mp[i][l]); puts("");
		mp[i].clear();
	}
}

int main(){

	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case %d\n", tt);
		work();
	}

	return 0;
}
« Back
