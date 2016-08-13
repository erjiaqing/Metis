#include <cstdio>  
using namespace std;
  
int num[1<<8],ans[1<<8],zh[256][256],cnt;  
bool vis[1<<8];  
  
void dfs(int dep,int x,int y)  
{  
    int i,j;  
  
    if(ans[num[cnt-1]]>dep) ans[num[cnt-1]]=dep;  
  
    if(dep==10)  return;  
  
    for(i=x;i<cnt;i++)  
    {  
        for(j=(i==x?y:0);j<=i;j++)
        {  
            if(!vis[zh[num[i]][num[j]]])  
            {  
                vis[zh[num[i]][num[j]]]=1;  
                num[cnt++]=zh[num[i]][num[j]];  
  
                dfs(dep+1,i,j);  
  
                vis[zh[num[i]][num[j]]]=0;  
                cnt--;  
            }  
        }  
    }  
}  
int main()  
{  
    int i,j;  
  
    num[0]=240;//00001111  
    num[1]=204;//00110011  
    num[2]=170;//01010101  
    num[3]=0;//00000000  
    num[4]=255;//11111111  
  
    for(i=0;i<(1<<8);i++) ans[i]=11;  
  
    vis[240]=vis[204]=vis[170]=vis[0]=vis[255]=1;  
    ans[240]=ans[204]=ans[170]=ans[0]=ans[255]=1;  
  
    for(i=0;i<256;i++) for(j=0;j<256;j++)  
    {  
        zh[i][j]=~(i&j);  
        zh[i][j]&=0x000000FF;  
    }  
  
    cnt=5;  
  
    dfs(1,0,0);  
  
    for(i=0;i<(1<<8);i++)  printf("%d,",ans[i]);  
}  
