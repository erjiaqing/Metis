#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 2e5 + 5;
const double eps = 1e-5;

struct pit{
	
	double x, y;
	pit(double x = 0.00000000, double y = 0.00000000) : x(x), y(y) {};
	
	pit friend operator - (pit A, pit B){
		return pit(A.x - B.x, A.y - B.y);
	}
	
};
pit P[maxn], C[maxn], G;

typedef pit vec;

double det(vec u, vec v){
	
	return u.x * v.y - u.y * v.x;
}

double dot(vec u, vec v ){
	
	return u.x * v.x + u.y * v.y;
}

bool cmp(pit A, pit B){
	if(fabs(A.y - B.y) < eps) return A.x < B.x;
	else return A.y < B.y;
	/*
	if(fabs(A.x - B.x) > eps) return A.x < B.x;
	else return A.y < B.y;*/
}

int n, m;
void convex(){
	
	sort(P, P + n, cmp);
	int top = 0;
	for(int i = 0; i < n; ++i){
		while(top >= 2 && det(C[top-1] - C[top-2], P[i] - C[top-2]) < eps) --top;
		C[top++] = P[i];
	}
	int lasttop = top;
	for(int i = n - 1; i >= 0; --i){
		while(top > lasttop && det(C[top-1] - C[top-2], P[i] - C[top-2]) < eps) --top;
		C[top++] = P[i];
	}
	m = top - 1;
	//for(int i = 0; i < top; ++i) cerr<<C[i].x<<" "<<C[i].y<<endl;
}

void work(){
	
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%lf%lf", &P[i].x, &P[i].y);
	
	G.x = G.y = 0.00000000;
	double area = 0.00000000;
	for(int i = 1; i < n - 1; ++i){
		vec u = P[i] - P[0];
		vec v = P[i+1] - P[0];
		double nowarea = det(u, v);
		area += nowarea;
		G.x += nowarea * (P[0].x + P[i].x + P[i+1].x);
		G.y += nowarea * (P[0].y + P[i].y + P[i+1].y);
	}
	G.x /= area, G.x /= 3.00000000;
	G.y /= area, G.y /= 3.00000000;
	//printf("G %lf %lf\n", G.x, G.y);
	
	
	
	convex();
	//printf("%d\n", m);
	
	
	int ans = 0;
	for(int i = 0; i < m; ++i){
		int j = (i + 1) % m;
		vec u, v;
		
		u = G - C[i];
		v = C[j] - C[i];
		if(dot(u, v) < eps) continue;
		u = G - C[j];
		v = C[i] - C[j];
		if(dot(u, v) < eps) continue;
		++ans;
	}
	printf("%d\n", ans);
}

int main(){
	
	int case_number;
	scanf("%d", &case_number);
	for(int cs = 1; cs <= case_number; ++cs){
		work();
	}
	
	return 0;
}
