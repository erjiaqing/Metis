#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n & 1) puts("Balanced");
        else puts("Bad");
    }
    return 0;
}
