判斜率(x/gcd, y/gcd)直接丢map里unique

无方案和答案 % MOD 为 0 是有区别的

打标记使用时间戳

a = 10 * a + 1 可以用矩乘加速

数组要开1e5 [+ 5]!

pow(a, b)会调用c++自带函数

强联通、双联通要考虑一个孤立点

MOD的时候：(a - b + MOD) % MOD (a + b * c % MOD) % MOD

stack里有时存的边，这种时候大小不要开错了

选择性段错误: 没return 没赋初值

凸包排序后数组顺序会改变，不可以在这之后求重心

位运算优先级小于 ==

(int)x != round(x)

hash字符串：t = t * 27(!) + s[i] - 'A' + 1

有些dfs里用到的数组开全局会跪

n = 1e4 时明摆着要 n^2 bitset压位

nbcji的个性坑点:
vector<int> v; for(int i = 0; i <(没有=) v.size(); ++i)

做法向
博弈题做法：1.由最终态BFS（类似构了一颗树）2.打表找sg函数规律
没辙时想dp和网络流
启发式合并
