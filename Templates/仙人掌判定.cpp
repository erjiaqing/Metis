bool tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    stack[++top] = x; ins[x] = 1;
    int num = 0;
    for (int now = g[x]; now; now = pre[now]) {
        int y = nex[now];
        if (!dfn[y]) {
            if (!tarjan(y)) return 0;
            if (low[y] > dfn[x]) return 0;
            if (low[y] < dfn[x]) num++;
            low[x] = min(low[x], low[y]);
        } else if (ins[y]) {
            num++;
            low[x] = min(low[x], dfn[y]);
        } else return 0;
    }
    if (num >= 2) return 0;
    if (low[x] == dfn[x]) {
        while (stack[top] != x) {
            int y = stack[top];
            ins[y] = 0;
            stack[top--] = 0;
        }
        ins[x] = 0;
        stack[top--] = 0;
    }
    return 1;
}
