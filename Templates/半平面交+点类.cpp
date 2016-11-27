//记得加边界
struct Point {
    double x, y;
    Point (double x = 0, double y = 0):x(x),y(y){}
    void read(){
        scanf("%lf%lf",&x,&y);
    }
    Point operator +(const Point &B)const{
        return Point(x + B.x, y + B.y);
    }
    Point operator -(const Point &B)const{
        return Point(x - B.x, y - B.y);
    }
    Point operator *(double a)const{
        return Point(x * a, y * a);
    }
    Point operator /(double a)const{
        return Point(x / a, y / a);
    }        
};
double det(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
double det(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
double dot(Point a, Point b){
    return a.x * b.x + a.y * b.y;
}
double sqr(double x){
    return x*x;
}
double len(Point a){
    return sqrt(dot(a,a));
}
struct Border{
    Point p1, p2;
    double alpha;
    Border(): p1(), p2(), alpha(0.0){}
    Border(const Point &a, const Point &b):p1(a),p2(b),alpha(atan2(p2.y - p1.y, p2.x - p1.x) ) {}//a->b, 左侧 
    bool operator == (const Border &b)const{
        return dcmp(alpha - b.alpha) == 0;
    }
    bool operator < (const Border &b)const{
        int c = dcmp(alpha - b.alpha);
        if (c != 0) return c > 0;
        return dcmp(det(b.p2 - b.p1, p1 - b.p1)) >= 0;
    }
};

void lineIntersect(Point a, Point b, Point c, Point d, Point &s){
    double s1 = det(a,b,c);
    double s2 = det(a,b,d);
    s = (c*s2 - d*s1) / (s2 - s1);
}
int x[101][2001];
int y[101][2001];
Point isBorder(const Border &a, const Border &b){
    Point is;
    lineIntersect(a.p1, a.p2, b.p1, b.p2, is);
    return is;
}
bool checkBorder(const Border &a, const Border &b, const Border &me){
    Point is;
    lineIntersect(a.p1, a.p2, b.p1, b.p2, is);
    return dcmp(det(me.p2 - me.p1, is - me.p1)) > 0;
}
double HPI(int N, Border border[]){//nlogn 
    static Border que[maxn*2+1];
    static Point ps[maxn];
    int head = 0, tail = 0, cnt = 0;
    sort(border, border + N);
    N = unique(border, border + N) - border;
    for (int i = 0; i < N; ++i){
        Border &cur = border[i];
        while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], cur))
            --tail;
        while (head + 1 < tail && !checkBorder(que[head], que[head + 1], cur))
            ++head;
        que[tail++] = cur;
    }
    while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], que[head]))
        --tail;
    while (head + 1 < tail && !checkBorder(que[head], que[head + 1], que[tail - 1]))
        ++head;
    if (tail - head <= 2)
        return 0,0;
    for (int i = head; i < tail; ++i)
        ps[cnt++] = isBorder(que[i], que[(i+1==tail)?(head):(i+1)]);
    double area = 0;
    for (int i = 0; i < cnt; ++i)
        area += det(ps[i], ps[(i+1)%cnt]);
    return fabs(area * 0.5);
}