#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> ppi;

const int maxn = 1e5 + 5;
const int inf = 1e9;

vector<ppi> mp[maxn];
void add_edge(int u, int v, int d, int id){
	mp[u].push_back(make_pair(v, make_pair(d, id)));
	mp[v].push_back(make_pair(u, make_pair(d, id)));
}

struct segtree{
	
	int tot;
	struct node{
		int lson, rson, maxx, minn;
		bool lazy;
	}nd[maxn*2];
	
	#define ls nd[i].lson
	#define rs nd[i].rson
	
	int build(int left, int rght){
		int i = ++tot;
		if(left < rght){
			int mid = (left + rght) >> 1;
			ls = build(left, mid);
			rs = build(mid + 1, rght);
		}
		return i;
	}
	
	void push_down(int i){
		swap(nd[ls].maxx, nd[ls].minn);
		swap(nd[rs].maxx, nd[rs].minn);
		nd[ls].maxx = -nd[ls].maxx;
		nd[ls].minn = -nd[ls].minn;
		nd[rs].maxx = -nd[rs].maxx;
		nd[rs].minn = -nd[rs].minn;
		nd[ls].lazy ^= 1; //
		nd[rs].lazy ^= 1; //
		nd[i].lazy = false;
	}
	
	void updata(int i){
		nd[i].maxx = max(nd[ls].maxx, nd[rs].maxx);
		nd[i].minn = min(nd[ls].minn, nd[rs].minn);
	}
	
	void change(int i, int left, int rght, int x, int z){
		if(nd[i].lazy) push_down(i);
		if(left == rght){
			nd[i].maxx = z;
			nd[i].minn = z; //
			return;
		}
		int mid = (left + rght) >> 1;
		if(ls && x <= mid) change(ls, left, mid, x, z);
		if(rs && x > mid) change(rs, mid + 1, rght, x, z);
		updata(i);
	}
	
	void negate(int i, int left, int rght, int x, int y){
		if(nd[i].lazy) push_down(i);
		if(x <= left && rght <= y){
			swap(nd[i].maxx, nd[i].minn);
			nd[i].maxx = -nd[i].maxx;
			nd[i].minn = -nd[i].minn;
			nd[i].lazy = true;
			return; //
		}
		int mid = (left + rght) >> 1;
		if(ls && x <= mid) negate(ls, left, mid, x, y);
		if(rs && y > mid) negate(rs, mid + 1, rght, x, y); //
		updata(i);
	}
	
	int query(int i, int left, int rght, int x, int y){
		if(nd[i].lazy) push_down(i);
		if(x <= left && rght <= y) return nd[i].maxx;
		int mid = (left + rght) >> 1;
		int lmax = -inf, rmax = -inf;
		if(ls && x <= mid) lmax = query(ls, left, mid, x, y);
		if(rs && y > mid) rmax = query(rs, mid + 1, rght, x, y);
		return max(lmax, rmax);
	}
	
	void clear(){
		nd[0].lson = nd[0].rson = nd[0].maxx = nd[0].minn = 0;
		nd[0].lazy = false;
		for(int i = 1; i <= tot; ++i) nd[i] = nd[0];
		tot = 0;
	}
}st;

int n, f[maxn];

struct qtree{
	
	int tot;
	struct node{
		int hson, top, size, dpth, papa, newid;
	}nd[maxn];
	
	void find(int u, int fa, int d){
		nd[u].hson = 0;
		nd[u].size = 1;
		nd[u].papa = fa;
		nd[u].dpth = d;
		int max_size = 0;
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].first;
			if(v == fa) continue;
			f[mp[u][l].second.second] = v;
			find(v, u, d + 1);
			nd[u].size += nd[v].size;
			if(max_size < nd[v].size){
				max_size = nd[v].size;
				nd[u].hson = v;
			}
		}
	}
	
	void connect(int u, int t){
		nd[u].top = t;
		nd[u].newid = ++tot;
		if(nd[u].hson != 0) connect(nd[u].hson, t);
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].first;
			if(v == nd[u].papa || v == nd[u].hson) continue;
			connect(v, v);
		}
	}
	
	int query(int u, int v){
		int rtn = -inf;
		while(nd[u].top != nd[v].top){
			if(nd[nd[u].top].dpth < nd[nd[v].top].dpth) swap(u, v); //
			rtn = max(rtn, st.query(1, 1, n, nd[nd[u].top].newid, nd[u].newid));
			u = nd[nd[u].top].papa;
		}
		if(u == v) return rtn;
		if(nd[u].dpth > nd[v].dpth) swap(u, v);
		rtn = max(rtn, st.query(1, 1, n, nd[u].newid + 1, nd[v].newid));
		return rtn;
	}
	
	void change(int u, int z){
		st.change(1, 1, n, nd[u].newid, z);
	}
	
	void negate(int u, int v){
		while(nd[u].top != nd[v].top){
			if(nd[nd[u].top].dpth < nd[nd[v].top].dpth) swap(u, v); //
			st.negate(1, 1, n, nd[nd[u].top].newid, nd[u].newid);
			u = nd[nd[u].top].papa;
		}
		if(u == v) return;
		if(nd[u].dpth > nd[v].dpth) swap(u, v);
		st.negate(1, 1, n, nd[u].newid + 1, nd[v].newid);
	}
	
	void clear(){
		tot = 0;
		nd[0].hson = nd[0].top = nd[0].size = nd[0].dpth = nd[0].papa = nd[0].newid = 0;
		for(int i = 1; i <= n; ++i) nd[i] = nd[0];
	}
}qt;

void work(){
	
	scanf("%d", &n);
	for(int i = 1; i < n; ++i){
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		add_edge(u, v, d, i);
	}
	qt.find(1, 0, 1);
	qt.connect(1, 1);
	st.build(1, n);
	for(int u = 1; u <= n; ++u)
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].first;
			if(v == qt.nd[u].papa) continue;
			qt.change(v, mp[u][l].second.first);
		}
	while(true){
		char str[10];
		scanf("%s", str);
		if(str[0] == 'D') break;
		int a, b;
		scanf("%d%d", &a, &b);
		if(str[0] == 'Q') printf("%d\n", qt.query(a, b));
		if(str[0] == 'C') qt.change(f[a], b);
		if(str[0] == 'N') qt.negate(a, b);
	}
	st.clear();
	qt.clear();
	for(int i = 1; i <= n; ++i) mp[i].clear();
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();
	
	return 0;
}
