#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
struct Type {
	int l, r, x;
} a[N * 4];

int n, m, l[N], r[N], pos[N], t, ind[N];
long long ans;
int tot, lst[N], id[N], nxt[N];

void Add(int x, int y)
{
	id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot;
}

void dfs(int x)
{
	
	l[x] = ++t;
	ind[t] = x;
	for (int i = lst[x]; i; i = nxt[i])
	{
		dfs(id[i]);
	}
	r[x] = t;
}

void build(int x, int l, int r)
{
	//cerr<<x<<" "<<l<<" "<<r<<"     ..."<<endl;
	a[x].l = l; a[x].r = r; a[x].x = 1;
	if (l == r) pos[l] = x;
	else
	{
		int m = (l + r) / 2;
		build(x * 2, l, m);
		build(x * 2 + 1, m + 1, r);
	}
}

void modify(int x, int l, int r, int k)
{
	//printf("%d %d %d %d LLL\n", x, l, r, k);
	if (a[x].l == l && a[x].r == r) a[x].x = max(a[x].x, k);
	else
	{
		int m = (a[x].l + a[x].r) / 2;
		if (r <= m) modify(x * 2, l, r, k);
		else if (l >= m + 1) modify(x * 2 + 1, l, r, k);
		else
		{
			modify(x * 2, l, m, k);
			modify(x * 2 + 1, m + 1, r, k);
		}
	}
}

void query(int x)
{
	int mx;
	while (x)
	{
		if (a[x].x > mx) mx = a[x].x;
		x /= 2;
	}
	//cerr << mx <<endl;
	//cerr<< ind[mx] << " ..."<<endl;
	ans = ans + (long long)ind[mx];
}

int main()
{
	while (true)
	{
		scanf("%d%d", &n, &m);
		if (n + m == 0) break;
		
		tot = 0; memset(lst, 0, sizeof(lst));
		
		for (int i = 2; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			Add(x, i);
		}
		t = 0; dfs(1);
		//puts("..");
		ans = 0; build(1, 1, n);
		for (int i = 1; i <= m; i++)
		{
			char ch; cin >> ch;
			int x; scanf("%d", &x);
			if (ch == 'M')
			{
				//if(x == 5) cerr<<l[x] << " "<<r[x]<<" "<<l[x]<<endl;
				if (l[x] <= r[x]) modify(1, l[x], r[x], l[x]);
				//for (int j = 1; j <= 20; j++) printf("%d ", a[j].x); puts("aa");
			}
			else  query(pos[l[x]]);
		}
		//cerr<<"??"<<pos[l[5]]<<endl;
		cout << ans << endl;
	}
	return 0;
}
