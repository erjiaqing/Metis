const int N = 3e5 + 10;
	int n;
	std::vector<int> edge[N];
	int father[N][21];
	int size[N], deep[N];
	int pos[N], tot;
	void solve(std::vector<int> &query) {
	    static int stack[N], fa[N];
	    static std::vector<int> all;
	    static std::pair<int, int> best[N];
	    static int extra[N], ans[N];
	    std::vector<int> rem = query;
	    int top = 0;
	    all.clear();
	    sort(query.begin(), query.end(), cmp_pos);
	    for (int i = 0; i < (int)query.size(); i ++) {
	        int u = query[i];
	        if (top == 0) {
	            stack[++top] = u;
	            all.push_back(u);
	            best[u] = std::make_pair(0, u);
	        } else {
	            int lca = least_common_ancestor(u, stack[top]);
	            for ( ; deep[stack[top]] > deep[lca]; top --) {
	                if (deep[stack[top - 1]] <= deep[lca]) {
	                    fa[stack[top]] = lca;
	                }
	            }
	            if (stack[top] != lca) {
	                fa[lca] = stack[top];
	                stack[++top] = lca;
	                best[lca] = std::make_pair(n + 10, -1);
	                all.push_back(lca);
	            }
	            fa[u] = stack[top];
	            stack[++top] = u;
	            all.push_back(u);
	        }
	    }
	}