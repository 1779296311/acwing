/*********************************************
*     ------------------------
*     ------------------------
*     file name: graph_theory_pro.cpp
*     author   : @ JY
*     date     : 2021--01--05
**********************************************/
#include <bits/stdc++.h>
namespace p360{
    const int N = 5e5 + 12;
    int head[N], ne[N], to[N], cost[N];
    int ch[N], cne[N], cto[N], cw[N], st[N];
    int d[N], dist[N], fa[N][32], pw[N], px[N], low[N], dfn[N], sum[N];
    int k, t, n, m, idx, cidx, code, tp, cnt;
    void _add(int x, int y, int v){
        to[++idx]=y, cost[idx]=v, ne[idx]=head[x], head[x]=idx;
    }
    void _add_c(int x, int y, int v){
        cto[++cidx] = y, cw[cidx] = v, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _build(int x, int y){
        int c = 0;
        for(int i=head[x]; i; i=ne[i]){
            if(to[i] == y){
                c = cost[i];
                break;
            }
        }
        sum[y] = sum[++cnt] = c, sum[x] = 0;
        for(int i=y; i!=x; i=px[i])sum[px[i]] = sum[cnt] += pw[i];
        for(int i=y; i!=px[x]; i=px[i]){
            int mi = std::min(sum[i], sum[cnt]-sum[i]);
            _add_c(cnt, i, mi), _add_c(i, cnt, mi);
        }
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                px[y] = x, pw[y] = cost[i];
                low[x] = std::min(low[x], low[y]);
                if(low[y] >= dfn[x]){
                    int z = st[tp];
                    while(st[tp--] != y);
                    _build(x, z);
                }
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(y == p)continue;
            dist[y] = dist[x] + cw[i];
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _deal(){
        std::cin >> n >> m >> k;
        cnt = n;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        t = (int)(log(cnt) / log(2)) + 1;
        for(int i=1; i<=cnt; ++i){
            if(!d[i])_dfs(i, 0);
        }
        for(int i=1, x, y; i<=k; ++i){
            std::cin >> x >> y;
            int lca = _lca(x, y);
            if(lca <=  n){
                std::cout << dist[x] + dist[y] - (dist[lca] << 1) << std::endl;
            }else{
                int a = x, b = y;
                for(int j=t;  j>=0; --j){
                    if (d[fa[x][j]] >= d[lca] + 1) x = fa[x][j];
                }
                for(int j=t;  j>=0; --j){
                    if (d[fa[y][j]] >= d[lca] + 1) y = fa[y][j];
                }
                int mi = abs(sum[x] - sum[y]); mi = std::min(mi, sum[lca] - mi);
                std::cout << dist[a]-dist[x]+dist[b]-dist[y]+mi << std::endl;
            }
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p412{
    const int N = 5e5 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N], to[N], edge[N];
    int d[N];
    int n, m, idx, be, ed;
    void _add(int x, int y, int v){
        to[++idx]=y, edge[idx]=v,ne[idx]=head[x], head[x]=idx;
        to[++idx]=x, edge[idx]=0,ne[idx]=head[y], head[y]=idx;
    }
    bool _bfs(int be, int ed){
        std::memset(d, 0, sizeof d);
        std::queue<int> q;
        q.push(be);
        d[be] = 1;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i] || d[y])continue;
                d[y] = d[x] + 1;
                if(y == ed)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int ed, int flow){
        if(x == ed)return flow;
        int rest = flow;
        for(int i=head[x]; rest && i; i=ne[i]){
            int y = to[i];
            if(!edge[i] || d[y] != d[x] + 1)continue;
            int k = _dinic(y, ed, std::min(edge[i], rest));
            if(!k)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _calc(){
        int ans = 0, flow;
        while(_bfs(be, ed)){
            while((flow=_dinic(be, ed, INF))){
                ans += flow;
            }
        }
        std::cout << ans << std::endl;
    }
    void _read(){
        std::cin >> n >> m;
        idx = be = 1, ed = m;
        for(int i=1, x, y, v; i<=n; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v);
        }
    }
    void _deal(){
        _read();
        _calc();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p411{
    const int N = 2048, INF = 0x3f3f3f3f;
    int head[N<<1], ne[N << 2], to[N << 2], edge[N<<2];
    int ch[N << 1], cto[N << 2], cne[N << 2];
    int dfn[N], low[N], st[N], co[N], vi[N], d[N];
    int idx, cidx, n, tp, code, dn, sum, be, ed;
    std::vector<int> wifi[N];
    void _add(int x, int y, int v){
        to[++idx]=y, edge[idx]=v,ne[idx]=head[x], head[x]=idx;
        to[++idx]=x, edge[idx]=0,ne[idx]=head[y], head[y]=idx;
    }
    void _add(int x, int y){
        cto[++cidx] =y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        vi[x] = st[++tp] = x;
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return ;
        int y; ++dn;
        do y=st[tp--], vi[y]=0, co[y]=dn;
        while(x!=y);
    }
    bool _bfs(int be, int ed){
        std::memset(d, 0, sizeof d);
        std::queue<int> q;
        q.push(be);
        d[be] = 1;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i] || d[y])continue;
                d[y] = d[x] + 1;
                if(y == ed)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int ed, int flow){
        if(x == ed)return flow;
        int rest = flow;
        for(int i=head[x]; rest && i; i=ne[i]){
            int y = to[i];
            if(!edge[i] || d[y] != d[x] + 1)continue;
            int k = _dinic(y, ed, std::min(edge[i], rest));
            if(!k)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _calc(){
        while(_bfs(be, ed)){
            while(_dinic(be, ed, INF));
        }
        for(int i=2; i<=idx; ++i){
            if(!edge[i])_add(to[i], to[i^1]);
        }
        for(int i=be; i<=ed; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=1; i<=sum; ++i){
            int j = i << 1;
            if(edge[j|1] || co[to[j]] == co[to[j^1]]){
                wifi[to[j^1]].emplace_back(to[j]-n);
            }
        }
        for(int i=1; i<=n; ++i){
            std::cout << wifi[i].size() << " ";
            std::sort(begin(wifi[i]), end(wifi[i]));
            for(int &wf : wifi[i]){
                std::cout << wf << " ";
            }
            std::cout << std::endl;
        }
    }
    void _read(){
        idx = cidx = 1;
        std::cin >> n;
        be = n * 2 + 1, ed = be + 1;
        for(int i=1, sz, x; i<=n; ++i){
            std::cin >> sz;
            while(sz--){
                std::cin >> x;
                _add(i, x+n, 1);
                ++sum;
            }
        }
        for(int i=1; i<=n; ++i)_add(be, i, 1);
        for(int i=1; i<=n; ++i)_add(i+n, ed, 1);
    }
    void _deal(){
        _read();
        _calc();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p410_dinic{
    const int N = 128, INF = 0x3f3f3f3f;
    int head[N<<3], ne[N<<4], to[N<<4], edge[N<<4];
    int ch[N<<3], cne[N<<4], cto[N<<4];
    int low[N], dfn[N], st[N], co[N], vi[N], d[N];
    int k, n, m, idx, cidx, code, tp, dn, len, be, ed, sum;
    std::tuple<int, int, int, int> pos[N];
    std::tuple<char, int> res[N];
    void _add(int x, int y, int e){
        to[++idx]=y,edge[idx]=e,ne[idx]=head[x],head[x]=idx;
        to[++idx]=x,edge[idx]=0,ne[idx]=head[y],head[y]=idx;
    }
    void _add(int x, int y){
        cto[++cidx] = y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    bool _check(int i, int x, int y){
        auto[x1, x2, y1, y2] = pos[i];
        return x>=x1 && x<=x2 &&
               y>=y1 && y<=y2;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        vi[x] = st[++tp] = x;
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return ;
        int y; ++dn;
        do y=st[tp--], co[y]=dn, vi[y]=0;
        while(x!=y);
    }
    bool _bfs(int be, int ed){
        std::memset(d, 0, sizeof d);
        d[be] = 1;
        std::queue<int> q;
        q.push(be);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i] || d[y])continue;
                d[y] = d[x] + 1;
                if(y == ed)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int ed, int flow){
        if(x == ed)return flow;
        int rest = flow;
        for(int i=head[x]; rest && i; i=ne[i]){
            int y = to[i];
            if(d[y] != d[x] + 1 || !edge[i])continue;
            int k = _dinic(y, ed, std::min(rest, edge[i]));
            if(k==0)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(ch, 0, sizeof ch);
        std::memset(vi, 0, sizeof vi);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
        std::memset(co, 0, sizeof co);
        sum = len = code = dn = tp = 0;
        idx = cidx = 1;
    }
    void _read(){
        be = 2 * n + 1, ed = be + 1;
        for(int i=1; i<=n; ++i){
            auto &[x1, x2, y1, y2] = pos[i];
            std::cin >> x1 >> x2 >> y1 >> y2;
        }
        for(int i=1, x, y; i<=n; ++i){
            std::cin >> x >> y;
            for(int j=1; j<=n; ++j){
                if(_check(j, x, y))_add(i+n, j, 1),++sum;
            }
        }
        for(int i=1; i<=n; ++i)_add(be, i+n, 1);
        for(int i=1; i<=n; ++i)_add(i, ed, 1);
    }
    void _calc(){
        while(_bfs(be, ed)){
            while(_dinic(be, ed, INF));
        }
        for(int i=2; i<=idx; ++i){
            if(!edge[i]){
                _add(to[i], to[i ^ 1]);
            }
        }
        for(int i=be; i<=ed; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=1; i<=sum; ++i){
            int j = i << 1;
            if(edge[j|1] && co[to[j]] != co[to[j^1]]){
                res[++len] = {to[j], to[j^1]};
            }
        }
        std::cout << "Heap " << ++k << std::endl;
        if(!len){
            std::cout << "none" << std::endl;
        }else{
            std::sort(res+1, res+len+1, [&](auto &a, auto &b){
                    return std::get<0>(a) < std::get<0>(b); });
            for(int i=1; i<=len; ++i){
                auto [a, b] = res[i];
                std::cout << '(' << (char)(a-1+'A')
                    << ',' <<  b - n << ") ";
            }
        }
        std::cout << std::endl;
    }
    void _deal(){
        while(std::cin>>n, n){
            _init();
            _read();
            _calc();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p410{
    const int N = 64;
    int head[N << 4], ne[N << 5], to[N << 5]; 
    int vi[N], match[N];
    int dfn[N], low[N], co[N], st[N];
    int n, k, tp, code, dn, idx;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    std::tuple<int, int, int, int> pos[N];
    bool _check(int i, int x, int y){
        auto[x1, x2, y1, y2] = pos[i];
        return x>=x1 && x<=x2 &&
               y>=y1 && y<=y2;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        vi[x] = st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(x>n && match[y] == x)continue;
            if(x<=n && match[x] != y)continue;
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return ;
        int y; ++dn;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = dn;
        }while(x!=y);
    }
    bool _dfs(int x, int id){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y] == id)continue;
            vi[y] = id;
            if(!match[y] || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(match, 0, sizeof match);
        std::memset(vi, 0, sizeof vi);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
        std::memset(co, 0, sizeof co);
        idx = code = dn = tp = 0;
    }
    void _read(){
        for(int i=1; i<=n; ++i){
            auto &[x1, x2, y1, y2] = pos[i];
            std::cin >> x1 >> x2 >> y1 >> y2;
        }
        for(int i=1, x, y; i<=n; ++i){
            std::cin >> x >> y;
            for(int j=1; j<=n; ++j){
                if(_check(j, x, y)){
                    _add(i+n, j), _add(j, i+n);
                }
            }
        }
    }
    void _calc(){
        std::cout << "Heap " << ++k << std::endl;
        for(int i=1; i<=n; ++i)_dfs(i+n, i);
        std::memset(vi, 0, sizeof vi);
        for(int i=1; i<=2*n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        int f = 0;
        for(int i=1; i<=n; ++i){
            if(co[i] != co[match[i]]){
                f = 1;
                break;
            }
        }
        if(!f){
            std::cout << "none" << std::endl;
            return ;
        }
        for(int i=1; i<=n; ++i){
            if(co[i] != co[match[i]]){
                std::cout << '(' << (char)(i-1+'A')
                    << ',' << match[i] - n << ") ";
            }
        }
        std::cout << std::endl;
    }
    void _deal(){
        while(std::cin>>n, n){
            _read();
            _calc();
            std::cout << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p409{
    const int N = 128;
    int e[N][N], vi[N], match[N];
    int t, n, m;
    bool _dfs(int x, int id){
        for(int y=1; y<=n; ++y){
            if(vi[y] == id || !e[x][y])continue;
            vi[y] = id;
            if(!match[y] || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            std::memset(e, 0, sizeof e);
            std::cin >> n >> m;
            for(int i=1, x, y; i<=m; ++i){
                std::cin >> x >> y;
                e[x][y] = 1;
            }
            int ans = n;
            std::memset(match, 0, sizeof match);
            std::memset(vi, 0, sizeof vi);
            for(int i=1; i<=n; ++i)ans -= _dfs(i, i);
            std::cout << ans << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p408{
    using pii = std::pair<int, int>;
    const int N = 5012, INF = 0x3f3f3f3f;
    char g[128][128];
    int e[N][N], w[N][N], la[N], lb[N], va[N], upd[N], vb[N], match[N];
    int n, m, n1, n2;
    pii pe[N], ho[N];
    void _read(){
        for(int i=1; i<=n; ++i){
            scanf("%s", g[i] + 1);
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(g[i][j] == 'm'){
                    pe[++n1] = {i, j};
                }else if(g[i][j] == 'H'){
                    ho[++n2] = {i, j};
                }
            }
        }
        for(int i=1; i<=n1; ++i){
            auto [x, y] = pe[i];
            for(int j=1; j<=n2; ++j){
                auto [x1, y1] = ho[j];
                w[i][j] = -(abs(x - x1) + abs(y - y1));
            }
        }
    }
    bool _dfs(int x){
        va[x] = 1;
        for(int y=1; y<=n1; ++y){
            if(vb[y])continue;
            if(la[x] + lb[y] == w[x][y]){
                vb[y] = 1;
                if(!match[y] || _dfs(match[y])){
                    match[y] = x;
                    return true;
                }
            }else{
                upd[y] = std::min(upd[y], la[x] + lb[y] - w[x][y]);
            }
        }
        return false;
    }
    void _km(){
        for(int i=1; i<=n1; ++i){
            la[i] = -INF; lb[i] = 0;
            for(int j=1; j<=n1; ++j){
                la[i] = std::max(la[i], w[i][j]);
            }
        }
        for(int i=1,id; i<=n1; ++i){
            while(true){
                std::memset(va, 0, sizeof va);
                std::memset(vb, 0, sizeof vb);
                std::memset(upd, 0x3f, sizeof upd);
                int delta = INF;
                if(_dfs(i))break;
                for(int j=1; j<=n1; ++j){
                    if(!vb[j])delta = std::min(delta, upd[j]);
                }
                for(int j=1; j<=n1; ++j){
                    if(va[j])la[j] -= delta;
                    if(vb[j])lb[j] += delta;
                }
            }
        }
        int ans = 0;
        for(int i=1; i<=n1; ++i)ans += w[match[i]][i];
        std::cout << -ans << std::endl;
    }
    void _init(){
        n1 = n2 = 0;
        std::memset(match, 0, sizeof match);
    }
    void _deal(){
        while(std::cin >> n >> m,n&&m){
            _init();
            _read();
            _km();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p407__{
    const int N = 1024;
    int sa[N][32], nu[N], vi[N], match[32][N], cnt[32];
    int n, m;
    int _dfs(int x, int id, int s, int e){
        for(int i=s; i<=e; ++i){
            int y = sa[x][i];
            if(vi[y] == id)continue;
            vi[y] = id;
            if(cnt[y] < nu[y]){
                match[y][++cnt[y]] = x;
                return true;
            }
            for(int j=1; j<=nu[y]; ++j){
                if(_dfs(match[y][j], id, s, e)){
                    match[y][j] = x;
                    return true;
                }
            }
        }
        return false;
    }
    bool _check(int mid){
        for(int st=1, i; st+mid-1<=m; ++st){
            int ed = st + mid- 1;
            std::memset(vi, 0, sizeof vi);
            std::memset(match, 0, sizeof match);
            std::memset(cnt, 0, sizeof cnt);
            for(i=1; i<=n; ++i){
                if(!_dfs(i, i, st, ed))break;
            }
            if(i>n)return true;
        }
        return false;
    }
    void _b_search(){
        int l = 0, r = m + 1;
        while(l < r){
            int mid = l + ((r - l) >> 1);
            if(!_check(mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        std::cout << r << std::endl;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j)std::cin >> sa[i][j];
        }
        for(int i=1; i<=m; ++i)std::cin >> nu[i];
        _b_search();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p407{
    const int N = 1024;
    int head[N << 5], ne[N << 8], to[N << 8];
    int sa[N][32], nu[N], vi[N << 8], match[32][N], cnt[32];
    int n, m, idx;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    int _dfs(int x, int id){
        for(int i=head[x]; i; i=ne[i]){
            int y = sa[x][to[i] - n];
            if(vi[y] == id)continue;
            vi[y] = id;
            if(cnt[y] < nu[y]){
                match[y][++cnt[y]] = x;
                return true;
            }
            for(int j=1; j<=nu[y]; ++j){
                if(_dfs(match[y][j], id)){
                    match[y][j] = x;
                    return true;
                }
            }
        }
        return false;
    }
    bool _check(int mid){
        for(int st=1, i; st+mid-1<=m; ++st){
            int ed = st+mid-1;
            std::memset(head, 0, sizeof head);
            std::memset(vi, 0, sizeof vi);
            std::memset(match, 0, sizeof match);
            std::memset(cnt, 0, sizeof cnt);
            int idx = 0;
            for(int i=1; i<=n; ++i){
                for(int j=st; j<=ed; ++j){
                    _add(i, n + j);
                }
            }
            for(i=1; i<=n; ++i){
                if(!_dfs(i, i))break;
            }
            if(i>n) return true;
        }
        return false;
    }
    void _b_search(){
        int l = 1, r = m + 1;
        while(l < r){
            int mid = l + ((r - l) >> 1);
            if(_check(mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        std::cout << r << std::endl;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                std::cin >> sa[i][j];
            }
        }
        for(int i=1; i<=m; ++i)std::cin >> nu[i];
        _b_search();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p406{
    const int N = 64;
    char g[N][N];
    int head[N << 8], ne[N << 8], to[N << 8];
    int mp1[N][N], mp2[N][N], match[N<<8], vi[N << 8];
    int idx, t, k, n, m, code1, code2;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(mp1, 0, sizeof mp1);
        std::memset(mp2, 0, sizeof mp2);
        std::memset(match, 0, sizeof match);
        idx = code1 = code2 = 0;
    }
    int _dfs(int x){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            scanf("%s", g[i]+1);
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(g[i][j]=='#')continue;
                if(mp1[i][j-1]){
                    mp1[i][j] = mp1[i][j-1];
                }else{
                    mp1[i][j] = ++code1;
                }
                if(mp2[i-1][j]){
                    mp2[i][j] = mp2[i-1][j];
                }else{
                    mp2[i][j] = ++code2;
                }
            }
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(g[i][j] != 'o')continue;
                _add(mp1[i][j], mp2[i][j]);
            }
        }
    }
    void _calc(){
        int ans = 0;
        for(int i=1; i<=code1; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << "Case :" << ++k << std::endl;
        std::cout << ans << std::endl;
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            _init();
            _read();
            _calc();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p405__{
    const int N = 128;
    int e[N][N], color[N], t[N], f[N], res[N], newid[N], dp[N][N];
    int n, m, cnt;
    std::vector<int> g[N][3];
    bool _dfs(int x, int co){
        color[x] = co;
        g[newid[x]][co].emplace_back(x);
        for(int i=1; i<=n; ++i){
            if(!e[x][i])continue;
            if(!color[i]){
                if(!_dfs(i, 3-co))return false;
            }else if(color[x] == color[i]){
                return false;
            }
        }
        return true;
    }
    void _dfs(int i, int re, int &sz){
        if(!i)return ;
        int co = dp[i][re];
        for(int x : g[i][co]){
            t[x] = res[++sz] = x;
        }
        _dfs(i-1, re - g[i][co].size(), sz);
    }
    int _f(int x){return f[x]==x ? x : f[x]=_f(f[x]);}
    void _deal(){
        std::cin >> n;
        for(int i=1; i<=n; ++i)f[i] = i;
        for(int i=1, x; i<=n; ++i){
            std::memset(t, 0, sizeof t);
            while((std::cin>>x, x))t[x] = 1;
            for(int j=1; j<=n; ++j){
                if(i!=j && !t[j]){
                    e[i][j] = e[j][i] = 1;
                    f[_f(i)] = _f(j);
                }
            }
        }
        for(int i=1; i<=n; ++i){
            if(!newid[_f(i)]) newid[_f(i)] = ++cnt;
            newid[i] = newid[_f(i)];
        }
        for(int i=1; i<=n; ++i){
            if(!color[i] && !_dfs(i, 1)){
                std::cout << "No solution" << std::endl;
                return;
            }
        }
        int m = n >> 1;
        std::memset(dp, -1, sizeof dp);
        dp[0][0] = 0;
        for(int i=1; i<=cnt; ++i){
            int sz1 = g[i][1].size();
            int sz2 = g[i][2].size();
            for(int j=0; j<=m; ++j){
                if(j>=sz1 && dp[i-1][j-sz1]!=-1)dp[i][j] = 1;
                if(j>=sz2 && dp[i-1][j-sz2]!=-1)dp[i][j] = 2;
                std::cout << dp[i][j] << std::endl;
            }
        }
        std::memset(t, 0, sizeof t);
        int ans = 0;
        for(int i=m; i>=0; --i){
            if(dp[cnt][i] != -1){
                _dfs(cnt, i, ans);
                break;
            }
        }
        std::sort(res+1, res+1+ans);
        std::cout << ans << " ";
        for(int i=1; i<=ans; ++i)std::cout << res[i] << " ";
        std::cout << std::endl;
        std::cout << n - ans << " ";
        for(int i=1; i<=n; ++i){
            if(!t[i])std::cout << i << " ";
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p405{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int dfn[N], low[N], st[N], co[N], vi[N];
    int n, m, idx, code, tp, dn;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    int _neg(int x){
        if(x <= n)return x + n;
        return x - n;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        vi[x] = st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return;
        int y ;++dn;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = dn;
        }while(x!=y);
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
        std::memset(co, 0, sizeof co);
        std::memset(vi, 0, sizeof vi);
        idx = dn = code = tp = 0;
    }
    void _read(){
        _add(1, n + 1);
        char ch1, ch2;
        for(int i=1, x, y; i<=m; ++i){
            scanf("%d%c %d%c", &x, &ch1, &y, &ch2);
            x = ++x + (ch1=='h') * n;
            y = ++y + (ch2=='h') * n;
            _add(x, _neg(y)), _add(y, _neg(x));
        }
    }
    void _sd(){
        for(int i=1; i<=(n<<1); ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=1; i<=n; ++i){
            if(co[i] == co[i+n]){
                std::cout << "bad luck" << std::endl;
                return ;
            }
        }
        for(int i=2; i<=n; ++i){
            std::cout << i << ((co[i] > co[i+n]) ? "w " : "h ");
        }
        std::cout << std::endl;
    }
    void _deal(){
        while((std::cin>>n>>m)&&n&&m){
            _init();
            _read();
            _sd();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p404_{
    using pii = std::pair<int, int>;
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int dfn[N], low[N], st[N], co[N], mp[N], vi[N];
    int n, m, idx, t, code, dn, tp;
    pii pos[N];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x],head[x] = idx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        vi[x]  = st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return ;
        int y;++dn;
        do
            y = st[tp--],
            vi[y] = 0,
            co[y] = dn;
        while(x != y);
    }
    bool _check(int s1, int t1, int s2, int t2){
        if(s1>t1)std::swap(s1, t1);
        if(s2>t2)std::swap(s2, t2);
        return (t1>s2 && t2>t1 && s1<s2)||
               (t2>s1 && t1>t2 && s2<s1);
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
        std::memset(vi, 0, sizeof vi);
        std::memset(co, 0, sizeof co);
        idx = dn = code = tp = 0;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            pos[i] = {x, y};
        }
        for(int i=1, x; i<=n; ++i){
            mp[std::cin >> x,x] = i;
        }
    }
    void _calc(){
        if(m > 3*n - 6){
            std::cout << "NO" << std::endl;
            return ;
        }
        for(int i=1; i<=m; ++i){
            auto [s1, t1] = pos[i];
            for(int j=1; j<i; ++j){
                auto [s2, t2] = pos[j];
                if(_check(mp[s1], mp[t1], mp[s2], mp[t2])){
                    _add(i, j+m), _add(j+m, i);
                    _add(i+m, j), _add(j, i+m);
                }
            }
        }
        for(int i=1; i<=2*m; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=1; i<=m; ++i){
            if(co[i] == co[i+m]){
                std::cout << "NO" << std::endl;
                return;
            }
        }
        std::cout << "YES" << std::endl;
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            _init();
            _read();
            _calc();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p402__{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int ch[N], cne[N << 1], cto[N << 1];
    int n, m, idx, cidx, code, dn, tp;
    int dfn[N], low[N], st[N], vi[N], co[N], in_[N], size[N];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        vi[x] = 1, st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return;
        int y; ++dn;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = dn;
            ++size[dn];
        }while(x!=y);
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        std::memset(vi, 0, sizeof vi);
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(co[x] == co[y] || vi[co[y]])continue;
                _add_c(co[x], co[y]);
                ++in_[co[y]];
            }
            for(int i=head[x]; i; i=ne[i])vi[co[to[i]]] = 0;
        }
    }
    void _calc(){
        int cnt = 0, f = 0;
        for(int x=1; x<=dn; ++x){
            if(in_[x])continue;
            ++cnt;
            if(f || size[x] > 1)continue;
            int tmp = 1;
            for(int i=ch[x]; i; i=cne[i]){
                if(in_[cto[i]]<2){
                    tmp = 0;
                    break;
                }
            }
            f |= tmp;
        }
        printf("%.6f", (n-(cnt-f))*1. / n*1.);
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y);
        }
    }
    void _deal(){
        _read();
        _sd();
        _calc();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p401_{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int ch[N], cne[N << 1], cto[N << 1];
    int n, m, t, cidx, idx, code, dn, tp;
    int low[N], dfn[N], co[N], st[N], vi[N], in_[N];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        st[++tp] = x; vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return ;
        ++dn;int y;
        do{
            y = st[tp--],
            co[y] = dn,
            vi[y] = 0;
        }while (x != y);
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(ch, 0, sizeof ch);
        std::memset(low, 0, sizeof low);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(vi, 0, sizeof vi);
        std::memset(in_, 0, sizeof in_);
        std::memset(co, 0, sizeof co);
        code = cidx = idx = tp = dn = 0;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y);
        }
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(co[x] == co[y])continue;
                ++in_[co[y]];
                _add_c(co[x], co[y]);
            }
        }
    }
    void _topsort(){
        std::queue<int> q;
        for(int i=1; i<=dn; ++i){
            if(!in_[i])q.push(i);
        }
        int cnt = 0;
        while(q.size()){
            int x = q.front();q.pop();
            ++cnt;
            if(q.size())break;
            for(int i=ch[x]; i; i=cne[i]){
                int y = cto[i];
                if(!--in_[y])q.push(y);
            }
        }
        if(q.size() || cnt!=dn){
            std::cout << "No" << std::endl;
        }else{
            std::cout << "Yes" << std::endl;
        }
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            _init();
            _read();
            _sd();
            _topsort();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p400{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int n, idx, len;
    int vi[N], ans[N];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _dfs(int x){
        while(head[x]){
            int y = to[head[x]];
            head[x] = ne[head[x]];
            _dfs(y);
        }
        ans[len++] = x;
    }
    void _deal(){
        std::cin >> n;
        int t = (1 << (n - 1)) - 1;
        for(int i=0; i<(1<<(n-1)); ++i){
            _add(i, (i<<1)&t|1), _add(i, (i<<1)&t);
        }
        _dfs(0);
        std::cout << (1 << n) << " ";
        while(--len)std::cout << ((ans[len] >> (n-2)) & 1);
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p399{
    using pii = std::pair<int, int>;
    const int N = 5e5 + 12;
    int vi[N], st[N], ans[N], pre[N];
    int n, idx, tp, len;
    std::vector<pii> e[64];
    void _dfs(int x){
        for(auto [v, y] : e[x]){
            if(vi[v])continue;
            vi[v] = 1;
            _dfs(y);
            ans[++len] = v;
        }
    }
    void _init(){
        std::memset(vi, 0, sizeof vi);
        for(int i=1; i<=n; ++i)e[i].clear();
        n = len = tp = 0;
    }
    void _euler(int s){
        st[++tp] = s;
        while(tp){
            int x = st[tp], i = 0, pv;
            for(auto [v, y] : e[x]){
                if(!vi[v]){
                    vi[pv = v] = i = y;
                    break;
                }
            }
            if(i){
                st[++tp] = i;
                pre[tp] = pv;
            }else{
                ans[++len] = pre[tp--];
            }
        }
    }
    void _deal(){
        int x, y, z, be = 1e5;
        for( ; ; ){
            std::cin >> x >> y;
            if(!x && !y)return;
            std::cin >> z;
            be = std::min(x, y);
            _init();
            for( ; ; ){
                n = std::max({n, x, y});
                e[x].emplace_back(z, y);
                e[y].emplace_back(z, x);
                std::cin >> x >> y;
                if(!x && !y)break;
                std::cin >> z;
            }
            int f = 0;
            for(int i=1; i<=n; ++i){
                if(e[i].size() & 1){
                    f = 1;
                    break;
                }else{
                    std::sort(begin(e[i]), end(e[i]));
                }
            }
            if(f){
                std::cout << "Round trip does not exist.";
            }else{
                _euler(be);
                while(len--) std::cout << ans[len] << " ";
                //_dfs(be);
                //while(len){
                    //std::cout << ans[len--] << " ";
                //}
            }
            std::cout << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p398{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[ N << 1 ];
    int ch[N], cne[N << 1], cto[N << 1];
    int low[N], dfn[N], d[N], cut[N], st[N], co[N], fa[N][32], cnt[N], id[N], newid[N];
    int n, m, idx, code, tp, dn, cidx, root, t;
    std::vector<int> dcc[N >> 5];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        st[++tp] = x;
        if(x == root && !head[x]){
            dcc[++dn].push_back(x);
            return ;
        }
        int f = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
                if(low[y] < dfn[x])continue;
                if(++f>1 || x!=root)cut[x] = 1;
                int z; ++dn;
                do{
                    z = st[tp--];
                    dcc[dn].push_back(z);
                }while(z!=y);
                dcc[dn].push_back(x);
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        cnt[x] = (x>dn) + cnt[p];
        for(int i=1; (1<<i)<=d[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(y == p)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(ch, 0, sizeof ch);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(fa, 0, sizeof fa);
        std::memset(low, 0, sizeof low);
        std::memset(d, 0, sizeof d);
        std::memset(cut, 0, sizeof cut);
        std::memset(id, 0, sizeof id);
        std::memset(newid, 0, sizeof newid);
        std::memset(cnt, 0, sizeof cnt);
        std::memset(co, 0, sizeof co);
        for(int i=1; i<=dn; ++i)dcc[i].clear();
        code = cidx = tp = dn = 0;
        idx = 1;
    }
    void _read(){
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
    }
    void _sd(){
        for(root=1; root<=n; ++root){
            if(!dfn[root])_tarjan(root);
        }
        int tmp = dn;
        for(int i=1; i<=n; ++i){
            if(cut[i])newid[i] = ++tmp;
        }
        for(int i=1; i<=dn; ++i){
            for(int x : dcc[i]){
                if(cut[x]){
                    _add_c(i, newid[x]);
                    _add_c(newid[x], i);
                }
                co[x] = i;
            }
            for(int x : dcc[i]){
                for(int j=head[x]; j; j=ne[j]){
                    int y = to[j];
                    if(co[y] == i)id[j / 2] = i;
                }
            }
        }
        t = (int)(log(tmp) / log(2)) + 1;
        for(int i=1; i<=tmp; ++i){
            if(!d[i]) _dfs(i, 0);
        }
    }
    void _calc(){
        int x, y, q, lca;
        std::cin >> q;
        while(q--){
            std::cin >> x >> y;
            x = id[x], y = id[y], lca = _lca(x, y);
            std::cout
                << cnt[x] + cnt[y] + (lca>dn) - (cnt[lca] << 1) <<
            std::endl;
        }
    }
    void _deal(){
        while(std::cin >> n >> m){
            if(!n && !m)break;
            _init();
            _read();
            _sd();
            _calc();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p397{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int ch[N], cne[N << 1], cto[N << 1];
    int low[N], dfn[N], st[N], bri[N], co[N], d[N], fa[N][32];
    int n, m, q, code, tp, dn, cidx, idx = 1, t;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y, cne[cidx] = ch[x], ch[x] = cidx;
    }
    void _tarjan(int x, int in_e){
        dfn[x] = low[x] = ++code;
        st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y, i);
                low[x] = std::min(low[x], low[y]);
                if(low[y] > dfn[x])bri[i] = bri[i^1] = 1;
            }else if(i != (in_e ^ 1)){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] < dfn[x])return;
        ++dn;
        int y;
        do{
            y = st[tp--];
            co[y] = dn;
        }while(x!=y);
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(y == p)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1,x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
    }
    void _sd(){
        _tarjan(1, 0);
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(co[x] == co[y])continue;
                _add_c(co[x], co[y]);
            }
        }
        t = (int)(log(dn) / log(2)) + 1;
    }
    void _calc(int x, int y){
        std::cout
            << d[x] + d[y] - (d[_lca(x, y)] << 1) <<
        std::endl;
    }
    void _deal(){
        int x, y;
        _read();
        _sd();
        _dfs(1, 0);
        std::cin >> q;
        while(q--){
            std::cin >> x >> y;
            _calc(co[x], co[y]);
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p396{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int dfn[N], low[N], st[N], cut[N];
    int t, n, idx, tp, code, dn, root, k;
    std::vector<int> dcc[N >> 7];
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        st[++tp] = x;
        if(x==root && !head[x]){
            dcc[++dn].push_back(x);
            return ;
        }
        int f = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
                if(low[y] < dfn[x])continue;
                if(++f>1 || x!=root)cut[x] = 1;
                ++dn; int z;
                do{
                    z = st[tp--];
                    dcc[dn].push_back(z);
                }while(z!=y);
                dcc[dn].push_back(x);
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(ne, 0, sizeof ne);
        std::memset(low, 0, sizeof low);
        std::memset(dfn, 0, sizeof dfn);
        std::memset(cut, 0, sizeof cut);
        for(int i=1; i<=dn; ++i)dcc[i].clear();
        n = idx = code = tp = dn = 0;
    }
    void _read(){
        int x, y;
        while(t--){
            std::cin >> x >> y;
            n = std::max({n, x, y});
            _add(x, y), _add(y, x);
        }
    }
    void _calc(){
        for(root=1; root<=n; ++root){
            if(!dfn[root])_tarjan(root);
        }
        long long res1 = 0, res2 = 1;
        for(int i=1; i<=dn; ++i){
            int cn = 0, size = dcc[i].size();
            for(auto &x : dcc[i]){
                if((cn += cut[x]) > 1)break;
            }
            if(cn > 1)continue;
            if(cn == 1)++res1, res2 *= (size - 1);
            if(cn == 0){
                ++res1;
                if(size>1)++res1,res2 *= (size*(size-1)) / 2;
            }
        }
        std::cout
            << "Case " << ++k << ": "
            << res1 << " " << res2 <<
        std::endl;
    }
    void _deal(){
        while(std::cin >> t, t){
            _init();
            _read();
            _calc();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p395{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int low[N], dfn[N], co[N], bri[N], st[N], in_[N];
    int n, m, idx, code, ans, dn, tp;
    void _add(int x, int y){
        to[++idx] = y, ne[idx] = head[x], head[x] = idx;
    }
    void _tarjan(int x, int in_e){
        low[x] = dfn[x] = ++code;
        st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y, i);
                low[x] = std::min(low[x], low[y]);
                if(low[y] > dfn[x])bri[i] = bri[i ^ 1] = 1;
            }else if(i != (in_e ^ 1)){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] != dfn[x])return ;
        ++dn;int y;
        do{
            y = st[tp--];
            co[y] = dn;
        }while(x!=y);
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i, 0);
        }
        for(int i=2; i<=idx; ++i){
            if(!bri[i])continue;
            ++in_[co[to[i]]];
        }
        for(int i=1; i<=dn; ++i){
            ans += in_[i] == 1;
        }
        std::cout << (ans + 1) / 2<< std::endl;
    }
    void _deal(){
        std::cin >> n >> m;
        idx = 1;
        for(int i=1, x , y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _sd();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p394{
    const int N = 5e5;
    const double EPS = 1e-5;
    int head[N], ne[N << 1], to[N << 1], cost[N << 1];
    int n, m, idx, sum, code;
    int vi[N];
    double d[N];
    std::unordered_map<std::string, int> mp;
    std::unordered_map<char, int> smp {
        {'S', 1000}, {'G', 500},
        {'D', 300},  {'T', 200},
        {'K', 150},
    };
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _spfa(int x, double m){
        vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            double w = m - cost[i];
            if(d[y] > d[x] + w){
                d[y] = d[x] + w;
                if(vi[y] || _spfa(y, m))return true;
            }
        }
        vi[x] = 0;
        return false;
    }
    bool _check(double m){
        for(int i=0; i<=n; ++i){
            d[i] = 0x3f3f3f3f;
            vi[i] = 0;
        }
        for(int i=1; i<=n; ++i){
            if(_spfa(i, m))return true;
        }
        return false;
    }
    void _b_search(){
        double l = 0, r = 1e5;
        while((r-l) > EPS){
            double m = (l + r) / 2;
            if(_check(m)){
                l = m;
            }else{
                r = m;
            }
        }
        std::cout << ((l<=0) ? -1 : round(l)) << std::endl;;
    }
    void _deal(){
        std::cin >> n;
        std::stringstream ss;
        std::string line, tmp, be;
        for(int i=1; i<=n; ++i){
            std::cin >> line;
            ss.clear();
            ss << line;
            sum = 0; be = "";
            while(std::getline(ss, tmp, '-')){
                sum += smp[tmp[0]];
                if(!be.size())be = tmp;
            }
            if(!mp.count(be))mp[be]   = ++code;
            if(!mp.count(tmp))mp[tmp] = ++code;
            _add(mp[be], mp[tmp], sum);
        }
        n = mp.size();
        _b_search();
    }
    int main(int argc,const char *argv[]){
         _deal();
        return 0;
    }
};
namespace p393{
    const int N = 1024;
    int head[N], ne[N << 3], cost[N << 3], to[N << 3];
    int d[N], p[N], nd[N], vi[N], cnt[N];
    int n, m, t, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _spfa(int s24){
        std::memset(head, 0, sizeof head);
        std::memset(cnt, 0, sizeof cnt);
        std::memset(vi, 0, sizeof vi);
        std::memset(d, 0xcf, sizeof d);
        for(int i=1; i<=24; ++i){
            _add(i, i-1, -p[i]);
            _add(i-1, i, 0);
            if(i>=8){
                _add(i-8,  i, nd[i]);
            }else{
                _add(i+16, i, nd[i] - s24);
            }
        }
        _add(0, 24, s24);_add(24, 0, -s24);
        std::queue<int> q;
        q.push(0);
        d[0] = 0;
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] >= d[x] + cost[i])continue;
                d[y] = d[x] + cost[i];
                cnt[y] = cnt[x] + 1;
                if(cnt[y] >= 25)return false;
                if(!vi[y])q.push(y), vi[y] = 1;
            }
        }
        return true;
    }
    void _b_search(){
        int l = 0, r = n + 1;
        while(l < r){
            int m = l + ((r - l) >> 1);
            if(_spfa(m)){
                r = m;
            }else{
                l = m + 1;
            }
        }
        if(r == n + 1){
            std::cout << "No Solution" << std::endl;
        }else{
            std::cout << r << std::endl;
        }
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            std::memset(p, 0, sizeof p);
            for(int i=1; i<=24; ++i)std::cin >> nd[i];
            std::cin >> n;
            for(int i=1, x; i<=n; ++i)++p[std::cin>>x, x+1];
            _b_search();
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p392_{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int n, m, idx, code, t, len, co;
    int ci[N], vi[N], color[N], pos[N], pre[N];
    int dfn[N], d[N], fa[N][32], pa[N], a[N], sz[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        color[x] = co;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
        }
        for(int i=head[x]; i; i=ne[i]){
            if(i & 1)continue;
            int y = to[i];
            if(vi[y] || y == p)continue;
            _dfs(y, x);
        }
    }
    std::pair<int, int> _lca(int x, int y){
        int ca = color[x], cb = color[y];
        if(ca != cb)return {-1, -1};
        int a = x, b = y, f = 0;
        if(d[x] < d[y])std::swap(x, y),f = 1;
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return {d[a]-d[x], d[b]-d[x]};
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        if(fa[x][0])return {d[a]-d[fa[x][0]], d[b]-d[fa[x][0]]};
        x = pos[x], y = pos[y];
        if(f)std::swap(x, y);
        int ansa = d[a] - 1, ansb = d[b] - 1;
        int da = x > y ? sz[ca] - x + y : y - x;
        int db = y > x ? sz[ca] - y + x : x - y;
        int ma = std::max(ansa+da, ansb);
        int mb = std::max(ansb+db, ansa);
        if(ma < mb){
            ansa += da;
        }else if(mb < ma){
            ansb += db;
        }else if(std::min(ansa+da, ansb) >
                    std::min(ansb+db, ansa)){
            ansb += db;
        }else{
            ansa += da;
        }
        return {ansa, ansb};
    }
    void _div(){
        for(int i=1; i<=n; ++i){
            if(color[i])continue;
            ++co;
            int st = i, si, len = 0;
            while(!dfn[a[st]])dfn[st=a[st]] = 1;
            si = a[st];
            while(si != st){
                ci[++len] = si;
                pos[si]   = len;
                vi[si]    = 1;
                si        = a[si];
            }
            ci[++len] = si;
            pos[si]   = len;
            vi[si]    = 1;
            sz[co]    = len;
            for(int i=1; i<=len; ++i)_dfs(ci[i], 0);
        }
    }
    void _deal(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<=n; ++i){
            std::cin >> a[i];
            _add(i, a[i]), _add(a[i], i);
        }
        _div();
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            auto [a, b] = _lca(x, y);
            std::cout << a << " " << b << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();;
        return 0;
    }

};
namespace p392{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int n, m, idx, code, t, len, co;
    int ci[N], vi[N], color[N], pos[N], pre[N];
    int dfn[N], d[N], fa[N][32], pa[N], a[N], sz[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
        }
        for(int i=head[x]; i; i=ne[i]){
            if(i & 1)continue;
            int y = to[i];
            if(vi[y] || y == p)continue;
            _dfs(y, x);
        }
    }
    void _dfs(int x, int p, int co){
        color[x] = co;
        dfn[x] = ++code;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            if(dfn[y]){
                if(dfn[x] > dfn[y])continue;
                for(; y!=x; y=pre[y]) pa[++len] = y;
                pa[++len] = x;
            }else{
                pre[y] = x;
                _dfs(y, x, co);
            }
        }
    }
    std::pair<int, int> _lca(int x, int y){
        int ca = color[x], cb = color[y];
        if(ca != cb)return {-1, -1};
        int a = x, b = y, f = 0;
        if(d[x] < d[y])std::swap(x, y),f = 1;
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return {d[a]-d[x], d[b]-d[x]};
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        if(fa[x][0])return {d[a]-d[fa[x][0]], d[b]-d[fa[x][0]]};
        x = pos[x], y = pos[y];
        if(f)std::swap(x, y);
        int ansa = d[a] - 1, ansb = d[b] - 1;
        int da = x > y ? sz[ca] - x + y : y - x;
        int db = y > x ? sz[ca] - y + x : x - y;
        int ma = std::max(ansa+da, ansb);
        int mb = std::max(ansb+db, ansa);
        if(ma < mb){
            ansa += da;
        }else if(mb < ma){
            ansb += db;
        }else if(std::min(ansa+da, ansb) >
                    std::min(ansb+db, ansa)){
            ansb += db;
        }else{
            ansa += da;
        }
        return {ansa, ansb};
    }
    void _div(){
        for(int i=1; i<=n; ++i){
            if(color[i])continue;
            code = len = 0;
            _dfs(i, 0, ++co);
            sz[co] = len;
            int s = pa[len], k = 0;
            for(int x=s; a[x]!=s; x=a[x]){
                ci[++k] = x;
                pos[x] = k;
                vi[x] = 1;
            }
            for(int i=1; i<=len; ++i)_dfs(ci[i], 0);
        }
    }
    void _deal(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<=n; ++i){
            std::cin >> a[i];
            _add(i, a[i]), _add(a[i], i);
        }
        _div();
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            auto [a, b] = _lca(x, y);
            std::cout << a << " " << b << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();;
        return 0;
    }
};
namespace p391{
    const int N = 5e5 + 12;
    int head[N], ne[N << 1], to[N << 1], cost[N << 1];
    int n, m, t, idx;
    int d[N], fa[N][32];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
        }
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i];
                y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _deal(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1, x, y; i<n; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _dfs(1, 0);
        for(int i=1, x, y, z; i<=m; ++i){
            std::cin >> x >> y >> z;
            int pxy = _lca(x, y);
            int pxz = _lca(x, z);
            int pyz = _lca(y, z);
            if(pxy == pyz)std::swap(pxz, pyz);
            if(d[pxy] < d[pyz])std::swap(pxy, pyz);
            std::cout << pxy << " " <<
                d[x] + d[y] - d[pxy] + d[z] - 2*d[pxz] << 
            std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p390{
    using ll = long long;
    const int N = 2e5 + 12;
    int head[N], ne[N << 2], to[N << 2];
    int n, m, idx, s, t;
    int vi[N], pre[N];
    ll d1[N], d2[N], d3[N], cost[N << 2];
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    int _bfs(int st, ll *d){
        int ans = st;
        std::memset(pre, 0, sizeof pre);
        std::memset(vi, 0, sizeof vi);
        std::queue<int> q;
        q.emplace(st);
        d[st]  = 0;
        vi[st] = 1;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(vi[y])continue;
                vi[y]  = 1;
                d[y]   = d[x] + cost[i];
                pre[y] = x;
                q.emplace(y);
                if(d[ans] < d[y])ans = y;
            }
        }
        return ans;
    }
    void _deal(){
        ll ans = 0;
        std::cin >> n >> m;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        s = _bfs(1, d1);
        t = _bfs(s, d2);
        _bfs(t, d3);
        for(int x=1; x<=n; ++x){
            ans = std::max(ans, std::min(d2[x],d3[x]));
        }
        std::cout << ans + d2[t] << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p389_{
    using ll = long long;
    const int N = 2e5 + 12;
    const ll INF = -1;
    int head[N], ne[N << 2], to[N << 2];
    int n, idx, s, t, l, r, pre[N];
    ll d[N], dep[N], dp[N], cost[N << 2];
    std::unordered_set<int> mp;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    int _bfs(int s){
        int ans = s;
        for(int i=1; i<=n; ++i)d[i] = -1;
        std::queue<int> q;
        q.emplace(s);
        d[s] = 0;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] != -1)continue;
                d[y] = d[x] + cost[i];
                dep[y] = dep[x] + 1;
                pre[y] = x;
                q.emplace(y);
                if(d[ans] < d[y])ans = y;
            }
        }
        return ans;
    }
    void _dfs(int x, int p){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            _dfs(y, x);
            dp[x] = std::max(dp[x], cost[i] + dp[y]);
            if(mp.count(y) || !mp.count(x))continue;
            if(d[t]-d[x] == dp[y] + cost[i])r = x;
            if(d[x] == dp[y] + cost[i] && dep[x] > dep[l])l = x;
        }
    }
    void _deal(){
        std::cin >> n;
        for(int i=1, x, y, v; i<=n; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        r = t = _bfs(l=s=_bfs(1));
        for(int x=t; x; x=pre[x])mp.insert(x);
        _dfs(s, 0);
        std::cout << d[t] << std::endl;
        std::cout << std::max(0ll, dep[r] - dep[l]) << std::endl;
        //for(int x=t; x; x=pre[x])mp.insert(x);
        //int left = s, right = t, flag = 1;
        //for(int i = t; i != s; i = pre[i]) 
        //{
            //ll ld = _dfs(i, 0);
            //if(ld == d[i]) 
            //{
                //left = i;
                //flag = 0;
            //}
            //if(ld == d[t] - d[i]) right = i;
        //}
        //int ans = 0;
        //for(int i = right; i != left; i = pre[i]) ++ans;
        //std::cout << dp[t] << std::endl;
        //std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }

};
//30969390713  173810
//30969406643  123654
namespace p389__{
    using ll = long long;
    const int N = 2e5 + 12;
    const ll INF = -1;
    int head[N], ne[N << 2], to[N << 2];
    int n, idx, s, t, l, r, pre[N], mp[N];
    ll d[N], dep[N], dp[N], cost[N << 2], vi[N];
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        for (int i = head[x]; i; i = ne[i]) {
            int y = to[i];
            if (y == p) continue;
            pre[y] = x;
            dep[y] = dep[x] + 1;
            d[y] = d[x] + cost[i];
            if (d[0] < d[y]) d[0] = d[y], pre[0] = y;
            _dfs(y, x);
        }
    }
    int _bfs(int st){
        int ans = st;
        std::memset(vi, 0, sizeof vi);
        std::memset(pre, 0, sizeof pre);
        std::queue<int> q;
        q.emplace(st);
        d[st] = 0;
        vi[st] = 1;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(vi[y])continue;
                vi[y] = 1;
                d[y] = d[x] + cost[i];
                dep[y] = dep[x] + 1;
                pre[y] = x;
                q.emplace(y);
                if(d[ans] < d[y])ans = y;
            }
        }
        return ans;
    }
    void dfs(int x, int p){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            dfs(y, x);
            dp[x] = std::max(dp[x], cost[i] + dp[y]);
            if(mp[y] || !mp[x])continue;
            if(d[t]-d[x] == dp[y] + cost[i])r = x;
            if(d[x] == dp[y] + cost[i] && dep[x] > dep[l])l = x;
        }
    }
    void _deal(){
        std::cin >> n;
        for(int i=1, x, y, v; i<=n; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        r = t = _bfs(l=s=_bfs(1));
        for(int x=t; x; x=pre[x])mp[x]=1;
        dfs(s, 0);
        std::cout << d[t] << std::endl;
        std::cout << std::max(0ll, dep[r] - dep[l]) << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p389{
    const int N = 64, INF = 0x3f3f3f3f;
    struct node {
        int x, y, d;
        node () {}
        node (int x, int y, int d) :
            x(x), y(y), d(d) {};
        bool operator < (const node &other) const {
            return d < other.d;
        }
    }nodes[N << 4];
    int n, m;
    int a[N], sum[N << 10],d[N << 10], f[N], dp[N << 10];
    int _f(int x){return f[x] == x ? x : f[x]=_f(f[x]);}
    int _kruskal(int st){
        int tot = 0, ans = 0;
        for(int i=0; i<n; ++i){
            if(st & (1 << i))++tot;
            f[i] = i;
        }
        for(int i=1; i<=m; ++i){
            auto[x, y, d] = nodes[i];
            if(!(st&(1<<x)) || !(st&(1<<y)))continue;
            x = _f(x), y = _f(y);
            if(x == y)continue;
            f[x] = y;
            ans += d;
            --tot;
        }
        return !--tot ? ans : INF;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=0; i<n; ++i)std::cin >> a[i];
        for(int i=1; i<=m; ++i){
            auto &[x, y, d] = nodes[i];
            std::cin >> x >> y >> d;
        }
        std::sort(nodes+1, nodes+m+1);
        for(int i=0; i<n; ++i)sum[1<<i] = a[i];
        for(int i=1; i<(1<<n); ++i){
            dp[i]  = INF;
            sum[i] = (sum[i^(i&-i)] + sum[i&-i]);
        }
        for(int i=1; i<(1<<n); ++i){
            if(!sum[i])dp[i] = _kruskal(i);
        }
    }
    void _dp(){
        dp[0] = 0;
        for(int i=0; i<(1<<n); ++i){
            if(sum[i])continue;
            for(int j=0; j<(1<<n); ++j){
                if((i & j) || sum[j])continue;
                dp[i|j] = std::min(dp[i|j], dp[i] + dp[j]);
            }
        }
        if(dp[(1 << n) - 1] == INF){
            std::cout << "Impossible" << std::endl;
        }else{
            std::cout << dp[(1<<n)-1] << std::endl;
        }
    }
    void _deal(){
        _read();
        _dp();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p387{
    const int N = 1024;
    const double EPS = 1e-5;
    struct node{
        int x, y;
        double dis;
        node () {};
        node (int x, int y, double d) :
            x(x), y(y), dis(d) {};
        bool operator < (const node &other) const {
            return dis < other.dis;
        }
    }nodes[N << 10];
    int posx[N], posy[N];
    int f[N], h[N];
    int s, n, m, cnt;
    int _f(int x){return x==f[x] ? x : f[x]=_f(f[x]);}
    double _distance(int i, int j){
        int x1 = posx[i], y1 = posy[i];
        int x2 = posx[j], y2 = posy[j];
        return sqrt((x1-x2)*(x1-x2) +
                    (y1-y2)*(y1-y2));
    }
    bool _kruskal(double mid){
        std::memset(h,0, sizeof h);
        int t = 1;
        for(int i=1; i<=n; ++i)f[i] = i;
        for(int i=0; i<cnt; ++i){
            if(t == n)return true;
            int x = _f(nodes[i].x);
            int y = _f(nodes[i].y);
            if(x == y)continue;
            if(mid < nodes[i].dis)continue;
            f[x] = y;
            ++t;
        }
        int re = 0;
        for(int i=1; i<=n; ++i)re += !h[_f(i)]++;
        return re <= s;
    }
    double _b_search(double l, double r){
        while((r-l) > EPS){
            double mid = (l + r) / 2;
            if(_kruskal(mid)){
                r = mid;
            }else{
                l = mid;
            }
        }
        return l;
    }
    double _read(){
        cnt = 0;
        std::cin >> s >> n;
        for(int i=1; i<=n; ++i){
            std::cin >> posx[i] >> posy[i];
        }
        double maxd = 0;
        for(int i=1; i<n; ++i){
            for(int j=i+1; j<=n; ++j){
                nodes[cnt++] = {i, j, _distance(i, j)};
                maxd = std::max(maxd, nodes[cnt-1].dis);
            }
        }
        std::sort(nodes, nodes + cnt);
        return maxd;
    }
    void _deal(){
        std::cin >> m;
        while(m--)printf("%.2f\n", _b_search(0, _read()));
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p386{
    const int N = 128, INF = 0x3f3f3f3f;
    long long e[N][N];
    double c[N][N];
    int n, m;
    void _deal(){
        std::cin >> n >> m;
        std::memset(e, 0x3f, sizeof e);
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            e[x][y] = e[y][x] = v;
            c[x][y] = c[y][x] = 1;
        }
        for(int i=1; i<=n; ++i)e[i][i] = 0, c[i][i] = 1;
        for(int k=1; k<=n; ++k){
            for(int i=1; i<=n; ++i){
                for(int j=1; j<=n; ++j){
                    if(i==j || j==k || i==k)continue;
                    long long d = e[i][k] + e[k][j];
                    if(e[i][j] > d){
                        e[i][j] = d;
                        c[i][j] = c[i][k] * c[k][j];
                    }else if(e[i][j] == d){
                        c[i][j] += c[i][k] * c[k][j];
                    }
                }
            }
        }
        for(int i=1; i<=n; ++i){
            double ans = 0;
            for(int be=1; be<=n; ++be){
                if(be == i)continue;
                for(int ed=be+1; ed<=n; ++ed){
                    if(ed == i)continue;
                    if(e[be][i] + e[i][ed] == e[be][ed]){
                        ans += (c[be][i] * c[i][ed]*1.) / c[be][ed]*1.;
                    }
                }
            }
            printf("%.3f", ans);
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p385{
    const int N = 128, INF = 0x3f3f3f3f;
    int e[N][N];
    int n, m;
    void _deal(){
        std::cin >> n >> m;
        std::memset(e, 0x3f, sizeof e);
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            e[x][y] = e[y][x] = 1;
        }
        for(int i=1; i<=n; ++i)e[i][i] = 0;
        for(int k=1; k<=n; ++k){
            for(int i=1; i<=n; ++i){
                for(int j=1; j<=n; ++j){
                    if(e[i][k] == INF || e[k][j] == INF)continue;
                    e[i][j] = std::min(e[i][j], e[i][k] + e[k][j]);
                }
            }
        }
        int ans = 0;
        for(int i=1; i<=n; ++i){
            for(int j=i+1; j<=n; ++j){
                if(e[i][j] == INF)continue;
                ans = std::max(ans, e[i][j]);
            }
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p340_{
    const int N = 3e4 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N << 2], to[N << 2], cost[N << 2];
    int n, m, k, idx, vi[N], dp[1024][1024];
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _spfa(int s){
        std::memset(dp, 0x3f, sizeof dp);
        dp[s][0] = 0;
        std::queue<int> q;
        q.emplace(s);
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x], y, w; i; i=ne[i]){
                y = to[i];
                w = std::max(dp[x][0], cost[i]);
                if(dp[y][0] > w){
                    dp[y][0] = w;
                    if(!vi[y])vi[y]=1, q.push(y);
                }
                for(int j=1; j<=k; ++j){
                    w = std::min(dp[x][j-1],
                            std::max(dp[x][j], cost[i]));
                    if(dp[y][j] > w){
                        dp[y][j] = w;
                        if(!vi[y])vi[y]=1, q.push(y);
                    }
                }
            }
        }
    }
    void _deal(){
        std::cin >> n >> m >> k;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        _spfa(1);
        int ans = INF;
        for(int i=0; i<=k; ++i){
            ans = std::min(ans, dp[n][i]);
        }
        if(ans == INF)ans = -1;
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p384{
    using pii = std::pair<int, int>;
    const int N = 1e4, INF = 0x3f3f3f3f;
    int head[N], ne[N << 1], to[N << 1], w[N << 1];
    int d[N], op[N], c[N];
    int n, m, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        w[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dijkstra(int s, int p){
        std::memset(d, 0x3f, sizeof d);
        d[s] = 0;
        op[s] = p;
        std::priority_queue<pii> q;
        q.emplace(0, s);
        while(q.size()){
            auto [dis, x] = q.top();q.pop();
            int pre = op[x];
            if(-dis != d[x])continue;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] > d[x] + 2*abs(x-y) + abs(pre-w[i])){
                    d[y] = d[x] + 2*abs(x-y) + abs(pre-w[i]);
                    op[y] = w[i];
                    q.emplace(-d[y], y);
                }
            }
        }
    }
    void _deal(){
        int p;
        std::cin >> n >> m;
        for(int i=1; i<=m; ++i){
            std::cin >> c[i];
            if(!c[i])p = i;
        }
        for(int i=1; i<=m; ++i){
            for(int j=1; j<=n; ++j){
                if(c[i] && c[i] + j > 0 && c[i] + j <= n){
                    _add(j, c[i] + j, i);
                }
            }
        }
        _dijkstra(1, p);
        if(d[n] == INF)d[n] = -1;
        std::cout << d[n] << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p383{
    using pii = std::pair<int, int>;
    const int N = 1e4 + 12, INF = 0x3f3f3f3f;
    int head[N], to[ N << 4 ], ne[ N << 4 ], cost[N << 4];
    int d[N], vi[N], mp[N], dp[N][2];
    int t, n, m, idx, be, ed;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dij(int s, int t){
        std::memset(d,  0x3f, sizeof d);
        std::memset(vi, 0x00, sizeof vi);
        d[s] = 0;
        std::priority_queue<pii> q;
        q.emplace(0, s);
        while(q.size()){
            int x = q.top().second;q.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] <= d[x] + cost[i])continue;
                d[y] = d[x] + cost[i];
                q.emplace(-d[y], y);
            }
        }
    }
    int _dp(){
        _dij(be, ed);
        for(int i=1; i<=n; ++i)mp[i] = i;
        std::sort(mp+1, mp+n+1, [&](int a, int b){
                return d[a] < d[b]; });
        dp[be][0] = 1;
        for(int j=1; j<=n; ++j){
            int x = mp[j];
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] == d[x] + cost[i]){
                    dp[y][0] += dp[x][0];
                    dp[y][1] += dp[x][1];
                }
                if(d[y] + 1 == d[x] + cost[i]){
                    dp[y][1] += dp[x][0];
                }
            }
        }
        return dp[ed][0] + dp[ed][1];
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            idx = 0;
            std::memset(head, 0, sizeof head);
            std::cin >> n >> m;
            for(int i=1, x, y, v; i<=m; ++i){
                std::cin >> x >> y >> v;
                _add(x, y, v);
            }
            std::cin >> be >> ed;
            std::cout << _dp() << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p382{
    const int N = 1024 << 4, INF = 0xcfcfcfcf;
    int head[N], ne[N << 2], to[ N << 2 ], edge[N << 2], cost[N << 2];
    int vi[N], d[N], pre[N], incf[N];
    int n, idx, ans, k;
    void _add(int x, int y, int z, int c){
        to[++idx] = y;
        cost[idx] = c;
        edge[idx] = z;
        ne[idx] = head[x];
        head[x] = idx;

        to[++idx] = x;
        cost[idx] = -c;
        edge[idx] = 0;
        ne[idx] = head[y];
        head[y] = idx;
    }
    bool _spfa(int s, int t){
        std::memset(d,  0xcf, sizeof d);
        std::memset(vi, 0x00, sizeof vi);
        std::queue<int> q;
        q.push(s);
        d[s] = 0;
        vi[s] = 1;
        incf[s] = 1 << 30;
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i])continue;
                if(d[y] >= d[x] + cost[i])continue;
                d[y] = d[x] + cost[i];
                pre[y] = i;
                incf[y] = std::min(incf[x], edge[i]);
                if(!vi[y])vi[y] = 1,q.push(y);
            }
        }
        return d[t] != INF;
    }
    void _update(int s, int t){
        int x = t;
        while(x != s){
            int i = pre[x];
            edge[i] -= incf[t];
            edge[i^1] += incf[t];
            x = to[i^1];
        }
        ans += d[t] * incf[t];
    }
    int _map(int i, int j, int f){
        return (i-1) * n + j + n * n * f;
    }
    void _deal(){
        idx = 1;
        std::cin >> n >> k;
        for(int i=1, c; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                std::cin >> c;
                _add(_map(i, j, 0), _map(i, j, 1), 1,  c);
                _add(_map(i, j, 0), _map(i, j, 1), k-1,  0);
                if(i<n)_add(_map(i, j, 1), _map(i+1, j, 0), k, 0);
                if(j<n)_add(_map(i, j, 1), _map(i, j+1, 0), k, 0);
            }
        }
        int be = 1, ed = 2 * n * n;
        while(_spfa(be, ed))_update(be, ed);
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p381{
    const int N = 128 << 1, INF = 0x3f3f3f3f;
    int head[N], ne[N << 4], to[ N << 4 ], edge[N << 4], e[N << 4];
    int d[N];
    int n, m, idx;
    void _add(int x, int y, int z){
        to[++idx] = y; e[idx] = z; ne[idx] = head[x]; head[x] = idx;
        to[++idx] = x; e[idx] = 0; ne[idx] = head[y]; head[y] = idx;
    }
    bool _bfs(int s, int t){
        std::memset(d, 0, sizeof d);
        d[s] = 1;
        std::queue<int> q;
        q.push(s);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i] || d[y])continue;
                d[y] = d[x] + 1;
                if(y == t)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int flow, int t){
        if(x == t)return flow;
        int rest = flow;
        for(int i=head[x]; rest && i; i=ne[i]){
            int y = to[i];
            if(!edge[i] || d[y] != d[x] + 1)continue;
            int k = _dinic(y, std::min(rest, edge[i]), t);
            if(k == 0)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _init(){
        std::memset(head, 0, sizeof head);
        std::memset(e, 0, sizeof e);
        idx = 1;
    }
    void _read(){
        char c;
        for(int i=1, x, y, mid;i<=m; ++i){
            std::cin >> c; std::cin >> x;
            std::cin >> c;
            std::cin >> c; std::cin >> y;
            ++x, ++y;
            _add(x+n, y, INF), _add(y+n, x, INF);
        }
        for(int i=1; i<=n; ++i) _add(i, i+n, 1);
    }
    int _calc(){
        int ans = INT_MAX;
        for(int be=n+1; be<=2*n; ++be){
            for(int ed=be-n-1; ed<=n; ++ed){
                std::memcpy(edge, e, sizeof e);
                int flow = 0, maxflow;
                while(_bfs(be, ed)){
                    while((flow=_dinic(be, INF, ed)))maxflow += flow;
                }
                ans = std::min(ans, maxflow);
            }
        }
        return ans;
    }
    void _deal(){
        while(std::cin >> n >> m){
            _init();
            _read();
            std::cout << _calc() << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p380{
    const int N = 3e5 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N], to[N], edge[N];
    int h1[N], ne1[N], to1[N];
    int low[N], dfn[N], d[N];
    int n, m, t, idx, idx1;
    int dcc, tp, code;
    int co[N], st[N], vi[N], res[N];
    int be, ed;

    void _add(int x, int y, int z){
        to[++idx] = y;
        edge[idx] = z;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _add1(int x, int y){
        to1[++idx1] = y;
        ne1[idx1] = h1[x];
        h1[x] = idx1;
    }
    bool _bfs(int s, int t){
        std::memset(d, 0, sizeof d);
        d[s] = 1;
        std::queue<int> q;
        q.push(s);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!edge[i] || d[y])continue;
                d[y] = d[x] + 1;
                if(y == t)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int flow, int t){
        if(x == t)return flow;
        int rest = flow;
        for(int i=head[x]; rest && i; i=ne[i]){
            int y = to[i];
            if(d[y] != d[x] + 1 || !edge[i])continue;
            int k = _dinic(y, std::min(rest, edge[i]), t);
            if(k==0)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        vi[x] = 1, st[++tp] = x;
        for(int i=h1[x]; i; i=ne1[i]){
            int y = to1[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(dfn[x] != low[x])return;
        ++dcc;int y;
        do y=st[tp--], vi[y] = 0, co[y]=dcc; while(x!=y);
    }
    void _read(){
        std::cin >> n >> m >> t;
        be = n + m + 1, ed = be + 1;
        idx = idx1 = 1;
        for(int i=1, x, y; i<=t; ++i){
            std::cin >> x >> y;
            _add(x, y+n, 1), _add(y+n, x, 0);
        }
        for(int i=1; i<=n; ++i)_add(be, i, 1), _add(i, be, 0);
        for(int i=1; i<=m; ++i)_add(i+n, ed, 1), _add(ed, i+n, 0);
    }
    void _deal(){
        _read();
        while(_bfs(be, ed)){
            while(_dinic(be, INT_MAX, ed));
        }
        for(int i=2; i<=idx; ++i){
            if(!edge[i]) _add1(to[i], to[i^1]); 
        }
        for(int i=be; i<=ed; ++i){
            if(!dfn[i])_tarjan(i);
        }
        int ans = 0;
        for(int i=1; i<=t; ++i){
            int id = i << 1;
            if(!edge[id] || co[to[id]] == co[to[id^1]])continue;
            res[++ans] = i;
        }
        std::cout << ans << std::endl;
        for(int i=1; i<=ans; ++i)std::cout << res[i] << " ";
        std::cout << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace _dinic{
    const int N = 1e5, INF = 0x3f3f3f3f;
    int head[N], edge[N << 2], ne[N << 2], to[N << 2];
    int d[N];
    int n, m, idx;
    void _add(int x, int y, int z){
        to[++idx] = y, edge[idx] = z;
        ne[idx] = head[x], head[x] = idx;
        to[++idx] = x, edge[idx] = 0;
        ne[idx] = head[y], head[y] = idx;
    }
    bool _bfs(int s, int t){
        std::memset(d, 0, sizeof d);
        std::queue<int> q;
        q.push(s);
        d[s] = 1;
        while(q.size()){
            int x  = q.front(); q.pop();
            for(int i=head[x]; i; i=ne[i]){
                if(!edge[i])continue;
                int y = to[i];
                if(d[y])continue;
                d[y] = d[x] + 1;
                if(y == t)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _dinic(int x, int flow, int t){
        if(x == t)return flow;
        int rest = flow;
        for(int i=head[x], k; i; i=ne[i]){
            int y = to[i];
            if(!edge[i] || d[y] != d[x] + 1)continue;
            k = _dinic(y, std::min(flow, edge[i]), t);
            if(k == 0)d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
        return flow - rest;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1, x, y, z; i<=m; ++i){
            std::cin >> x >> y >> z;
            _add(x, y, z);
        }
        int flow = 0, ans = 0;
        while(_bfs(1, n)){
            while((flow = _dinic(1, INF, n)))ans += flow;
        }
        std::cout << ans << std::endl;
    }
};
namespace ek{
    const int N = 1e5, INF = 0x3f3f3f3f;
    int head[N], edge[N << 2], to[N << 2], ne[N << 2];
    int pre[N << 2], incf[N << 2], vi[N << 2];
    int n, m, idx;
    void _add(int x, int y, int c){
        to[++idx] = y, edge[idx] = c, ne[idx] = head[x], head[x] = idx;
        to[++idx] = x, edge[idx] = 0, ne[idx] = head[y], head[y] = idx;
    }
    bool _bfs(int s, int t){
        std::queue<int> q;
        q.emplace(s);
        vi[s] = 0;
        incf[s] = INF;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                if(!edge[i])continue;
                int y = to[i];
                if(vi[y])continue;
                vi[y] = 1;
                incf[y] = std::min(incf[x], edge[i]);
                pre[y] = i;
                if(y == t)return true;
                q.push(y);
            }
        }
        return false;
    }
    int _update(int s, int t){
        int ans = incf[t];
        while(s != t){
            int i = pre[t];
            incf[i] -= edge[t];
            incf[i^1] += edge[t];
            t = to[i ^ 1];
        }
        return ans;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0, x, y, c; i<=m; ++i){
            std::cin >> x >> y >> c;
            _add(x, y, c);
        }
        int ans = 0;
        while(_bfs(1, n))ans += _update(1, n);
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();;
        return 0;
    }
};
namespace p379{
    const int N = 256;
    int n, m;
    int e[N][N], vi[N], match[N];
    int succ[N], hide[N];
    void _read(){
        std::cin >> n >> m;
        for(int i=0, x, y; i<m; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
    }
    void _floyd(){
        for(int k=1; k<=n; ++k){
            for(int i=1; i<=n; ++i){
                for(int j=1; j<=n; ++j){
                    e[i][j] |= e[i][k] && e[k][j];
                }
            }
        }
        for(int i=1; i<=n; ++i)e[i][i] = 0;
    }
    bool _dfs(int x){
        for(int y=1; y<=n; ++y){
            if(!e[x][y] || vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        _read();
        _floyd();
        int ans = n;
        for(int i=1; i<=n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans -= _dfs(i);
        }
        //for(int i=1; i<=n; ++i){
            //std::cout << match[i] << "   ";
        //}
        for(int i=1; i<=n; ++i)succ[match[i]] = 1;
        for(int i=1,t=0; i<=n; ++i){
            if(!succ[i]) hide[++t] = i;
        }
        std::memset(vi, 0, sizeof vi);
        int f = 1;
        while(f){
            f = 0;
            for(int i=1; i<=ans; ++i){
                for(int j=1; j<=n; ++j){
                    vi[j] |= e[hide[i]][j];
                }
            }
            for(int i=1; i<=ans; ++i){
                if(vi[hide[i]]){
                    f = 1;
                    while(vi[hide[i]])hide[i] = match[hide[i]];
                }
            }
        }
        for(int i=1; i<=ans; ++i)std::cout << hide[i] << "  ";
        std::cout << std::endl;
        //for(int i=1; i<=ans; ++i)std::cout << hide[i] << "  ";
        //std::cout << std::endl;
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p378_better{
    using pii = std::pair<int,int>;
    const int N = 128;
    const int fun[9] {-2, -1, 2, -1, -2, 1, 2, 1, -2};
    int vi[N][N];
    pii match[N][N] ;
    int n, m, k;
    int e[N][N];
    bool _valid(int x, int y){
        return x>=1 && y>=1 && x<=n && y<=m;
    }
    bool _dfs(int x, int y){
        for(int i=0; i<8; ++i){
            int x1 = x + fun[i], y1 = y + fun[i + 1];
            if(!_valid(x1, y1) || e[x1][y1])continue;
            if(vi[x1][y1])continue;
            vi[x1][y1] = 1;
            auto [mx, my] = match[x1][y1];
            if(!mx || _dfs(mx, my)){
                match[x1][y1] = {x, y};
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> m >> k;
        for(int i=0, x, y; i<k; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
        int ans = n * m - k;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j] || (i + j)&1)continue;
                std::memset(vi, 0, sizeof vi);
                ans -= _dfs(i, j);
            }
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p378{
    const int N = 128;
    const int fun[9] {-2, -1, 2, -1, -2, 1, 2, 1, -2};
    int head[N << 12], ne[N << 12], to[N << 12];
    int match[N << 12], vi[N << 12];
    int n, m, k, idx;
    int e[N][N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _read(){
        std::cin >> n >> m >> k;
        for(int i=0, x, y; i<k; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
    }
    bool _valid(int x, int y){
        return x>=1 && y>=1 && x<=n && y<=m;
    }
    bool _dfs(int x){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        _read();
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if((i+j) & 1 || e[i][j])continue;
                for(int f=0; f<8; ++f){
                    int x = i + fun[f], y = j + fun[f+1];
                    if(!_valid(x, y) || e[x][y])continue;
                    _add(i*n+j, x*n+y);
                }
            }
        }
        int ans = n * m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if((i+j) & 1 || e[i][j])continue;
                std::memset(vi, 0, sizeof vi);
                ans -= _dfs(i*n+j);
            }
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace ptest{
    const int N = 128;
    int e[N][N], match[N], vi[N];
    int n, m;
    bool _dfs(int x){
        for(int y=n; y<n*2; ++y){
            if(vi[y] || !e[x][y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin  >> n >> m;
        for(int i=0, x, y; i<m; ++i){
            std::cin >> x >> y;
            e[x][y+n] = 1;
        }
        int ans = 0;
        for(int i=0; i<n; ++i){
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
        for(int i=0; i<n; ++i){ std::cout << match[i] << "     "; }
        std::cout << std::endl;
        for(int i=n; i<n+n; ++i){ std::cout << match[i] << "     "; }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p377{
    using pii = std::pair<int,int>;
    const int N = 2048;
    int n, m, code, sn;
    char e[N][N];
    int g[N << 1][N << 1];
    int mp[N][N], mp1[N][N], match[N << 1], vi[N << 1];
    bool _dfs(int x){
        for(int y=1; y<=code; ++y){
            if(vi[y] || !g[x][y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> n >> m;
        int code1 = 0, code2 = 0;
        for(int i=0; i<n; ++i)std::cin >> e[i];
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                if(e[i][j] == '.')continue;
                if(j && e[i][j-1] == '*'){
                    mp[i][j] = mp[i][j-1];
                }else{
                    mp[i][j] = ++code1;
                }
                if(i && e[i-1][j] == '*'){
                    mp1[i][j] = mp1[i-1][j];
                }else{
                    mp1[i][j] = ++code2;
                }
            }
        }
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                if(e[i][j] == '.')continue;
                g[mp[i][j]][mp1[i][j]] = 1;
            }
        }
        code = std::max(code1, code2);
    }
    void _deal(){
        _read();
        int ans = 0;
        for(int i=1; i<=code; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p376{
    using pii = std::pair<int, int>;
    const int N = 256;
    int n, m, k, f;
    int e[N][N], match[N], vi[N];
    bool _dfs(int x){
        for(int y=0; y<m; ++y){
            if(vi[y] || !e[x][y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> m >> k;
        std::memset(e, 0, sizeof e);
        std::memset(match, 0, sizeof match);
        for(int i=0, a, b, c; i<k; ++i){
            std::cin >> a >> b >> c;
            if(!b || !c)continue;
            e[b][c] = e[c][b] = 1;
        }
    }
    bool _deal(){
        std::cin >> n;
        if(!n)return false;
        _read();
        int ans = 0;
        for(int i=1; i<n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p375{
    using pii = std::pair<int, int>;
    const double ESP  = 1e-10;
    const int N = 128;
    double la[N], lb[N], upd[N];
    int va[N], vb[N], match[N];
    double e[N][N];
    pii a[N], b[N];
    int n, ans[N];
    bool _dfs(int x){
        va[x] = 1;
        for(int y=1; y<=n; ++y){
            if(vb[y])continue;
            double rs = la[x] + lb[y] - e[x][y];
            if(fabs(rs) < ESP){
                vb[y] = 1;
                if(!match[y] || _dfs(match[y])){
                    match[y] = x;
                    return true;
                }
            }else{
                upd[y] = std::min(upd[y], la[x] + lb[y] - e[x][y]);
            }
        }
        return false;
    }
    void _km(){
        for(int i=1; i<=n; ++i){
            la[i] = -( 1 << 30 );
            lb[i] = 0;
            for(int j=1; j<=n; ++j){
                la[i] = std::max(la[i], e[i][j]);
            }
        }
        for(int i=1; i<=n; ++i){
            while(true){
                std::memset(va, 0, sizeof va);
                std::memset(vb, 0, sizeof vb);
                for(int j=1; j<=n; ++j)upd[j] = 1e10;
                if(_dfs(i))break;
                double delta = 1e10;
                for(int j=1; j<=n; ++j){
                    if(vb[j])continue;
                    delta = std::min(delta, upd[j]);
                }
                for(int j=1; j<=n; ++j){
                    if(va[j])la[j] -= delta;
                    if(vb[j])lb[j] += delta;
                }
            }
        }
        for(int i=1; i<=n; ++i)ans[match[i]] = i;
        for(int i=1; i<=n; ++i)std::cout << ans[i] << std::endl;
    }
    double _dis(int i, int j){
        auto [x1, y1] = a[i];
        auto [x2, y2] = b[j];
        return sqrt((x1-x2)*(x1-x2)*1.0 +
                    (y1-y2)*(y1-y2)*1.0);
    }
    void _read(){
        std::cin >> n;
        for(int i=1; i<=n; ++i){
            std::cin >> a[i].first >> a[i].second;
        }
        for(int i=1; i<=n; ++i){
            std::cin >> b[i].first >> b[i].second;
        }
        for(int i=1; i <=n; ++i){
            for(int j=1; j<=n; ++j){
                e[i][j] = -_dis(i, j);
            }
        }
    }
    void _deal(){
        _read();
        _km();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p374_{
    using pii = std::pair<int, int>;
    const int N = 64;
    const double EPS = 1e-8;
    int n, m, k;
    double t1, t2, v;
    int match[N * N], vi[ N * N ];
    pii pos1[N], pos2[N];
    void _read(){
        std::cin >> n >> m >> t1 >> t2 >> v;
         t1 /= 60;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            pos2[i] = {x, y};
        }
        for(int i=1, x, y; i<=n; ++i){
            std::cin >> x >> y;
            pos1[i] = {x, y};
        }
    }
    double _dis(int a, int b){
        auto [x1, y1] = pos2[a];
        auto [x2, y2] = pos1[b];
        return sqrt((x1-x2)*(x1-x2) +
                    (y1-y2)*(y1-y2));
    }
    bool _dfs(int x, double m){
        for(int i=1; i<=n*k; ++i){
            if(vi[i])continue;
            if(_dis(x, (i-1)/k + 1) > v * (m-(i-1)%k*(t1+t2)-t1) )continue;
            vi[i] = 1;
            if(!match[i] || _dfs(match[i], m)){
                match[i] = x;
                return true;
            }
        }
        return false;
    }
    bool _check(double mid){
        k = std::min((mid + t2) / (t1 + t2), 50.0);
        std::memset(match, 0, sizeof match);
        for(int i=1; i<=m; ++i){
            std::memset(vi, 0, sizeof vi);
            if(!_dfs(i, mid))return false;
        }
        return true;
    }
    double _b_search(){
        double l = 0, r = 5e6;
        while((r-l) > EPS){
            double m = (l + r) / 2;
            if(_check(m)){
                r = m;
            }else{
                l = m;
            }
        }
        return l;
    }
    void _deal(){
        _read();
        printf("%.6lf", _b_search());
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
}
namespace p374{
    const int N = 256;
    int head[N], to[N << 8], ne[N << 8];
    int vi[N << 8], match[N << 8];
    int n, m, t, idx;
    int e[N][N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x){
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> m >> t;
        for(int i=1, x, y; i<=t; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j])continue;
                _add(i, j+n);
            }
        }
        int ans = 0;
        for(int i=1; i<=n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p373{
    const int N = 128 << 7;
    const int fun[5] {0, 1, 0, -1, 0};
    int head[N], ne[N << 1],  to[N << 1];
    int match[N], vi[N];
    int n, t, idx;
    int e[128][128];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x){
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    bool _valid(int x, int y){
        return x>0 && y>0 && x<=n && y<=n;
    }
    void _deal(){
        std::cin >> n >> t;
        for(int i=0, x, y; i<t; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if((i+j) & 1 || e[i][j] == 1)continue;
                for(int f=0; f<4; ++f){
                    int x = i + fun[f], y = j + fun[f + 1];
                    if(!_valid(x, y))continue;
                    if(e[x][y] == 1)continue;
                    _add(i*n+j, x*n+y);
                }
            }
        }
        int ans = 0;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if((i+j) & 1 || e[i][j] == 1)continue;
                std::memset(vi, 0, sizeof vi);
                ans += _dfs(i * n + j);
            }
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p372{
    const int N = 1e5 + 12;
    int head[N], ne[N << 2], to[N << 2], cost[N << 2];
    int color[N];
    int n, m, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x, int co, int mid){
        color[x] = co;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(cost[i] <= mid)continue;
            if(!color[y]){
                if(!_dfs(y, 3 - co, mid))return false;
            }else if(color[y] == color[x]){
                return false;
            }
        }
        return true;
    }
    bool _check(int m){
        std::memset(color, 0, sizeof color);
        for(int i=1; i<n; ++i){
            if(!color[i] && !_dfs(i, 1, m))return false;
        }
        return true;
    }
    int _b_search(){
        if(m==1)return 0;
        int l = 0, r = 1e9 + 1;
        while(l < r){
            int m = l + ((r - l) >> 1);
            if(_check(m)){
                r = m;
            }else{
                l = m + 1;
            }
        }
        return r;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0, x, y, v; i<m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        std::cout << _b_search() << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p371{
    const int N = 1024 << 1;
    struct node { int s, t, v; } nodes [N];
    int head[N], ne[N << 11], to[N << 11];
    int low[N], dfn[N], st[N], vi[N], co[N], mp[N], val[N];
    int n, idx, code, tp, sn;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _valid(int s1, int s2, int t1, int t2) {
        return s2>t1 && t2>s1;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        vi[x] = 1,st[++tp] = x;
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] != dfn[x])return;
        ++sn;int y;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = sn;
        }while(x!=y);
    }
    void _sd(){
        for(int i=0; i<2*n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=0; i<n; ++i){
            if(co[i] == co[i+n]){
                std::cout << "NO" << std::endl;
                return;
            }
        }
        std::cout << "YES" << std::endl;
        for(int i=0; i<n; ++i){
            auto [s, e, t] = nodes[i];
            if(co[i] < co[i+n]){
                printf("%02d:%02d %02d:%02d\n",
                    s/60, s%60, (s+t)/60, (s+t)%60
                 );
            }else{
                printf("%02d:%02d %02d:%02d\n",
                    (e-t)/60,(e-t)%60, (e)/60, (e)%60
                 );
            }
        }
    }
    void _read(){
        std::string s, t, l;
        std::string s1, s2, t1, t2;
        int i1, i2;
        std::cin >> n;
        for(int i=0; i<n; ++i){
            std::cin >> s >> t >> l;
            i1 = s.find(':'), i2 = t.find(':');
            s1 = {s.begin(), s.begin() + i1};
            t1 = {t.begin(), t.begin() + i2};
            s2 = s.substr(i1 + 1), t2 = t.substr(i2 + 1);
            nodes[i] = {
                std::stoi(s1) * 60 + std::stoi(s2),
                std::stoi(t1) * 60 + std::stoi(t2),
                std::stoi(l)
            };
        }
        for(int i=0; i<n; ++i){
            auto [s1, e1, t1] = nodes[i];
            for(int j=0; j<n; ++j){
                auto [s2, e2, t2] = nodes[j];
                if(i == j)continue;
                if(_valid(s1, s1+t1, s2, s2+t2))_add(i, j+n), _add(j, i+n);
                if(_valid(s1, s1+t1, e2-t2, e2))_add(i, j), _add(j+n, i+n);
                if(_valid(e1-t1, e1, s2, s2+t2))_add(i+n, j+n), _add(j, i);
                if(_valid(e1-t1, e1, e2-t2, e2))_add(i+n, j), _add(j+n, i);
            }
        }
    }
    void _deal(){
        _read();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p370{
    const int N = 1024;
    int head[N << 1], ne[ N * N << 2], to[ N * N << 2 ];
    int low[N << 1], dfn[N << 1], st[N << 1], vi[N << 1], co[ N << 1 ];
    int n, m, idx, code, tp, sn;
    std::string op;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        st[++tp] = x;
        vi[x] = 1;
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] != dfn[x])return;
        ++sn;int y;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = sn;
        }while(x !=y);
    }
    void _sd(){
        for(int i=0; i<2*n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int i=0; i<n; ++i){
            if(co[i] == co[i+n]){
                std::cout << "NO" << std::endl;
                return;
            }
        }
        std::cout << "YES" << std::endl;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v >> op;
            if(op[0] == 'A'){
                if(v){
                    _add(x+n, x), _add(y+n, x);
                }else{
                    _add(x, y+n), _add(y, x+n);
                }
            }else if(op[0] == 'X'){
                if(v){
                    _add(x, y+n), _add(y, x+n);
                    _add(y+n, x), _add(x+n, y);
                }else{
                    _add(x, y), _add(y, x);
                    _add(x+n, y+n), _add(y+n, x+n);
                }
            }else{
                if(v){
                    _add(x+n, y), _add(y+n, x);
                }else{
                    _add(x, x+n), _add(y, y+n);
                }
            }
        }
    }
    void _deal(){
        _read();
        _sd();
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p369{
    using ll = long long;
    const int N = 1e5 + 12, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    int h1[N], to1[N << 1], ne1[N << 1], cost1[N << 1];
    int h2[N], to2[N << 1], ne2[N << 1], cost2[N << 1];
    ll f1[N], f2[N], d1[N], d2[N], sum1[N], sum2[N];
    int in1[N], in2[N], dis[N], pre[N], bri[N];
    int l, n, m, S, T, q;
    int idx, len;
    int pa[N];
    void _add(int x, int y ,int v){
        to1[++idx] = y;
        cost1[idx] = v;
        ne1[idx] = h1[x];
        h1[x] = idx;

        to2[idx] = x;
        cost2[idx] = v;
        ne2[idx] = h2[y];
        h2[y] = idx;
    }
    void _topsort(ll *f, int *head, int *to, int *ne,
                   int *cost, int *mk, int s){
        std::queue<int> q;
        f[s] = 1;
        if(s==S)dis[s] = 0;
        for(int i=1; i<=n; ++i){
            if(!mk[i])q.push(i);
        }
        q.push(s);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                f[y] = (f[y] + f[x]) % MOD;
                if(!--mk[y])q.push(y);
                if(s==S && dis[y] > dis[x] + cost[i]){
                    dis[y] = dis[x] + cost[i];
                    pre[y] = i;
                }
            }
        }
    }
    void _getpath(int i){
        for(i=pre[i]; to1[i]; i=pre[to2[i]])pa[len++] = i;
        pa[++len] = i;
        std::reverse(pa, pa+len);
        for(int i=0; i<len; ++i){
            int id = pa[i];
            int x = to2[id], y = to1[id];
            bri[id] = (f1[x] * f2[y]) % MOD == f1[T] % MOD;
            sum1[i+1] += sum1[i] + bri[id] * cost1[id];
            sum2[i+1] += sum2[i] + cost1[id];
        }
    }
    void _init(){
        idx = len = 0;
        std::memset(sum1, 0, sizeof sum1);
        std::memset(sum2, 0, sizeof sum2);
        std::memset(d1, 0, sizeof d1);
        std::memset(d2, 0, sizeof d2);
        std::memset(in1, 0, sizeof in1);
        std::memset(in2, 0, sizeof in2);
        std::memset(h1, 0, sizeof h1);
        std::memset(h2, 0, sizeof h2);
        std::memset(f1, 0, sizeof f1);
        std::memset(f2, 0, sizeof f2);
        std::memset(dis, 0x3f, sizeof dis);
        std::memset(pre, 0, sizeof pre);
        std::memset(bri, 0, sizeof bri);
        std::memset(pa, 0, sizeof pa);
    }
    void _read(){
        std::cin >> n >> m >> S >> T >> q;
        ++S, ++T;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(++x, ++y, v);
            ++in1[y], ++in2[x];
        }
    }
    int _dp(){
        int k = 1;
        for (int i = 2; i <= len; i++) {
            d1[i] = std::min(sum1[i], d1[i - 1] + sum1[i] - sum1[i - 1]);
            while (k + 1 <= i && sum2[i] - sum2[k] > q) k++;
            d1[i] = std::min(d1[i], sum1[k] - (sum1[k] > sum1[k-1] ? q - (sum2[i] - sum2[k]) : 0));
        }
        d1[1] = d2[len] = 0, k = len;
        for (int i = len - 1; i; i--) {
            d2[i] = std::min(sum1[len] - sum1[i], d2[i + 1] + sum1[i + 1] - sum1[i]);
            while (k - 1 >= i && sum2[k] - sum2[i] > q) k--;
            d2[i] = std::min(d2[i], sum1[len] - sum1[k] - (sum1[k+1] > sum1[k] ? q - (sum2[k] - sum2[i]): 0));
        }
        ll ans = 2e9;
        for (int i = 1; i <= len; i++) ans = std::min(ans, d1[i] + d2[i]);
        k = 1;
        for (int i = 2; i <= len; i++) {
            while (k + 1 <= i && sum2[i] - sum2[k] > 2 * q) k++;
            ans = std::min(ans, sum1[len] - sum1[i] + sum1[k] - (bri[k] ? 2 * q - (sum2[i] - sum2[k]) : 0));
        }
        return ans;
    }
    void _deal(){
        std::cin >> l;
        while(l--){
            _init();
            _read();
            _topsort(f1, h1, to1, ne1, cost1, in1, S);
            if(dis[T] == INF){
                std::cout << -1 << std::endl;
                continue;
            }
            _topsort(f2, h2, to2, ne2, cost2, in2, T);
            _getpath(T);
            std::cout << _dp() << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
    int dp(){
        int k = 1;
        for(int i=2; i<=len; ++i){
            while(sum2[i] - sum2[k] > q)++k;
            d1[i] = std::max(d1[i-1],
                sum1[i] - sum1[k] +
                (sum1[k-1]==sum1[k] ? 0 : q-(sum2[i]-sum2[k])) 
            );
        }
        k = len;
        for(int i=len-1; i>=1; --i){
            while(sum2[k]-sum2[i] > q)--k;
            d2[i] = std::max(d2[i+1],
                    sum1[k] - sum1[i] +
                    ((sum1[k+1]<=sum1[k]) ? 0 :q-(sum2[k]-sum2[i]))
            );
        }
        ll ans = 0;
        for(int i=1; i<=len; ++i)ans = std::max(ans, d1[i] + d2[i]);
        return sum1[len] - ans;
    }
};

//368. 银河
namespace p3688{
    const int N = 1e5 + 12;
    int head[N], to[N << 2], ne[N << 2], cost[N << 2];
    int ch[N], cne[N << 2], cto[N << 2], cc[N << 2];
    int low[N], dfn[N], st[N], vi[N], co[N], in[N], d[N];
    int n, m, idx, cidx, code, tp, dn;
    long long  ans = -1;
    std::vector<int> dcc[N];
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _add_c(int x, int y, int v){
        cto[++cidx] = y;
        cc[cidx] = v;
        cne[cidx] = ch[x];
        ch[x] = cidx;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        vi[x] = 1;
        st[++tp] = x;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] != dfn[x])return;
        ++dn; int y;
        do{
            y = st[tp--];
            vi[y] = 0;
            co[y] = dn;
            dcc[dn].emplace_back(y);
        }while(x != y);
    }
    bool _dfs(int x){
        vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(co[x] == co[y] && cost[i])return false;
            if(vi[y])continue;
            if(!_dfs(y))return false;
        }
        return true;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1, x, y, t; i<=m; ++i){
            std::cin >> t >> x >> y;
            if(t == 1){
                _add(x, y, 0);
                _add(y, x, 0);
            }else if(t == 2){
                _add(x, y, 1);
            }else if(t == 3){
                _add(y, x, 0);
            }else if(t == 4){
                _add(y, x, 1);
            }else{
                _add(x, y, 0);
            }
        }
        for(int i=1; i<=n; ++i)_add(0, i, 1);
    }
    void _sd(){
        for(int i=0; i<=n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        std::memset(vi, 0, sizeof vi);
        for(int i=0; i<=n; ++i){
            if(!vi[i] && !_dfs(i))return ;
        }
        for(int x=0; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(co[x] == co[y])continue;
                _add_c(co[x], co[y], cost[i]);
                ++in[co[y]];
            }
        }
        ans = 0;
        for(int x=dn; x>=1; --x){
            for(int i=ch[x]; i; i=cne[i]){
                int y = cto[i];
                d[y] = std::max(d[y], d[x] + cc[i]);
            }
        }
        for(int i=1; i<=dn; ++i)ans += (long long)d[i] * dcc[i].size();
    }
    void _deal(){
        _read();
        _sd();
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
    long long _topsort(){
        long long res = 0;
        std::queue<int> q;
        for(int i=1; i<=dn; ++i){
            if(!in[i])q.emplace(i);
        }
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=ch[x]; i; i=cne[i]){
                int y = cto[i];
                if(!--in[y]){
                    q.emplace(y);
                    d[y] = d[x] + cc[i];
                }
            }
        }
        for(int i=1; i<=dn; ++i)res += (long long)d[i] * dcc[i].size();
        return res;
    }
};
namespace p368{
    const int N = 128;
    int head[N], ne[N << 7], to[N << 7];
    int ch[N], cne[N << 7], cto[N << 7], in[N], out[N];
    int low[N], dfn[N], st[N << 1], vi[N], co[N];
    int n, m, idx, cidx, code, tp, dn;
    int p, q;
    std::vector<int> dcc[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y;
        cne[cidx] = ch[x];
        ch[x] = cidx;
    }
    void _read(){
        std::cin >> n;
        for(int i=1, x; i<=n; ++i){
            while(std::cin >> x, x){
                _add(i, x);
            }
        }
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        st[++tp] = x;
        vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
            }else if(vi[y]){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(low[x] != dfn[x]) return;
        ++dn; int y;
        do{
            y = st[tp--];
            dcc[dn].emplace_back(y);
            co[y] = dn;
            vi[y] = 0;
        }while(x != y);
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i);
        }
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(co[x] == co[y])continue;
                _add_c(co[x], co[y]);
                ++in[co[y]];
                ++out[co[x]];
            }
        }
        for(int i=1; i<=dn; ++i){
            if(!in[i])++q;
            if(!out[i])++p;
        }
    }
    void _deal(){
        _read();
        _sd();
        std::cout << p << std::endl;
        std::cout << (dn==1 ? 0 : std::max(p, q)) << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p367{
    const int N = 1e4 + 12;
    int head[N], to[N << 4], ne[N << 4];
    int st[N << 4], ans[N << 4], vi[N << 4];
    int n, m, idx, tp, dn;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _euler(){
        st[++tp] = 1;
        while(tp){
            int x = st[tp];
            int i = head[x];
            while(i && vi[i])i=ne[i];
            if(i){
                st[++tp] = to[i];
                head[x] = ne[i];
                vi[i] = vi[i ^1] = 1;
            }else{
                --tp;
                ans[dn++] = x;
            }
        }
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0, x, y; i<m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _euler();
        for(int i=dn-1; i>=0; --i)std::cout << ans[i] << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p365{
    const int N = 2048;
    int hate[N][N];
    int head[N], ne[N*N], to[N*N];
    int low[N], dfn[N], st[N], cut[N], co[N], color[N];
    std::vector<int> dcc[N];
    int res[N];
    int n, m, idx, cidx, code, tp, root, dn, ans;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        st[++tp] = x;
        if(x == root && head[x] == 0){
            dcc[++dn].emplace_back(x);
            return ;
        }
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
                if(low[y] < dfn[x])continue;
                ++dn;
                int t;
                do{
                    t = st[tp--];
                    dcc[dn].emplace_back(t);
                }while(t != y);
                dcc[dn].emplace_back(x);
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _init(){
        for(int i=1; i<=dn; ++i)dcc[i].clear();
        cidx = idx = 1;
        ans = tp = dn = code = 0;
        std::memset(head, 0, sizeof head);
        std::memset(hate, 0, sizeof hate);
        std::memset(res, 0, sizeof res);
        std::memset(co, 0, sizeof co);
        std::memset(dfn, 0, sizeof dfn);
    }
    void _read(){
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            hate[x][y] = hate[y][x] = 1;
        }
        for(int i=1; i<=n; ++i){
            for(int j=i+1; j<=n; ++j){
                if(hate[i][j])continue;
                _add(i, j), _add(j, i);
            }
        }
    }
    bool _dfs(int x, int cl){
        color[x] = cl;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(co[y] != co[x])continue;
            if(color[y] == color[x])return true;
            if(color[y])continue;
            if(_dfs(y, 3 - cl))return true;
        }
        return false;
    }
    void _calc(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(root=i);
        }
        for(int i=1; i<=dn; ++i){
            for(auto &x : dcc[i]){
                co[x] = i;
                color[x] = 0;
            }
            if(!_dfs(dcc[i][0], 1))continue;
            for(auto &x : dcc[i])res[x] = 1;
        }
        for(int i=1; i<=n; ++i)ans += !res[i];
    }
    bool _deal(){
        std::cin >> n >> m;
        if(!n && !m)return false;
        _init();
        _read();
        _calc();
        std::cout << ans << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        while(_deal());
        return 0;
    }

    int ch[N], cne[N*N], cto[N*N], new_id[N];
    void _add_c(int x, int y){
        cto[++cidx] = y;
        cne[cidx] = ch[x];
        ch[x] = cidx;
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(root=i);
        }
        int num = idx;
        for(int i=1; i<=idx; ++i){
            if(cut[i])new_id[i] = ++num;
        }
        for(int i=1; i<=dn; ++i){
            for(auto &x : dcc[i]){
                if(cut[x]){
                    _add_c(i, new_id[x]);
                    _add_c(new_id[x], i);
                }else{
                    co[x] = i;
                }
            }
        }
    }
};
namespace p364{
    const int N = 1e5 + 12;
    int head[N], to[N << 2], ne[N << 2];
    int ch[N], cto[N << 1], cne[N << 1];
    int co[N], low[N], dfn[N], bridge[N << 2];
    int fa[N][32], d[N], f[N];
    int n, m, q, t, idx, code, color;
    int cidx, k;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _add_c(int x, int y){
        cto[++cidx] = y;
        cne[cidx] = ch[x];
        ch[x] = cidx;
    }
    void _tarjan(int x, int in_e){
        low[x] = dfn[x] = ++code;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y, i);
                low[x]  = std::min(low[x], low[y]);
                if(low[y] > dfn[x])bridge[i] = bridge[i^1] = 1;
            }else if(i != (in_e ^ 1)){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _dfs(int x){
        co[x] = color;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(co[y] || bridge[i])continue;
            _dfs(y);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _dfs(int x, int p){
        fa[x][0] = p;
        d[x] = d[p] + 1;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
        }
        for(int i=ch[x]; i; i=cne[i]){
            int y = cto[i];
            if(y == p)continue;
            _dfs(y, x);
        }
    }
    void _init(){
        cidx = idx = 1;
        color = code = 0;
        t = (int)(log(n) / log(2)) + 1;
        std::memset(dfn, 0, sizeof dfn);
        std::memset(head, 0, sizeof head);
        std::memset(ch, 0, sizeof ch);
        std::memset(co, 0, sizeof co);
        std::memset(d, 0, sizeof d);
        std::memset(bridge, 0, sizeof bridge);
        for(int i=1; i<=n; ++i)f[i] = i;
    }
    void _read(){
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        std::cin >> q;
    }
    void _sd(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(i, 0);
        }
        for(int i=1; i<=n; ++i){
            if(!co[i])++color, _dfs(i);
        }
        for(int i=2; i<=idx; ++i){
            int x = to[i ^ 1], y = to[i];
            if(co[x] != co[y])_add_c(co[x], co[y]);
        }
    }
    int _f(int x) {return x==f[x] ? x : f[x] = _f(f[x]); }
    bool _deal(){
        std::cin >> n >> m;
        if(!n && !m)return false;
        _init();
        _read();
        _sd();
        _dfs(1, 0);
        int ans = cidx / 2;
        std::cout << "Case " << ++k << ":" << std::endl;
        for(int i=1, x, y; i<=q; ++i){
            std::cin >> x >> y;
            x = _f(co[x]), y = _f(co[y]);
            int lca = _lca(x, y);
            while(d[x] > d[lca])--ans, f[x]=fa[x][0], x=_f(x);
            while(d[y] > d[lca])--ans, f[y]=fa[y][0], y=_f(y);
            std::cout << ans << std::endl;
        }
        std::cout << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace vdcc{
    const int N = 1e5 + 12;
    int head[N], to[N<<1], ne[N<<1], cost[N << 1]; 
    int low[N], dfn[N], cut[N];
    int st[N];
    std::vector<int> dcc[N];
    int n, m, idx = 1, dn, sn, code;
    int root, num;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _tarjan(int x){
        low[x] = dfn[x] = ++code;
        st[++sn] = x;
        if(x==root && !head[x]){
            dcc[dn++].emplace_back(x);
            return ;
        }
        int f = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                low[x] = std::min(low[x], low[y]);
                if(low[y] < dfn[x])continue;
                if(++f>1 || x!=root)cut[x] = 1;
                ++dn;
                int t;
                do{
                    t = st[sn--];
                    dcc[dn].emplace_back(t);
                }while(t != y);
                dcc[dn].emplace_back(x);
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _v_dcc(){
        std::cin >> n >> m;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        for(int i=1; i<=n; ++i){
            if(!dfn[i])_tarjan(root=i);
        }
    }
    int new_id[N], nn = 1, ch[N], cto[N], cne[N], color[N];
    void _add_c(int x, int y){
        cto[++nn] = y;
        ne[nn] = ch[x];
        ch[x] = nn;
    }
    void _sd(){
        num = ++idx;
        for(int i=1; i<=n; ++i){
            if(cut[i])new_id[i] = ++num;
        }
        for(int i=1; i<=dn; ++i){
            for(auto &x : dcc[i]){
                if(cut[x]){
                    _add_c(i, new_id[x]);
                    _add_c(new_id[x], i);
                }else{
                    color[x] = i;
                }
            }
        }
    }
};
namespace edcc{
    const int N = 1e5 + 12;
    int head[N], to[N <<1], ne[N << 1], cost[N << 1];
    int color[N], low[N], dfn[N], bridge[N];
    int n, m, idx = 1, code, cn;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _tarjan(int x, int in_e){
        low[x] = dfn[x] = ++code;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y, i);
                low[x] = std::min(low[y], low[x]);
                if(low[y] > dfn[x])bridge[i] = bridge[i ^ 1] = 1;
            }else if(i != (in_e ^ 1)){
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void _dfs(int x, int co){
        color[x] = co;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[y];
            if(color[y] || bridge[i])continue;
            _dfs(y, co);
        }
    }
    void _get_edcc(){
        std::cin >> n >> m;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        _tarjan(1, 0);
        for(int i=1; i<=n; ++i){
            if(!color[i]) _dfs(i, ++cn);
        }
    }
    int sh[N], sto[N << 1], sne[N << 1], sidx = 1;
    void _s_add(int x, int y){
        to[++sidx] = y;
        ne[sidx] = sh[x];
        sh[x] = sidx;
    }
    void _sd(){
        for(int i=1; i<=m; ++i){
            int x = to[i], y = to[i ^ 1];
            if(color[x] == color[y])continue;
            _s_add(x, y);
            _s_add(color[x], color[y]);
        }
    }
}
namespace p403{
    const int N = 1e5 + 12;
    int head[N], to[N << 4], ne[N << 4];
    int dfn[N], se[N], low[N], cut[N];
    long long ans[N];
    int n, m, idx, code;
    void  _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _tarjan(int x){
        dfn[x] = low[x] = ++code;
        se[x] = 1;
        int f = 0, sum = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!dfn[y]){
                _tarjan(y);
                se[x] += se[y];
                low[x] = std::min(low[x], low[y]);
                if(low[y] >= dfn[x]){
                    if(++f > 1 || x != 1)cut[x] = 1;
                    sum += se[y];
                    ans[x] += (long long)se[y] * (n - se[y]);
                }
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        if(cut[x]){
            ans[x] += (long long)(n - sum - 1)*(sum+1) + (n-1);
        }else{
            ans[x] = (n - 1) * 2;
        }
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _tarjan(1);
        for(int i=1; i<=n; ++i){
            std::cout << ans[i] << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};

namespace tarjan{
    const int N = 1e5 + 12;
    int head[N], to[N<<1], ne[N<<1], cost[N<<1];
    int dfn[N], low[N];
    int n, m, idx = 1, code;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    namespace edge{
        int bridge[N << 1];
        void _tarjan(int x, int in_edge){
            dfn[x] = low[x] = ++code;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!dfn[y]){
                    _tarjan(y, i);
                    low[x] = std::min(low[x], low[y]);
                    if(low[y] > dfn[x])bridge[i] = bridge[i^1] = 1;
                }else if(i != (in_edge ^ 1)){
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        }
        void _deal(){
            std::cin >> n >> m;
            for(int i=1, x, y, v; i<=m; ++i){
                std::cin >> x >> y >> v;
                _add(x, y, v), _add(y, x, v);
            }
            for(int i=1; i<=n; ++i){
                if(dfn[i])continue;
                _tarjan(i, 0);
            }
            for(int i=1; i<idx; ++i){
                if(bridge[i]){
                    std::cout << to[i] << to[i ^ 1];
                }
            }
            std::cout << std::endl;
        }
        int main(int argc,const char *argv[]){
            _deal();
            return 0;
        }
    };
    namespace point{
        int cut[N], root;
        void _tarjan(int x){
            dfn[x] = low[x] = ++code;
            int f = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(!dfn[y]){
                    _tarjan(y);
                    low[x] = std::min(low[x], low[y]);
                    if(low[y] >= dfn[x]){
                        if(++f>1 || x!=root)cut[x] = 1;
                    }
                }else{
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        }
        void _deal(){
            std::cin >> n >> m;
            for(int i=1, x, y, v; i<=m; ++i){
                std::cin >> x >> y >> v;
                _add(x, y, v), _add(y, x, v);
            }
            for(int i=1; i<=n; ++i){
                if(dfn[i])continue;
                _tarjan(root=i);
            }
            for(int i=1; i<=n; ++i){
                if(cut[i])std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    };
};
namespace p402{
    const int N = 5e4 + 12, INF = 0x3f3f3f3f;
    int head[N], to[N << 2], ne[N << 2], cost[N << 2];
    int vi[N], d[N];
    int n, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    int _spfa(int s=0){
        std::memset(d, -0x3f, sizeof d);
        vi[s] = 1;
        d[s]  = 0;
        std::queue<int> q;
        q.emplace(s);
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] < d[x] + cost[i]){
                    d[y] = d[x] + cost[i];
                    if(!vi[y])vi[y]=1, q.emplace(y);
                }
            }
        }
        return d[50001];
    }
    void _deal(){
        for(int i=1; i<=50001; ++i){
            _add(i-1, i, 0);
            _add(i, i-1, -1);
        }
        std::cin >> n;
        for(int i=0, x, y , v; i<n; ++i){
            std::cin >> x >> y >> v;
            _add(x, y+1, v);
        }
        std::cout << _spfa() << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p340{
    const double EPS = 1e-5;
    const int N = 1e5 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N], to[N], cnt[N], vi[N];
    int f[N], t[N];
    double d[N];
    int n, p, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        t[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _spfa(double m){
        std::queue<int> q;
        for(int i=1; i<=n; ++i){
            q.emplace(i);
            cnt[i] = d[i] = 0;
            vi[i] = 1;
        }
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                double cost = (t[i]*m - f[x]);
                if(d[y] > d[x] + cost){
                    d[y] = d[x] + cost;
                    cnt[y] = cnt[x]+1;
                    if(cnt[y]>=n)return true;
                    if(!vi[y])vi[y] = 1, q.emplace(y);
                }
            }
        }
        return false;
    }
    double _b_search(){
        double l = 0, r = 1000;
        while((r-l) > EPS){
            double m = (l + r) / 2;
            std::cout << m << std::endl;
            if(_spfa(m)){
                l = m;
            }else{
                r = m;
            }
        }
        return l;
    } 
    void _deal(){
        std::cin >> n >> p;
        for(int i=1; i<=n; ++i)std::cin >> f[i];
        for(int i=1, x, y, v; i<=p; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v);
        }
        printf("%2.f", _b_search());
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p339{
    const int N = 1e6 + 12;
    int head[N], to[N], ne[N], fa[N], vi[N];
    int dp[N][2];
    int n, idx, root, ans;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
        fa[y] = x;
    }
    int _getloop(int x){
        while(!vi[fa[x]])vi[x] = 1, x = fa[x];
        return x;
    }
    void _dp(int x, int f){
        int sto = INT_MAX;
        vi[x] = 1;
        dp[x][0] = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(root == y)continue;
            _dp(y, f);
            sto = std::min(sto, std::max(dp[y][0], dp[y][1]) - dp[y][0]);
            dp[x][0] += std::max(dp[y][0], dp[y][1]);
        }
        dp[x][1] = dp[x][0] - sto + 1;
        if(x == fa[root] && f)dp[x][1] = dp[x][0] + 1;
    }
    void _deal(){
        std::cin >> n;
        for(int i=1; i<=n; ++i){
            int x;
            std::cin >> x;
            _add(x, i);
        }
        for(int i=1; i<=n; ++i){
            if(vi[i])continue;
            root = _getloop(i);
            _dp(root, 0);
            int tmp = std::max(dp[root][0], dp[root][1]);
            _dp(root, 1);
            tmp = std::max(tmp, dp[root][0]);
            ans += tmp;
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p338{
    using ll = long long;
    const int N = 1e6 + 12;
    int head[N], to[N << 1], ne[N <<1];
    ll d[N], cost[ N << 1 ], ans, sums[N], dep[N];
    struct node {
        ll to, w ;
    }fa[N], loop[N];
    int vi[N], v[N], q[N << 1];
    int n, idx, code, cnt;
    void _add(int x, int y, ll v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x){
        vi[x] = ++code;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == fa[x].to)continue;
            if(vi[y]){
                if(vi[x] > vi[y])continue;
                loop[++cnt].to = y;
                loop[cnt].w = cost[i];
                for(; x!=y; y=fa[y].to){
                    loop[++cnt] = fa[y];
                }
            }else{
                fa[y].to = x;
                fa[y].w = cost[i];
                _dfs(y);
            }
        }
    }
    ll _dfs(int x, int p){
        ll res = 0;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p || v[y])continue;
            res = std::max(res, _dfs(y, x));
            res = std::max(res, (ll)d[x] + cost[i] + d[y]);
            d[x] = std::max(d[x], cost[i] + d[y]);
        }
        return res;
    }
    ll _value(int index){ return dep[index] - sums[index]; }
    void _calc(){
        for(int k=1; k<=n; ++k){
            if(vi[k])continue;
            cnt = 0, code = 0;
            ll tmp = 0;
            _dfs(k);
            for(int i=1; i<=cnt; ++i)v[loop[i].to] = 1;
            for(int i=1; i<=cnt; ++i){
                int x = loop[i].to;
                tmp = std::max(tmp, _dfs(x, 0));
                dep[i] = d[x];
            }
            for(int i=1; i<=cnt; ++i){
                dep[i+cnt] = dep[i];
                sums[i] = sums[i-1] + loop[i].w;
            }
            int l = 1, r = 0;
            for(int i=1; i<=cnt*2; ++i){
                if(i>cnt)sums[i] = sums[i-1] + loop[i-cnt].w;
                if(l<=r) tmp = std::max(tmp, _value(q[l]) + sums[i] + dep[i]);
                while(l<=r && _value(q[r]) <= _value(i))--r;
                q[++r] = i;
                while(l<=r && i-q[l]+1 >= cnt)++l;
            }
            ans += tmp;
        }
    }
    void _deal(){
        std::cin >> n;
        for(int i=1; i<=n; ++i){
            ll x, v;
            std::cin >> x >> v;
            _add(i, x, v), _add(x, i, v);
        }
        _calc();
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p337{
    using ll = long long;
    using pli = std::pair<ll, int>;
    const int N = 5e4 + 12;
    ll head[N], to[N << 1], ne[N << 1], cost[N << 1];
    int so[N], fr[N], nd[N], nd1[N];
    pli wait[N];
    int fa[N][32], vi[N];
    ll  d[N], dis[N][32], sum, res = -1;
    int n, m, idx, t;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
            dis[x][i] = dis[x][i-1] + dis[fa[x][i-1]][i-1];
        }
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            dis[y][0] = cost[i];
            _dfs(y, x);
        }
    }
    bool _dfs(int x){
        if(vi[x])return true;
        bool ans = false;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(d[x] > d[y])continue;
            ans = true;
            if(!_dfs(y))return false;
        }
        return ans;
    }
    bool _check(ll limit){
        std::memset(vi,   0, sizeof vi);
        std::memset(nd1,  0, sizeof nd1);
        int n1=0, n2=0, n3=0, n4=0;
        for(int i=1; i<=m; ++i){
            ll tmp = 0, x = so[i];
            for(int k=t; k>=0; --k){
                if(fa[x][k]>1 && tmp+dis[x][k] <= limit){
                    tmp += dis[x][k];
                    x = fa[x][k];
                }
            }
            if(fa[x][0] == 1 && tmp + dis[x][0] <= limit){
                wait[++n1] = {limit-(tmp+dis[x][0]), x};
            }else{
                vi[x] = 1;
            }
        }
        int f = 0;
        for(int i=head[1]; i; i=ne[i]){
            int y = to[i];
            if(!_dfs(y))f = nd1[y] = 1;
        }
        if(!f)return true;
        for(int i=1; i<=n1; ++i){
            auto [leav, x] = wait[i];
            if(nd1[x] && leav < dis[x][0]){
                nd1[x] = 0;
            }else{
                fr[++n3] = leav;
            }
        }

        for(int i=head[1]; i; i=ne[i]){
            int y = to[i];
            if(nd1[y])nd[++n4] = dis[y][0];
        }
        if(!n4)return true;
        if(n3 < n4)return false;
        std::sort(fr + 1, fr + 1 + n3);
        std::sort(nd + 1, nd + 1 + n4);
        int i = 1, j = 1;
        while(i<=n3 && j<=n4){
            if(nd[j] <= fr[i])++j;
            ++i;
        }
        return j > n4;
    }
    void _b_search(){
        ll l = 1, r = sum + 1;
        while(l < r){
            ll m = l + ((r - l) >> 1);
            if(_check(m)){
                res = r = m;
            }else{
                l = m + 1;
            }
        }
    }
    void _read(){
        std::cin >> n;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            int x, y, v;
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
            sum += v;
        }
        std::cin >> m;
        for(int i=1; i<=m; ++i)std::cin >> so[i];
    }
    void _deal(){
        _read();
        _dfs(1, 0);
        _b_search();
        std::cout << res << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p336{
    using ll = long long;
    const int N = 1e5 + 12, INF = 0x3f3f3f3f;
    struct node {
        int x, y, v;
        bool operator < (const node &other) const {
            return v < other.v;
        }
    } nodes[N * 3];
    int n, m, idx, t;
    int head[N], to[N * 3], ne[N * 3], cost[N * 3];
    int f[N], d[N], used[N * 3];
    int fa[N][32], d1[N][32], d2[N][32];
    ll  ans = LONG_LONG_MAX, sum, nums[N * 3];
    void _read(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<=m; ++i){
            int x, y, v;
            std::cin >> x >> y >> v;
            nodes[i] = {x, y, v};
        }
    }
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    int _f(int x){return x==f[x] ? x : f[x]=_f(f[x]);}
    int _kruskal(int s=1){
        for(int i=1; i<=n; ++i)f[i] = i;
        std::sort(nodes+1, nodes+1+m);
        int k = 1;
        for(int i=1; i<=m; ++i){
            int x = _f(nodes[i].x);
            int y = _f(nodes[i].y);
            if(x == y)continue;
            f[x] = y;
            sum += nodes[i].v;
            used[i] = 1;
            if(++k == n)break;
        }
        return sum;
    }
    void _build(){
        for(int i=1; i<=m; ++i){
            if(!used[i])continue;
            int x = nodes[i].x, y = nodes[i].y, v = nodes[i].v;
            _add(x, y, v), _add(y, x, v);
        }
    }
    void _dfs(int x=1, int p=0){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        d2[x][0] = -INF;
        for(int i=1; (1<<i)<=d[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
            d1[x][i] = std::max(d1[x][i-1], d1[fa[x][i-1]][i-1]);
            int a = d1[x][i-1], pa = d1[fa[x][i-1]][i-1];
            if(a == pa){
                d2[x][i] = std::max(d2[x][i-1], d2[fa[x][i-1]][i-1]);
            }else if(a > pa){
                d2[x][i] = std::max(d2[x][i-1], pa);
            }else{
                d2[x][i] = std::max(d2[fa[x][i-1]][i-1], a);
            }
        }
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            d1[y][0] = cost[i];
            _dfs(y, x);
        }
    }
    void _bfs(int s=1){
        d[s] = 1;
        d2[s][0] = -INF;
        std::queue<int> q;
        q.emplace(s);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y])continue;
                d1[y][0] = cost[i];
                d2[y][0] = -INF;
                fa[y][0] = x;
                d[y] = d[x] + 1;
                q.emplace(y);
                for(int j=1; (1<<j)<=d[y]; ++j){
                    fa[y][j] = fa[fa[y][j-1]][j-1];
                    d1[y][j] = std::max(d1[y][j-1], d1[fa[y][j-1]][j-1]);
                    int a = d1[y][j-1], pa = d1[fa[y][j-1]][j-1];
                    if(a == pa){
                        d2[y][j] = std::max(d2[y][j-1], d2[fa[y][j-1]][j-1]);
                    }else if(a > pa){
                        d2[y][j] = std::max(d2[y][j-1], pa);
                    }else{
                        d2[y][j] = std::max(d2[fa[y][j-1]][j-1], a);
                    }
                }
            }
        }
    }
    int _lca(int x, int y, ll v){
        if(d[x] < d[y])std::swap(x, y);
        int k = 0;
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] < d[y])continue;
            nums[k++] = d1[x][i];
            nums[k++] = d2[x][i];
            x = fa[x][i];
        }
        if(x != y){
            for(int i=t; i>=0; --i){
                if(fa[x][i] != fa[y][i]){
                    nums[k++] = d1[x][i];
                    nums[k++] = d2[x][i];
                    nums[k++] = d1[y][i];
                    nums[k++] = d2[y][i];
                    x = fa[x][i], y = fa[y][i];
                }
            }
            nums[k++] = d1[x][0];
            nums[k++] = d1[y][0];
        }
        ll v1 = -INF, v2 = -INF;
        for(int i=0; i<k; ++i){
            if(nums[i] > v1){
                v2 = v1;
                v1 = nums[i];
            }else if(nums[i]!=v1 && nums[i] > v2){
                v2 = nums[i];
            }
        }
        if(v1 < v)return ans = std::min(ans, sum - v1 + v);
        return ans = std::min(ans, sum - v2 + v);
    }
    void _calc(){
        for(int i=1; i<=m; ++i){
            if(used[i])continue;
            _lca(nodes[i].x, nodes[i].y, nodes[i].v);
        }
    }
    void _deal(){
        _read();
        _kruskal();
        _build();
        _dfs();
        _calc();
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};

namespace p355{
    using ll  = long long;
    using pii = std::pair<int, int>;
    const int N = 1e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int d[N], fa[N<<1][32], v[N];;
    char op;
    int t, n, m, idx, code;
    ll cost[N << 1], dis[N];
    ll ans;
    std::set<pii> mp;
    std::set<pii>::iterator it, l, r;
    void _add(int x, int y, ll v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        d[x] = d[p] + 1;
        fa[x][0] = p;
        v[x] = ++code;
        for(int i=1; (1<<i)<=d[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            dis[y] = dis[x] + cost[i];
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(d[x] < d[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(d[fa[x][i]] >= d[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    ll _getdis(int l, int m, int r){
        return (dis[l] + dis[m] - 2*dis[_lca(l, m)]) +
               (dis[m] + dis[r] - 2*dis[_lca(m, r)]) -
               (dis[l] + dis[r] - 2*dis[_lca(l, r)]);
    }
    void _deal(){
        std::cin >> n;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            int x, y, v;
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        _dfs(1, 0);
        std::cin >> m;
        for(int i=1; i<=m; ++i){
            std::cin >> op;
            if(op == '?'){
                std::cout << (ans >> 1) << std::endl;
                continue;
            }
            int x;
            std::cin >> x;
            if(op == '+') mp.insert({v[x], x});
            l = r = it = mp.lower_bound({v[x], x});
            auto t = mp.end();
            auto [lv, lx] = *(it==mp.begin() ? --t : --l);
            auto [rv, rx] = *(++r==mp.end() ? mp.begin() : r);
            ll d = _getdis(lx, x, rx);
            if(op == '-') mp.erase(it), ans -= d;
            if(op == '+') ans += d;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
    void _update(char c, int x){
        if(c == '+'){
            if(!mp.size()){
                mp.insert({v[x], x});
                return;
            }
            l = --mp.lower_bound({v[x], x});
            r = mp.lower_bound({v[x], x});
            if(r == mp.begin())l = --mp.end();
            if(r == mp.end())r = mp.begin();
            ans += _getdis(l->second, x, r->second);
            mp.insert({v[x], x});
        }else{
            mp.erase({v[x], x});
            if(!mp.size())return ;
            l = --mp.lower_bound({v[x], x});
            r = mp.lower_bound({v[x], x});
            if(r == mp.begin())l = --mp.end();
            if(r == mp.end())r = mp.begin();
            ans -= _getdis(l->second, x, r->second);
        }
    }
};
//------------------------------------------------------------------------------------
namespace p354{
    using pii = std::pair<int, int>;
    const int N = 3e5 + 12;
    int head[N], ne[N << 1], to[N<<1];
    int deep[N], fa[N<<1][32], w[N], d1[N<<1], d2[N<<1];
    int ans[N];
    int t, n, m, idx;
    std::vector<pii> op1[N], op2[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        deep[x] = deep[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=deep[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(p == y)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(deep[x]<deep[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(deep[fa[x][i]] >= deep[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _update(int s, int e){
        int lca = _lca(s, e);
        op1[s].emplace_back(deep[s], 1);
        op1[fa[lca][0]].emplace_back(deep[s], -1);

        op2[e].emplace_back(deep[s] - 2*deep[lca] + n, 1);
        op2[lca].emplace_back(deep[s] - 2*deep[lca] + n, -1);
    }
    void _query(int x, int p){
        int v1 = deep[x] + w[x], v2 = w[x] - deep[x] + n;
        int r1 = d1[v1], r2 = d2[v2];
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            _query(y, x);
        }
        for(auto &[f, s] : op1[x]) d1[f] += s;
        for(auto &[f, s] : op2[x]) d2[f] += s;
        ans[x] = (d1[v1] - r1) + (d2[v2] - r2);
    }
    void _deal(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            int x, y;
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        for(int i=1; i<=n; ++i)std::cin >> w[i];
        _dfs(1, 0);
        for(int i=1; i<=m; ++i){
            int x, y;
            std::cin >> x >> y;
            _update(x, y);
        }
        _query(1, 0);
        for(int i=1; i<=n; ++i)std::cout << ans[i] << " ";
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};

namespace p353{
    const int N = 1e5 + 12;
    struct node { int l, r, m, id; } tree[N  << 6];
    int a[N], b[N], v[N], mp[N];
    int head[N], ne[N << 1], to[N << 1];
    int deep[N], fa[N][32], rt[N], res[N];
    int n, m, idx, t, mpn, code;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        deep[x]  = deep[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1<<i)<=deep[x]; ++i)fa[x][i] = fa[fa[x][i-1]][i-1];
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(p == y)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(deep[x] < deep[y])std::swap(x, y);
        for(int i=t; i>=0; --i){
            if(deep[fa[x][i]] >= deep[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _pushup(int id){
        int l = tree[id].l, r = tree[id].r;
        int k = tree[l].m  >= tree[r].m ? l : r;
        tree[id].m  = tree[k].m;
        tree[id].id = tree[k].id;
    }
    void _update(int &id, int node, int v, int l, int r){
        if(!id)id = ++code;
        if(l == r){
            tree[id].m += v;
            tree[id].id = l;
            return ;
        }
        int m = l + ((r - l) >> 1);
        if(node <= m){
            _update(tree[id].l, node, v, l, m);
        }else{
            _update(tree[id].r, node, v, m+1, r);
        }
        _pushup(id);
    }
    int _merge(int p, int q, int l, int r){
        if(!p)return q;
        if(!q)return p;
        if(l == r){
            tree[p].m += tree[q].m;
            return p;
        }
        int m = l + ((r - l) >> 1);
        tree[p].l = _merge(tree[p].l, tree[q].l, l, m);
        tree[p].r = _merge(tree[p].r, tree[q].r, m + 1, r);
        _pushup(p);
        return p;
    }
    void _query(int x, int p){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            _query(y, x);
            rt[x] = _merge(rt[x], rt[y], 1, mpn);
        }
        if(!tree[rt[x]].m)return ;
        res[x] = tree[rt[x]].id;
    }
    void _deal(){
        std::cin >> n >> m ;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            int x, y;
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _dfs(1, 0);
        for(int i=1; i<=m; ++i){
            std::cin >> a[i] >> b[i] >> v[i];
            mp[i] = v[i];
        }
        std::sort(mp + 1, mp + m + 1);
        mpn = std::unique(mp + 1, mp + m + 1) - mp - 1;
        for(int i=1; i<=m; ++i){
            int lca = _lca(a[i], b[i]);
            int mpi = std::lower_bound(mp + 1, mp + mpn + 1, v[i]) - mp;
            _update(rt[a[i]], mpi, 1, 1, mpn);
            _update(rt[b[i]], mpi, 1, 1, mpn);
            _update(rt[lca],  mpi, -1, 1, mpn);
            _update(rt[fa[lca][0]],  mpi, -1, 1, mpn);
        }
        _query(1, 0);
        for(int i=1; i<=n; ++i)std::cout << mp[res[i]] << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p352{
    const int N = 1e5 + 12;
    int head[N], ne[N << 1], to[N << 1];
    int deep[N], fa[N << 1][32], date[N];
    int ans, idx, t, n, m;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dfs(int x, int p){
        deep[x]  = deep[p] + 1;
        fa[x][0] = p;
        for(int i=1; (1 << i)<=deep[x]; ++i){
            fa[x][i] = fa[fa[x][i-1]][i-1];
        }
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(p == y)continue;
            _dfs(y, x);
        }
    }
    int _lca(int x, int y){
        if(deep[x] < deep[y])std::swap(x, y);
        for(int i=t; i>=1; --i){
            if(deep[fa[x][i]] >= deep[y])x = fa[x][i];
        }
        if(x == y)return x;
        for(int i=t; i>=0; --i){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    void _update(int x, int y, int v){
        date[x] += v;
        date[y] += v;
        date[_lca(x, y)] -= (v * 2);
    }
    void _query(int x, int p){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(y == p)continue;
            _query(y, x);
            date[x] += date[y];
            if(date[y] == 0){
                ans += m;
            }else if(date[y] == 1){
                ans += 1;
            }
        }
    }
    void _deal(){
        std::cin >> n >> m;
        t = (int)(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            int x, y;
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        _dfs(1, 0);
        for(int i=0; i<m; ++i){
            int x, y;
            std::cin >> x >> y;
            _update(x, y, 1);
        }
        _query(1, 0);
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p351{
    const int N = 500000 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N << 1], to[N << 1], cost[N << 1];
    int d[N], vi[N], pre[N], pa[N], md[N];
    int n, s;
    int idx=1, len;
    int _bfs(int s){
        std::memset(d, 0x3f, sizeof d);
        pre[s] = d[s] = 0;
        std::queue<int> q;
        q.emplace(s);
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] != INF)continue;
                d[y] = d[x] + cost[i];
                pre[y] = i;
                q.emplace(y);
            }
        }
        int ans = 1;
        for(int i=2; i<=n; ++i){
            if(d[ans] < d[i])ans = i;
        }
        return ans;
    }
    void _dfs(int x){
        vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            _dfs(y);
            md[x] = std::max(md[x], cost[i] + md[y]);
        }
    }
    void _add(int x,int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _getpath(){
        int p = _bfs(_bfs(1));
        for(; pre[p]; p=to[pre[p]^1])pa[len++] = p;
        pa[len++] = p;
    }
    void _getpathmax(int &ans){
        for(int i=0; i<len; ++i)vi[pa[i]] = 1;
        for(int i=0; i<len; ++i)_dfs(pa[i]);
        for(int i=0; i<len; ++i)ans = std::max(ans, md[pa[i]]);
    }
    void _read(){
        std::cin >> n >> s;
        for(int i=1; i<n; ++i){
            int x, y, v;
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y ,x, v);
        }
    }
    void _calc(int &ans){
        int l=0, r=0, tmp = INF;
        int L=d[pa[0]], R=d[pa[len - 1]];
        while(r<len){
            int i = pa[l], j = pa[r];
            while(r<len && d[i] - d[j] <= s){
                int t1 = std::max(L - d[i], d[j] - R);
                tmp = std::min(tmp, t1);
                j = pa[++r];
            }
            r = std::max(r, ++l);
        }
        ans = std::max(ans, tmp);
    }
    void _deal(int ans=0){
        _read();
        _getpath();
        _getpathmax(ans);
        _calc(ans);
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p350{
    const int N = 1e5 + 12, INF = 0x3f3f3f3f;
    int n, k;
    int head[N], cost[N << 1], to[N << 1], ne[N << 1];
    int vi[N], d[N], pre[N];
    int idx=1, u, v;
    void _add(int x, int y){
        to[++idx] = y;
        cost[idx] = 1;
        ne[idx] = head[x];
        head[x] = idx;
    }
    int _bfs(int s){
        std::memset(d, 0x3f, sizeof d);
        std::queue<int> q;
        q.emplace(s);
        pre[s] = d[s] = 0;
        while(q.size()){
            int x = q.front();q.pop();
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] != INF)continue;
                d[y] = d[x] + cost[i];
                pre[y] = i;
                q.emplace(y);
            }
        }
        int x = 1;
        for(int i=2; i<=n; ++i){
            if(d[x] < d[i])x = i;
        }
        return x;
    }
    void _dfs(int x, int &ans){
        vi[x] = 1;
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            _dfs(y, ans);
            ans = std::max(ans, d[x] + cost[i] + d[y]);
            d[x] = std::max(d[x], d[y] + cost[i]);
        }
    }
    void _change(){
        for(; pre[u]; u=to[pre[u] ^ 1]){
            cost[pre[u]] = cost[pre[u]^1] = -1;
        }
    }
    int _calc(){
        return d[u = _bfs(_bfs(1))];
    }
    int _calc(int x){
        std::memset(d, 0, sizeof d);
        _change();
        int ans = 0;
        return (_dfs(x, ans), ans);
    }
    void _deal(){
        std::cin >> n >> k;
        for(int i=1; i<n; ++i){
            int x, y;
            std::cin >> x >> y;
            _add(x, y), _add(y, x);
        }
        int l1 = _calc(), l2 = 0;
        if(k == 2)l2 = _calc(1);
        std::cout << (2*(n-1) - l1 - l2 + k) << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};


namespace p349{
    using ll  = long long;
    using pii = std::pair<int, int>;
    const int N = 1024, MOD = INT_MAX;
    int head[N], to[N << 10], cost[N << 10], ne[N << 10];
    int vi[N], d[N], cnt[N];
    int n, m, idx;
    std::priority_queue<pii,
        std::vector<pii>,
        std::greater<pii>> q;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dijkstra(){
        std::memset(d, 0x3f, sizeof d);
        d[1] = 0;
        q.emplace(0, 1);
        while(q.size()){
            int x = q.top().second;q.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] <= d[x] + cost[i])continue;
                d[y] = d[x] + cost[i];
                q.emplace(d[y], y);
            }
        }
    }
    int _clac(){
        ll ans = 1;
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] == d[x] + cost[i])++cnt[y];
            }
        }
        for(int i=1; i<=n; ++i){
            if(cnt[i])ans = ans * cnt[i] % MOD;
        }
        return ans;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0; i<m; ++i){
            int x, y, v;
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
        _dijkstra();
        std::cout << _clac() << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};

namespace p348{
    using ll = long long;
    const int N = 1e4 + 12;
    const double EPS = 1e-6, INF = 1e18;
    struct node{int x, y; double z;} nodes[N];
    double d[N];
    int vi[N];
    int n;
    double _distance(node &a, node &b){
        return sqrt((a.x-b.x)*(a.x-b.x) +
                    (a.y-b.y)*(a.y-b.y));
    }
    bool _prim(double m){
        std::fill(vi, vi + n, 0);
        std::fill(d, d + n, INF);
        vi[0] = 1, d[0] = 0;
        double ans = 0.0;
        for(int i=0; i<n; ++i){
            double t = INF;
            int k = 0;
            for(int j=0; j<n; ++j){
                if(!vi[j] && t>d[j])t=d[j], k=j;
            }
            vi[k] = 1;
            ans += d[k];
            for(int j=0; j<n; ++j){
                t = fabs(nodes[k].z - nodes[j].z) -
                    m * _distance(nodes[k], nodes[j]) + EPS;
                if(!vi[j] && d[j] > t)d[j] = t;
            }
        }
        return ans >= 0.0;
    }
    double _b_search(){
        double l = 0, r = 10000001.0;
        while((r-l) > EPS){
            double m = (l + r) / 2;
            if(_prim(m)){
                l = m;
            }else{
                r = m;
            }
        }
        return (l + r) / 2;
    }
    bool _deal(){
        if((std::cin >> n, !n))return false;
        for(int i=0; i<n; ++i){
            std::cin >> nodes[i].x >> nodes[i].y >> nodes[i].z;
        }
        printf("%.3f\n", _b_search());
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p348_fuck{
    using ll = long long;
    const int N = 1e4 + 12;
    const double EPS = 1e-6;
    int n, idx;
    int f[N];
    struct node{int x, y; double z;} nodes[N], e[N * N];
    int _f(int x){ return x==f[x] ? x : f[x]=_f(f[x]); }
    double _distance(node &a, node &b){
        return sqrt((a.x-b.x)*(a.x-b.x) +
                    (a.y-b.y)*(a.y-b.y));
    }
    void _add(int m){
        idx = 0;
        for(int i=0; i<n; ++i){
            for(int j=i+1; j<n; ++j){
                double d = _distance(nodes[i], nodes[j]);
                e[idx++] = {i, j, abs(nodes[i].z-nodes[j].z) - m*d};
            }
        }
    }
    bool _kruskal(int m){
        _add(m);
        for(int i=0; i<-n; ++i)f[i] = i;
        std::sort(e, e + idx, [&](auto &a, auto &b){
                return a.z > b.z; });
        double ans = 0.0;
        for(int i=0; i<idx; ++i){
            int x = _f(e[i].x);
            int y = _f(e[i].y);
            if(x == y)continue;
            f[x] = y;
            ans += e[i].z;
        }
        return ans >= 0.0;
    }
    double _b_search(){
        double l = 0, r = 10000001.0;
        while((r - l) > EPS){
            double m = (l + r) / 2;
            if(_kruskal(m)){
                l = m;
            }else{
                r = m;
            }
        }
        return (l + r) / 2;
    }
    bool _deal(){
        if(std::cin >> n, !n)return false;
        for(int i=0; i<n; ++i){
            int x, y; double z;
            std::cin >> x >> y >> z;
            nodes[i] = {x, y, z};
        }
        printf("%.3f", _b_search());
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p347{
    using pii = std::pair<int, int>;
    const int N = 32, INF = 0x3f3f3f3f;
    struct node {
        int x, y, v;
        bool operator < (const node &other) const {
            return v < other.v;
        }
        void init() { x=y=0,v=-1; }
    }e[N << 4], maxl[N << 4];
    int edges[N][N];
    int n, s, idx, cnt, ans;
    int f[N], color[N];
    std::vector<int> ccs[N];
    std::string x, y;
    std::unordered_map<std::string, int> mp;
    std::map<pii, bool> mppath;
    void  _add(int x, int y, int w){
        edges[x][y] = edges[y][x] = w;
    }
    int _f(int x) { return x==f[x] ? x : f[x]=_f(f[x]); }
    void _dfs(int x){
        color[x] = cnt;
        ccs[cnt].emplace_back(x);
        for(int y=2; y<=idx; ++y){
            if(!edges[x][y] || color[y])continue;
            _dfs(y);
        }
    }
    void _dfs(int x, int pre){
        for(int i=2; i<=idx; ++i){
            if(pre==i || !mppath[{x, i}])continue;
            if(maxl[i].v == -1){
                if(maxl[x].v > edges[x][i]){
                    maxl[i] = maxl[x];
                }else{
                    maxl[i].x = x;
                    maxl[i].y = i;
                    maxl[i].v = edges[x][i];
                }
            }
            _dfs(i, x);
        }
    }
    void _read(){
        mp.emplace("Park", ++idx);
        std::cin >> n;
        for(int i=0; i<n; ++i){
            int w;
            std::cin >> x >> y >> w;
            if(!mp.count(x))mp[x] = ++idx;
            if(!mp.count(y))mp[y] = ++idx;
            int tx = mp[x], ty = mp[y];
            e[i] = {tx, ty, w};
            _add(tx, ty, w), _add(ty, tx, w);
        }
        std::cin >> s;
    }
    void _staining(){
        for(int i=2; i<=idx; ++i){
            if(!color[i])++cnt, _dfs(i);
        }
    }
    void _init(){
        for(int i=1; i<=idx; ++i)f[i] = i;
        std::sort(e, e + n);
    }
    void _kruskal(){
        for(int i=0; i<n; ++i){
            int x = _f(e[i].x);
            int y = _f(e[i].y);
            if(x==y || x==1 || y==1)continue;
            mppath[{e[i].x, e[i].y}] = mppath[{e[i].y, e[i].x}] = 1;
            f[x] = y;
            ans += e[i].v;
        }
    }
    void _link(){
        for(int i=1; i<=cnt; ++i){
            int t, v = INF;
            for(auto &y : ccs[i]){
                if(!edges[1][y] || edges[1][y] >= v)continue;
                t = y, v = edges[1][y];
            }
            mppath[{1, t}] = mppath[{t, 1}] = 1;
            ans += v;
        }
    }
    void _select(){
        while(s-- > cnt){
            for(int i=0; i<=idx; ++i)maxl[i].init();
            _dfs(1, -1);
            int v = 0, del;
            for(int y=2; y<=idx; ++y){
                if(edges[1][y] && v < maxl[y].v - edges[1][y]){
                    v = maxl[y].v - edges[1][y];
                    del = y;
                }
            }
            if(v <= 0)break;
            ans -= v;
            mppath[{1, del}] = mppath[{del, 1}] = 1;
            mppath[{maxl[del].x, maxl[del].y}]  = 0;
        }
    }
    void _deal(){
        _read();
        _init();
        _staining();
        _kruskal();
        _link();
        _select();
        std::cout << "Total miles driven: " << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p346{
    using ll = long long;
    const int N = 6000 + 12;
    struct node{
        int x, y, v;
        bool operator < (const node &other) const {
            return v < other.v;
        }
    } e[N];
    int t, n;
    int f[N], s[N];
    int _f(int x){ return x==f[x] ? x : f[x]=_f(f[x]); }
    ll _kruskal(){
        ll ans = 0;
        for(int i=1; i<n; ++i){
            int x = _f(e[i].x);
            int y = _f(e[i].y);
            if(x == y)continue;
            ans += (ll)(s[y] * s[x] - 1) * (e[i].v + 1);
            f[x] = y;
            s[y] += s[x];
        }
        return ans;
    }
    void _deal(){
        std::cin >> n;
        for(int i=1; i<n; ++i){
            std::cin >> e[i].x >> e[i].y >> e[i].v;
        }
        for(int i=1; i<=n; ++i)s[i] = 1, f[i] = i;
        std::sort(e + 1, e + n);
        std::cout << _kruskal() << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};

namespace p345{
    const int N = 128 << 1;
    int g[N][N], ans[N][N];
    int n, t, s ,e;
    int idx;
    std::unordered_map<int, int> mp;
    void _mul(int (*res)[N], int (*m1)[N], int (*m2)[N]){
        static int tmp[N][N];
        std::memset(tmp, 0x3f, sizeof tmp);
        for(int k=1; k<=idx; ++k){
            for(int i=1; i<=idx; ++i){
                for(int j=1; j<=idx; ++j){
                    tmp[i][j] = std::min(tmp[i][j], m1[i][k] + m2[k][j]);
                }
            }
        }
        std::memcpy(res, tmp, sizeof tmp);
    }
    int _quickm(){
        std::memset(ans, 0x3f, sizeof ans);
        for(int i=1; i<=idx; ++i)ans[i][i] = 0;
        while(n){
            if(n & 1)_mul(ans, ans, g);
            _mul(g, g, g);
            n >>= 1;
        }
        return ans[s][e];
    }
    void _deal(){
        std::memset(g, 0x3f, sizeof g);
        std::cin >> n >> t >> s >> e;
        if(!mp.count(s))mp[s] = ++idx;
        if(!mp.count(e))mp[e] = ++idx;
        s = mp[s], e = mp[e];
        while(t--){
            int x, y, z;
            std::cin >> z >> x >> y;
            if(!mp.count(x))mp[x] = ++idx;
            if(!mp.count(y))mp[y] = ++idx;
            x = mp[x], y = mp[y];
            g[x][y] = g[y][x] = std::min(g[x][y], z);
        }
        std::cout << _quickm() << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p344{
    const int N = 128, INF = 0x3f3f3f3f;
    int n, m, e[N][N], d[N][N], mid[N][N];
    std::vector<int> pa;
    void _get_path(int i, int j){
        if(mid[i][j] == 0)return;
        _get_path(i, mid[i][j]);
        pa.emplace_back(mid[i][j]);
        _get_path(mid[i][j], j);
    }
    void _deal(){
        std::cin >> n >> m;
        std::memset(e, 0x3f, sizeof e);
        for(int i=0; i<m; ++i){
            int u, v, l;
            std::cin >> u >> v >> l;
            e[u][v] = e[v][u] = std::min(e[u][v], l);
        }
        for(int i=1; i<=n; ++i)e[i][i] = 1;
        std::memcpy(d, e, sizeof e);
        int ans = INF;
        for(int k=1; k<=n; ++k){
            for(int i=1; i<k; ++i){
                for(int j=i+1; j<k; ++j){
                    if((long long)d[i][j] + e[j][k] + e[k][i] < ans){
                        ans = d[i][j] + e[j][k] + e[k][i];
                        pa.clear();
                        pa.push_back(i);
                        _get_path(i, j);
                        pa.push_back(j);
                        pa.push_back(k);
                    }
                }
            }
            for(int i=1; i<=n; ++i){
                for(int j=1; j<=n; ++j){
                    if(d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                        mid[i][j] = k;
                    }
                }
            }
        }
        if(ans == INF){
            std::cout<< "No solution." << std::endl;
            return;
        }
        for(auto &x : pa)std::cout << x << " ";
    }
    int main(int argc,const char *argv[]){
        _deal();;
        return 0;
    }
};

namespace p343{
    const int N = 32;
    int e[N][N];
    int n, m;
    std::string tmp;
    bool _deal(){
        if((std::cin >> n >> m, (!n && !m)))return false;
        std::memset(e, 0, sizeof e);
        int t=0, t1=0, t2=0, r;
        std::string ans;
        while(++t<=m){
            r = 0;
            std::cin >> tmp;
            if(e[tmp[0]-'A'][tmp[2]-'A'] == 1)continue;
            if(t1 || t2)continue;
            e[tmp[0]-'A'][tmp[2]-'A'] = 1;
            for(int k=0; k<n; ++k){
                for(int i=0; i<n; ++i){
                    for(int j=0; j<n; ++j){
                        e[i][j] |= e[i][k] && e[k][j];
                    }
                }
            }
            for(int i=0; i<n; ++i){
                for(int j=i+1; j<n; ++j){
                    if(e[i][j] && e[j][i])t1 = t;
                    r += e[i][j] || e[j][i];
                }
            }
            if(!t1 && r == n*(n-1)/2)t2 = t;
        }
        if(!t1 && !t2){
            std::cout <<
                "Sorted sequence cannot be determined." <<
            std::endl;
            return true;
        }
        if(t1){
            std::cout <<
                "Inconsistency found after " << t1 << " relations." << 
            std::endl;
            return true;
        }
        std::vector<int> mp(n), tmp(n);
        for(int i=0; i<n; ++i){
            for(int j=i+1; j<n; ++j){
                if(e[i][j])++mp[j];
                if(e[j][i])++mp[i];
            }
        }
        std::iota(begin(tmp), end(tmp), 0);
        std::sort(begin(tmp), end(tmp), [&](int i, int j){
                return mp[i] < mp[j]; });
        ans = "Sorted sequence determined after ";
        ans += std::to_string(t2);
        ans += " relations: ";
        for(int i=0; i<n; ++i)ans += tmp[i] + 'A';
        std::cout << ans << '.' << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p342{
    using pii = std::pair<int, int>;
    const int N = 25000 + 12, INF = 0x3f3f3f3f;
    int head[N], ne[N << 4], to[N << 4], cost[N << 4];
    int color[N], in[N], d[N], vi[N];
    std::vector<int> ccs[N];
    int idx, cnt;
    int t, r, p, s;
    std::queue<int> q;
    std::priority_queue<pii, std::vector<pii>,
                        std::greater<pii>> pq;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx]   = head[x];
        head[x]   = idx;
    }
    void _dfs(int x){
        color[x] = cnt;
        ccs[cnt].push_back(x);
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!color[y])_dfs(y);
        }
    }
    void _dijkstra(int c){
        for(auto x : ccs[c])pq.emplace(d[x], x);
        while(pq.size()){
            int x = pq.top().second;
            pq.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[y] > d[x] + cost[i]){
                    d[y] = d[x] + cost[i];
                    if(color[x] == color[y]){
                        pq.emplace(d[y], y);
                    }
                }
                if(color[x] == color[y])continue;
                if(!--in[color[y]])q.emplace(color[y]);
            }
        }
    }
    void _deal(){
        std::cin >> t >> r >> p >> s;
        for(int i=0; i<r; ++i){
            int u, v, w;
            std::cin >> u >> v >> w;
            _add(u, v, w), _add(v, u, w);
        }
        for(int i=1; i<=t; ++i){
            if(!color[i])++cnt, _dfs(i);
        }
        for(int i=0; i<p; ++i){
            int u, v, w;
            std::cin >> u >> v >> w;
            _add(u, v, w);
            ++in[color[v]];
        }
        std::memset(d, 0x7f, sizeof d);
        d[s] = 0;
        q.emplace(color[s]);
        for(int i=1; i<=cnt; ++i){
            if(!in[i])q.emplace(i);
        }
        while(q.size()){
            int c = q.front();q.pop();
            _dijkstra(c);
        }
        for(int i=1; i<=t; ++i){
            std::cout
                <<
                (d[i] >= 1e9 ? "NO PATH" : std::to_string(d[i]))
                <<
            std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p341{
    using pii = std::pair<int, int>;
    using fun = std::function<int(int, int)>;
    const int N = 1e5 + 12;
    int head1[N], head2[N], ne[N * 5 * 2], to[N * 5 * 2];
    int cost[N], d1[N], d2[N], vi[N];
    int n, m, idx;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx]   = head1[x];
        head1[x]  = idx;

        to[++idx] = x;
        ne[idx]   = head2[y];
        head2[y]  = idx;
    }
    void _spfa(int *head, int *d, int s, fun _cmp, fun _get){
        std::memset(vi, 0, sizeof vi);
        std::queue<int> q;
        q.emplace(s);
        d[s] = cost[s];
        vi[s] = 1;
        while(q.size()){
            int x = q.front();q.pop();
            vi[x] = 0;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(_cmp(d[y], _get(d[x], cost[y]))){
                    d[y] = _get(d[x], cost[y]);
                    if(!vi[y])vi[y] = 1, q.emplace(y);
                }
            }
        }
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i)std::cin >> cost[i];
        for(int i=1; i<=m; ++i){
            int x, y, z;
            std::cin >> x >> y >> z;
            _add(x, y);
            if(z == 2)_add(y, x);
        }
        std::memset(d1, 0x3f, sizeof d1);
        std::memset(d2, 0x00, sizeof d2);
        _spfa(head1, d1, 1,
                [&](int a, int b){return a > b;},
                [&](int a, int b){return std::min(a, b);}
            );
        _spfa(head2, d2, n,
                [&](int a, int b){return a < b;},
                [&](int a, int b){return std::max(a, b);}
            );
        int ans = 0;
        for(int i=1; i<=n; ++i)ans = std::max(ans, d2[i]-d1[i]);
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p341_fuck{
    using pii = std::pair<int, int>;
    using fun = std::function<int(int, int)>;
    using pfun = std::function<bool(const pii &a, const pii &b)>;
    const int N = 1e5 + 12;
    int head1[N], head2[N], ne[N * 5 * 2], to[N * 5 * 2];
    int d1[N], d2[N], vi[N], cost[N];
    int n, m, idx;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx]  = head1[x];
        head1[x] = idx;

        to[++idx] = x;
        ne[idx]  = head2[y];
        head2[y] = idx;
    }
    void _dijkstra(int *head, int *d, int s, int e,
                    fun _cmp, fun _get, pfun pcmp){
        std::memset(vi, 0, sizeof vi);
        std::priority_queue<pii,
            std::vector<pii>,
            decltype(pcmp)> q(pcmp);
        q.emplace(cost[s], s);
        d[s] = cost[s];
        while(q.size()){
            auto [dd, x] = q.top();q.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(_cmp(d[y], _get(d[x], cost[y]))){
                    d[y] = _get(d[x], cost[y]);
                    q.emplace(d[y], y);
                }
            }
        }
    }
    int _calc(){
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q1;
        std::priority_queue<pii> q2;
        d1[1] = cost[1];
        d2[n] = cost[n];
        q1.emplace(d1[1], 1);
        q2.emplace(d2[n], n);
        while(q1.size()){
            int x = q1.top().second;q1.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head1[x]; i; i=ne[i]){
                int y = to[i];
                if(d1[y] <= std::min(d1[x], cost[y]))continue;
                d1[y] = std::min(d1[x], cost[y]);
                q1.emplace(d1[y], y);
            }
        }
        std::memset(vi, 0, sizeof vi);
        while(q2.size()){
            int x = q2.top().second; q2.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head2[x]; i; i=ne[i]){
                int y = to[i];
                if(d2[y] >= std::max(d2[x], cost[y]))continue;
                d2[y] = std::max(d2[x], cost[y]);
                q2.emplace(d2[y], y);
            }
        }
        for(int i=1; i<=n; ++i) std::cout << d1[i] << "  ";
        std::cout << std::endl;
        for(int i=1; i<=n; ++i) std::cout << d2[i] << "  ";
        std::cout << std::endl;
        int ans = 0;
        for(int i=1; i<=n; ++i)ans = std::max(ans, d2[i] - d1[i]);
        return ans;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i)std::cin >> cost[i];
        for(int i=1; i<=m; ++i){
            int x, y, z;
            std::cin >> x >> y >> z;
            _add(x, y);
            if(z == 2)_add(y, x);
        }
        std::memset(d1, 0x3f, sizeof d1);
        std::memset(d2, 0x00, sizeof d2);
        std::cout << _calc() << std::endl;
        //_dijkstra(head1, d1, 1, n,
                    //[&](int a, int b){return a > b;},
                    //[&](int a, int b){return std::min(a, b) ;},
                    //[&](const pii& a, const pii &b){return a.first > b.first;}
                    //);
        //_dijkstra(head2, d2, n, 1,
                    //[&](int a, int b){return a < b;},
                    //[&](int a, int b){return std::max(a, b);},
                    //[&](const pii& a, const pii &b){return a.first < b.first;}
                    //);
        //int ans = 0;
        //for(int i=1; i<=n; ++i)ans = std::max(ans, d2[i] - d1[i]);
        //std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p340__{
    const int N = 1024;
    int head[N], to[N << 10], ne[N << 10], cost[N << 10];
    int vi[N], d[N];
    int n, p, k;
    int idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _bfs(int m){
        std::deque<int> q;
        std::memset(vi, 0, sizeof vi);
        std::memset(d,  0x3f, sizeof d);
        int ans = 0;
        q.push_back(1);
        d[0] = 0;
        while(q.size()){
            int now = q.front();q.pop_front();
            if(now == n)break;
            if(vi[now])continue;
            vi[now] = 1;
            for(int i=head[now]; i; i=ne[i]){
                int y = to[i];
                int c = cost[i] > m;
                if(d[y] <= c + d[now])continue;
                d[y] = c + d[now];
                if(c == 1)q.push_back(y);
                if(c == 0)q.push_front(y);
            }
        }
        return d[n] <= k;
    }
    int _b_search(int l, int r){
        while(l < r){
            int m = l + ((r - l) >> 1);
            if(_bfs(m)){
                r = m;
            }else{
                l = m + 1;
            }
        }
        return r;
    }
    void _deal(){
        int r = INT_MIN;
        std::cin >> n >> p >> k;
        for(int i=0; i<p; ++i){
            int x, y, z;
            std::cin >> x >> y >> z;
            _add(x, y, z), _add(y, x, z);
            r = std::max(r, z);
        }
        if(!_bfs(r)){
            std::cout << "-1" << std::endl;
            return;
        }
        std::cout << _b_search(0, r + 1) << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

