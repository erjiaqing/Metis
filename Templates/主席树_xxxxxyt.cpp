const int maxn = 1e5 + 5;
const int inf = 1e9 + 1;
struct segtree{
	int tot, rt[maxn];
	struct node{
		int lson, rson, size;
	}nd[maxn*40];
	void insert(int &i, int left, int rght, int x){
		int j = ++tot;
		int mid = (left + rght) >> 1;
		nd[j] = nd[i];
		nd[j].size++;
		i = j;
		if(left == rght) return;
		if(x <= mid) insert(nd[j].lson, left, mid, x);
		else insert(nd[j].rson, mid + 1, rght, x);
    }
	int query(int i, int j, int left, int rght, int k){
		if(left == rght) return left;
		int mid = (left + rght) >> 1;
		if(nd[nd[j].lson].size - nd[nd[i].lson].size >= k) return query(nd[i].lson, nd[j].lson, left, mid, k);
		else return query(nd[i].rson, nd[j].rson, mid + 1, rght, k - (nd[nd[j].lson].size - nd[nd[i].lson].size));
	}
}st;
int n, m;
int a[maxn], b[maxn], rnk[maxn], mp[maxn];
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
	for(int i = 1; i <= n; ++i) st.insert(st.rt[i] = st.rt[i-1], 1, n, b[i]);
	for(int i = 1; i <= m; ++i){
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		printf("%d\n", mp[st.query(st.rt[x-1], st.rt[y], 1, n, k)]);
	}	
	return 0;
}
