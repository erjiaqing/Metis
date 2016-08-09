#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 2e5 + 5;
const int inf = 1e9;

struct segtree{
	
	int tot;
	struct node{
		int lson, rson, minn, lazy;
	}nd[maxn*2];
	
	#define ls nd[i].lson
	#define rs nd[i].rson
	
	int build(int left, int rght){
		int i = ++tot;
		nd[i].lson = nd[i].rson = 0;
		nd[i].lazy = nd[i].minn = 0;
		if(left < rght){
			int mid = (left + rght) >> 1;
			ls = build(left, mid);
			rs = build(mid + 1, rght);
		}
		return i;
	}
	void push_down(int i){
		nd[ls].minn += nd[i].lazy;
		nd[ls].lazy += nd[i].lazy;
		nd[rs].minn += nd[i].lazy;
		nd[rs].lazy += nd[i].lazy;
		nd[i].lazy = 0;
	}
	void modify(int i, int left, int rght, int x, int y, int z){
		if(nd[i].lazy != 0) push_down(i);
		if(x <= left && rght <= y){
			nd[i].lazy += z;
			nd[i].minn += z;
			return;
		}
		int mid = (left + rght) >> 1;
		if(ls && x <= mid) modify(ls, left, mid, x, y, z);
		if(rs && y > mid) modify(rs, mid + 1, rght, x, y, z);
		nd[i].minn = min(nd[ls].minn, nd[rs].minn);
	}
	int query(int i, int left, int rght, int x, int y){
		if(nd[i].lazy != 0) push_down(i);
		if(x <= left && rght <= y) return nd[i].minn;
		int mid = (left + rght) >> 1;
		int lmin = inf, rmin = inf;
		if(ls && x <= mid) lmin = query(ls, left, mid, x, y);
		if(rs && y > mid) rmin = query(rs, mid + 1, rght, x, y);
		return min(lmin, rmin);
	}
}st;

int n, m, a[maxn], b[maxn], rk[maxn];
int pre[maxn], suc[maxn], lst[maxn];
struct evnt{
	int pos, left, rght, v;
	evnt(int pos = 0, int left = 0, int rght = 0, int v = 0) : pos(pos), left(left), rght(rght), v(v) {}
}e[maxn*2];
vector<evnt> vec[maxn];

bool check(){
	
	st.tot = 0;
	st.build(1, n);
	for(int i = 1; i <= n; ++i) vec[i].clear();
	for(int i = 1; i <= m; ++i) vec[e[i].pos].push_back(e[i]);
	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < vec[i].size(); ++j)
			st.modify(1, 1, n, vec[i][j].left, vec[i][j].rght, vec[i][j].v);
		if(st.query(1, 1, n, i, n) == 0) return false;
	}
	return true;
}

bool cmp(int i, int j){
	return a[i] < a[j];
}
void work(){
	
	scanf("%d", &n);
	a[0] = -1;
	for(int i = 1; i <= n; ++i) scanf("%d",  &a[i]);
	for(int i = 1; i <= n; ++i) rk[i] = i;
	sort(rk + 1, rk + 1 + n, cmp);
	for(int i = 1, j = 0; i <= n; ++i){
		if(a[rk[i]] != a[rk[i-1]]) b[rk[i]] = ++j;
		else b[rk[i]] = j;
	}
	for(int i = 1; i <= n; ++i) lst[i] = 0;
	for(int i = 1; i <= n; ++i){
		pre[i] = lst[b[i]];
		lst[b[i]] = i;
	}
	for(int i = 1; i <= n; ++i) lst[i] = n + 1;
	for(int i = n; i >= 1; --i){
		suc[i] = lst[b[i]];
		lst[b[i]] = i;
	}
	m = 0;
	for(int i = 1; i <= n; ++i){
		e[++m] = evnt(pre[i] + 1, i, suc[i] - 1, +1);
		e[++m] = evnt(i + 1, i, suc[i] - 1, -1);
	}
	
	if(check()) puts("non-boring");
	else puts("boring");
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--) work();
	return 0;
}
