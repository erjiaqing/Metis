//Point Biconnected Component
bool mark[M << 1];
int part;
int ind, dfn[N], low[N], st[M << 1], top, root[N];
void tarjan(int x, int cur)
{
	dfn[x] = low[x] = ++ind;
	for(int i = hd[x]; i; i = nx[i])
	{
		if(mark[i]) continue;
		mark[i] = mark[i ^ 1] = 1;
		st[++top] = i;
		
		int v = th[i];
		if(dfn[v])
		{
			low[x] = min(low[x], dfn[v]);
			continue;
		}
		
		tarjan(v, cur);
		low[x] = min(low[x], low[v]);
		
		if(low[v] >= dfn[x])
		{
			++part;
			int k;
			//cerr<<"====="<<endl;
			do
			{
				k = st[top--];
				//cerr<<th[k]<<endl<<th[k ^ 1]<<endl;
				root[th[k]] = cur;//联通块里点双联通分量标号最小值
				root[th[k ^ 1]] = cur;
				addtree(part, th[k]);
				addtree(th[k], part);//part为点双联通分量的标号
				addtree(part, th[k ^ 1]);
				addtree(th[k ^ 1], part);
			}while(th[k ^ 1] != x);
			//cerr<<"====="<<endl;
		}
	}
}

bool vis[N << 1];
long long val[N << 1], son[N << 1];
void dfs(int x)
{
	vis[x] = 1;
	val[x] = (x <= n ? w[x] : 1ll);
	son[x] = 0ll;
	for(int i = thd[x]; i; i = tnx[i])
		if(!vis[tth[i]])
		{
			//cerr<<tth[i]<<" "<<x<<endl;
			int v = tth[i];
			dfs(v);
			(val[x] *= val[v]) %= MOD;
			
			if(x <= n) (son[x] += val[v]) %= MOD;
		}
}
