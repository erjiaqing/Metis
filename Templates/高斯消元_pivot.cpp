//special为一组特解，null_space为零向量解空间，ｎ个方程，ｍ个未知量
double a[N][M], b[N], special[M], null_space[M][M];
int idx[N];
bool pivot[M];
double eps=1e-9;
void gauss() {
    int row = 0;
    fill(idx, idx + n, -1);
    fill(pivot, pivot + m, false);
    for (int col = 0; row < n && col < m; ++col) {
        int best = row;
        for (int i = row + 1; i < n; ++i) {
            if (fabs(a[i][col]) > fabs(a[best][col])) best = i;
        }
        for (int i = 0; i < m; ++i) {
            double tmp = a[best][i];
            a[best][i] = a[row][i];	a[row][i] = tmp;
        }
        double tmp = b[best];
        b[best]= b[row]; b[row] = b[best];
        if (fabs(a[row][col]) < eps) continue;
        idx[row] = col;
        pivot[col] = true;
        double coef = a[row][col];
        for (int i = 0; i < m; ++i) {a[row][i] /= coef;}
        b[row] /= coef;
        for (int i = 0; i < n; ++i) {
            if (i != row && fabs(a[i][col]) > eps) {
                double coef = a[i][col];
                for (int j = 0; j < m; ++j) {a[i][j] -= a[row][j] * coef;}
                b[i] -= b[row] * coef;
            }
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (fabs(b[i]) > eps) {	return;} //no solution
    }
    fill(special, special + m, 0);
    for (int i = 0; i < row; ++i) {special[idx[i]] = b[i];}
    for (int i = 0; i < m - row; ++i) {
        for (int j = 0; j < m; ++j) {null_space[j][i] = 0;}
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (!pivot[i]) {
            for (int j = 0; j < row; ++j) {null_space[idx[j]][cnt] = a[j][i];}
            null_space[i][cnt++] = -1;
        }
    }
}