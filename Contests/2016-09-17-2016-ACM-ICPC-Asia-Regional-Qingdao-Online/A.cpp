#include <bits/stdc++.h>
using namespace std;

const int maxn = 35;
const long long inf = 1e9;

int m;
long long n, ans;
long long pw[10][maxn];

vector<long long> vec;

long long binary(int left, int rght){
    
    while(left < rght){
        int mid = (left + rght) >> 1;
        if(vec[mid] >= n) rght = mid;
        else left = mid + 1;
    }
    return vec[rght];
}

void work(){
    
    //cin >> n;
    //cout << binary(0, m - 1) << endl;
    scanf("%I64d", &n);
    printf("%I64d\n", binary(0, m - 1));
}

void pre(){
    
    long long x;
    for(int a = 0; a < maxn; ++a){
        x = pw[2][a];
        if(x > inf) break;
        for(int b = 0; b < maxn; ++b){
            x = pw[2][a] * pw[3][b];
            if(x > inf) break;
            for(int c = 0; c < maxn; ++c){
                x = pw[2][a] * pw[3][b] * pw[5][c];
                if(x > inf) break;
                for(int d = 0; d < maxn; ++d){
                    x = pw[2][a] * pw[3][b] * pw[5][c] * pw[7][d];
                    if(x > inf) break;
                    vec.push_back(x);
                }
            }
        }
    }
    sort(vec.begin(), vec.end());
    //for(int i = 0; i < vec.size(); ++i) printf("%lld,", vec[i]);
    //printf("%d\n", vec.size());
    m = vec.size();
}

int main(){
    
    for(int i = 1; i < 10; ++i) pw[i][0] = 1;
    for(int i = 1; i < 10; ++i)
        for(int j = 1; j < maxn; ++j) pw[i][j] = pw[i][j-1] * i;
    
    pre();
    
    int t;
    scanf("%d", &t);
    while(t--) work();
    
    return 0;
}
