#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int inf = 1e6;

int n;
char ch;
double ans[maxn];

bool scan(int &x){
    
    bool rtn = true;
    int l = 0; x = 0;
    while(ch <= '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9'){
        ++l;
        if(l > 7) rtn = false;
        if(rtn) x *= 10, x += ch - '0';
        ch = getchar();
    }
    return rtn;
}

void work(){
    
    bool flag = scan(n);
    flag &= (n <= inf);
    if(flag) printf("%.5f\n", ans[n]);
    else printf("%.5f\n", ans[inf]);
}

int main(){
    
    for(int i = 1; i <= inf; ++i) ans[i] = ans[i-1] + 1.00 / i / i;
    while(scanf("%c", &ch) != EOF) work();
    
    return 0;
}
