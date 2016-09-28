#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e3 + 5;
const int maxm = 1e5 + 5;

int m, ans;
pair<string, string> ph;
vector<string> vec[maxm];
map<pair<string, string>, int> cnt;

void calc(){
	
	for(int i = 1; i <= m; ++i){
		int l = vec[i].size() - 1;
		for(int j = 0; j < l; ++j){
			pair<string, string> p = make_pair(vec[i][j], vec[i][j+1]);
			++cnt[p];
			//cout << p.first << ' ' << p.second << ' ' << cnt[p] << ' ' << ans << endl;
			if(cnt[p] > ans){
				ans = cnt[p];
				ph = p;
			}else if(cnt[p] == ans) ph = min(ph, p);
		}
	}
}

char s[maxl];

void deal(){
	
	++m;
	int l = strlen(s);
	string tmp = "";
	for(int i = 0; i < l; ++i){
		if(s[i] == ','){
			if(tmp != "") vec[m].push_back(tmp);
			++m;
			tmp = "";
			continue;
		}
		if(s[i] == ' '){
			if(tmp != "") vec[m].push_back(tmp);
			tmp = "";
			continue;
		}
		tmp += s[i];
	}
	if(tmp != "") vec[m].push_back(tmp);
}

int main(){
	
	for(int cs = 1; gets(s); ++cs){
		
		for(int i = 1; i <= m; ++i) vec[i].clear();
		m = ans = 0;
		cnt.clear();
	
		deal();
		while(true){
			gets(s);
			if(s[0] == '#') break;
			deal();
		}
		calc();
		cout << ph.first << ' ' << ph.second << ':' << ans << endl;
	}

	return 0;
}
