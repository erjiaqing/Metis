#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 5;

int tot;
map<pair<string, bool>, int> id;
vector<int> son[maxn];
string str[maxn];
int flag[maxn];

bool cmp(int i, int j){
	
	if(flag[i] != flag[j]) return flag[i] < flag[j];
	else return str[i] < str[j];
}

void print(int u, int dpth){
	
	for(int i = 0; i < 4 * dpth; ++i) putchar(' ');
	if(dpth != -1) cout << str[u] << endl;
	
	for(int l = 0; l < son[u].size(); ++l){
		int v = son[u][l];
		print(v, dpth + 1);
	}
}

char s[maxn];

void deal(){
	
	//puts(s);
	int l = strlen(s);
	string tmp = "", lst = "", now = "";
	s[l] = '/';
	for(int i = 0, j = 0; i <= l; ++i){
		if(s[i] == '/'){
			tmp += '/';
			bool mark = (i == l);
			pair<string, bool> p = make_pair(tmp, mark);
			if(id.find(p) == id.end()){
				id[p] = ++tot;
				str[tot] = now;
				flag[tot] = mark;
				son[id[make_pair(lst, false)]].push_back(tot);
			}
			
			lst = tmp;
			now = "";
			//tmp = "";
			
			/*puts("------------");
			cout << tmp << endl;
			printf("%d %d\n", tot, flag[tot]);
			puts("............");*/
			
			continue;
		}
		tmp += s[i];
		now += s[i];
	}
}

int main(){
	
	for(int cs = 1; gets(s); ++cs){
	
		printf("Case %d:\n", cs);
		
		memset(flag, 0, sizeof flag);
		id.clear();
		id[make_pair("", false)] = 0;
		for(int i = 0; i <= tot; ++i) son[i].clear();
		tot = 0;
		
		deal();
		while(true){
			gets(s);
			if(s[0] == '0' && s[1] == 0) break;
			deal();
		}
		
		for(int i = 0; i <= tot; ++i) sort(son[i].begin(), son[i].end(), cmp);
		print(0, -1);
	}

	return 0;
}
