//圆并-圆交
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 8;

double x[2][2], y[2][2];

const double pi=acos(-1);
const double eps=1e-12;
double sqr(double x){
	return x*x;
}
double sign(double x){
	return (x>eps)-(x<-eps);
}
double ans[2333];
int n;
struct P{
	double x,y;
	P(){}
	P(double x,double y):x(x),y(y){}
	void scan(){scanf("%lf%lf",&x,&y);}
	double sqrlen(){return (sqr(x)+sqr(y));}
	double len(){return sqrt(sqr(x)+sqr(y));}
	P zoom(double d){
		double l=d/len();
		return P(l*x,l*y);
	}
	P rev(){
		return P(y,-x);
	}
}dvd,a[233];
P centre[233];
double atan2(P x){
	return atan2(x.y,x.x);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P operator*(double a,P b){
	return P(a*b.x,a*b.y);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
struct circle{
	double r;P o;
	circle(){}
	void scan(){
		o.scan();
		//scanf("%lf",&r);
	}
}cir[2333];
struct arc{
	double theta;
	int delta;
	P p;
	arc(){}
	arc(double theta,P p,int d):theta(theta),p(p),delta(d){}
}vec[4444];
int nV;
bool operator<(arc a,arc b){
	return a.theta+eps<b.theta;
}
int cnt;
void psh(double t1,P p1,double t2,P p2){
	if(t2+eps<t1)
		cnt++;
	vec[nV++]=arc(t1,p1,1);
	vec[nV++]=arc(t2,p2,-1);
}
void combine(int d,double area,P o){
	if(sign(area)==0)return;
	centre[d]=1/(ans[d]+area)*(ans[d]*centre[d]+area*o);
	ans[d]+=area;
}
bool equal(double x,double y){
	return x+eps>y and y+eps>x;
}
bool equal(P a,P b){
	return equal(a.x,b.x) and equal(a.y,b.y);
}
bool equal(circle a,circle b){
	return equal(a.o,b.o) and equal(a.r,b.r);
}
P p[4];
double cub(double x){return x*x*x;}

int main()
{
	int Case = 0;
	
	n = 4;
	while(1)
	{
		++Case;
		
		double cur = 0;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				scanf("%lf%lf", &x[i][j], &y[i][j]), cur += x[i][j] + y[i][j];
				
		if(cur < eps) break;
		
		int tmp = 0;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
			{
				cir[tmp].o.x = 0.5 * (x[0][i] + x[1][j]);
				cir[tmp].o.y = 0.5 * (y[0][i] + y[1][j]);
				cir[tmp].r = 0.5 * sqrt(sqr(x[0][i] - x[1][j]) + sqr(y[0][i] - y[1][j]));
				//cerr<<cx[tmp]<<" "<<cy[tmp]<<" "<<cr[tmp]<<endl;
				++tmp;
			}
		
		for(int i = 0; i <= n; ++i) ans[i] = 0.0;
		for(int i = 0; i <= n; ++i) centre[i] = P(0, 0);
		
		
		for(int i=0;i<n;i++){
			dvd=cir[i].o-P(cir[i].r,0);
			
			nV=0;
			vec[nV++]=arc(-pi,dvd,1);
			cnt=0;
			for(int j=0;j<n;j++)if(i!=j){
				double d=(cir[j].o-cir[i].o).sqrlen();
				if(d<sqr(cir[j].r-cir[i].r)+eps){
					if(cir[i].r+i*eps<cir[j].r+j*eps)
						psh(-pi,dvd,pi,dvd);
				}else if(d+eps<sqr(cir[j].r+cir[i].r)){
					double lambda=0.5*(1+(sqr(cir[i].r)-sqr(cir[j].r))/d);
					P cp=cir[i].o+lambda*(cir[j].o-cir[i].o);
					P nor((cir[j].o-cir[i].o).rev().zoom(sqrt(sqr(cir[i].r)-(cp-cir[i].o).sqrlen())));
					P frm(cp+nor);
					P to(cp-nor);
					psh(atan2(frm-cir[i].o),frm,atan2(to-cir[i].o),to);
				}
			}
			sort(vec+1,vec+nV);
			vec[nV++]=arc(pi,dvd,-1);
			
			for(int j=0;j+1<nV;j++){
				cnt+=vec[j].delta;
				double theta=vec[j+1].theta-vec[j].theta;
				double area=sqr(cir[i].r)*theta*0.5;
				combine(cnt,area,cir[i].o+1.0/area/3*cub(cir[i].r)*P(sin(vec[j+1].theta)-sin(vec[j].theta),cos(vec[j].theta)-cos(vec[j+1].theta)));
				combine(cnt,-sqr(cir[i].r)*sin(theta)*0.5,1./3*(cir[i].o+vec[j].p+vec[j+1].p));
				combine(cnt,vec[j].p*vec[j+1].p*0.5,1.0/3*(vec[j].p+vec[j+1].p));
			}
		}
		
		printf("Case %d: ", Case);
		printf("%.3f\n\n",ans[1] - ans[4]);		
	}	
	
	return 0;
}
