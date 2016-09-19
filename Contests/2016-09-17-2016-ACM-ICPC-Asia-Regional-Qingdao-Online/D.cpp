#include <bits/stdc++.h>
using namespace std;

long long calc(long long l, long long r){
    
    //printf("%lld %lld\n", l, r);
    if(r <= 1LL) return 0LL;
    if(r <= 2LL) return 1LL;
    if(r <= l + 2LL) return 2LL;
    if(l == 0LL) l = 1LL;
    //printf("%lld %lld\n", l, r);
    return (r - l - 2LL) / 2LL + 2LL;
}

int main(){
    
    long long l, r;
    while(scanf("%I64d%I64d", &l, &r) == 2) printf("%I64d\n", calc(l, r));
    //while(scanf("%lld%lld", &l, &r) == 2) printf("%lld\n", calc(l, r));
    
    return 0;
}
