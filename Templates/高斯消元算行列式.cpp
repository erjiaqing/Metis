void Guass() {
    --n;
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int pos = i; int mx = 0;
        for (int j = i; j <= n; j++)
            if (abs(e[j][i])>mx) {
                mx = abs(e[j][i]);
                pos = j;
            }
        if (pos != i) {
            for (int j = 1; j <= n; j++) {
                swap(e[i][j], e[pos][j]);
            }
            ans *= -1;
        }
        int inv = P(e[i][i], pp - 2);
        for (int j = i+1;j <= n; j++) {
            int t = inv * e[j][i] % pp;
            for (int k = i; k <= n; k++)
                e[j][k] = (e[j][k] - t*e[i][k]) % pp;
        }
    }
    for (int i = 1; i <= n; i++)
        ans = ans * e[i][i] % pp;
    if (ans < 0) ans += pp;
    cout << ans << endl;
}