const int L = 600005;//n * 2 开大一点，只开n会挂
struct Node
{
	Node *nx[26], *fail;
	int l, num;
};
Node *root, *last, sam[L], *b[L];
int sum[L], f[L];
int cnt;
char s[L];
int l;
void add(int x)
{
	++cnt;
	Node *p = &sam[cnt];
	Node *pp = last;
	p->l = pp->l + 1;
	last = p;
	for(; pp && !pp->nx[x]; pp = pp->fail) pp->nx[x] = p;
	if(!pp) p->fail = root;
	else{
		if(pp->l + 1 == pp->nx[x]->l) p->fail = pp->nx[x];
		else{
			++cnt;
			Node *r = &sam[cnt], *q = pp->nx[x];
			*r = *q;
			r->l = pp->l + 1;
			q->fail = p->fail = r;
			for(; pp && pp->nx[x] == q; pp = pp->fail) pp->nx[x] = r;
		}
	}
}
int main()
{
	scanf("%s", s);
	l = strlen(s);
	root = last = &sam[0];
	for(int i = 0; i < l; ++i) add(s[i] - 'a');
	for(int i = 0; i <= cnt; ++i) ++sum[sam[i].l];
	for(int i = 1; i <= l; ++i) sum[i] += sum[i - 1];
	for(int i = 0; i <= cnt; ++i) b[--sum[sam[i].l]] = &sam[i];
	Node *now = root;
	for(int i = 0; i < l; ++i){
		now = now->nx[s[i] - 'a'];
		++now->num;
	}
	for(int i = cnt; i > 0; --i){
		int len = b[i]->l;
		//cerr<<"num="<<b[i]->num<<endl;
		f[len] = max(f[len], b[i]->num);
		//cerr<<b[i]->num<<" "<<b[i]->fail->num<<" ..."<<endl;
		b[i]->fail->num += b[i]->num;
		//cerr<<b[i]->num<<" "<<b[i]->fail->num<<" ..."<<endl;
	}
	for(int i = l - 1; i >= 1; --i) f[i] = max(f[i], f[i + 1]);
	for(int i = 1; i <= l; ++i) printf("%d\n", f[i]);
	return 0;
}
