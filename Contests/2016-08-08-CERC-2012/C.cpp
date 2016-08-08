#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 5e4 + 5;

const char s1[] = "hbcnofpskvyiwu";
const char s2[] = "helibenenamgalsiclarcascticrmnfeconicuzngageassebrkrrbsrzrnbmotcrurhpdagcdinsnsbtexecsbahftareosirptauhgtlpbbipoatrnfrrarfdbsgbhhsmtdsrgcnfllvlaceprndpmsmeugdtbdyhoertmybluacthpanppuamcmbkcfesfmmdnolr";
int l1 = strlen(s1);
int l2 = strlen(s2);

int n;
bool f[maxn];
char str[maxn];

bool check1(int i){
	
	for(int j = 0; j < l1; j += 1)
		if(s1[j] == str[i]) return true;
	return false;
}

bool check2(int i){
	
	for(int j = 0; j < l2; j += 2)
		if(s2[j] == str[i-1] && s2[j+1] == str[i]) return true;
	return false;
}

void work(){
	
	scanf("%s", str + 1);
	n = strlen(str + 1);
	
	memset(f, 0, sizeof f);
	f[0] = true;
	for(int i = 1; i <= n; ++i){
		if(i > 0) f[i] |= f[i-1] & check1(i);
		if(i > 1) f[i] |= f[i-2] & check2(i);
	}
	if(f[n]) puts("YES");
	else puts("NO");
}

int main(){
	
	//printf("%d %d\n", l1, l2);
		
	int t;
	scanf("%d", &t);
	for(int cs = 1; cs <= t; ++cs) work();

	return 0;
}
