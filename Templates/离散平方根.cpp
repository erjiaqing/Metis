inline bool quad_resi(long long x,long long p){
	return power_mod(x, (p - 1) / 2, p) == 1;
}
struct quad_poly {
	long long zero, one, val, mod;
	
	quad_poly(long long zero,long long one,long long val,long long mod):\
		zero(zero),one(one),val(val),mod(mod)	{}
	
	quad_poly multiply(quad_poly o){
		long long z0 = (zero * o.zero + one * o.one % mod * val % mod) % mod;
		long long z1 = (zero * o.one + one * o.zero) % mod;
		return quad_poly(z0, z1, val ,mod);
	}
	
	quad_poly pow(long long x){
		if (x == 1) return *this;
		quad_poly ret = this -> pow(x / 2);
		ret = ret.multiply(ret);
		if (x & 1) ret = ret.multiply(*this);
		return ret;
	}
}·
inline long long calc_root(long long a,long long p){
	a %= p;
	if (a < 2) return a;
	if (!quad_resi(a, p)) return p;
	if (p % 4 == 3) return power_mod(a, (p + 1) / 4, p);
	long long b = 0;
	while (quad_resi((my_sqr(b, p) - a + p) % p, p)) b = rand() % p;
	quad_poly ret = quad_poly(b, 1, (my_sqr(b, p) - a + p) % p, p);
	ret = ret.pow((p + 1) / 2);
	return ret.zero;
}
void exgcd(long long a,long long b,long long &d,long long &x,long long &y){
	if (b == 0){
		d = a; x = 1; y = 0;
	}
	else{
		exgcd(b, a%b, d, y, x);
		y -= a / b * x;
	}
}
void solve_sqrt(long long c,long long a,long long b,long long r,long long mod,vector<long long> &ans){
	long long x, y, d;
	exgcd(a, b, d, x, y);
	long long n = 2 * r;
	if (n % d == 0){
		x *= n / d;
		x = (x % (b / d) + (b / d)) % (b / d);
		long long m = x * a - r;
		while (m < mod){
			if (m >= 0 && m * m % mod == c){
				ans.push_back(m);
			}
			m += b / d * a;
		}
	}
}
void discrete_root(long long x,long long N,long long r,vector<long long> &ans){
	ans.clear();
	for (int i = 1; i * i <= N; ++i)
		if (N % i == 0){
			solve_sqrt(x, i, N/i, r, N, ans);
			solve_sqrt(x, N/i, i, r, N, ans);
		}
	sort(ans.begin(), ans.end());
	int sz = unique(ans.begin(),ans.end()) - ans.begin();
	ans.resize(sz);
}