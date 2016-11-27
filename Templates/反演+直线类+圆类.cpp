typedef Point Vector;
const double INVERSION_CONST = 10000.0;
struct Line {
	Point p; Vector v;
	Line() {}
	Line(Point _p, Vector _v) : p(_p), v(_v) {}
	Vector normal() const{ //normal法向量，返回指向方向向量左手侧
		return Vector(-v.y, v.x);
	}
    void print() {
        printf("(%.10f, %.10f) + t * (%.10f, %.10f)\n", p.x, p.y, v.x, v.y);
    }
};
inline bool sameSidePL(const Point &a, const Point &b, const Line &l) {
	return sgn(det(l.p - a, l.v) * det(l.p - b, l.v)) > 0;
}
inline bool pointOnLine(const Point &a, const Line &l) {
	return !sgn(det(a - l.p, l.v));
}
inline Point intersectLL(const Line &la, const Line &lb) {
    double t = det(lb.v, la.p - lb.p) / det(la.v, lb.v);
	return la.p + la.v * t;
}
//三点求圆心 
inline Point outerCenter(const Point &a, const Point &b, const Point &c) {
    Line la = Line((a + b) / 2.0, (b - a).normal());//点类补上法向量 返回(-y,x) 
    Line lb = Line((a + c) / 2.0, (c - a).normal());
    return intersectLL(la, lb);
}
struct Circle {
	double x, y, r;
	Circle() {
        x = y = r = 0;
    }
	Circle(double _x, double _y, double _r) : x(_x), y(_y), r(_r) {}
	bool operator == (const Circle &c) {
		return !sgn(x - c.x) && !sgn(y - c.y) && !sgn(r - c.r);
	}
	bool operator != (const Circle &c) {
		return sgn(x - c.x) || sgn(y - c.y) || sgn(r - c.r);
	}
	Point getPoint(double ang) const {
		return Point(x + r * cos(ang), y + r * sin(ang));
	}
	Point center() const {
		return Point(x, y);
	}
    void read() {
        scanf("%lf %lf %lf", &x, &y, &r);
    }
    void print() {
        printf("%.10f %.10f %.10f\n", x, y, r);
    }
    bool operator < (const Circle &a) const {
        return sgn(y - a.y) < 0;
    }
};
// 点到圆的切点
inline pair<Point, Point> tangentPointCP(const Circle &c, const Point &p) {
	double ang = atan2(p.y - c.y, p.x - c.x);
	double alpha = acos(c.r / len(Point(c.x, c.y) - p));
	return make_pair(c.getPoint(ang + alpha), c.getPoint(ang - alpha));
}
// 求两圆的外公切点，ret[0],ret[1]属于圆a，ret[2],ret[3]属于圆b
inline vector<Point> outerTangentPoint(const Circle &a, const Circle &b) {
	vector<Point> ret;
    Vector v = Vector(b.x - a.x, b.y - a.y);
	double ang = atan2(v.y, v.x);
    double alpha = acos((a.r - b.r) / len(v));
	ret.push_back(a.getPoint(ang + alpha));
	ret.push_back(a.getPoint(ang - alpha));
	ret.push_back(b.getPoint(ang + alpha));
	ret.push_back(b.getPoint(ang - alpha));
	return ret;
}
// 求两圆的外公切线
inline pair<Line, Line> outerTangentLine(Circle a, Circle b) {
    vector<Point> t = outerTangentPoint(a, b);
    return make_pair(Line(t[0], t[2] - t[0]), Line(t[1], t[3] - t[1]));
}
inline Point inversionPP(const Point &p1, const Point &p) {
    Vector v = p1 - p;
    double leng = len(v);
    double k = INVERSION_CONST / leng;
    v = v / leng * k;
    return v + p;
}
inline Circle inversionCC(const Circle &c, const Point &p) {
    Point p0 = c.getPoint(0);
    Point p1 = c.getPoint(0.5 * pi);
    Point p2 = c.getPoint(pi);
    p0 = inversionPP(p0, p);
    p1 = inversionPP(p1, p);
    p2 = inversionPP(p2, p);
    Point ct = outerCenter(p0, p1, p2);
    double radius = len(ct - p0);
    return Circle(ct.x, ct.y, radius);
}
inline Circle inversionLC(const Line &l, const Point &p) {
    Point p1 = l.p;
    Point p2 = l.p + l.v;
    p1 = inversionPP(p1, p);
    p2 = inversionPP(p2, p);
    Point ct = outerCenter(p, p1, p2);
    double radius = len(ct - p);
    return Circle(ct.x, ct.y, radius);
}
int getCCintersect(Circle c1, Circle c2, vector<Point>&sol){
	double d = Length(C1.c - C2.c);
	if(sign(d)==0){
		if(sign(C1.r - C2.r) == 0)return -1;
		return 0;
	}
	if (sign(C1.r + C2.r - d) < 0)return 0;
	if (sign(fabs(C1.r - C2.r) - d) > 0)return 0;
	double a = angle(C2.c - C1.c);
	double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
	Point p1 = C1.point(a-da), p2 = C1.point(a+da);
	sol.push_back(p1);
	if (p1 == p2)return 1;
	sol.push_back(p2);
	return 2;
}