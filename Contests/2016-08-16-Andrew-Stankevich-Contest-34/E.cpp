#include <cstdio>
using namespace std;

const int ans[] = {0, 1, 2, 3, 5, 8, 14, 25, 45, 85, 162, 310, 595, 1165, 2285, 4485, 8808, 17306, 34302, 68009, 134853};

int main(){
	
	int n;
	scanf("%d", &n);
	printf("%d\n", ans[n]);

	return 0;
}
