long long exgcd(long long a, long long b, long long &x, long long &y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	long long res = exgcd(b, a % b, x, y);
	long long t = y;
	y = x - a / b * y;;
	x = t; 
	return res;
}