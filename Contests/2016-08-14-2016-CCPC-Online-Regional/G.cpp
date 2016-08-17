#include <queue>
#include <map>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

typedef pair<int, int> pii;

const int maxr = 10;
const int maxn = 30;
const int maxs = 7000;
const int mod = 772002;
const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

int r, c, n, ans_mask;
char mp[maxr][maxr];

int idx(int posx, int posy){
	if(posx < 0 || posx >= r) return -1;
	if(posy < 0 || posy >= c) return -1;
	return posx * c + posy;
}
bool check(int pos, int mask){
	
	int ux = pos / c;
	int uy = pos % c;
	for(int i = 0; i < 8; ++i){
		int vx = ux + dx[i];
		int vy = uy + dy[i];
		int v = idx(vx, vy);
		if(v == -1) continue;
		if(mask & (1 << v)) return false;
	}
	return true;
}
vector<int> legal, vec;
void get_vec(){
	
	vec.clear();
	for(int i = 0; i < legal.size(); ++i){
		int mask = legal[i];
		if(mask >= (1 << n)) break;
		if((mask | ans_mask) != mask) continue;
		bool flag = false;
		for(int j = 0; j < n; ++j){
			if(!(mask & (1 << j))) continue;
			if(!check(j, mask ^ (1 << j))){
				flag = true;
				break;
			}
		}
		if(!flag) vec.push_back(mask);
	}
	//printf("%d\n", vec.size());
}
int f[maxn][600], cnt[600], h[maxn];
int ans[maxs];
int calc(int all){
	
	//printf("%d : -------------\n", all);
	int m = 0;
	memset(h, -1, sizeof h);
	for(int i = 0; i < n; ++i)
		if(all & (1 << i)) h[i] = m++;
	//printf("%d\n", m);
	memset(cnt, 0, sizeof cnt);
	for(int mask = 0; mask < (1 << m); ++mask){
		for(int i = 0; i < n; ++i){
			if(h[i] != -1) continue;
			int ux = i / c;
			int uy = i - c * ux;
			bool flag = true;
			//printf("%d\n", i);
			for(int j = 0; j < 8; ++j){
				int vx = ux + dx[j];
				int vy = uy + dy[j];
				int v = idx(vx, vy);
				if(v == -1) continue;
				//printf("v %d\n", v);
				if((all & (1 << v)) && !(mask & (1 << h[v]))) flag = false;
			}
			cnt[mask] += flag;
		}
		//printf("cnt[%d] = %d\n", mask, cnt[mask]);
	}
	
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	for(int upos = 0; upos <= n; ++upos){
		int vpos = upos + 1;
		for(int umask = 0; umask < (1 << m); ++umask){
			for(int i = 0; i < m; ++i){
				if(umask & (1 << i)) continue;
				int vmask = umask | (1 << i);
				f[vpos][vmask] += f[upos][umask];
				f[vpos][vmask] %= mod;
			}
			f[vpos][umask] += f[upos][umask] * (cnt[umask] - (upos - __builtin_popcount(umask)));
			f[vpos][umask] %= mod;
		}
	}
	/*for(int i = 0; i <= n; ++i)
		for(int j = 0; j < (1 << m); ++j)
			printf("f[%d][%d] = %d\n", i, j, f[i][j]);*/
	return f[n][(1<<m)-1];
}
void work(){
	
	ans[0] = 0;
	n = r * c;
	ans_mask = 0;
	for(int i = 0; i < r; ++i){
		scanf("%s", mp[i]);
		for(int j = 0; j < c; ++j)
			if(mp[i][j] == 'X') ans_mask |= 1 << idx(i, j);
	}
	get_vec();
	int m = vec.size();
	//printf("%d\n", m);
	for(int i = 0; i < m; ++i) ans[i] = calc(vec[i]);
	//for(int i = 0; i < m; ++i) printf("ans[%d] = %d\n", vec[i], ans[i]);
	for(int i = m - 1; i >= 0; --i)
		for(int j = i - 1; j >= 0; --j)
			if((vec[i] | vec[j]) == vec[i])
				ans[j] -= ans[i], ans[j] += ans[j] < 0 ? mod : 0;
	printf("%d\n", ans[0]);
}

int main(){
	
	for(int i = 0; i < (1 << 25); ++i)	if(__builtin_popcount(i) <= 9) legal.push_back(i);
	//printf("%d\n", legal.size());
	for(int cs = 1; ~scanf("%d%d", &r, &c); ++cs){
		printf("Case #%d: ", cs);
		work();
	}

	return 0;
}
