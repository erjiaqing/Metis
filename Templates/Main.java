//javac Main.java
//java Main
import java.io.*;
import java.util.*;
import java.math.*;
public class Main{
	public static BigInteger n,m;
	public static Map<BigInteger,Integer> M = new HashMap();
	public static BigInteger dfs(BigInteger x){
		if(M.get(x)!=null)return M.get(x);
		if(x.mod(BigInteger.valueOf(2))==1){
		}else{
            string p = n.toString();
		}
		M.put();
	}
    static int NNN = 1000000;
    static BigInteger N;
    static BigInteger One = new BigInteger("1");
    static BigInteger[] num_step = new BigInteger[NNN];
	public static void main(String []arg){
		Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
		{
        int p = cin.nextInt();
        n = cin.nextBigInteger();
        n.multiply(m);
        M.clear();
        if(n.compareTo(BigInteger.ZERO)==0)break;
        if(n.compareTo(m)<=0){
				System.out.println(m.subtract(n));
				continue;
			}
        BigInteger[] QB = new BigInteger[5000*20];
        Integer[] QD = new Integer[5000*20];
        int head=0,tail=0;
        QB[tail]=n;
        QD[tail]=0;
        tail++;
        BigInteger ans = n.subtract(m).abs();
            if(ans.compareTo(BigInteger.valueOf(dep).add(m.subtract(now).abs()))>0)
                ans=BigInteger.valueOf(dep).add(m.subtract(now).abs());
            head++;
            if(now.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE)!=0){
                nxt=now.divide(BigInteger.valueOf(2));
                if(M.get(nxt)==null){
                    M.put(nxt,1);
                }
            }
        System.out.println(ans);
    }
}
}
还有这样的hashset用法:
static Collection c = new HashSet();
if(c.contains(p) == false)
//读入优化
public class Main {
    BigInteger Zero = BigInteger.valueOf(0);
    BigInteger[][] a = new BigInteger[50][50];
    public void run() {
        out = new PrintWriter(System.out);
        in = new BufferedReader(new InputStreamReader(System.in));
        String s;
        for ( ; ; ) {
            try {
                s = next();
                BigInteger ans = new BigInteger(s);
                ans = ans.add(Zero);
                ans = ans.subtract(Zero);
                ans = ans.multiply(ans);
                ans = ans.divide(ans);
                String t = ans.toString();
                int dig = t.length();
                if (ans.compareTo(Zero) == 1) {
                    out.println(">");
                } else if (ans.compareTo(Zero) == 0) {
                    out.println("=");
                } else if (ans.compareTo(Zero) == -1) {
                    out.println("<");
                }
            }
            catch (RuntimeException e) {break;}
        }
        out.close();
    }
    public static void main(String[] args) {new Main().run();}
    public StringTokenizer token = null;
    public BufferedReader in;
    public PrintWriter out;
    public String next() {
        while (token == null || !token.hasMoreTokens()) {
            try {token = new StringTokenizer(in.readLine());}
            catch (IOException e) {throw new RuntimeException(e);}
        }
        return token.nextToken();
    }
    public int nextInt() {return Integer.parseInt(next());}
    public double nextDouble() {return Double.parseDouble(next());}
    public BigInteger nextBigInteger() {return new BigInteger(next());}
}