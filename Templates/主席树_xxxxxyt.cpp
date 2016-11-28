const int N = 1e5 + 5;
const int inf = 1e9 + 1;
struct segtree{
	int tot, rt[N];
	struct node{int ls, rs, size;}nd[N*40];
	void insert(int &i, int lf, int rg, int x){
		int j = ++tot;
		nd[j] = nd[i]; nd[j].size++; i = j;
		if(lf == rg) return;
		int mid = (lf + rg) >> 1;
		if(x <= mid) insert(nd[j].ls, lf, mid, x);
		else insert(nd[j].rs, mid + 1, rg, x);
    }
	int query(int i, int j, int lf, int rg, int k){
		if(lf == rg) return lf;
		int mid = (lf + rg) >> 1;
		if(nd[nd[j].ls].size - nd[nd[i].ls].size >= k)
			return query(nd[i].ls, nd[j].ls, lf, mid, k);
		else return query(nd[i].rs, nd[j].rs, mid + 1, rg,
			k - (nd[nd[j].ls].size - nd[nd[i].ls].size));
	}
}st;
int n, m, a[N], b[N], rnk[N], mp[N];
bool cmp(int i, int j){return a[i] < a[j];}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) rnk[i] = i;
	sort(rnk + 1, rnk + 1 + n, cmp);
	a[0] = inf;
	for(int i = 1, j = 0; i <= n; ++i){
		int k = rnk[i], kk = rnk[i-1];
		if(a[k] != a[kk]) b[k] = ++j;
		else b[k] = j;
		mp[b[k]] = a[k];
	}
	for(int i = 1; i <= n; ++i)
		st.insert(st.rt[i] = st.rt[i-1], 1, n, b[i]);
	for(int i = 1, x, y, k; i <= m; ++i){
		scanf("%d%d%d", &x, &y, &k);
		printf("%d\n", mp[st.query(st.rt[x-1], st.rt[y], 1, n, k)]);
	}	
	return 0;
}
