typedef map<double, double> mii;
typedef map<double, double>::iterator mit;//对于全部为int的数据，用int 
const double eps = 1e-9;
struct Point {
	double x,y;
    Point (double x = 0, double y = 0):x(x),y(y){} 
    void read(){
        scanf("%lf%lf",&x,&y);
    }
    Point operator +(const Point &b)const{
        return Point(x + b.x, y + b.y);
    }
    Point operator -(const Point &b)const{
        return Point(x - b.x, y - b.y);
    }
	Point(const mit &p): x(p->first), y(p->second) {}
};
double det(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
int sgn(double x){
	return x < -eps ? -1 : x > eps; 
}
inline bool checkinside(mii &a, const Point &p) { // `border inclusive`
	int x = p.x, y = p.y;
	mit p1 = a.lower_bound(x);
	if (p1 == a.end()) return false;
	if (p1->first == x) return y <= p1->second;
	if (p1 == a.begin()) return false;
	mit p2(p1--);
	return sgn(det(p - Point(p1), Point(p2) - p)) >= 0;
}
inline void addPoint(mii &a, const Point &p) { // `no collinear points`
	int x = p.x, y = p.y;
	mit pnt = a.insert(make_pair(x, y)).first, p1, p2;
	for (pnt->second = y; ; a.erase(p2)) {
		p1 = pnt;
		if (++p1 == a.end())
			break;
		p2 = p1;
		if (++p1 == a.end())
			break;
		if (det(Point(p2) - p, Point(p1) - p) < 0)
			break;
	}
	for ( ; ; a.erase(p2)) {
	if ((p1 = pnt) == a.begin())
		break;
	if (--p1 == a.begin())
		break;
	p2 = p1--;
	if (det(Point(p2) - p, Point(p1) - p) > 0)
		break;
	}
}
int main()
{
    int q,t;
    scanf("%d",&q); 
    Point tmp;
    mii upper,lower;
	for (int i = 1; i <= q; ++i)
	{
		scanf("%d",&t);
		tmp.read();
		Point tmp2 = tmp;
		tmp2.y = -tmp2.y;//注意下凸包纵坐标变负判断 
		if (t == 1){
			if (!checkinside(upper,tmp))//注意不能缺少这个判断 
				addPoint(upper,tmp);
			if (!checkinside(lower,tmp2))
				addPoint(lower,tmp2);			
		}else{
			if (checkinside(upper,tmp)&&checkinside(lower,tmp2))puts("YES");
			else puts("NO");			
		}		
	}	
	return 0;
}