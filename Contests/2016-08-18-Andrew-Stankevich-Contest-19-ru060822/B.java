import java.util.*;
import java.io.*;
import java.math.*;
public class Main{
	
	static int maxn = 205;
	static int n;
	static int[] lson = new int[maxn];
	static int[] rson = new int[maxn];
	static int[] sz = new int[maxn];
	static BigInteger[] f = new BigInteger[maxn];
	static BigInteger[][] cnr = new BigInteger[maxn][maxn];
	static BigInteger One = new BigInteger("1");
	static BigInteger Zero = new BigInteger("0");
	static BigInteger rtn;
	
	public static BigInteger dfs(int u){
		if(u == 0) return One;
		sz[u] = 1;
		rtn = One;
		rtn = rtn.multiply(dfs(lson[u]));
		rtn = rtn.multiply(dfs(rson[u]));
		sz[u] = sz[u] + sz[lson[u]];
		sz[u] = sz[u] + sz[rson[u]];
		rtn = rtn.multiply(cnr[sz[lson[u]]+sz[rson[u]]][sz[lson[u]]]);
		return f[u] = rtn;
	}
	
	public static void main(String []arg){
		
		Scanner cin = new Scanner(System.in);
		//Printer cout = new Printer(System.out);
		
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < maxn; ++j)
				cnr[i][j] = BigInteger.ZERO;
		
		cnr[0][0] = One;
		for(int i = 1; i < 205; ++i){
			cnr[i][0] = One;
			for(int j = 1; j <= i; ++j)
			{
				cnr[i][j] = cnr[i-1][j-1].add(cnr[i-1][j]);
			}
			
		}
		
		n = cin.nextInt(); // scanf
		for(int i = 1; i <= n; ++i){
			lson[i] = cin.nextInt();
			rson[i] = cin.nextInt();
		}
		
		sz[0] = 0;
		System.out.println(dfs(1)); // print
	}
}
