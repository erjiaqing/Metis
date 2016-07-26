#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long MOD = 1e9 + 7;
const int N = 111111;
const int M = 222222;

int n, m;
long long w[N];

int tot, hd[N], th[M << 1], nx[M << 1];
void addedge(int x, int y)
{
	++tot;
	th[tot] = y; nx[tot] = hd[x]; hd[x] = tot;
}

int treetot, thd[N << 1], tth[M << 4], tnx[M << 4];
void addtree(int x, int y)
{
	++treetot;
	tth[treetot] = y; tnx[treetot] = thd[x]; thd[x] = treetot;
}

//AC -> Add it to template
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

long long power(long long x, long long y)
{
	long long res = 1;
	for(; y; y >>= 1)
	{
		if(y & 1) res = res * x % MOD;
		x = x * x % MOD;
	}
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		tot = 1;
		memset(hd, 0, sizeof(hd));
		ind = 0;
		top = 0;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(mark, 0, sizeof(mark));
		treetot = 1;
		memset(thd, 0, sizeof(thd));
		memset(root, 0, sizeof(root));
		
		
		scanf("%d%d", &n, &m);
		
		part = n;
		
		int tmp, x, y;
		for(int i = 1; i <= n; ++i) scanf("%d", &tmp), w[i] = tmp;
		for(int i = 1; i <= m; ++i) scanf("%d%d", &x, &y), addedge(x, y), addedge(y, x);
		
		for(int i = 1; i <= n; ++i)
			if(!dfn[i])
			{
				tarjan(i, part + 1);
			}
		
		memset(vis, 0, sizeof(vis));
		long long sum = 0;
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
			{
				if(root[i])
				{
					dfs(root[i]);
					(sum += val[root[i]]) %= MOD;
				}
				else//A singel dot
				{
					(sum += w[i]) %= MOD;
				}
			}
		
		long long ans = 0;
		
		for(int i = 1; i <= n; ++i)
		{
			if(root[i])
			{
				long long cur = (((sum - val[root[i]] + MOD) % MOD + val[root[i]] * power(val[i], MOD - 2) % MOD) % MOD + son[i]) % MOD;
				(ans += (long long)i * cur % MOD) %= MOD;
				//cerr<<i<<" "<<cur<<"...."<<endl;
			}
			else
			{
				//cerr<<i<<" ..?"<<endl;
				(ans += (long long)i * (sum - w[i] + MOD) % MOD) %= MOD;
			}
		}
		
		if(ans < 0) ans += MOD;
		cout<<ans<<endl;
		
	}
	return 0;
}
