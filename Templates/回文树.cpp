#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 400010;
int ch[N][26], fail[N], len[N], tot, cnt1[N], cnt2[N];
char s[200010];

void ready(){
	len[0] = 0;  len[1] = -1;
	fail[0] = 1; fail[1] = -1;
}
void Insert(char *s, int *cnt){
	int now = 1, l = strlen(s), x, y, tmp;
	for(int i = 0; i < l; i ++){
		x = s[i] - 'a';
		while(s[i] != s[i - len[now] - 1]) now = fail[now];
		if (!ch[now][x]){
			ch[now][x] = ++ tot;
			len[tot] = len[now] + 2;
		}
		y = ch[now][x];
		tmp = fail[now];
		if (tmp == -1) fail[y] = 0;
		else{
			while(s[i] != s[i - len[tmp] - 1]) tmp = fail[tmp];
			fail[y] = ch[tmp][x];
		}
		now = y;
		cnt[now] ++;
	}
}

int main(){
	int T, tests = 0;
	scanf("%d", &T);
	while(tests < T){
		for(int i = 0; i <= tot; i ++){
			for(int j = 0; j < 26; j ++) ch[i][j] = 0;
			len[i] = cnt1[i] = cnt2[i] = 0;
		}
		tot = 1;
		ready();
		scanf("%s", s);
		Insert(s, cnt1);
		scanf("%s", s);
		Insert(s, cnt2);
		for(int i = tot; i >= 2; i --)
			cnt1[fail[i]] += cnt1[i],
			cnt2[fail[i]] += cnt2[i];
		LL ans = 0;
		for(int i = 2; i <= tot; i ++) ans += 1LL * cnt1[i] * cnt2[i];
		printf("Case #%d: %lld\n",++tests, ans);
	}
	return 0;
}
