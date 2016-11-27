void BuildSA(char *s) {
	int len=strlen(s+1),p;
	for (int i=1;i<=len;++i) trk[i]=s[i],sum[trk[i]]++;
	for (int i=1;i<=MAXN;++i) sum[i]+=sum[i-1];
	for (int i=len;i;--i) sa[sum[trk[i]]]=i,sum[trk[i]]--;
	rank[sa[1]]=1;p=1;
	for (int i=2;i<=len;++i){
		if (trk[sa[i]]!=trk[sa[i-1]])	p++;
		rank[sa[i]]=p;
	}
	for (int j=1;p<len;j<<=1){
		for (int i=1;i<=len;++i)	trk[i]=rank[i],sum[i]=0;
		p=0;
		for (int i=len-j+1;i<=len;++i)	tsa[++p]=i;
		for (int i=1;i<=len;++i) if (sa[i]-j>0)	tsa[++p]=sa[i]-j;
		for (int i=1;i<=len;++i) sum[trk[tsa[i]]]++;
		for (int i=1;i<=MAXN;++i) sum[i]+=sum[i-1];
		for (int i=len;i;--i) sa[sum[trk[tsa[i]]]]=tsa[i],sum[trk[tsa[i]]]--;
		rank[sa[1]]=1;p=1;
		for (int i=2;i<=len;++i){
			if (trk[sa[i]]!=trk[sa[i-1]] || trk[sa[i]+j]!=trk[sa[i-1]+j]) p++;
			rank[sa[i]]=p;
		}
	}
	h[sa[1]]=0;p=0;
	for (int i=1;i<=len;++i){
		if (rank[i]==1)	continue;
		while (s[i+p]==s[sa[rank[i]-1]+p])	p++;
		h[i]=p;
		if (p) p--;
	}
	for (int i=1;i<=len;++i) height[rank[i]]=h[i];
}