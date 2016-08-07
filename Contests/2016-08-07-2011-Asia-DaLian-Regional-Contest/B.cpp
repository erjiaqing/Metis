#include <cstdio>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 5e4 + 5;
const int maxm = 1e5 + 5;

ll ans;
int w, h, n, l, m;
int xx1[maxn], yy1[maxn], xx2[maxn], yy2[maxn];

struct evnt{
	int pos, left, rght, type;
	evnt(int pos = 0, int left = 0, int rght = 0, int type = 0) : pos(pos), left(left), rght(rght), type(type) {}
}e[maxm];
bool cmp(evnt i, evnt j){
	if(i.pos != j.pos) return i.pos < j.pos;
	else return i.type > j.type;
}

multiset<int> st1, st2;
multiset<int> ::iterator it;

void work(){
	
	ans = 0;
	for(int i = 1; i <= n; ++i) scanf("%d%d%d%d", &xx1[i], &yy1[i], &xx2[i], &yy2[i]);
	
	int last_ans, last_pos;
	
	m = 0;
	for(int i = 1; i <= n; ++i){
		e[++m] = evnt(xx1[i], yy1[i], yy2[i], 1);
		e[++m] = evnt(xx2[i] + 1, yy1[i], yy2[i], 2);
	}
	sort(e + 1, e + 1 + m, cmp);
	last_pos = 1, last_ans = h - l + 1;
	st1.clear(); st1.insert(h + 1);
	st2.clear(); st2.insert(0);
	for(int i = 1; i <= m; ++i){
		if(e[i].pos != last_pos){
			ans += 1LL * last_ans * (e[i].pos - last_pos);
			//printf("%d -- %d : %lld\n", last_pos, e[i].pos, 1LL * last_ans * (e[i].pos - last_pos));
		}
		if(e[i].type == 1){
			//for(it = st1.begin(); it != st1.end(); ++it) printf("%d\n", *it);
			it = st2.lower_bound(-e[i].left);
			int left = *it; left = -left;
			it = st1.lower_bound(e[i].rght);
			int rght = *it;
			//printf("[%d,%d]\n", left, rght);
			last_ans -= rght - left > l ? rght - left - l : 0;
			last_ans += e[i].left - left > l ? e[i].left - left - l : 0;
			last_ans += rght - e[i].rght > l ? rght - e[i].rght - l : 0;
			st1.insert(e[i].left);
			st2.insert(-e[i].rght);
		}else{
			st1.erase(st1.find(e[i].left));
			st2.erase(st2.find(-e[i].rght));
			it = st2.lower_bound(-e[i].left);
			int left = *it; left = -left;
			it = st1.lower_bound(e[i].rght);
			int rght = *it;
			//printf("[%d,%d]\n", left, rght);
			last_ans += rght - left > l ? rght - left - l : 0;
			last_ans -= e[i].left - left > l ? e[i].left - left - l : 0;
			last_ans -= rght - e[i].rght > l ? rght - e[i].rght - l : 0;
		}
		last_pos = e[i].pos;
		//printf("%d : %d\n", last_pos, last_ans);
	}
	ans += 1LL * last_ans * (w + 1 - last_pos);
	//printf("half %d %lld\n", last_ans, ans);
	
	m = 0;
	for(int i = 1; i <= n; ++i){
		e[++m] = evnt(yy1[i], xx1[i], xx2[i], 1);
		e[++m] = evnt(yy2[i] + 1, xx1[i], xx2[i], 2);
	}
	sort(e + 1, e + 1 + m, cmp);
	last_pos = 1, last_ans = w - l + 1;
	st1.clear(); st1.insert(w + 1);
	st2.clear(); st2.insert(0);
	for(int i = 1; i <= m; ++i){
		if(e[i].pos != last_pos){
			ans += 1LL * last_ans * (e[i].pos - last_pos);
			//printf("%d -- %d : %lld\n", last_pos, e[i].pos, 1LL * last_ans * (e[i].pos - last_pos));
		}
		if(e[i].type == 1){
			//for(it = st1.begin(); it != st1.end(); ++it) printf("%d\n", *it);
			it = st2.lower_bound(-e[i].left);
			int left = *it; left = -left;
			it = st1.lower_bound(e[i].rght);
			int rght = *it;
			//printf("[%d,%d]\n", left, rght);
			last_ans -= rght - left > l ? rght - left - l : 0;
			last_ans += e[i].left - left > l ? e[i].left - left - l : 0;
			last_ans += rght - e[i].rght > l ? rght - e[i].rght - l : 0;
			st1.insert(e[i].left);
			st2.insert(-e[i].rght);
		}else{
			st1.erase(st1.find(e[i].left));
			st2.erase(st2.find(-e[i].rght));
			it = st2.lower_bound(-e[i].left);
			int left = *it; left = -left;
			it = st1.lower_bound(e[i].rght);
			int rght = *it;
			//printf("[%d,%d]\n", left, rght);
			last_ans += rght - left > l ? rght - left - l : 0;
			last_ans -= e[i].left - left > l ? e[i].left - left - l : 0;
			last_ans -= rght - e[i].rght > l ? rght - e[i].rght - l : 0;
		}
		last_pos = e[i].pos;
		//printf("%d : %d\n", last_pos, last_ans);
	}
	ans += 1LL * last_ans * (h + 1 - last_pos);
	//printf("last_ans %d last_pos %d\n", last_ans, last_pos);
	if(l == 1) ans /= 2;
	printf("%lld\n", ans);
}

int main(){
	
	while(scanf("%d%d%d%d", &w, &h, &n, &l) == 4) work();

	return 0;
}
