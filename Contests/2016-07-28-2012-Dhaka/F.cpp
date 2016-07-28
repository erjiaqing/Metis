#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
char a[50][20][50];
int f[20][50];
int ans[25];
int c[50];

int Id(char ch)
{
	if (ch >= '0' && ch <= '9') return ch - '0' + 26;
	else return ch - 'A';
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		char ch;
		cin >> ch;
		c[i] = Id(ch);
	}
	for (int i = 1; i <= n; i++)
	{
		char ch;
		for (int j = 1; j <= 16; j++)
			for (int k = 1; k <= 43; k++)
			{
				cin >> a[c[i]][j][k];
			}
		for (int j = 1; j <= 43; j++)
			cin >> ch;
	}
	for (int i = 1; i <= m; i++)
	{
		char s[25];
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		//cerr << len<<endl;
		memset(f, -1, sizeof(f));
		for (int j = 1; j <= len; j++)
		{
			int t = Id(s[j]);
			for (int p = 1; p <= 16; p++)
				for (int q = 1; q <= 43; q++)
					if (a[t][p][q] == '*')
					{
						if (f[p][q] == -1) f[p][q] = j;
						else f[p][q] = 0;
					}
		}
		memset(ans, 0, sizeof(ans));
		for(int p = 1; p <= 16; p++)
			for(int q = 1; q <= 43; q++)
				if (f[p][q] > 0) ans[f[p][q]] = 1;
		printf("Query %d: ", i);
		for (int j = 1; j <= len; j++)
			if (ans[j]) printf("Y");
			else printf("N");
		printf("\n");
	}
	return 0;
}
