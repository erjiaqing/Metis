int n;
double A,B;
struct Point{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    void modify(){
        x = max(x,0.0);
        x = min(x,A);
        y = max(y,0.0);
        y = min(y,B);
    }
}p[1000000];
double sqr(double x){
    return x * x;
}
double Sqrt(double x){
    if(x < eps) return 0;
    return sqrt(x);
}
Point operator + (const Point &a,const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point &a,const Point &b){
    return Point(a.x - b.x, a.y - b.y);
}
Point operator * (const Point &a,const double &k){
    return Point(a.x * k, a.y * k);
}
Point operator / (const Point &a,const double &k){
    return Point(a.x / k, a.y / k);
}
double det (const Point &a,const Point &b){
    return a.x * b.y - a.y * b.x;
}
double dist(const Point &a, const Point &b){
    return Sqrt(sqr(a.x - b.x)+sqr(a.y - b.y));
}
double work(const Point &x){
    double ans = 1e9;
    for(int i=1;i<=n;i++)
        ans = min(ans,dist(x,p[i]));
    return ans;
}
int main(){
    srand(time(NULL));
    int numcase;
    cin>>numcase;
    while (numcase--){
        scanf("%lf%lf%d",&A,&B,&n);
        for(int i=1;i<=n;i++){
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        double total_ans = 0;
        Point total_aaa;
        for(int ii = 1;ii<=total/n;ii++){
            double ans = 0;
            Point aaa;
            Point p;
            p.x = (rand() % 10000) * A / 10000;
            p.y = (rand() % 10000) * B / 10000;
            double step = 2 * max(A,B);
            for(double T = 1e6;T > 1e-2;T = T * 0.98){
                double thi = (rand() % 10000) * pi2 / 10000;
                Point now = p + Point(cos(thi), sin(thi)) * step * (rand() % 10000)/10000;
                now.modify();
                double now_ans = work(now);
                double delta = now_ans -ans;
                if(delta > 0) {
                    p = now;
                    ans = now_ans;
                    aaa = now;
                }
                else{
                    if((rand() % 10000) / 10000.0 > exp(delta / T)) p = now;
                }
                step = max(step * 0.9,1e-3);
            }
            if(ans > total_ans) total_ans = ans, total_aaa = aaa;
        }
        printf("The safest point is (%.1f, %.1f).\n",total_aaa.x,total_aaa.y);
    }
}