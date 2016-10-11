#define N 1500
int next[N][10], flag[N], fail[N], a[N];
int m, ans, root;
int newnode(){
	m++;
	for (int i = 1; i <= 4; i++)
		next[m][i] = -1;
	flag[m] = 1;
	return m;
}
void init(){
	m = -1;
	root = newnode();
}
void insert(char s[]){
	int len = strlen(s+1);
	int now = root;
	for (int i = 1; i <= len; i++){
		int t = id(s[i]);
		if (next[now][t] == -1)
			next[now][t] = newnode();
		now = next[now][t];
	}
	flag[now] = 0;
}
void build(){
	queue<int> Q;
	fail[root] = root;
	for (int i = 1; i <= 4; i++)
		if (next[root][i] == -1)
			next[root][i] = root;
		else{
			fail[next[root][i]] = root;
			flag[next[root][i]] &= flag[root];
			Q.push(next[root][i]);
		}
	while (!Q.empty()){
		int now = Q.front();
		Q.pop();
		for (int i = 1; i <= 4; i++)
			if (next[now][i] == -1)
				next[now][i] = next[fail[now]][i];
			else{
				fail[next[now][i]] = next[fail[now]][i];
				flag[next[now][i]] &= flag[next[fail[now]][i]];
				Q.push(next[now][i]);
			} 
	}
}
char s[1005];
int main(){
	int n;
	int cases = 0;
	while(scanf("%d", &n), n){
		init();
		for (int i = 1; i <= n; i++){
			scanf("%s", s+1);
			insert(s);
		}
		build();
	}
	return 0;
} 
