#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 351000;

struct sam{
	
	int tot, lst;
	struct node{
		int indx[26], fa, lnth, rts;
		void init(){
			fa = -1;
			lnth = rts = 0;
			memset(indx, -1, sizeof indx);
		}
	}nd[maxn];
	
	void init(){
		tot = lst = 0;
		nd[tot].init();
	}
	int newnode(){
		nd[++tot].init();
		return tot;
	}
	
	void insert(char ch){
		int c = ch - 'a';
		int newp = newnode(), p = lst;
		nd[newp].lnth = nd[p].lnth + 1;
		while(p != -1 && nd[p].indx[c] == -1){
			nd[p].indx[c] = newp;
			p = nd[p].fa;
		}
		if(p == -1) nd[newp].fa = 0;
		else{
			int q = nd[p].indx[c];
			if(nd[p].lnth + 1 == nd[q].lnth) nd[newp].fa = q;
			else{
            int newq = newnode();
            nd[newq] = nd[q];
            nd[newq].lnth = nd[p].lnth + 1;
            nd[q].fa = nd[newp].fa = newq;
            while(p != -1 && nd[p].indx[c] == q){
                nd[p].indx[c] = newq;
                p = nd[p].fa;
            }
			}
		}
		lst = newp;
	}
	
}dict;

bool cmp(int i, int j){
	return dict.nd[i].lnth > dict.nd[j].lnth;
}

int n, ans[maxn], rk[maxn];
char str[maxn];

void work(){
	
	dict.init();
	n = strlen(str);
	for(int i = 0; i < n; ++i) dict.insert(str[i]);
	for(int i = 1; i <= dict.tot; ++i) rk[i] = i;
	sort(rk + 1, rk + 1 + dict.tot, cmp);
	for(int i = 0, p = 0; i < n; ++i)
		dict.nd[p=dict.nd[p].indx[str[i]-'a']].rts = 1;
	for(int i = 1; i <= dict.tot; ++i){
		int p = rk[i];
		ans[dict.nd[p].lnth] = max(ans[dict.nd[p].lnth], dict.nd[p].rts);
		dict.nd[dict.nd[p].fa].rts += dict.nd[p].rts;
	}
	for(int i = n; i >= 1; --i) ans[i-1] = max(ans[i-1], ans[i]);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
}

int main(){
	while(~scanf("%s", str)) work();
	return 0;
}
