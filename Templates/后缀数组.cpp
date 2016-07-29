//sa[i] 表示排第 i 位的后缀是谁 rk[i] 表示后缀 i 排第几位
//h[i] 为 suffix(sa[i-1]) 和 suffix(sa[i]) 的最长公共前缀
//开数组要*2
inline void getsa(int j){	
	memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;++i) ++sum[rk[i+j]];
    for(int i=1;i<=n;++i) sum[i]+=sum[i-1];
    for(int i=n;i>0;--i) tsa[sum[rk[i+j]]--]=i;
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;++i) ++sum[rk[i]];
    for(int i=1;i<=n;++i) sum[i]+=sum[i-1];
    for(int i=n;i>0;--i) sa[sum[rk[tsa[i]]]--]=tsa[i];
}
int main(){
	scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;++i) ++sum[s[i]];
    for(int i=1;i<=MC;++i) sum[i]+=sum[i-1];
	for(int i=n;i>0;--i) sa[sum[s[i]]--]=i;
    rk[sa[1]]=1;
    for(int i=2,p=1;i<=n;++i){
        if(s[sa[i]]!=s[sa[i-1]]) ++p;
        rk[sa[i]]=p;
    }
    for(int j=1;j<=n;j<<=1){
        getsa(j);
        trk[sa[1]]=1;
        for(int i=2,p=1;i<=n;++i){
            if(rk[sa[i]]!=rk[sa[i-1]] || rk[sa[i]+j]!=rk[sa[i-1]+j]) ++p;
            trk[sa[i]]=p;
        }
        for(int i=1;i<=n;++i) rk[i]=trk[i];
	}
	for(int i=1;i<=n;++i) printf("%d ",sa[i]); printf("\n");
    for(int i=1,j=0;i<=n;++i){
        if(rk[i]==1) continue;
        while(i+j<=n && sa[rk[i]-1]+j<=n && s[i+j]==s[sa[rk[i]-1]+j]) ++j;
        h[rk[i]]=j;
        if(j>0) --j;
	}
	for(int i=1;i<=n;++i) printf("%d ",h[i]); printf("\n");
    return 0;
}
