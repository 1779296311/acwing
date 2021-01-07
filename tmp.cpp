#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N=25005;
const int M=50005;

int t,m1,m2,s,idx,cnt;
int head[N],d[N], to[M << 1], ne[M << 1], cost[M << 1];
int vis[N],color[N], in[N];
vector<int> ccs[N];
queue<int> q;
priority_queue<pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>> > pq;
void add(int u,int v,int w) {
    to[++idx] = v;
    cost[idx] = w;
    ne[idx] = head[u];
    head[u] = idx;
}

void dfs(int x) {
        color[x] = cnt;
        ccs[cnt].push_back(x);
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!color[y])dfs(y);
        }
}

void dijkstra(int c) {
        for(auto x : ccs[c])pq.emplace(d[x], x);
        while(pq.size()){
            int x = pq.top().second;
            pq.pop();
            if(vis[x])continue;
            vis[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] > d[x] + cost[i]){
                    d[y] = d[x] + cost[i];
                    if(color[x] == color[y]) pq.emplace(d[y], y);
                }
                if(color[x] == color[y])continue;
                if(!--in[color[y]])q.emplace(color[y]);
            }
        }
}

int main()
{
    cin>>t>>m1>>m2>>s;
    for(int i=0; i<m1; ++i){
        int u, v, w;
        std::cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    for(int i=1; i<=t; ++i){
        if(!color[i])++cnt, dfs(i);
    }
    for(int i=0; i<m2; ++i){
        int u, v, w;
        std::cin >> u >> v >> w;
        add(u, v, w);
        ++in[color[v]];
    }
    std::memset(d, 0x3f, sizeof d);
    d[s] = 0;
    q.emplace(color[s]);
    for(int i=1; i<=cnt; ++i){
        if(!in[i])q.emplace(i);
    }
    while(q.size()){
        int c = q.front();q.pop();
        dijkstra(c);
    }
    for(int i=1;i<=t;i++) {
        if(d[i]>=1e9) printf("NO PATH\n");
        else printf("%d\n",d[i]);
    }
    return 0;
}
