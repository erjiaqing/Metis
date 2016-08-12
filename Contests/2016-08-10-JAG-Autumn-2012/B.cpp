#include <bits/stdc++.h>
using namespace std;

const char suit[] = "SHDC";

struct card{
	int rank, times;
	char suit;
	bool scan(){
		suit = 0;
		while(suit < 'A' || suit > 'Z'){
			suit = getchar();
			if(suit == '#') return false;
		}
		char ch = getchar();
		if(ch == 'A') rank = 14;
		else if(ch == 'T') rank = 10;
		else if(ch == 'J') rank = 11;
		else if(ch == 'Q') rank = 12;
		else if(ch == 'K') rank = 13;
		else rank = ch - '0';
		times = 1;
		return true;
	}
	
	bool friend operator < (card i, card j){return i.times == j.times ? i.rank > j.rank : i.times > j.times;}
	bool friend operator > (card i, card j){return i.times == j.times ? i.rank < j.rank : i.times < j.times;}
};

struct hand{
	card crds[5];
	bool flush, straight;
	int fir_kind, sec_kind;
	
	void scan(){for(int i = 0; i < 5; ++i) crds[i].scan();}
	bool is_straight(){
		for(int i = 2; i < 5; ++i) if(crds[i].rank != crds[i-1].rank - 1) return false;
		if(crds[0].rank != 14) return crds[0].rank == crds[1].rank + 1;
		else{
			if(crds[1].rank == 13) return true;
			if(crds[4].rank == 2){
				for(int i = 1; i < 5; ++i) swap(crds[i], crds[i-1]);
				return true;
			}
			return false;
		}
	}
	void pre(){
		int cnt[26];
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < 5; ++i) ++cnt[crds[i].rank];
		fir_kind = sec_kind = 0;
		for(int i = 2; i <= 14; ++i){
			if(cnt[i] >= fir_kind) sec_kind = fir_kind, fir_kind = cnt[i];
			else sec_kind = max(sec_kind, cnt[i]);
			for(int j = 0; j < 5; ++j) if(crds[j].rank == i) crds[j].times = cnt[i];
		}
		flush = false;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < 5; ++i) ++cnt[crds[i].suit-'A'];
		for(int i = 0; i < 26; ++i) if(cnt[i] == 5) flush = true;
		sort(crds, crds + 5);
		straight = is_straight();
	}
	bool is_royal_straight_flush(){
		if(!flush || !straight) return false;
		return crds[0].rank == 14;
	}
	bool is_four_of_a_kind(){
		if(fir_kind == 4) return true;
		else return false;
	}
	bool is_full_house(){
		if(fir_kind == 3 && sec_kind == 2) return true;
		else return false;
	}
	bool is_three_of_a_kind(){
		if(fir_kind == 3) return true;
		else return false;
	}
	bool is_two_pairs(){
		if(fir_kind == 2 && sec_kind == 2) return true;
		else return false;
	}
	bool is_one_pair(){
		if(fir_kind == 2) return true;
		else return false;
	}
	int spec(){
		if(is_royal_straight_flush()) return 9;
		if(straight && flush) return 8;
		if(is_four_of_a_kind()) return 7;
		if(is_full_house()) return 6;
		if(flush) return 5;
		if(straight) return 4;
		if(is_three_of_a_kind()) return 3;
		if(is_two_pairs()) return 2;
		if(is_one_pair()) return 1;
		return 0;
	}
};

int high_card(hand mine, hand yours){
	for(int i = 0; i < 5; ++i){
		if(mine.crds[i] < yours.crds[i]) return 1; // actully >
		if(mine.crds[i] > yours.crds[i]) return -1;
	}
	return -1;
}

int showdown(hand mine, hand yours){
	mine.pre();
	yours.pre();
	int spec_mine = mine.spec();
	int spec_yours = yours.spec();
	if(spec_mine > spec_yours) return 1;
	if(spec_mine < spec_yours) return -1;
	return high_card(mine, yours);
}

int cnt, win_cnt;
bool mine_found, yours_found;
hand mine, yours, mine_fir, yours_fir;
card pool_mine[7], pool_yours[7];
bool flag_mine[7], flag_yours[7], flag[26][20];

void dfs_yours(int pos, int beg){
	
	if(pos == 2){
		for(int i = 0, j = 0; i < 7; ++i){
			if(flag_yours[i]) continue;
			yours.crds[j++] = pool_yours[i];
		}
		if(!yours_found || showdown(yours, yours_fir) == 1) yours_fir = yours;
		yours_found = true;
		return;
	}
	for(int i = beg; i < 7; ++i){
		flag_yours[i] = true;
		dfs_yours(pos + 1, i + 1);
		flag_yours[i] = false;
	}
}

void dfs_mine(int pos, int beg){
	
	if(pos == 2){
		for(int i = 0, j = 0; i < 7; ++i){
			if(flag_mine[i]) continue;
			mine.crds[j++] = pool_mine[i];
		}
		if(!mine_found || showdown(mine, mine_fir) == 1) mine_fir = mine;
		mine_found = true;
		return;
	}
	for(int i = beg; i < 7; ++i){
		flag_mine[i] = true;
		dfs_mine(pos + 1, i + 1);
		flag_mine[i] = false;
	}
}

void dfs_turn_and_river(int pos){
	
	if(pos == 7){
		mine_found = false;
		yours_found = false;
		dfs_mine(0, 0);
		dfs_yours(0, 0);
		++cnt;
		if(showdown(mine_fir, yours_fir) == 1) ++win_cnt;
		return;
	}
	for(int i = 0; i < 4; ++i){
		char s = suit[i];
		for(int j = 2; j <= 14; ++j){
			if(flag[s-'A'][j]) continue;
			flag[s-'A'][j] = true;
			pool_mine[pos].suit = s;
			pool_mine[pos].rank = j;
			pool_yours[pos] = pool_mine[pos];
			dfs_turn_and_river(pos + 1);
			flag[s-'A'][j] = false;
		}
	}
}

int main(){
	
	while(true){
		
		if(!pool_mine[0].scan()) break;
		pool_mine[1].scan();
		for(int i = 0; i < 5; ++i) pool_yours[i].scan();
		for(int i = 2; i < 5; ++i) pool_mine[i] = pool_yours[i];
		memset(flag, 0, sizeof flag);
		for(int i = 0; i < 5; ++i) flag[pool_yours[i].suit-'A'][pool_yours[i].rank] = true;
		for(int i = 0; i < 5; ++i) flag[pool_mine[i].suit-'A'][pool_mine[i].rank] = true;
		cnt = win_cnt = 0;
		dfs_turn_and_river(5);
		printf("%.15f\n", 1.00 * win_cnt / cnt);
	}

	return 0;
}
