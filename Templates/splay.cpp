// splay template
const int INF = 0x3fffffff;
const int Mn = 200000 + 10;
struct node {
	node *ch[2], *fa;
	int val, maxv, maxl, maxr, sum;
	int size;
	inline node() {
		val = size = sum = 0;
		// add init here
		maxv = maxl = maxr = -INF;
	}
	inline int which() {
		return fa->ch[1] == this;
	}
	inline void set(node *temp, int dir) {
		ch[dir] = temp;
		temp->fa = this;
	}
	inline void update() {
		size = 1 + ch[0]->size + ch[1]->size;
		// update here
		sum = val + ch[0]->sum + ch[1]->sum;
		maxl = max(ch[0]->maxl, ch[0]->sum + val + max(0, ch[1]->maxl));
		maxr = max(ch[1]->maxr,ch[1]->sum + val + max(0, ch[0]->maxr));
		maxv = max(max(ch[0]->maxv, ch[1]->maxv), max(0,ch[0]->maxr) + val + max(0, ch[1]->maxl));
		
	}
	inline void release() {

	}
}npool[Mn];
int ntot;
inline node* newnode() {
	// add init here
	npool[ntot].sum = npool[ntot].val = npool[ntot].size = 0;
	npool[ntot].maxv = npool[ntot].maxl = npool[ntot].maxr = -INF;
	return &npool[ntot++];
}
node *null, *head;
inline void print(node* root) {
	if(root == null) {
		return;
	}
	print(root->ch[0]);
	printf("%d ",root->val);
	print(root->ch[1]);
}
inline node* create(int val = 0) {
	node* temp = newnode();
	temp->val = val;
	temp->ch[0] = temp->ch[1] = temp->fa = null;
	return temp;
}
inline void rotate(node *root) {
	node *fa = root->fa;
	int dir = root->which();
	fa->release();
	root->release();
	fa->set(root->ch[!dir], dir);
	fa->fa->set(root, fa->which());
	root->set(fa, !dir);
	if(fa == head) {
		head = root;
	}
	fa->update();
}
inline void splay(node *root, node *target) {
	for(root->release(); root->fa != target;) {
		if(root->fa->fa == target) {
			rotate(root);
		} else {
			root->which() == root->fa->which() ? (rotate(root->fa) , rotate(root)) : (rotate(root), rotate(root));
		}
	}
	root->update();
}
inline int _rank(node *root) {
	splay(root, null);
	return root->ch[0]->size + 1;
}
inline node* find(int _rank) {
	node *now = head;
	for(; now->ch[0]->size + 1 != _rank;) {
		now->release();
		if(now->ch[0]->size + 1 > _rank) {
			now = now->ch[0];
		} else {
			_rank -= now->ch[0]->size + 1;
			now = now->ch[1];
		}
	}
	return now;
}
inline void splay(int left, int right) {
	splay(find(right), null);
	splay(find(left), head);
}
// between pos and pos + 1
inline node* insert(int pos, int val) {
	splay(pos, pos + 1);
	node *now = head->ch[0];
	node *cur = create(val);
	now->set(cur, 1);
	splay(cur, null);
	return head;
}
// between pos and pos + 1
inline void insert(int pos, int n, int val[]) {
	splay(pos, pos + 1);
	node *now = head->ch[0];
	for(int i = 1; i <= n; ++i) {
		node *cur = create(val[i]);
		now->set(cur, 1);
		now = cur;
	}
	splay(now, null);
}
inline void erase(node *root) {
	int pos = _rank(root);
	splay(pos - 1, pos + 1);
	head->ch[0]->ch[1] = null;
	head->ch[0]->update();
	head->update();
}
// query[left, right]
inline int query_maxv(int left, int right) {
	splay(left - 1, right + 1);
	return head->ch[0]->ch[1]->maxv;
}
// two useless nodes
inline void prepare() {
	ntot = 0;
	null = newnode();
	head = create();
	node *tail = create();
	head->set(tail, 1);
	splay(tail, null);
}