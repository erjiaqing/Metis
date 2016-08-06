#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, long long> pii;

const int maxn = 1e5 + 5;
const int sqrtm = 300;

int n, m, clr[maxn];
long long sum[maxn][2], ans[2], summ;
vector<int> big;

vector<pii> mp[maxn];
void add_edge(int u, int v, long long d){
    mp[u].push_back(make_pair(v, d));
    if(u != v) mp[v].push_back(make_pair(u, d));
}
bool cmp(pii i, pii j){
    return i.first < j.first;
}

long long query(int c){
    
    long long rtn = 0;
    rtn += ans[c];
    for(int i = 0; i < big.size(); ++i){
        int u = big[i];
        if(clr[u] == c) rtn += sum[u][c];
    }
    return rtn;
}

void modify(int u){
    
    clr[u] ^= 1;
    if(mp[u].size() <= sqrtm){
        for(int l = 0; l < mp[u].size(); ++l){
            int v = mp[u][l].first;
            if(mp[v].size() > sqrtm) continue;
            if(u == v){
                ans[clr[u]] += mp[u][l].second;
                ans[!clr[u]] -= mp[u][l].second;
                continue;
            }
            if(clr[v] == clr[u]) ans[clr[v]] += mp[u][l].second;
            else ans[clr[v]] -= mp[u][l].second;
        }
    }
    for(int i = 0; i < big.size(); ++i){
        int v = big[i];
        int l = lower_bound(mp[v].begin(), mp[v].end(), make_pair(u, 0LL)) - mp[v].begin();
        //printf("lower_boudn %d : %d\n", v, l);
        if(l != mp[v].size() && mp[v][l].first == u && (mp[u].size() <= sqrtm || u >= v)){
            sum[v][clr[u]] += mp[v][l].second;
            sum[v][!clr[u]] -= mp[v][l].second;
        }
    }
}

void work(){
    
    for(int i = 1; i <= n; ++i) scanf("%d", &clr[i]);
    for(int i = 1; i <= m; ++i){
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, 1LL * d);
        summ += 1LL * d;
    }
    for(int u = 1; u <= n; ++u){
        sort(mp[u].begin(), mp[u].end(), cmp);
        vector<pii> tmp;
        tmp.clear();
        for(int l = 0, i = -1; l < mp[u].size(); ++l){
            if(i == -1 || mp[u][l].first != tmp[i].first) ++i, tmp.push_back(mp[u][l]);
            else tmp[i].second += mp[u][l].second;
        }
        mp[u] = tmp;
    }
    for(int u = 1; u <= n; ++u)
    {
        if(mp[u].size() <= sqrtm){
            for(int l = 0; l < mp[u].size(); ++l){
                int v = mp[u][l].first;
                if(mp[v].size() > sqrtm) continue;
                if(clr[u] == 0 && clr[v] == 0) ans[0] += mp[u][l].second;
                if(clr[u] == 1 && clr[v] == 1) ans[1] += mp[u][l].second;
                if(u == v){
                    if(clr[u] == 0 && clr[v] == 0) ans[0] += mp[u][l].second;
                    if(clr[u] == 1 && clr[v] == 1) ans[1] += mp[u][l].second;
                }
            }
        }else{
            big.push_back(u);
            for(int l = 0; l < mp[u].size(); ++l){
                int v = mp[u][l].first;
                if(mp[v].size() > sqrtm && v < u) continue;
                sum[u][clr[v]] += mp[u][l].second;
            }
        }
    }
    ans[0] /= 2, ans[1] /= 2;
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i){
        char ch[10];
        scanf("%s", ch);
        if(ch[0] == 'A'){
            int c1, c2;
            scanf("%d%d", &c1, &c2);
            long long rtn = summ;
            if(c1 == 0 && c2 == 0) rtn = query(0);
            if(c1 == 1 && c2 == 1) rtn = query(1);
            if(c1 != c2) rtn -= query(0) + query(1);
            cout<<rtn<<endl;
        }else{
            int u;
            scanf("%d", &u);
            modify(u);
        }
    }
    
    for(int i = 1; i <= n; ++i) mp[i].clear();
    summ = ans[0] = ans[1] = 0;
    for(int i = 1; i <= n; ++i) sum[i][0] = sum[i][1] = 0;
    big.clear();
}

int main(){
    
    //freopen("D.in", "r", stdin);
    
    int cs = 1;
    for(; scanf("%d%d", &n, &m) == 2; ++cs){
        printf("Case %d:\n", cs);
        work();
    }
    
    return 0;
}
