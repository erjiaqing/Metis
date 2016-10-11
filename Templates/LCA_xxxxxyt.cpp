int maxbit, dpth[maxn], ance[maxn][maxb];
void dfs(int u, int fath){
    dpth[u] = dpth[fath] + 1; ance[u][0] = fath;
    for(int i = 1; i <= maxbit; ++i) ance[u][i] = ance[ance[u][i-1]][i-1];
    for(int l = last[u]; l; l = next[l]){
        int v = dstn[l];
        if(v == fath) continue;
        dfs(v, u);
    }
}
int lca(int u, int v){
    if(dpth[u] < dpth[v]) swap(u, v);
    int p = dpth[u] - dpth[v];
    for(int i = 0; i <= maxbit; ++i)
        if(p & (1 << i)) u = ance[u][i];
    if(u == v) return u;
    for(int i = maxbit; i >= 0; --i){
        if(ance[u][i] == ance[v][i]) continue;
        u = ance[u][i]; v = ance[v][i];
    }
    return ance[u][0];
}