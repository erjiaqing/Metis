#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 2e4 + 10;

int n, m, flag = 0;
int fa[maxn], val[maxn], lnth[maxn];

int get_fa(int u){
	
	if(fa[u] == u) return u;
	int p = fa[u];
	fa[u] = get_fa(fa[u]);
	lnth[u] ^= lnth[p];
	return fa[u];
}

void oper_p_v(int p, int v){
	
	//printf("I %d %d\n", p, v);
	
	int rt = get_fa(p);
	v ^= lnth[p];
	if(val[rt] == v) return;
	if(val[rt] == -1) val[rt] = v;
	else flag = 1;
}

void oper_p_q_v(int p, int q, int v){
	
	//printf("I %d %d %d\n", p, q, v);
	
	int rtp = get_fa(p), rtq = get_fa(q);
	v ^= lnth[p] ^ lnth[q];
	
	if(rtp == rtq){
		if(v != 0) flag = 1;
		return;
	}
	
	if(val[rtp] != -1 && val[rtq] != -1){
		if((val[rtp] ^ val[rtq]) != v) flag = 1;
		return;
	}
	if(val[rtp] == -1){
		fa[rtp] = rtq;
		lnth[rtp] = v;
	} else {
		fa[rtq] = rtp;
		lnth[rtq] = v;
	}
}

void oper_query(){
	
	int k, p[20];
	scanf("%d", &k);
	for(int i = 1; i <= k; ++i) scanf("%d", &p[i]), ++p[i];
	getchar();
	
	//printf("Q %d\n", k);
	
	if(flag == 2) return;
	
	int tot = 0, ans = 0;
	int rtt[20], cnt[20], tv[20];
	for(int i = 1; i <= k; ++i){
		int rt = get_fa(p[i]);
		bool found = false;
		for(int j = 1; j <= tot; ++j){
			if(rtt[j] != rt) continue;
			cnt[j]++;
			tv[j] ^= lnth[p[i]];
			found = true;
			break;
		}
		if(found) continue;
		++tot;
		rtt[tot] = rt;
		cnt[tot] = 1;
		tv[tot] = lnth[p[i]];
	}
	for(int i = 1; i <= tot; ++i){
		if(cnt[i] % 2 && val[rtt[i]] == -1){
			puts("I don't know.");
			return;
		} else{
			if(cnt[i] % 2 == 1) ans ^= val[rtt[i]];
			ans ^= tv[i];
		}
	}
	printf("%d\n", ans);
}

void work(){
	
	flag = 0;
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) val[i] = -1;
	for(int i = 1; i <= n; ++i) lnth[i] = 0;
	
	char ch = getchar();
	int oper;
	for(int i = 1, fact = 0; i <= m; ++i){
		ch = getchar();
		if(ch == 'I') oper = 1;
		else oper = 2;
		
		//putchar(ch);
		
		int p = 0, q = 0, v = 0;
		if(oper == 1){
			++fact;
			scanf("%d%d", &p, &q);
			ch = getchar();
			//putchar(ch);
			//while(true);
			if(ch == ' '){
				scanf("%d", &v);
				++p, ++q;
				ch = getchar();
			} else {
				v = q, q = 0;
				++p;
			}
		}
		
		//printf("oper %d\n", oper);
		
		if(oper == 2) oper_query();
		if(flag == 2) continue;
		if(oper == 1 && q == 0) oper_p_v(p, v);
		if(oper == 1 && q != 0) oper_p_q_v(p, q, v);
		if(flag == 1){
			flag = 2;
			printf("The first %d facts are conflicting.\n", fact);
		}
		
		/*printf("i : %d\n", i);
		printf("flag %d\n", flag);
		for(int j = 1; j <= n; ++j) printf("fa[%d] = %d\n", j, fa[j]);
		for(int j = 1; j <= n; ++j) printf("lnth[%d] = %d\n", j, lnth[j]);
		for(int j = 1; j <= n; ++j) printf("val[%d] = %d\n", j, val[j]);
		puts("----------------------");*/
	}
}

int main(){
	
	int t = 0;
	while(true){
		++t;
		scanf("%d%d", &n, &m);
		if(n + m == 0) break;
		else{
			printf("Case %d:\n", t);
			work();
			puts("");
		}
	}

	return 0;
}
« Back
