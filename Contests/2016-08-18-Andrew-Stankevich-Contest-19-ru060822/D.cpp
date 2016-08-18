#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

const int N = 50;
char S[N], T[N], a[N], b[N];
int n;
map<long long, bool> mp;

int index(char c) {
	if (c == 'A') return 0;
	if (c == 'D') return 1;
	if (c == 'G') return 2;
	if (c == 'T') return 3;
}

long long get_id(char *s) {
	long long id = 0;
	for (int i = 0; i < n; i++)
		id = id * 4 + index(s[i]);
	return id;
}

bool solve() {
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) a[k] = S[k];
			for (int l = i, r = j; l < r; l++, r--) {
				char t = a[l]; a[l] = a[r]; a[r] = t;
			}
			for (int p = 0; p < n; p++)
				for (int q = p; q < n; q++) {
					for (int k = 0; k < n; k++) b[k] = a[k];
					for (int l = p, r = q; l < r; l++, r--) {
						char t = b[l]; b[l] = b[r]; b[r] = t;
					}
					long long t = get_id(b);
					mp[t] = 1;
				}
		}
		
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) a[k] = T[k];
			for (int l = i, r = j; l < r; l++, r--) {
				char t = a[l]; a[l] = a[r]; a[r] = t;
			}
			for (int p = 0; p < n; p++)
				for (int q = p; q < n; q++) {
					for (int k = 0; k < n; k++) b[k] = a[k];
					for (int l = p, r = q; l < r; l++, r--) {
						char t = b[l]; b[l] = b[r]; b[r] = t;
					}
					long long t = get_id(b);
					if (mp[t]) return 1;
				}
		}
	return 0;
}

int main() {
	scanf("%s", S);
	scanf("%s", T);
	n = strlen(S);
	if (solve()) puts("Similar");
	else puts("Different");
	return 0;
}
