// sap
struct edge{
    int v, r, flow;
    edge(int v, int flow, int r) : v(v), flow(flow), r(r) {}
};
vector<edge> edge[maxn];
void add_edge(int u, int v, int flow){
    edge[u].push_back(edge(v, flow, edge[v].size()));
    edge[v].push_back(edge(u, 0, edge[u].size() - 1));
}
int maxflow, disq[maxn], dist[maxn]; 
int sap(int u, int nowflow){
    if(nowflow == 0 || u == T) return nowflow;
    int tempflow, deltaflow = 0;
    for(int l = 0; l < edge[u].size(); ++l){
        int v = edge[u][l].v;
        if(edge[u][l].flow > 0 && dist[u] == dist[v] + 1){
            tempflow = sap(v, min(nowflow - deltaflow, edge[u][l].flow));
            edge[u][l].flow -= tempflow;
            edge[v][edge[u][l].r].flow += tempflow;
            deltaflow += tempflow;
            if(deltaflow == nowflow || dist[S] >= T) return deltaflow;
        }
    }
    disq[dist[u]]--;
    if(disq[dist[u]] == 0) dist[S] = T;
    dist[u]++; disq[dist[u]]++;
    return deltaflow;
}
int main(){while(dist[S] < T) maxflow += sap(S, inf);}
// 费用流
struct edge{
    int v, r, cost, flow;
    edge(int v, int flow, int cost, int r) : v(v), flow(flow), cost(cost), r(r) {}
};
vector<edge> edge[maxn];
void add_edge(int u, int v, int flow, int cost){
    edge[u].push_back(edge(v, flow, cost, edge[v].size()));
    edge[v].push_back(edge(u, 0, -cost, edge[u].size() - 1));
}
int S, T, maxflow, mincost;
int dist[maxn], pth[maxn], lnk[maxn];
bool inq[maxn]; queue<int> que;
bool find_path(){
    for(int i = 1; i <= T; ++i) dist[i] = inf;
    dist[S] = 0;
    que.push(S);
    while(!que.empty()){
        int u = que.front();
        que.pop(); inq[u] = false;
        for(int l = 0; l < edge[u].size(); ++l){
            int v = edge[u][l].v;
            if(edge[u][l].flow > 0 && dist[v] > dist[u] + edge[u][l].cost){
                dist[v] = dist[u] + edge[u][l].cost;
                pth[v] = u; lnk[v] = l;
                if(!inq[v]) inq[v] = true, que.push(v);
            }
        }
    }
    if(dist[T] < inf) return true;
    else return false;
}
void adjust(){
    int deltaflow = inf, deltacost = 0;
    for(int v = T; v != S; v = pth[v]){
        deltaflow = min(deltaflow, edge[pth[v]][lnk[v]].flow);
        deltacost += edge[pth[v]][lnk[v]].cost;
    }
    maxflow += deltaflow;
    mincost += deltaflow * deltacost;
    for(int v = T; v != S; v = pth[v]){
        edge[pth[v]][lnk[v]].flow -= deltaflow;
        edge[edge[pth[v]][lnk[v]].v][edge[pth[v]][lnk[v]].r].flow += deltaflow;
    }
}
int main(){while(find_path()) adjust();}
