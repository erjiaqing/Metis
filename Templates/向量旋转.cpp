void rotate(double theta){
	double coss = cos(theta), sinn = sin(theta);
	double tx = x * coss - y * sinn;
	double ty = x * sinn + y * coss;
	x = tx, y = ty;
}