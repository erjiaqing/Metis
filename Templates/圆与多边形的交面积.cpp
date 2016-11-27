//外面乘sgn(det(pa,pb))，累加后再求fabs即面积 
double areaCT(double R, Point pa, Point pb){
	if (len(pa) < len(pb))swap(pa,pb);
	if (len(pb) < eps)return 0;
	Point pc = pb - pa;
	double a = len(pb), b = len(pa), c = len(pc);
	double cosB = dot(pb,pc)/a/c, B = acos(cosB);
	double cosC = dot(pa,pb)/a/b, C = acos(cosC);
	double S, h, theta;
	if (a > R) {
		S = C / 2 * R * R;
		h = a * b * sin(C)/c;
		if (h < R && B < pi/2)
			S -= acos(h/R) * R * R - h * sqrt(max(0.,R*R-h*h));
	}else if (b > R){
		theta = pi - B - asin(sin(B)/R*a);
		S = 0.5 * a * R * sin(theta) + (C - theta)*0.5*R*R;
	}else{
		S = 0.5 * sin(C) * a * b;
	}
	return S;
}