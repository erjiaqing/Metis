int side(const Point &p, const Point &a, const Point &b){return sign(det(b-a,p-a));}
Point intersect(const Point &a, const Point &b, const Point &c, const Point &d){
	double s1 = det(b-a,c-a), s2 = det(b-a,d-a);
	return (c*s2 - d*s1)/(s2-s1);
}
bool parallel(const Point &a, const Point &b, const Point &c, const Point &d){
	return sign(det(b-a,c-d)) == 0;
}
int cut(int n, Point p[], const Point &a, const Point &b){
	static Point res[maxn];
	p[0] = p[n];
	int m = 0;
	for (int i = 1; i <= n; ++i){
		Point pre = p[i-1];
		Point cur = p[i];
		if (side(pre,a,b) >= 0)
			res[++m] = pre;
		if (!parallel(cur,pre,b,a)){
			Point tmp = intersect(pre,cur,a,b);
			if (sign(dot(tmp - pre, tmp - cur)) < 0)
				res[++m] = tmp;
		}
	}
	if (m < 3)
		m = 0;
	for (int i = 1; i <= m; ++i)
	p[i] = res[i];
	return m;	
}