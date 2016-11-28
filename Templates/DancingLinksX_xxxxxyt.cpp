// HUST 1017
// 给定一个 n 行 m 列的 0/1 矩阵，选择某些行使得每一列都恰有一个 1
const int MAXN = 1e3 + 5;
const int MAXM = MAXN * MAXN;
const int INF = 1e9;
int ans, chosen[MAXM];
struct DancingLinks{
	int row, col, tot;
	int up[MAXM], dn[MAXM], lf[MAXM], rg[MAXM];
	int hd[MAXM], sz[MAXM];
	int posr[MAXM], posc[MAXM];
	
	void init(int _n, int _m){
		row = _n, col = _m;
		for(int i = 0; i <= col; ++i){
			sz[i] = 0; up[i] = dn[i] = i;
			lf[i] = i - 1; rg[i] = i + 1;
		}
		rg[col] = 0; lf[0] = col; tot = col;
		for(int i = 1; i <= row; ++i) hd[i] = -1;
	}
	void lnk(int r, int c){
		++tot; ++sz[c];
		dn[tot] = dn[c]; up[tot] = c;
		up[dn[c]] = tot; dn[c] = tot;
		posr[tot] = r; posc[tot] = c;
		if(hd[r] < 0) hd[r] = lf[tot] = rg[tot] = tot;
		else{
			lf[tot] = hd[r]; rg[tot] = rg[hd[r]];
			lf[rg[hd[r]]] = tot; rg[hd[r]] = tot;
		}
	}
	void remove(int c){ // 删除列时删除能覆盖其的行
		rg[lf[c]] = rg[c]; lf[rg[c]] = lf[c];
		for(int i = dn[c]; i != c; i = dn[i])
			for(int j = rg[i]; j != i; j = rg[j]){
				dn[up[j]] = dn[j]; up[dn[j]] = up[j];
				--sz[posc[j]];
			}
	}
	void resume(int c){
		rg[lf[c]] = c; lf[rg[c]] = c;
		for(int i = dn[c]; i != c; i = dn[i])
			for(int j = rg[i]; j != i; j = rg[j]){
				up[dn[j]] = j; dn[up[j]] = j;
				++sz[posc[j]];
			}
	}
	bool dance(int dpth){
		if(rg[0] == 0){
			printf("%d", dpth);
			for(int i = 0; i < dpth; ++i) printf(" %d", chosen[i]);
			puts(""); return true;
		}
		int c = rg[0];
		for(int i = rg[0]; i; i = rg[i]) if(sz[i] < sz[c]) c = i;
		remove(c); // 当前消去第c列
		for(int i = dn[c]; i != c; i = dn[i]){ // 第c列是由第i行覆盖的
			chosen[dpth] = posr[i];
			for(int j = rg[i]; j != i; j = rg[j]) remove(posc[j]); // 删除第i行能覆盖的其余列 因为它们只能被覆盖一次
			if(dance(dpth + 1)) return true;
			for(int j = lf[i]; j != i; j = lf[j]) resume(posc[j]);
		}
		resume(c);
		return false;
	}
};
DancingLinks dlx;
int n, m;
void work(){
	dlx.init(n, m);
	for(int i = 1, k, j; i <= n; ++i){
		scanf("%d", &k);
		while(k--) scanf("%d", &j), dlx.lnk(i, j);
	}
	if(!dlx.dance(0)) puts("NO");
}

// 重复覆盖
// 给定一个 n 行 m 列的 0/1 矩阵，选择某些行使得每一列至少有一个 1
struct DancingLinks{
	int row, col, tot;
	int up[MAXM], dn[MAXM], lf[MAXM], rg[MAXM];
	int head[MAXM], sz[MAXM];
	void init(int _n, int _m){
		row = _n, col = _m;
		for(int i = 0; i <= col; ++i){
			sz[i] = 0; up[i] = dn[i] = i;
			lf[i] = i - 1; rg[i] = i + 1;
		}
		rg[col] = 0; lf[0] = col; tot = col;
		for(int i = 1; i <= row; ++i) head[i] = -1;
	}
	void lnk(int r, int c){
		++tot; ++sz[c];
		dn[tot] = dn[c]; up[dn[c]] = tot;
		up[tot] = c; dn[c] = tot;
		if(head[r] < 0) head[r] = lf[tot] = rg[tot] = tot;
		else{
			rg[tot] = rg[head[r]]; lf[rg[head[r]]] = tot;
			lf[tot] = head[r]; rg[head[r]] = tot;
		}
	}
	void remove(int c){ // 删除列时不删除行 因为列可被重复覆盖
		for(int i = dn[c]; i != c; i = dn[i])
			rg[lf[i]] = rg[i], lf[rg[i]] = lf[i];
	}
	void resume(int c){
		for(int i = up[c]; i != c; i = up[i])
			rg[lf[i]] = i, lf[rg[i]] = i;
	}
	void dance(int d){
		if(ans <= d) return;
		if(rg[0] == 0){ans = min(ans, d); return;}
		int c = rg[0];
		for(int i = rg[0]; i != 0; i = rg[i]) if(sz[i] < sz[c]) c = i;
		for(int i = dn[c]; i != c; i = dn[i]){ // 枚举c列是被哪行覆盖
			remove(i);
			for(int j = rg[i]; j != i; j = rg[j]) remove(j); // 删除可被i行覆盖的列 因为不需要再考虑它们的覆盖问题
			dance(d + 1);
			for(int j = lf[i]; j != i; j = lf[j]) resume(j);
			resume(i);
		}
	}
};
DancingLinks dlx;
