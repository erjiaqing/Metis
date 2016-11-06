double dot(point a, point b){
	return a.x * b.x + a.y * b.y;
}
double det(point a, point b){
	return a.x * b.y - a.y * b.x;
}
double area2(point pa, point pb){
	if(pa.len() < pb.len()) swap(pa, pb);
	if(pb.len() < EPS) return 0;
	double S;
	double a = pb.len();
	double b = pa.len();
	double c = (pb - pa).len();
	double cosB = dot(pb, pb - pa) / a / c;
	double B = acos(cosB);
	double cosC = dot(pa, pb) / a / b;
	double C = acos(cosC);
	if(a > r){
		S = C / 2 * r * r;
		double h = a * b * sin(C) / c;
		if(h < r && B < PI / 2) S -= acos(h / r) * r * r - h * sqrt(r * r - h * h);
	}else if(b > r){
		double theta = PI - B - asin(sin(B) / r * a);
		S = .5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
	}else S = .5 * sin(C) * a * b;
	return S;
}
double area(point a, point b, point c){
	double S = 0.00;
	point oa = a - o;
	point ob = b - o;
	point oc = c - o;
	S += area2(oa, ob) * sign(det(oa, ob));
	S += area2(ob, oc) * sign(det(ob, oc));
	S += area2(oc, oa) * sign(det(oc, oa));
	return S;
}

void work(){
	
	k = k * k;
	for(int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	scanf("%lf%lf", &_a.x, &_a.y);
	scanf("%lf%lf", &_b.x, &_b.y);
	o.x = (k * _a.x - _b.x) / (k - 1);
	o.y = (k * _a.y - _b.y) / (k - 1);
	r = ((k * (sqr(_a.x - _b.x) + sqr(_a.y - _b.y))) / sqr(1 - k));
	if(sign(r) <= 0){
		puts("0.0000000000");
		return;
	}
	r = sqrt(r);
	double ans = 0, tot = 0;
	for(int i = 2; i <= n - 1; ++i){
		int j = i + 1;
		ans += area(p[1], p[i], p[j]);
	}
	printf("%.10f\n", abs(ans));
}
