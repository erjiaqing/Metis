#define lc (o<<1)
#define rc ((o<<1)|1)
using namespace std;
const int maxn = 800 * 4 + 100;
const int INF = 2e9;
int qxl,qxr,qyl,qyr;
int v,n,a[900][900];
pair<int,int> better(const pair<int,int>&a, const pair<int,int> &b){
	return make_pair(max(a.first,b.first),min(a.second,b.second));
}
struct sgtree{
	pair<int,int>node[maxn];//维护了最大值和最小值 
	void maintain(int o){
		node[o] = better(node[lc],node[rc]);
	}
	void update2(int o, int L, int R, const sgtree &a, const sgtree &b){
		if (L == R){
			node[o] = better(a.node[o],b.node[o]);
			return;
		}
		int mid = L + R >>1;
		update2(lc,L,mid,a,b);
		update2(rc,mid+1,R,a,b);
		node[o] = better(a.node[o],b.node[o]);
	}	
	void update3(int o, int L, int R, const sgtree &a, const sgtree &b){
		if (L == R){
			node[o] = better(a.node[o],b.node[o]);
			return;
		}
		int mid = L + R >>1;
		if (qyl <= mid)
		update3(lc,L,mid,a,b);
		else
		update3(rc,mid+1,R,a,b);
		maintain(o);		
	}	
	void build(int o, int L, int R){
		if (L == R){
			node[o].first = node[o].second = a[qxl][L];
			return;
		}
		int mid = L + R >> 1;
		build(lc,L,mid);
		build(rc,mid + 1, R);
		maintain(o);	
	}
	void update(int o, int L, int R){
		if (L == R){
			node[o].first = node[o].second = v;
			return;
		}
		int mid = L + R >> 1;
		if (qyl <= mid){
			update(lc,L,mid);
		}else{	
			update(rc,mid+1,R);
		}
		maintain(o);		
	}
	pair<int,int> query(int o, int L, int R){
		if (qyl <= L && qyr >= R){
			return node[o];
		}
		pair<int,int>ret = make_pair(0,INF);
		int mid = L + R >> 1;
		if (qyl <= mid){
			ret = better(ret,query(lc,L,mid));
		}
		if (qyr > mid){
			ret = better(ret,query(rc,mid+1,R));
		}
		return ret;	
	}
};

struct sgtree2{
	sgtree node[maxn];
	void build(int o, int L, int R){
		if (L == R){
			qxl = L;
			node[o].build(1,1,n);
			return;
		}
		int mid = L + R >> 1;
		build(lc,L,mid);
		build(rc,mid + 1, R);
		node[o].update2(1,1,n,node[lc],node[rc]);
	}
	void update(int o, int L, int R){
		if (L == R){
			node[o].update(1,1,n);
			return;
		}
		int mid = L + R >> 1;
		if (qxl <= mid){
			update(lc,L,mid);
		}else{
			update(rc,mid+1,R);
		}
		node[o].update3(1,1,n,node[lc],node[rc]);
	}
	pair<int,int> query(int o, int L, int R){
		if (qxl <= L && qxr >= R){
			return node[o].query(1,1,n);
		}
		pair<int,int>ret = make_pair(0,INF);
		int mid = L + R >> 1;
		if (qxl <= mid){
			ret = better(ret,query(lc,L,mid));
		}
		if (qxr > mid){
			ret = better(ret,query(rc,mid+1,R));
		}
		return ret;	
	}
}tree;