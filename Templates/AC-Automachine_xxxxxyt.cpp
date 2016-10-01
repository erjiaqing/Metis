struct trie{

    int size, indx[maxs][26], word[maxs], fail[maxs];
    bool jump[maxs];

    int idx(char ff){return ff - 'a';}

    void insert(char s[]){

        int u = 0;
        for(int i = 0; s[i]; ++i){
            int k = idx(s[i]);
            if(!indx[u][k]) indx[u][k] = ++size;
            u = indx[u][k];
        }
        word[u] = 1;
        jump[u] = true;
    }

    void get_fail(){

        queue<int> que;
        int head = 0, tail = 0;
        que.push(0);

        while(!que.empty()){
            int u = que.front();
            que.pop();
            for(int k = 0; k < 26; ++k){
                if(!indx[u][k]) continue;
                int v = indx[u][k];
                int p = fail[u];
                while(p && !indx[p][k]) p = fail[p];
                if(indx[p][k] && indx[p][k] != v) p = indx[p][k];
                fail[v] = p;
                jump[v] |= jump[p];
                que.push(v);
            }
        }
    }

    int query(char s[]){

        int rtn = 0, p = 0;
        int flag[maxs];
        memcpy(flag, word, sizeof flag);
        for(int i = 0; s[i]; ++i){
            int k = idx(s[i]);
            while(p && !indx[p][k]) p = fail[p];
            p = indx[p][k];
            int v = p;
            while(jump[v]){
                rtn += flag[v];
                flag[v] = 0;
                v = fail[v];
            }
        }
        return rtn;
    }

} dict;
