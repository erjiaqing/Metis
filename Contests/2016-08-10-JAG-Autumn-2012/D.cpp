#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double inf = 1e4;

struct pit{
	double x, y;
	pit(double x = 0.00, double y = 0.00) : x(x), y(y) {}
	pit friend operator + (pit A, pit B){return pit(A.x + B.x, A.y + B.y);}
	pit friend operator - (pit A, pit B){return pit(A.x - B.x, A.y - B.y);}
	pit friend operator * (pit A, double k){return pit(A.x * k, A.y * k);}
}P[15], cor[4];
typedef pit vec;
double dot(vec u, vec v){return u.x * v.x + u.y * v.y;}
double det(vec u, vec v){return u.x * v.y - u.y * v.x;}
pit line_intersect(pit P1, pit P2, pit Q1, pit Q2){
	//printf("(%lf, %lf)-(%lf, %lf)  (%lf, %lf)-(%lf, %lf)\n", P1.x, P1.y, P2.x, P2.y, Q1.x, Q1.y, Q2.x, Q2.y);
	//puts("done");
	double s1 = det(Q1 - P1, P2 - P1);
	double s2 = det(P2 - P1, Q2 - P1);
	return pit(Q1 + (Q2 - Q1) * (s1 / (s1 + s2)));
}
double dist_line_pit(pit pos, vec v, pit P){
	double a = fabs(det(v, P - pos));
	double b = sqrt(dot(v, v));
	return a / b;
}

int n, ans;
double w, h, r, vx, vy, mind;

void hit(pit pos, vec v, double pass){

	//printf("(%lf, %lf) (%lf, %lf) %lf\n", pos.x, pos.y, v.x, v.y, pass);
	if(pass > inf + eps) return;
	for(int i = 2; i <= n; ++i){
		if(dot(v, P[i] - pos) < -eps) continue;
		double d = dist_line_pit(pos, v, P[i]);
		if(d > 2.00 * r + eps) continue;
		double dd = sqrt(dot(P[i] - pos, P[i] - pos) - d * d) - sqrt((2.00 * r) * (2.00 * r) - d * d);
		if(pass + dd < mind + eps){
			mind = pass + dd;
			ans = i;
		}
	}
	if(ans != -1) return;
	for(int i = 0; i < 4; ++i){
		if(dot(cor[i] - pos, cor[i] - pos) < eps) continue;
		if(dot(cor[i] - pos, v) < eps) continue;
		if(dist_line_pit(pos, v, cor[i]) < eps){
			hit(cor[i], pit(-v.x, -v.y), pass + sqrt(dot(cor[i] - pos, cor[i] - pos)));
			return;
		}
	}
	for(int i = 0; i < 4; ++i){
		int j = i + 1; j %= 4;
		if(fabs(det(v, cor[i] - cor[j])) < eps) continue;
		if(det(cor[i] - pos, v) < eps || det(v, cor[j] - pos) < eps) continue;
		pit Q = line_intersect(cor[i], cor[j], pos, pos + v);
		if(dot(Q - pos, Q - pos) < eps) continue;
		//printf("%d\n", i);
		vec vv = v;
		if((i & 1) == 0) vv.y = -v.y;
		else vv.x = -v.x;
		hit(Q, vv, pass + sqrt(dot(Q - pos, Q - pos)));
		return;
	}
	//puts("Wrong!");
}

void work(){
	
	ans = -1;
	mind = inf;
	scanf("%lf%lf%lf%lf%lf", &w, &h, &r, &vx, &vy);
	for(int i = 1; i <= n; ++i) scanf("%lf%lf", &P[i].x, &P[i].y);
	cor[0] = pit(r, r);
	cor[1] = pit(w - r, r);
	cor[2] = pit(w - r, h - r);
	cor[3] = pit(r, h - r);
	hit(P[1], vec(vx, vy), 0.00);
	printf("%d\n", ans);
}

int main(){
	while(true){
		scanf("%d", &n);
		if(n == 0) break;
		work();
	}
	return 0;
}
