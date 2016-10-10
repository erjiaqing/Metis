struct Splay{
	
	int tot, rt;
	struct Node{
		int lson, rson, fath, sz;
		int data;
		bool lazy;
	};
	Node nd[MAXN];
	
	void reverse(int i){
		if(!i) return;
		swap(nd[i].lson, nd[i].rson);
		nd[i].lazy = true;
	}
	void push_down(int i){
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
		nd[i].sz = nd[j].sz;
		nd[j].sz = nd[nd[j].lson].sz + nd[nd[j].rson].sz + 1;
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
		nd[i].sz = nd[j].sz;
		nd[j].sz = nd[nd[j].lson].sz + nd[nd[j].rson].sz + 1;
	}
	void down_path(int i){
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
		rt = i;
	}
	int insert(int stat){ // 插入信息
		int i = rt;
		++tot;
		nd[tot].data = stat;
		nd[tot].sz = 1;
		if(!nd[i].sz){
			nd[tot].fath = 0;
			rt = tot;
			return tot;
		}
		while(i){
			++nd[i].sz;
			if(stat < nd[i].data){
				if(nd[i].lson) i = nd[i].lson;
				else{
					nd[i].lson = tot;
					break;
				}
			}else{
				if(nd[i].rson) i = nd[i].rson;
				else{
					nd[i].rson = tot;
					break;
				}
			}
		}
		nd[tot].fath = i;
		splay(tot);
		return tot;
	}
	void delet(int i){ // 删除信息
		if(!i) return;
		splay(i);
		int ls = nd[i].lson;
		int rs = nd[i].rson;
		nd[ls].fath = nd[rs].fath = 0;
		nd[i].lson = nd[i].rson = 0;
		if(ls == 0){
			rt = rs;
			nd[rs].fath = 0;
		}else{
			rt = ls;
			while(nd[ls].rson) ls = nd[ls].rson;
			splay(ls);
			nd[ls].fath = 0;
			nd[rs].fath = ls;
			nd[ls].rson = rs;
		}
		nd[rt].sz += nd[nd[rt].rson].sz;
	}
	int get_rank(int i){ // 查询节点编号为 i 的 rank
		splay(i);
		return nd[nd[i].rson].sz + 1;
	}
	int find(int stat){ // 查询信息为 stat 的节点编号
		int i = rt;
		while(i){
			if(stat < nd[i].data) i = nd[i].lson;
			else if(stat > nd[i].data) i = nd[i].rson;
				 else return i;
		}
		return i;
	}
	int get_kth_max(int k){ // 查询第 k 大 返回其节点编号
		int i = rt;
		while(i){
			if(k <= nd[nd[i].rson].sz) i = nd[i].rson;
			else if(k > nd[nd[i].rson].sz + 1) k -= nd[nd[i].rson].sz + 1, i = nd[i].lson;
				 else return i;
		}
		return i;
	}
};
Splay sp;
