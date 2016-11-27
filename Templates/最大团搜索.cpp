void init(){
	int i, j;
	for (i=1; i<=n; ++i) for (j=1; j<=n; ++j) scanf("%d", &g[i][j]);
}
void dfs(int size){
	int i, j, k;
	if (len[size]==0) {
		if (size>ans) {
			ans=size; found=true;
		}
		return;
	}
	for (k=0; k<len[size] && !found; ++k) {
		if (size+len[size]-k<=ans) break;
		i=list[size][k];
		if (size+mc[i]<=ans) break;
		for (j=k+1, len[size+1]=0; j<len[size]; ++j)
		if (g[i][list[size][j]]) list[size+1][len[size+1]++]=list[size][j];
		dfs(size+1);
	}
}
void work(){
	int i, j;
	mc[n]=ans=1;
	for (i=n-1; i; --i) {
		found=false;
		len[1]=0;
		for (j=i+1; j<=n; ++j) if (g[i][j]) list[1][len[1]++]=j;
		dfs(1);
		mc[i]=ans;
	}
}