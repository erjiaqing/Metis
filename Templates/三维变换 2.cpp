struct Matrix{
    double a[4][4];
    int n,m;
    Matrix(int n = 4):n(n),m(n){
		for(int i = 0; i < n; ++i)
		a[i][i] = 1; 
	}
    Matrix(int n, int m):n(n),m(m){}
    Matrix(Point A){
        n = 4;
        m = 1;
        a[0][0] = A.x;
        a[1][0] = A.y;
        a[2][0] = A.z;
        a[3][0] = 1;
    }
//+-略 
    Matrix operator *(const Matrix &b)const{
        Matrix ans(n,b.m);
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < b.m; ++j)
        {
            ans.a[i][j] = 0;
            for (int k = 0; k < m; ++k)
            ans.a[i][j] += a[i][k] * b.a[k][j];
        }
        return ans;        
    }
    Matrix operator * (double k)const{
        Matrix ans(n,m);
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        ans.a[i][j] = a[i][j] * k;
        return ans;
    }
};
Matrix cur(4), I(4);

Point get(int i){//以下三个是变换矩阵，get是使用方法 
    Matrix ori(p[i]);
    ori = cur * ori;
    return Point(ori.a[0][0],ori.a[1][0],ori.a[2][0]);    
}

void trans(){//平移 
    int l,r;
    Point vec;
    vec.read();
    cur = I;
    cur.a[0][3] = vec.x;
    cur.a[1][3] = vec.y;
    cur.a[2][3] = vec.z;
}
void scale(){//以base为原点放大k倍
    Point base;
    base.read();
    scanf("%lf",&k);
    cur = I;
    cur.a[0][0] = cur.a[1][1] = cur.a[2][2] = k;
    cur.a[0][3] = (1.0 - k) * base.x;
    cur.a[1][3] = (1.0 - k) * base.y;
    cur.a[2][3] = (1.0 - k) * base.z;
}
void rotate(){//绕以base为起点vec为方向向量的轴逆时针旋转theta 
    Point base,vec;
    base.read();
    vec.read();
    double theta;
    scanf("%lf",&theta);
    if (dcmp(vec.x)==0&&dcmp(vec.y)==0&&dcmp(vec.z)==0)return;
    double C = cos(theta), S = sin(theta);
    vec = vec / len(vec);
    Matrix T1,T2;
    T1 = T2 = I;
    T1.a[0][3] = base.x;
    T1.a[1][3] = base.y;
    T1.a[2][3] = base.z;
    T2.a[0][3] = -base.x;
    T2.a[1][3] = -base.y;
    T2.a[2][3] = -base.z;        
    cur = I;
    cur.a[0][0] = sqr(vec.x) * (1 - C) + C;
    cur.a[0][1] = vec.x * vec.y * (1-C) - vec.z * S;
    cur.a[0][2] = vec.x * vec.z * (1-C) + vec.y * S;
    cur.a[1][0] = vec.x * vec.y * (1-C) + vec.z * S;
    cur.a[1][1] = sqr(vec.y) * (1-C) + C;
    cur.a[1][2] = vec.y * vec.z * (1-C) - vec.x * S;    
    cur.a[2][0] = vec.x * vec.z * (1-C) - vec.y * S;
    cur.a[2][1] = vec.y * vec.z * (1-C) + vec.x * S;
    cur.a[2][2] = vec.z * vec.z * (1-C) + C;
    cur = T1 * cur * T2;
}