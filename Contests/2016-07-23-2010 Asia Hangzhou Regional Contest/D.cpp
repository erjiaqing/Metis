#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
const int dy[8] = {0, 0, -1, 1, -1, 1, 1, -1};
int n, c0, c1, x, y, now, a[20][20];

bool check(int x, int y)
{
	int p, q, cnt = 0;
	for (int i = 0; i < 8; i++)
	{
		if ((i & 1) == 0) cnt = 0;
		p = x + dx[i], q = y + dy[i];
		while (p >= 0 && p < 15 && q >= 0 && q < 15 && a[p][q] == a[x][y])
		{
			cnt++;
			if (cnt >= 4) return 1;
			p = p + dx[i], q = q + dy[i];
		}
	}
	return 0;
}

bool work1(int c)
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (a[i][j] == -1)
			{
				a[i][j] = c;
				if (check(i, j))
				{
					x = i, y = j;
					a[i][j] = -1;
					return 1;
				}
				a[i][j] = -1;
			}
	return 0;	
}

bool work2(int c)
{
	int cnt = 0;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (a[i][j] == -1)
			{
				a[i][j] = c;
				if (check(i, j))
				{
					cnt++;
					if (cnt == 2) {a[i][j] = -1; return 1;}
				}
				a[i][j] = -1;
			}
	return 0;
}

bool work3(int c)
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (a[i][j] == -1)
			{
				a[i][j] = c;
				if (work2(c) && !work1(c ^ 1))
				{
					x = i, y = j;
					a[i][j] = -1;
					return 1;
				}
				a[i][j] = -1;
			}
	return 0;
}

void solve()
{
	if (c0 != c1 && c0 + 1 != c1)
	{
		//cerr<<c0<<" "<<c1<<endl;
		puts("Invalid.");
		return ;
	}
	string s;
	if (c0 == c1) now = 1, s = "black"; else now = 0, s = "white";
	if (work1(now))
	{
		printf("Place %s at (%d,%d) to win in 1 move.\n", s.c_str(), x, y);
		return ;
	}
	if (work2(now ^ 1))
	{
		puts("Lose in 2 moves.");
		return ;
	}
	if (work3(now))
	{
		printf("Place %s at (%d,%d) to win in 3 moves.\n", s.c_str(), x, y);
		return ;
	}
	puts("Cannot win in 3 moves.");
}

int main()
{
	while (scanf("%d", &n) == 1)
	{
		//scanf("%d", &n);
		//cerr<<n<<endl;
		if (n == 0) return 0;
		memset(a, -1, sizeof(a));
		c0 = c1 = 0;
		for (int i = 1; i <= n; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			a[x][y] = z;
			if (z == 0) c0++; else c1++;
		}
		//cerr<<c0<<" "<<c1<<endl;
		//getchar();
		//getchar();
		solve();
	}
	return 0;
}
