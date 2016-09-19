#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxx = 1e6 + 5;

int gcd(int a, int b){
	
	if(b == 0) return a;
	else return gcd(b, a % b);
}

vector<int> vec[maxn];

struct event{

	int left, rght, id, val;
	event(int id = 0, int left = 0, int rght = 0, int val = 0) : id(id), left(left), rght(rght), val(val) {}
	
	bool friend operator < (event i, event j){
		
		if(i.rght != j.rght) return i.rght < j.rght;
		else return (i.id != 0) < (j.id != 0);
	}
};
vector<event> e;

int n, m;
int a[maxn], g_left[maxx], ans[maxn];

int bitt[maxn];
int lowbit(int i){
	
	return i & (-i);
}
void modify(int pos, int delta){
	
	for(int i = pos; i <= n; i += lowbit(i)) bitt[i] += delta;
}
int query(int pos){
	
	int rtn = 0;
	for(int i = pos; i > 0; i -= lowbit(i)) rtn += bitt[i];
	return rtn;
}

void work(){
	
	e.clear();
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	memset(g_left, 0, sizeof g_left);
	for(int i = 1; i <= n + 1; ++i) vec[i].clear();
	for(int i = n; i >= 1; --i){
		vec[i].push_back(i);
		int x = a[i];
		e.push_back(event(0, i, i, x));
		for(int j = 0; j < vec[i+1].size(); ++j){
			int k = vec[i+1][j];
			int y = a[k];
			int g = gcd(x, y);
			if(x == g) continue;
			x = g;
			vec[i].push_back(k);
			e.push_back(event(0, i, k, x));
		}
	}
	
	for(int i = 1; i <= m; ++i){
		int l, r;
		scanf("%d%d", &l, &r);
		e.push_back(event(i, l, r, 0));
	}
	
	memset(bitt, 0, sizeof bitt);
	sort(e.begin(), e.end());
	for(int i = 0; i < e.size(); ++i)
		if(e[i].id == 0){
		
			int g = e[i].val;
			if(g_left[g] > e[i].left) continue;
			modify(n - g_left[g] + 1, -1);
			g_left[g] = e[i].left;
			modify(n - g_left[g] + 1, 1);
			
		}else ans[e[i].id] = query(n - e[i].left + 1);
	
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
}

int main(){
	
	while(scanf("%d%d", &n, &m) == 2) work();

	return 0;
}
