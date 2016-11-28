double value(){
	double maxflow = 0.00;
	while(dist[S] <= T) maxflow += sap(S, inf);
	return -0.50 * (maxflow - d * n);
}
void build(double g){
	for(int i = 1; i <= n; ++i) add_edge(S, i, d); // s -> v : INF
	for(int i = 1; i <= n; ++i) add_edge(i, T, d + 2.00 * g - deg[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j){
			if(a[i] >= a[j]) continue;
			add_edge(i, j, 1.00); // u -> v : 1.00
			add_edge(j, i, 1.00);
		}
}
void clear(){
	memset(dist, 0, sizeof dist);
	memset(disq, 0, sizeof disq);
	for(int i = 1; i <= T; ++i) mp[i].clear();
}
double binary(double left, double rght){
	int step = 0;
	while(left + eps < rght && step <= 50){
		++step;
		double mid = (left + rght) / 2;
		clear();
		build(mid);
		double h = value();
		if(h > eps) left = mid;
		else rght = mid;
	}
	return left;
}
// 不带点权边权：c(u, v) = 1, c(s, v) = u, c(v, t) = u + 2g - d[v]
// 带边权不带点权：c(u, v) = w[e], c(s, v) = u, c(v, t) = u + 2g - d[v]
// 带点权（点权在分子点数在分母）边权：c(u, v) = w[e], c(s, v) = u,
//	c(v, t) = u + 2g - d[v] - 2p[v], u = sigma{2p[v] + w[e]}
