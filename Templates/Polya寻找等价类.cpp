/*
Polya定理：
设G={π1，π2，π3........πn}是X={a1，a2，a3.......an}上一个置换群，用m中颜色对X中的元素进行涂色，
那么不同的涂色方案数为：1/|G|*(m^C(π1)+m^C(π2)+m^C(π3)+...+m^C(πk)). 其中C(πk)为置换πk的循环节的个数。
*/
int f[101];
long long mul[101];
bool vis[101];
int pos[101];

int n, m, k;
long long ans = 0, K;
int a[301], b[301];
int getfa(int x) { return !f[x] ? x : (f[x] = getfa(f[x])); }
int g[301][301];
long long check()
{
	int cnt = 0;
	for (int i = 1; i <= n; i ++) vis[i] = false;
	for (int i = 1; i <= n; i ++)
		if (!vis[i])
		{
			for (int j = i; vis[j] == false; j = pos[j])
				vis[j] = true;
			++ cnt;
		}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if (g[i][j] != g[pos[i]][pos[j]]) return 0;
	return mul[cnt];
}

void dfs(int x)
{
	if (x == n + 1)
	{
		long long tmp = check();
		if (tmp) ++ K;
		ans += tmp;
		return ;
	}
	for (int i = 1; i <= n; i ++)
		if (!vis[i])
		{
			vis[i] = true;
			pos[x] = i;
			dfs(x + 1);
			vis[i] = false;
		}
}
int main( )
{
	scanf("%d %d %d", &n, &m, &k);
	mul[0] = 1;
	for (int i = 1; i <= n; i ++) mul[i] = mul[i - 1] * k;
	for (int i = 1; i <= m; i ++)
		scanf("%d %d", &a[i], &b[i]), g[a[i]][b[i]] ++, g[b[i]][a[i]] ++;
	dfs(1);
	cout << ans / K << endl;
	return 0;
}
