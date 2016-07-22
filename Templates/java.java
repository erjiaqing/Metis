import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String [] args) {
        Scanner cin = new Scanner(System.in);
        
        int n = cin.nextInt(), m = cin.nextInt(), size = cin.nextInt();
        
        BigInteger [][] c = new BigInteger[250][250];
        BigInteger [][] f = new BigInteger[250][250];
        int [] cnt = new int[250];
        
        for (int i = 0; i < 250; i ++) {
            cnt[i] = 0;
            for (int j = 0; j < 250; j ++) {
                c[i][j] = BigInteger.ZERO;
                f[i][j] = BigInteger.ZERO;
            }
        }
        
        for (int i = 1; i <= n; i ++) {
            int t = cin.nextInt();
            cnt[t] = cnt[t] + 1;
        }
        
        c[0][0] = c[1][0] = c[1][1] = BigInteger.ONE;
        for (int i = 1; i <= n; i ++) {
            c[i][0] = BigInteger.ONE;
            for (int j = 1; j <= i; j ++) {
                c[i][j] = c[i - 1][j - 1].add(c[i - 1][j]);
            }
        }
        
        f[0][0] = BigInteger.ONE;
        for (int i = 0; i < m; i ++) {
            for (int j = 0; j <= size; j ++) {
                for (int k = 0; k <= cnt[i + 1] && j + k <= size; k ++) {
                    f[i + 1][j + k] = f[i + 1][j + k].add(f[i][j].multiply(c[j + k][j]));
                }
            }
        }
        
        System.out.println(f[m][size]);
    }
}
