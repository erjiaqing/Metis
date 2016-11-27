const int Mr = 50 + 10;
const int Mc = 50 + 10;
const int Mn = Mc * Mr + 10;
struct Node {
    int l, r, u, d, x, y;
}a[Mn];
int a_cnt,ans[Mr],num[Mc],head;
int col[Mc],col_len,row_len;
bool mat[Mr][Mc];
int best_val;
bool vis[Mc];
int lim;
inline int add_node(int l, int r, int u, int d, int x,int y) {
    a[a[l].r = a_cnt].l = l;
    a[a[r].l = a_cnt].r = r;
    a[a[u].d = a_cnt].u = u;
    a[a[d].u = a_cnt].d = d;
    a[a_cnt].x = x;
    a[a_cnt].y = y;
    if(x != 0)
        num[y]++;
    return a_cnt++;
}
inline void del(int x) {
    for(int i = a[x].d; i != x; i = a[i].d) {
  		a[a[i].l].r = a[i].r;
  		a[a[i].r].l = a[i].l;
	}
}
inline void recover(int x) {
    for(int i = a[x].u; i != x; i = a[i].u) {
      	a[a[i].l].r = i;
      	a[a[i].r].l = i;
    }
}
inline int calc_h() {
	int res = 0;
	memset(vis,false, sizeof vis);
	for(int i = a[head].r; i != head; i = a[i].r) {
		if(!vis[i]) {
			++res;
			vis[a[i].y] = true;
			for(int j = a[i].d; j != i; j = a[j].d) {
				for(int k = a[j].r; k != j; k = a[k].r) {
					vis[a[k].y] = true;
				}
			}
		}
	}
	return res;
}
inline int get_val(int dep) {
	int res = 0;
	// calculate the current value
	
	return res;
}
inline void DLX(int dep) {
	if(dep + calc_h() > lim) {
		return;
	}
	int cur_val = get_val(dep);
	if(cur_val >= best_val) {
		return;
	}
    if(a[head].r == head) {
    	// solution found
    	best_val = min(best_val, cur_val);
    	return;
    }
    int sta(0),minx(0x7fffffff);
    for(int i = a[head].r; i != head; i = a[i].r) {
        if(num[a[i].y] < minx) {
            minx = num[sta = col[a[i].y]];
        }
    }
    // no valid rows to choose
    if(minx == 0)
        return;
    for(int i = a[sta].d; i != sta; i = a[i].d) {
    	del(i);
        for(int j = a[i].r; j != i; j = a[j].r) {
            del(j);
        }
        ans[dep] = a[i].x;     
        DLX(dep + 1);
        for(int j = a[i].l; j != i; j = a[j].l) {
            recover(j);
        }
        recover(i);
    }
    return; 
}
inline void init() {
    a_cnt = row_len = col_len = head  = 0;
    memset(mat, 0, sizeof mat);
    memset(num, 0, sizeof num);
}
inline void build(int n, int m) {
    head = add_node(0,0,0,0,0,0);
    col_len = m;
    row_len = n;
    col[0] = 0;
    for(int i = 1; i <= col_len; i++)
        col[i] = add_node(col[i-1],a[col[i-1]].r,a_cnt,a_cnt,0,i);
    for(int i = 1; i <= row_len; ++i) {
    	int t = -1;
    	for(int j = 1; j <= col_len; ++j) {
    		if(mat[i][j]) {
    			if(t == -1) {
    				t = add_node(a_cnt, a_cnt, col[j], a[col[j]].d, i, j);
    			} else {
    				add_node(t, a[t].r, col[j], a[col[j]].d, i, j);
    			}
    		}
    	}
    }
}