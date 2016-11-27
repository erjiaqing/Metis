struct Point {
	double x, y, z;
	Point (double x = 0, double y = 0, double z = 0):x(x),y(y),z(z){}
	bool operator < (const Point &b)const{
		if (dcmp(x - b.x)==0)return y < b.y;
		else return x < b.x;
	}
};
inline double dot(const Point &a, const Point &b){return a.x*b.x + a.y * b.y + a.z * b.z;}
inline double Length(const Point &a){return sqrt(dot(a,a));}
inline Point cross(const Point &a, const Point &b){
	return Point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
inline double det(const Point &A, const Point &B, const Point &C){//前两维的平面情况！！！！！！ 
	Point a = B - A;
	Point b = C - A;
	return a.x * b.y - a.y * b.x;
}
double Volume(const Point &a,const Point &b, const Point &c, const Point &d){
	return fabs(dot(d-a, cross(b-a,c-a)));
}
double dis(const Point & p, const vector<Point> &v) {
	Point n = cross(v[1] - v[0],v[2] - v[0]);
	return fabs(dot(p - v[0], n))/Length(n);
}
int n;
Point p[100],Zero,basee,vec;
vector<Point>v[300];
bool cmp(const Point &A, const Point &B) {
	Point a = A - basee;
	Point b = B - basee;
	return  dot(vec, cross(a,b)) <= 0;	
}
void caltri(const Point &A, Point B, Point C, double &w, Point &p) {
	double vol = Volume(Zero,A,B,C);
	w += vol;
	p = p + (Zero + A + B + C)/4*vol ;
}
pair<double, Point> cal(vector<Point> &v){
	basee = v[0];
	vec = cross(v[1] - v[0], v[2] - v[0]);
	double w = 0;
	Point centre;
	sort(v.begin(), v.end(),cmp);
	for (int i = 1; i < v.size() - 1; ++i)
	{
		caltri(v[0],v[i],v[i+1],w,centre);		
	}
	return make_pair(w,centre);
}
bool vis[70][70][70];
double work(){
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)p[i].read();
	Zero = p[0];
	for (int i = 0; i < 200; ++i)
	v[i].clear();
	memset(vis,0,sizeof(vis));	
	int rear = -1;
	Point centre;
	double w = 0;
	for (int a = 0; a < n; ++a)
	for (int b = a + 1; b < n; ++b)
	for (int c = b + 1; c < n; ++c)
	if (!vis[a][b][c])
	{
		Point A = p[b] - p[a];
		Point B = p[c] - p[a];
		Point N = cross(A,B);
		int flag[3] = {0};
		for (int i = 0; i < n; ++i)
		if (i != a && i != b && i != c)flag[dcmp(dot(N, p[i] - p[a]))+1] = 1;
		int cnt = 0;
		for (int i = 0; i < 3; ++i)
		if (flag[i])cnt++;
		if (!((cnt==2 && flag[1]==1) || cnt==1))continue;
		++rear;
		vector<int>num;
		v[rear].push_back(p[a]);
		v[rear].push_back(p[b]);
		v[rear].push_back(p[c]);
		num.push_back(a);
		num.push_back(b);
		num.push_back(c);		
		for (int i = c+1; i < n; ++i)
		if (dcmp(dot(N, p[i] - p[a]))==0) {
			v[rear].push_back(p[i]);
			num.push_back(i);
		}
		for (int x = 0; x < num.size(); ++x)
		for (int y = 0; y < num.size(); ++y)
		for (int z = 0; z < num.size(); ++z)
		vis[num[x]][num[y]][num[z]] = 1;
		pair<double, Point>tmp = cal(v[rear]);		
		centre = centre + tmp.second;
		w += tmp.first;	
	}
	centre = centre / w;
	double minn = 1e10;
	for (int i = 0; i <= rear; ++i)
	minn = min(minn, dis(centre, v[i]));
	return minn;
}