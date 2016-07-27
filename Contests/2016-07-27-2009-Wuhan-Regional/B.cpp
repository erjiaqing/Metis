#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 2e5 + 5;

int n, m, ind[maxn];
int l[5][maxn], r[5][maxn], val[maxn];

int oper(char ch){
	if(ch == 'X') return 0;
	if(ch == 'Y') return 1;
	if(ch == 'Z') return 2;
}

vector<int> mp[maxn];
void add_edge(int u, int v){
	++ind[v];
	mp[u].push_back(v);
}

queue<int> que;
bool topsort(){
	
	int totnode = 0;
	
	while(!que.empty()) que.pop();
	
	//int seq = 6 * n;
	int seq = -1;
	for(int i = 1; i <= 6 * n; ++i)
		if(ind[i] == 0){
			//val[i] = seq--;
			val[i] = ++seq;
			que.push(i);
			++totnode;
		}
	
	
	while(!que.empty()){
		int u = que.front();
		que.pop();
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l];
			--ind[v];
			if(ind[v] == 0){
				//val[v] = seq--;
				val[v] = ++seq;
				que.push(v);
				++totnode;
			}
		}
	}
	
	return (totnode == (6 * n));
}

void work(){
	
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < 3; ++j){
			l[j][i] = j * n + i;
			r[j][i] = j * n + i + n * 3;
			//cerr<<l[j][i]<<" "<<r[j][i]<<"   ..."<<endl;
			//add_edge(r[j][i], l[j][i]);
			add_edge(l[j][i], r[j][i]);
		}
	
	char ch;
	for(int i = 1; i <= m; ++i){
		ch = getchar(), ch = getchar();
		int u, v;
		scanf("%d%d", &u, &v);
		//putchar(ch);
		if(ch == 'I'){
			for(int j = 0; j < 3; ++j){
				//add_edge(r[j][u], l[j][v]);
				//add_edge(r[j][v], l[j][u]);
				add_edge(l[j][u], r[j][v]);
				add_edge(l[j][v], r[j][u]);
			}
		} else {
			int j = oper(ch);
			//add_edge(l[j][v], r[j][u]);
			add_edge(r[j][u], l[j][v]);
		}
	}
	
	
	if(topsort())
	{
		puts("POSSIBLE");
		
		for(int i = 1; i <= n; ++i)
		{
			int top = 0, a[10];
			for(int j = 0; j < 3; ++j) a[++top] = val[l[j][i]], a[++top] = val[r[j][i]];
			printf("%d %d %d %d %d %d\n", a[1], a[3], a[5], a[2], a[4], a[6]);
		}
		puts("");
	}
	
	else puts("IMPOSSIBLE\n");
	
	for(int i = 1; i <= 6 * n; ++i) mp[i].clear();
	memset(ind, 0, sizeof(ind));
}

int main(){
	
	int t = 0;
	while(true){
		++t;
		scanf("%d%d", &n, &m);
		if(n + m == 0) break;
		printf("Case %d: ", t);
		work();
	}
	
	return 0;
}
