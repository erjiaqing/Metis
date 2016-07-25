#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const int maxn = 1e3 + 5;
const int inf = 1e9;
const long long mod = 1e9 + 7;

struct pit{
	
	int x, y;
	pit(int x = 0, int y = 0) : x(x), y(y) {}
	
	bool friend operator == (pit A, pit B){
		if(A.x != B.x) return false;
		if(A.y != B.y) return false;
		else return true;
	}
};
pit P[maxn];

bool cmpx(pit A, pit B){
	
	if(A.x != B.x) return A.x < B.x;
	else return A.y < B.y;
}

int gcd(int a, int b){
	
	if(a < b) swap(a, b);
	if(b == 0) return a;
	else return gcd(b, a % b);
}

long long ans, fact[maxn];
int n;
vector<pit> vec;
void work(){
	
	ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &P[i].x);
		scanf("%d", &P[i].y);
	}
	
	sort(P + 1, P + 1 + n, cmpx);
	P[n+1] = pit(inf + 1, inf + 1);
	for(int i = 1; i <= n; ++i){
		int s = 0;
		long long tmp_ans = 0;
		for(int j = i + 1; j <= n; ++j){
			if(P[i] == P[j]){
				++s;
				continue;
			}
			int x = P[j].x - P[i].x;
			int y = P[j].y - P[i].y;
			int g = gcd(abs(x), abs(y));
			vec.push_back(pit(x / g, y / g));
		}
		sort(vec.begin(), vec.end(), cmpx);
		for(int j = 0, k = 1; j < vec.size(); ++j, ++k){
			if(j < vec.size() - 1 && vec[j] == vec[j+1]) continue;
			else{
				tmp_ans += fact[k] - 1 + mod;
				tmp_ans %= mod;
				k = 0;
			}
		}
		long long tmp = (tmp_ans + 1ll);
		tmp *= fact[s];
		tmp %= mod;
		ans +=  tmp - 1 + mod;
		ans %= mod;
		vec.clear();
	}
	
	cout << ans << endl;
}

int main(){
	
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i) fact[i] = fact[i-1] * 2, fact[i] %= mod;	
	
	int case_number;
	scanf("%d", &case_number);
	for(int cs = 1; cs <= case_number; ++cs) work();

	return 0;
}
