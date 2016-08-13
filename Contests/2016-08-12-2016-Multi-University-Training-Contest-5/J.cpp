#include <map>
#include <vector> //
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef unsigned long long ull;

const int maxn = 2e6 + 5;
const ull p = 131;

int n, m;
char str[maxn];
map<ull, int> lst;

struct segtree{
	
	int tot, rt[maxn];
	struct node{
		int lson, rson, sum;
	}nd[maxn];
	
	void init(){
		tot = 0;
		nd[0].lson = nd[0].rson = nd[0].sum = 0;
	}
	
	void insert(int &i, int left, int rght, int pos){
		int j = ++tot;
		nd[j] = nd[i];
		nd[j].sum++;
		i = j;
		if(left == rght) return;
		int mid = (left + rght) >> 1;
		if(pos <= mid) insert(nd[j].lson, left, mid, pos);
		else insert(nd[j].rson, mid + 1, rght, pos);
	}
	
	int query(int i, int j, int left, int rght, int x, int y){
		if(x <= left && rght <= y) return nd[j].sum - nd[i].sum;
		int mid = (left + rght) >> 1;
		int lsum = 0, rsum = 0;
		if(x <= mid) lsum = query(nd[i].lson, nd[j].lson, left, mid, x, y);
		if(y > mid) rsum = query(nd[i].rson, nd[j].rson, mid + 1, rght, x, y);
		return lsum + rsum;
	}
}st;

void add(char s[], int id){
	
	st.rt[id] = st.rt[id-1];
	ull h = 0;
	for(int i = 0; s[i]; ++i){
		h *= p;
		h += s[i];
		st.insert(st.rt[id], 0, n, lst[h]);
		lst[h] = id;
	}
}

void work(){
	
	st.init();
	lst.clear();
	
	for(int i = 1; i <= n; ++i){
		scanf("%s", str);
		add(str, i);
	}
	
	scanf("%d", &m);
	for(int i = 1, Z = 0; i <= m; ++i){
		int left, rght, L, R;
		scanf("%d%d", &L, &R);
		left = min((Z + L) % n, (Z + R) % n) + 1;
		rght = max((Z + L) % n, (Z + R) % n) + 1;
		printf("%d\n", Z = st.query(st.rt[left-1], st.rt[rght], 0, n, 0, left - 1));
	}
}

int main(){
	
	//freopen("J.txt", "r", stdin);
	while(scanf("%d", &n) == 1) work();
	
	return 0;
}
