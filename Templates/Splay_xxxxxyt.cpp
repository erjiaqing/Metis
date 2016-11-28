struct Splay{
	int tot, rt;
	struct Node{int ls, rs, fa, sz, data;};
	Node nd[N];
	void zig(int i){
		int j = nd[i].fa, k = nd[j].fa;
		if(k && j == nd[k].ls) nd[k].ls = i;
		else if(k) nd[k].rs = i;
		nd[i].fa = k; nd[j].fa = i;
		nd[nd[i].rs].fa = j;
		nd[j].ls = nd[i].rs; nd[i].rs = j;
		nd[i].sz = nd[j].sz;
		nd[j].sz = nd[nd[j].ls].sz + nd[nd[j].rs].sz + 1;
	}
	void zag(int i){
		int j = nd[i].fa, k = nd[j].fa;
		if(k && j == nd[k].ls) nd[k].ls = i;
		else if(k) nd[k].rs = i;
		nd[i].fa = k; nd[j].fa = i;
		nd[nd[i].ls].fa = j;
		nd[j].rs = nd[i].ls; nd[i].ls = j;
		nd[i].sz = nd[j].sz;
		nd[j].sz = nd[nd[j].ls].sz + nd[nd[j].rs].sz + 1;
	}
	void splay(int i){
		while(nd[i].fa){
			int j = nd[i].fa;
			if(nd[j].fa == 0){
				if(i == nd[j].ls) zig(i); else zag(i);
			}else{
				int k = nd[j].fa;
				if(j == nd[k].ls){
					if(i == nd[j].ls) zig(j), zig(i);
					else zag(i), zig(i);
				}else{
					if(i == nd[j].rs) zag(j), zag(i);
					else zig(i), zag(i);
				}
			}
		}
		rt = i;
	}
	int insert(int stat){
		int i = rt; ++tot;
		nd[tot].data = stat; nd[tot].sz = 1;
		if(!nd[i].sz){nd[tot].fa = 0; rt = tot; return tot;}
		while(i){
			++nd[i].sz;
			if(stat < nd[i].data){
				if(nd[i].ls) i = nd[i].ls;
				else{nd[i].ls = tot; break;}
			}else{
				if(nd[i].rs) i = nd[i].rs;
				else{nd[i].rs = tot; break;}
			}
		}
		nd[tot].fa = i; splay(tot);
		return tot;
	}
	void delet(int i){
		if(!i) return;
		splay(i);
		int ls = nd[i].ls, rs = nd[i].rs;
		nd[ls].fa = nd[rs].fa = 0;
		nd[i].ls = nd[i].rs = 0;
		if(ls == 0){rt = rs; nd[rs].fa = 0;}
		else{
			rt = ls;
			while(nd[ls].rs) ls = nd[ls].rs;
			splay(ls); nd[ls].fa = 0;
			nd[rs].fa = ls; nd[ls].rs = rs;
		}
		nd[rt].sz += nd[nd[rt].rs].sz;
	}
	int get_rank(int i){ // 查询节点编号为 i 的 rank
		splay(i);
		return nd[nd[i].rs].sz + 1;
	}
	int find(int stat){ // 查询信息为 stat 的节点编号
		int i = rt;
		while(i){
			if(stat < nd[i].data) i = nd[i].ls;
			else if(stat > nd[i].data) i = nd[i].rs;
				 else return i;
		}
		return i;
	}
	int get_kth_max(int k){ // 查询第k大 返回其节点编号
		int i = rt;
		while(i){
			if(k <= nd[nd[i].rs].sz) i = nd[i].rs;
			else if(k > nd[nd[i].rs].sz + 1)
				k -= nd[nd[i].rs].sz + 1, i = nd[i].ls;
				 else return i;
		}
		return i;
	}
};
Splay sp;
