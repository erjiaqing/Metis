#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const string tble[] = {
"Cleveland Cavaliers",
"Golden State Warriors",
"San Antonio Spurs",
"Miami Heat",
"Miami Heat",
"Dallas Mavericks",
"L.A. Lakers",
"L.A. Lakers",
"Boston Celtics",
"San Antonio Spurs",
"Miami Heat",
"San Antonio Spurs",
"Detroit Pistons",
"San Antonio Spurs",
"L.A. Lakers",
"L.A. Lakers",
"L.A. Lakers",
"San Antonio Spurs",
"Chicago Bulls",
"Chicago Bulls",
"Chicago Bulls",
"Houston Rockets",
"Houston Rockets",
"Chicago Bulls",
"Chicago Bulls",
"Chicago Bulls",
"Detroit Pistons",
"Detroit Pistons",
"L.A. Lakers",
"L.A. Lakers",
"Boston Celtics",
"L.A. Lakers",
"Boston Celtics",
"Philadelphia 76ers",
"L.A. Lakers",
"Boston Celtics",
"L.A. Lakers",
"Seattle Sonics",
"Washington Bullets",
"Portland Trail Blazers",
"Boston Celtics",
"Golden State Warriors",
"Boston Celtics",
"New York Knicks",
"L.A. Lakers",
"Milwaukee Bucks",
"New York Knicks",
"Boston Celtics",
"Boston Celtics",
"Philadelphia 76ers",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"Boston Celtics",
"St. Louis Hawks",
"Boston Celtics",
"Philadelphia Warriors",
"Syracuse Nats",
"Minneapolis Lakers",
"Minneapolis Lakers",
"Minneapolis Lakers",
"Rochester Royals",
"Minneapolis Lakers",
"Minneapolis Lakers",
"Baltimore Bullets",
"Philadelphia Warriors"
};

const int cnt = 70;

bool mark = false;
char s[105];
string str;

void work(){
	
	//cin >> str;
	if(!mark) char ch = getchar();
	mark = true;
	gets(s);
	str = "";
	for(int i = 0; s[i]; ++i) str += s[i];
	int ans = 0;
	for(int i = 0; i < cnt; ++i) if(tble[i] == str) ++ans;
	cout << ans << endl;
	//cout << str << endl;
}

int main(){
	
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; ++tt){
		printf("Case #%d: ", tt);
		work();
	}

	return 0;
}
