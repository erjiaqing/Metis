const int bas[12]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool check(const long long &prime,const long long &base){
	long long number = prime - 1;
	for	(; ~number & 1; number>>=1);
	long long result= power_mod(base, number, prime);
	for	(; number != prime - 1 && result != 1 && result != prime - 1; number<<=1){
		result = multiply_mod(result, result, prime);
	}
	return result == prime - 1 || (number & 1) == 1 ;
}
bool miller_rabin(const long long &number){
	if	(number < 2)	return	0;
	if 	(number < 4)	return	1;
	if	(~number & 1)	return	0;
	for	(int i = 0; i < 12 && bas[i] < number; ++i)
		if	(!check(number, bas[i])) return	0;
	return	1;
}
long long pollard_rho(const long long &number, const long long &seed){
	long long x = rand() % (number - 1) + 1, y = x;
	for	(int head = 1, tail = 2; ; ){
		x = multiply_mod(x, x, number);
		x = add_mod(x, seed, number);
		if	(x == y)	return	number;
		long long ans = gcd(myabs(x - y), number);
		if	(ans > 1 && ans < number)	return	ans;
		if	(++head == tail){
			y = x;
			tail <<= 1;
		}
	}
}
void factorize(const long long &number, vector<long long> &divisor){
	if	(number > 1)
		if	(miller_rabin(number))
			divisor.push_back(number);
		else{
			long long factor = number;
			for	(; factor >= number; factor = pollard_rho(number, rand() % (number - 1) + 1));
			factorize(number / factor, divisor);
			factorize(factor, divisor);
		}
}