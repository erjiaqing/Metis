struct qtree{
	int tot;
	struct node{
		int hson, top, size, dpth, papa, newid;
	}nd[maxn];
	void find(int u, int fa, int d){
		nd[u].hson = 0; nd[u].size = 1;
		nd[u].dpth = d; nd[u].papa = fa;
		int max_size = 0;
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].first;
			if(v == fa) continue;
			f[mp[u][l].second.second] = v;
			find(v, u, d + 1);
			nd[u].size += nd[v].size;
			if(max_size < nd[v].size){
				max_size = nd[v].size;
				nd[u].hson = v;
			}
		}
	}
	void connect(int u, int t){
		nd[u].top = t; nd[u].newid = ++tot;
		if(nd[u].hson != 0) connect(nd[u].hson, t);
		for(int l = 0; l < mp[u].size(); ++l){
			int v = mp[u][l].first;
			if(v == nd[u].papa || v == nd[u].hson) continue;
			connect(v, v);
		}
	}
	int query(int u, int v){
		int rtn = -inf;
		while(nd[u].top != nd[v].top){
			if(nd[nd[u].top].dpth < nd[nd[v].top].dpth) swap(u, v);
			rtn = max(rtn, 
				st.query(1, 1, n, nd[nd[u].top].newid, nd[u].newid));
			u = nd[nd[u].top].papa;
		}
		if(nd[u].dpth > nd[v].dpth) swap(u, v);
		rtn = max(rtn, st.query(1, 1, n, nd[u].newid , nd[v].newid));
		return rtn;
	}
	void modify(int u, int v){
		while(nd[u].top != nd[v].top){
			if(nd[nd[u].top].dpth < nd[nd[v].top].dpth) swap(u, v);
			st.modify(1, 1, n, nd[nd[u].top].newid, nd[u].newid);
			u = nd[nd[u].top].papa;
		}
		if(nd[u].dpth > nd[v].dpth) swap(u, v);
		st.modify(1, 1, n, nd[u].newid + 1, nd[v].newid);
	}
	void clear(){
		tot = 0;
		nd[0].hson = nd[0].top = nd[0].size = 0;
		nd[0].dpth = nd[0].papa = nd[0].newid = 0;
		for(int i = 1; i <= n; ++i) nd[i] = nd[0];
	}
}qt;
