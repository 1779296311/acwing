/*********************************************
*     ------------------------
*     ------------------------
*     file name: graph_theory_pro.cpp
*     author   : @ JY
*     date     : 2021--01--05
**********************************************/
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
#include <bitset>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <climits>
#include <cstring>
#include <vector>
#include <queue>
#include <functional>
#include <stdlib.h>

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
namespace p340{
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

