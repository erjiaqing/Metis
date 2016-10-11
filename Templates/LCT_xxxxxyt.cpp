// 这个有些地方有点问题… // 标注部分
const int MAXN = 2e5 + 5;
int n, m;
struct Lct{
	struct Node{
		int sum;
		int lson, rson, fath, ance;
		bool lazy;
	};
	Node nd[MAXN];
	void push_up(int i){
		nd[i].sum = nd[nd[i].lson].sum + nd[nd[i].rson].sum + 1;
	}
	void reverse(int i){ //
		if(!i) return;
		swap(nd[i].lson, nd[i].rson);
		nd[i].lazy = true;
	}
	void push_down(int i){ //
		if(!i || !nd[i].lazy) return;
		reverse(nd[i].lson);
		reverse(nd[i].rson);
		nd[i].lazy = false;
	}
	void zig(int i){
		int j = nd[i].fath;
		int k = nd[j].fath;
		if(k && j == nd[k].lson) nd[k].lson = i;
		else if(k) nd[k].rson = i;
		nd[i].fath = k;
		nd[j].fath = i;
		nd[nd[i].rson].fath = j;
		nd[j].lson = nd[i].rson;
		nd[i].rson = j;
		nd[i].ance = nd[j].ance;
		push_up(j);
		push_up(i);
	}
	void zag(int i){
		int j = nd[i].fath;
		int k = nd[j].fath;
		if(k && j == nd[k].lson) nd[k].lson = i;
		else if(k) nd[k].rson = i;
		nd[i].fath = k;
		nd[j].fath = i;
		nd[nd[i].lson].fath = j;
		nd[j].rson = nd[i].lson;
		nd[i].lson = j;
		nd[i].ance = nd[j].ance;
		push_up(j);
		push_up(i);
	}
	void down_path(int i){ //
		if(nd[i].fath) down_path(nd[i].fath);
		push_down(i);
	}
	void splay(int i){
		down_path(i);
		while(nd[i].fath){
			int j = nd[i].fath;
			if(nd[j].fath == 0){
				if(i == nd[j].lson) zig(i);
				else zag(i);
			}else{
				int k = nd[j].fath;
				if(j == nd[k].lson){
					if(i == nd[j].lson) zig(j), zig(i);
					else zag(i), zig(i);
				}else{
					if(i == nd[j].rson) zag(j), zag(i);
					else zig(i), zag(i);
				}
			}
		}
	}
	
	void access(int i){
		int j = 0;
		while(i){
			splay(i);
			if(nd[i].rson){
				nd[nd[i].rson].ance = i;
				nd[nd[i].rson].fath = 0;
			}
			nd[i].rson = j;
			nd[j].fath = i;
			push_up(i);
			j = i;
			i = nd[i].ance;
		}
	}
	void set_root(int i){ //
		access(i);
		splay(i);
		reverse(i);
	}
	int find_root(int i){ //
		access(i);
		splay(i);
		while(nd[i].lson) i = nd[i].lson;
		splay(i);
		return i;
	}
	void link(int i, int j){ //
		set_root(i);
		nd[i].ance = j;
		access(i);
	}
	void cut(int i){ //
		access(i);
		splay(i);
		nd[nd[i].lson].ance = nd[i].ance;
		nd[nd[i].lson].fath = 0;
		nd[i].lson = 0;
		nd[i].ance = 0;
	}
};
Lct lct;
void query(){
	int pos;
	scanf("%d", &pos);
	++pos;
	lct.access(pos);
	lct.splay(pos);
	printf("%d\n", lct.nd[pos].sum - 1);
}
void modify(){
	int pos, fath;
	scanf("%d%d", &pos, &fath);
	++pos, fath += pos;
	if(fath > n) fath = n + 1;
	lct.splay(pos);
	if(lct.nd[pos].lson){
		lct.nd[lct.nd[pos].lson].ance = lct.nd[pos].ance;
		lct.nd[lct.nd[pos].lson].fath = 0;
		lct.nd[pos].lson = 0;
	}
	lct.nd[pos].ance = fath;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		int k;
		scanf("%d", &k);
		k += i;
		if(k > n) k = n + 1;
		lct.nd[i].ance = k;
	}
	for(int i = 1; i <= n + 1; ++i) lct.nd[i].sum = 1;
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i){
		int k;
		scanf("%d", &k);
		if(k == 1) query();
		else modify();
	}
	return 0;
}
