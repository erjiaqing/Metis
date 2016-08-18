#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 5e5 + 5;

struct pit{
	int x, y, z;
	pit(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	void scan(){scanf("%d%d%d", &x, &y, &z);}
	void print(){printf("(%d, %d, %d)\n", x, y, z);}
	
	bool friend operator == (pit A, pit B){return A.x == B.x && A.y == B.y && A.z == B.z;}
	bool friend operator < (pit A, pit B){
		if(A.x != B.x) return A.x < B.x;
		else if(A.y != B.y) return A.y < B.y;
			 else return A.z < B.z;
	}
};

struct seg{
	
	pit A, B;
	seg(pit A = pit(0, 0), pit B = pit(0, 0)) : A(A), B(B) {}
	void print(){printf("(%d, %d, %d) (%d, %d, %d)\n", A.x, A.y, A.z, B.x, B.y, B.z);}
	bool friend operator == (seg u, seg v){return u.A == v.A && u.B == v.B;}
	bool friend operator < (seg u, seg v){
		if(u.A == v.A) return u.B < v.B;
		else return u.A < v.A;
	}
};

vector<pit> vt;
vector<seg> eg;

int main(){
	
	int n, V, E, F;
	scanf("%d", &n);
	F = n;
	for(int i = 1; i <= n; ++i){
		pit P[3];
		for(int j = 0; j < 3; ++j) P[j].scan();
		for(int j = 0; j < 3; ++j) vt.push_back(P[j]);
		for(int j = 0; j < 3; ++j){
			int k = j + 1; k %= 3;
			//printf("%d %d\n", j, k);
			eg.push_back(seg(P[j], P[k]));
		}
		for(int j = 0; j < 3; ++j){
			int k = j - 1; k += k < 0 ? 3 : 0;
			//printf("%d %d\n", j, k);
			eg.push_back(seg(P[j], P[k]));
		}
	}
	sort(vt.begin(), vt.end());
	sort(eg.begin(), eg.end());
	V = vt.size();
	E = eg.size();
	//printf("%d %d %d\n", V, E, F);
	//for(int i = 0; i < vt.size(); ++i) vt[i].print();
	//for(int i = 0; i < eg.size(); ++i) eg[i].print();
	for(int i = 1; i < vt.size(); ++i) if(vt[i] == vt[i-1]) --V;
	for(int i = 1; i < eg.size(); ++i) if(eg[i] == eg[i-1]) --E; E /= 2;
	//printf("%d %d %d\n", V, E, F);
	printf("%d\n", (2 - V + E - F) / 2);

	return 0;
}
