const int INF = 0x3fffffff;
struct node {
	int val, max, inc, size;
	int idx;
	bool rev;
	node *fa, *ch[2];
	node() {
		val = inc = 0;
		max = -INF;
	}
	inline bool isleft() {
	return (this == fa->ch[0]);
}
} npool[Mn], *null;
int ntot;
node *tree[Mn];
inline node* newnode() {
	node* res = &npool[ntot++];
	res->val = res->inc = 0;
	res->max = -INF;
	res->rev = 0;
	res->idx = -1;
	return res;
}
inline node* create(int idx, int val) {
	node* res = newnode();
	res->idx = idx;
	res->val = res->max = val;
	res->size = 1;
	res->fa = res->ch[0] = res->ch[1] = null;
	return res;
}
inline bool isroot(node* const x) {
	return (x->fa == null)|| (x->fa->ch[0] != x && x->fa->ch[1] != x);
}

inline void _inc(node* const x, int inc) {
	if(x == null)
		return;
	x->inc += inc;x->val += inc;x->max += inc;
}
inline void pushdown(node* const x) {
	if(x == null)
		return;
	if(x->inc) {
		_inc(x->ch[0], x->inc);
		_inc(x->ch[1], x->inc);
		x->inc = 0;
	}
	if(x->rev) {
		swap(x->ch[0], x->ch[1]);
		x->ch[0]->rev ^= 1;
		x->ch[1]->rev ^= 1;
		x->rev = 0;
	}
}
inline void update(node* const x) {
	pushdown(x);pushdown(x->ch[0]);pushdown(x->ch[1]);
	x->max = max(x->val, max(x->ch[0]->max, x->ch[1]->max));
}
inline void rotate(node* x) {
	node* const y = x->fa;
	int c = x->isleft();
	y->ch[c ^ 1] = x->ch[c];
	if(x->ch[c] != null)
		x->ch[c]->fa = y;
	x->fa = y->fa;
	if(y->fa->ch[0] == y)
		x->fa->ch[0] = x;
	else if(y->fa->ch[1] == y)
		x->fa->ch[1] = x;
	x->ch[c] = y;
	y->fa = x;
	update(y);
}
inline void _relax(node* const x) {
	if(!isroot(x)) {
		_relax(x->fa);
	}
	pushdown(x);
}
void splay(node* const x) {
	if(x == null) 
		return;
	while(!isroot(x)) {
		if(isroot(x->fa)) {
			pushdown(x->fa);pushdown(x);rotate(x);
		} else {
			pushdown(x->fa->fa);pushdown(x->fa);pushdown(x);
			if(x->isleft() == x->fa->isleft()) {
				rotate(x->fa);rotate(x);
			} else {
				rotate(x);rotate(x);
			}
		}
	}
	update(x);
}
// return the last jumped vertex and is the root of the splay
node* access(node *x) {
	node* y = null;
	for(;x != null; x = x->fa) {
		splay(x);
		x->ch[1] = y;
		update(x);
		y = x; 
	}
	return y;
}
node* getroot(node *x) {
	x = access(x);
	pushdown(x);
	while(x->ch[0] != null) {
		x = x->ch[0];
		pushdown(x);
	}
	return x;
}
// set x as the root of the tree and the root of the splay
inline void evert(node* x) {
	access(x)->rev ^= 1;
	splay(x);
}
// link (x, y) and set x as the root of the tree
inline void link(node* const x, node* const y) {
	evert(x);x->fa = y;access(x);
}
// cut (x, y) and set x and y the root of 2 trees
inline void cut(node* const x, node* const y) {
	evert(x);access(y);splay(y);
	y->ch[0]->fa = null;
	y->ch[0] = null;
	update(y);
}
// query x->y and set x the root
inline int query(node *x, node *y) {
	evert(x);access(y);splay(y);
	return y->max;
}
// inc w on x->y and set x the root
inline void modify(node *x, node *y, int w) {
	evert(x);access(y);splay(y);_inc(y, w);
}
inline void prepare() {
	ntot = 0;
	null = newnode();
	null->fa = null->ch[0] = null->ch[1] = null;
}