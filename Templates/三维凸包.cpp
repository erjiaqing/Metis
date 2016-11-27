//face里面存了所有面，face[i][j]对应面上info点的下表 
#define SIZE(X) (int(X.size()))
#define PI 3.14159265358979323846264338327950288
const double eps = 1e-8;
const double pi = acos(-1.0);
inline double Sqr(double a){
	return a * a;
}
inline double Sqrt(double a){
	return a <= 0 ? 0: sqrt(a);
}
class Point_3{
public:
	double x,y,z;
	Point_3(){}
	Point_3(double x, double y, double z) : x(x), y(y), z(z){}
	double length()const{
		return Sqrt(Sqr(x) + Sqr(y) + Sqr(z));
	}
	Point_3 operator + (const Point_3 &b)const{
		return Point_3(x + b.x, y + b.y, z + b.z);
	}
	Point_3 operator - (const Point_3 &b)const{
		return Point_3(x - b.x, y - b.y, z - b.z);
	}
	Point_3 operator * (double b)const{
		return Point_3(x * b, y * b, z * b);
	}
	Point_3 operator / (double b)const{
		return Point_3(x / b, y / b, z / b);
	}
	bool operator == (const Point_3 &b)const{
		return x==b.x && y==b.y && z==b.z;
	}
	bool operator < (const Point_3 &b)const{
		if(x!=b.x)return x<b.x;
		if(y!=b.y)return y<b.y;
		else return z<b.z;
	}
	void read(){
		scanf("%lf%lf%lf",&x,&y,&z);
	}
	Point_3 Unit()const{
		return *this/length();
	}
	double dot(const Point_3 &b)const{
		return x * b.x + y * b.y + z * b.z;
	}
	Point_3 cross(const Point_3 &b)const{
		return Point_3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}	
};
Point_3 Det(const Point_3 &a, const Point_3 &b){
	return Point_3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double dis(const Point_3 &a, const Point_3 &b){
	return Sqrt(Sqr(a.x-b.x) + Sqr(a.y-b.y) + Sqr(a.z-b.z));
}
inline int Sign (double x){
	return x < -eps? -1:(x>eps?1:0);
}
int mark[1005][1005];
Point_3 info[1005];
int n,cnt;
double mix(const Point_3 &a, const Point_3 &b, const Point_3 &c){
	return a.dot(b.cross(c));
}
double area(int a,int b,int c){
	return ((info[b] - info[a]).cross(info[c] - info[a])).length();
}
double volume(int a,int b, int c, int d){
	return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}
struct Face{
	int a,b,c;
	Face(){};
	Face (int a, int b, int c): a(a),b(b),c(c){}
	int &operator [](int k){
		if (k == 0)return a;
		if (k == 1) return b;
		return c;
	}
};
vector <Face> face;
inline void insert(int a, int b, int c){
	face.push_back(Face(a,b,c));
}
void add(int v){
	vector <Face> tmp;
	int a, b, c, d;
	cnt++;
	for (int i = 0; i < SIZE(face); i++){
		a = face[i][0];
		b = face[i][1];
		c = face[i][2];
		if (Sign(volume(v, a, b, c)) < 0)
		{
			mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
		}else{
			tmp.push_back(face[i]);
		}
	}
	face = tmp;
	for (int i = 0; i < SIZE(tmp); ++i){
		a = face[i][0];
		b = face[i][1];
		c = face[i][2];
		if (mark[a][b] == cnt) insert(b,a,v);
		if (mark[b][c] == cnt) insert(c,b,v);
		if (mark[c][a] == cnt) insert(a,c,v);
	}
}
int Find(){
	for (int i = 2; i < n; ++i){
		Point_3 ndir = (info[0] - info[i]).cross(info[1] - info[i]);
		if (ndir == Point_3()) continue;
		swap(info[i], info[2]);
		for (int j = i + 1; j < n; ++j)
			if(Sign(volume(0,1,2,j)) != 0){
				swap(info[j],info[3]);
				insert(0,1,2);
				insert(0,2,1);
				return 1;
			}
		}
	return 0;
}
double tD_convex(){
	sort(info, info + n);
	n = unique(info, info + n) - info;
	face.clear();
	random_shuffle(info,info + n);
	if (Find()){
		memset(mark, 0, sizeof(mark));
		cnt = 0;
		for (int i = 3; i < n; ++i)add(i);
		double ans = 0;
		for (int i = 0; i < SIZE(face); ++i){
			Point_3 p = (info[face[i][0]] - info[face[i][1]]).cross(info[face[i][2]] - info[face[i][1]]);
			ans += p.length();
		}
		return ans/2;
	}
	return -1;
}