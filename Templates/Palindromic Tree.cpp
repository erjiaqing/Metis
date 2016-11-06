/*len[i]节点i的回文串的长度（一个节点表示一个回文串）
  nxt[i][c]节点i的回文串在两边添加字符c以后变成的回文串的编号
  fail[i]节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串
  cnt[i]节点i表示的本质不同的串的个数（count()函数统计fail树上该节点及其子树的cnt和）
  num[i]以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
  lst指向新添加一个字母后所形成的最长回文串表示的节点
  s[i]表示第i次添加的字符（s[0]是任意一个在串s中不会出现的字符）
  n表示添加的字符个数
  一开始回文树有两个节点，0表示偶数长度串的根和1表示奇数长度串的根*/
const int N = 100005;
const int M = 30;
int n, ans[1005][1005];
char s[1005];
struct Palindromic_Tree {
	int nxt[N][M], fail[N];
	int cnt[N], num[N], len[N];
	int s[N], lst, n, m;
	int newnode (int l) {
		m++;
		for (int i = 1; i <= 26; i++) nxt[m][i] = 0; //------------ 
		/*fail[m] = */cnt[m] = num[m] = 0;
		len[m] = l;
		return m;
	}
	void init() {
		m = -1;
		newnode(0);
		newnode(-1);
		lst = 0;
		n = 0; s[n] = 0;
		fail[0] = 1;
	}
	int get_fail(int x) {
		while (s[n - len[x] - 1] != s[n]) x = fail[x];
		return x;
	}
	void Insert(char c) {
		int t = c - 'a' + 1;
		s[++n] = t;
		int now = get_fail(lst);
		if (nxt[now][t] == 0) {
			int tmp = newnode(len[now] + 2);
			fail[tmp] = nxt[get_fail(fail[now])][t];
			nxt[now][t] = tmp;
			num[tmp] = num[fail[tmp]] + 1;
		}
		lst = nxt[now][t];
		cnt[lst]++; //位置不同的相同串算多次 
	}
	void Count() {
		for (int i = m; i >= 0; i--) cnt[fail[i]] += cnt[i];
	}
} st;
int main() {
	st.init();
	for (int i = 1; i <= n; i++)
		st.Insert(s[i]);
	st.Count();
	ans = st.m - 1;
}
