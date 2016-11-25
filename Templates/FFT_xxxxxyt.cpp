// 复数 递归
const int maxn = 1e6 + 5;
typedef complex<long double> cpb;
int N;cpb a[maxn], aa[maxn], b[maxn], bb[maxn], c[maxn], cc[maxn];
typedef complex<double> cpb;
void fft(cpb x[], cpb xx[], int n, int step, int type){ // step 表示步长 代码后面举个例子说明一下好了
    if(n == 1){xx[0] = x[0]; return;}
    int m = n >> 1;
    fft(x, xx, m, step << 1, type); // A[0]
    fft(x + step, xx + m, m, step << 1, type); // A[1]
    cpb w = exp(cpb(0, type * pi / m)); // 求原根 pi / m 其实就是 2 * pi / n
    cpb t = 1;
    for(int i = 0; i < m; ++i){
        cpb t0 = xx[i]; // 这个里面是A[0]的内容
        cpb t1 = xx[i+m]; // 这个里面是A[1]的内容
        xx[i] = t0 + t * t1;
        xx[i+m] = t0 - t * t1;
        t *= w;
    }
}
int main(){
    // main函数我就乱写了 >w<
    a[].get();
    b[].get();
    A = a.length();
    B = b.length();
f    for(N = 1; N < A + B; N <<= 1);
    fft(a, aa, N, 1, 1);
    fft(b, bb, N, 1, 1);
    for(int i = 0; i < N; ++i) cc[i] = aa[i] * bb[i];
    fft(cc, c, N, 1, -1);
    for(int i = 0; i < N; ++i) c[i] /= N;
    c[].print();
    return 0;
}
// 原根 蝶型
const int p = 7340033;
const int g = 3;
void fft(int xx[], int n, int type){
    // 这里在对二进制位对称的位置进行交换
    for(int i = 0; i < n; ++i){ // i枚举每一个下表
        int j = 0; // j为n位二进制下i的对称
        for(int k = i, m = n - 1; m != 0; j = (j << 1) | (k & 1), k >>= 1, m >>= 1);
        if(i < j) swap(xx[i], xx[j]); // 为了防止换了之后又换回来于是只在 i < j 时交换
    }
    // for代替递归
    for(int m = 1; m < n; m <<= 1){ // m为当前讨论区间长度的一半
        int w = powmod(g, (1LL * type * (p - 1) / (m << 1) + p - 1) % (p - 1));
        for(int j = 0; j < n; j += (m << 1)){ // j为当前讨论区间起始位
            // 啊这些都和递归一样了
            int t = 1;
            for(int i = 0; i < m; ++i){
                int t0 = xx[i+j];
                int t1 = 1LL * xx[i+j+m] * t % p;
                xx[i+j] = (t0 + t1) % p;
                xx[i+j+m] = (t0 - t1 + p) % p;
                t = 1LL * t * w % p;
            }
        }
    }
}
int main(){
    // 继续乱写>w<
    a[].get();
    b[].get();
    A = a.length();
    B = b.length();
    for(N = 1; N < A + B; N <<= 1);
    fft(a, N, 1);
    fft(b, N, 1);
    for(int i = 0; i < N; ++i) c[i] = 1LL * a[i] * b[i] % p;
    fft(c, N, -1);
    int inv_N = powmod(N, p - 2);
    for(int i = 0; i < N; ++i) c[i] = 1LL * c[i] * inv_N % p;
    c[].print();
    return 0;
}
