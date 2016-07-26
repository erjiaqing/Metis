#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double inf = 1e9;

int sign(double x){
	if(fabs(x) < eps) return 0;
	else if(x > 0) return 1;
		 else return -1;
}

struct pit{
	double x, y;
	pit(double x = 0.00, double y = 0.00) : x(x), y(y) {}
	
	pit friend operator + (pit A, pit B){
		return pit(A.x + B.x, A.y + B.y);
	}
	pit friend operator - (pit A, pit B){
		return pit(A.x - B.x, A.y - B.y);
	}
	pit friend operator * (pit u, double k){
		return pit(u.x * k, u.y * k);
	}
	double lnth(){
		return sqrt(x * x + y * y);
	}
	void rotate(double theta){
		double coss = cos(theta), sinn = sin(theta);
		double tx = x * coss - y * sinn;
		double ty = x * sinn + y * coss;
		x = tx, y = ty;
	}
};
typedef pit vec;

double dot(vec u, vec v){
	return u.x * v.x + u.y * v.y;
}
double det(vec u, vec v){
	return u.x * v.y - u.y * v.x;
}

struct line{
	pit A, B;
	line(pit A = pit(0, 0), pit B = pit(0, 0)) : A(A), B(B) {}
};

pit line_intersect(line u, line v){
	double s1 = det(v.A - u.A, u.B - u.A);
	double s2 = det(u.B - u.A, v.B - u.A);
	pit rtn = v.A + (v.B - v.A) * (s1 / (s1 + s2));
	return rtn;
}

pit P[3];
line l[3], lz;

void shoot(double rate){
	
	int face = -1;
	double dist = inf;
	for(int i = 0; i < 3; ++i){
		if(sign(det(l[i].B - l[i].A, lz.B - lz.A)) == 0) continue;
		pit P = line_intersect(l[i], lz);
		if(sign(dot(P - lz.A, lz.B - lz.A)) <= 0) continue;
		if(sign(dot(P - l[i].A, P - l[i].B)) >= 0) continue;
		double tmp_dist = (P - lz.A).lnth();
		if(sign(tmp_dist) <= 0 || tmp_dist > dist) continue;
		face = i;
		dist = tmp_dist;
	}
	if(face == -1) return;
	line now = l[face];
	pit P = line_intersect(lz, now);
	vec u = lz.B - lz.A;
	vec v = now.B - now.A;
	v = pit(-v.y, v.x);
	if(sign(dot(v, u)) < 0) v = pit(-v.x, -v.y);
	double alpha = acos(dot(u, v) / u.lnth() / v.lnth());
	double beta = asin(sin(alpha) / rate);
	if(sign(det(u, v)) > 0) v.rotate(-beta);
	else v.rotate(beta);
	lz.A = P;
	lz.B = P + v;
}

void work(){
	
	scanf("%lf%lf", &lz.A.x, &lz.A.y);
	scanf("%lf%lf", &lz.B.x, &lz.B.y);
	for(int i = 0; i < 3; ++i) scanf("%lf%lf", &P[i].x, &P[i].y);
	for(int i = 0; i < 3; ++i){
		int j = i + 1; j %= 3;
		l[i].A = P[i];
		l[i].B = P[j];
	}
	
	double rate;
	scanf("%lf", &rate);
	shoot(rate);
	shoot(1.00 / rate);
	
	pit P = line_intersect(lz, line(pit(-1.00, 0.00), pit(1.00, 0.00)));
	if(sign(dot(P - lz.A, lz.B - lz.A)) <= 0) puts("Error");
	else printf("%.3f\n", P.x + eps);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
