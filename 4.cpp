/*********************************************
*     ------------------------
*     ------------------------
*     file name: 4.cpp
*     author   : @ JY
*     date     : 2020--11--21
**********************************************/
#include <iostream>
#include <climits>
#include <cmath>
#include <numeric>
#include <map>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <stdlib.h>

namespace p1268{
const int N = 500010;
int n, m;
int tree[N];
void _update(int x, int v){
    for(; x<N; x+=x&-x)tree[x] += v;
};
int _query(int x){
    int ans = 0;
    for(; x; x-=x&-x)ans += tree[x];
    return ans;
}
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        while(m--){
            int t, l, r;
            std::cin >> t >> l;
            if(t == 1){
                std::cin >> r;
                _update(l, 1);
                _update(r+1, -1);
            }else{
                std::cout << _query(l) % 2 << std::endl;
            }
        }
        return 0;
    }
};

namespace p1232{
const int M = 2e6 + 10;
struct node{
    int la, ra, lb, rb, lc, rc;
    long long h;
}att[M];
int arr[M], sum[M];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int A, B, C, m, v;
        std::cin >> A >> B >> C >> m;
        std::function<int(int, int, int)> _pos
            = [&](int i, int j, int k){
                return ((i - 1) * B + j - 1) * C + k; 
            };
        std::function<void(int *a, int, int, int, int, int, int, int)> _insert
            = [&](int *a, int x1, int x2, int y1, int y2, int z1, int z2, int v){
                    a[_pos(x1,   y1,   z1)  ] += v;
                    a[_pos(x1,   y2+1, z2+1)] += v;
                    a[_pos(x2+1, y2+1, z1)  ] += v;
                    a[_pos(x2+1, y1,   z2+1)] += v;

                    a[_pos(x1,   y1,   z2+1)] -= v;
                    a[_pos(x1,   y2+1, z1)  ] -= v;
                    a[_pos(x2+1, y1,   z1)  ] -= v;
                    a[_pos(x2+1, y2+1, z2+1)] -= v;
            };
        std::function<bool(int)> _check = [&](int mid){
            std::memcpy(sum, arr, sizeof(arr));
            for(int i=1; i<=mid; ++i){
                auto &[x1, x2, y1, y2, z1, z2, v] = att[i];
                _insert(sum, x1, x2, y1, y2, z1, z2, v);
            }
            for(int i=1; i<=A; ++i){
                for(int j=1; j<=B; ++j){
                    for(int k=1; k<=C; ++k){
                        int idx  = _pos(i, j, k);
                        sum[idx] += sum[_pos(i-1, j-1, k-1)] + sum[_pos(i-1, j, k)] +
                                    sum[_pos(i, j-1, k)] + sum[_pos(i, j, k-1)] -
                                   (sum[_pos(i-1, j, k-1)] + sum[_pos(i-1, j-1, k)] +
                                    sum[_pos(i, j-1, k-1)]);
                        if(sum[idx] < 0)return true;
                    }
                }
            }
            return false;
        };
        for(int i=1; i<=A; ++i){
            for(int j=1; j<=B; ++j){
                for(int k=1; k<=C; ++k){
                    std::cin >> v;
                    _insert(arr, i, i, j, j, k, k, v);
                }
            }
        }
        for(int i=1; i<=m; ++i){
            long long la, ra, lb, rb, lc, rc, h;
            std::cin >> att[i].la >> att[i].ra >> att[i].lb >>
                att[i].rb >> att[i].lc >> att[i].rc >> att[i].h;
            att[i].h *= -1;
        }

        int l = 1, r = m; 
        while(l < r){
            int mid = l + ((r - l) >> 1);
            if(_check(mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        std::cout << l << std::endl;
        return 0;
    }
};
namespace p736{
    int main(int argc,const char *argv[]){
        int n, q, l, r;
        std::cin >> n >> q;
        std::vector<int> res(n+2);
        while(q--){
            std::cin >> l >> r;
            ++res[l], --res[r+1];
        }
        int ans = 0;
        for(int i=1; i<=n; ++i)std::cout << (ans += res[i]) << " ";
        return 0;
    }
};
namespace p393{
    int main(int argc,const char *argv[]){
    }
};
namespace p368{
const int N = 1e5 + 2, M = N * 6;
int head[M], new_head[M], next[M], to[M], w[M], vi[M];
int dfn[N], low[N], in_st[N], st[N], scc[N], id[N], d[N];
int n, m, scc_cnt, sidx, ncnt, eidx;

void _add_edge(int *h, int x, int y, int v){
    to[++eidx] = y;
    next[eidx] = h[x];
    w[eidx] = v;
    h[x] = eidx;
}
void _tarjan(int x){
    dfn[x] = low[x] = ++ncnt;
    st[++sidx] = x;
    in_st[x] = 1;
    for(int t=head[x]; t; t=next[t]){
        int y = to[t];
        if(!dfn[y]){
            _tarjan(y);
            low[x] = std::min(low[x], low[y]);
        }else if(in_st[y]){
            low[x] = std::min(low[x], dfn[y]);
        }
    }
    if(dfn[x] != low[x])return;
    ++scc_cnt;
    int y;
    do{
        y        = st[sidx--];
        in_st[y] = 0;
        id[y]    = scc_cnt;
        ++scc[scc_cnt];
    }while(x != y);
}
int _dfs(int x){
    int ans = 0;
    vi[x]   = 1;
    for(int t=head[x]; t; t=next[t]){
        int y = to[t];
        if(id[x] == id[y])ans += w[t];
        if(vi[y] || id[x] != id[y])continue;
        ans += _dfs(y);
    }
    return ans;
}
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        for(int i=0; i<m; ++i){
            int t, a, b;
            std::cin >> t >> a >> b;
            switch(t){
                case 1: _add_edge(head, a, b, 0);
                case 3: _add_edge(head, b, a, 0); break;
                case 2: _add_edge(head, a, b, 1); break;
                case 4: _add_edge(head, b, a, 1); break;
                case 5: _add_edge(head, a, b, 0); break;
            }
        }
        for(int i=1; i<=n; ++i)_add_edge(head, 0, i, 1);
        _tarjan(0);
        bool f = 0;
        for(int i=0; i<=n; ++i){
            if(_dfs(i)){
                f = 1;
                break;
            }
        }
        if(f){
            std::cout << -1 << std::endl;
            return 0;
        }
        for(int x=0; x<=n; ++x){
            for(int t=head[x]; t; t=next[t]){
                int y = to[t];
                if(id[y] == id[x])continue;
                _add_edge(new_head, id[x], id[y], w[t]);
            }
        }
        for(int x=scc_cnt; x>=1; --x){
            for(int t=new_head[x]; t; t=next[t]){
                int y = to[t];
                if(d[y] < d[x] + w[t])d[y] = d[x] + w[t];
            }
        }
        long long res = 0;
        for(int x=1; x<=scc_cnt; ++x)res += d[x] * scc[x];
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p362_tree_array_1{
const int N = 50002;
    struct node{
        int l, r, c;
        bool operator () (const node &a, const node &b) const {
            return a.l < b.l;
        }
        bool operator < (const node &other){
            return r < other.r;
        }
    };
    int n;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::vector<node> nodes(n);
        for(int i=0; i<n; ++i){
            std::cin >> nodes[i].l >> nodes[i].r >> nodes[i].c;
        }
        std::sort(begin(nodes), end(nodes));
        std::set<int> mp;
        for(auto [l, r, c] : nodes){
            for(auto it=rbegin(mp); it!=rend(mp) && *it>=l && --c; ++it);
            while(c && (c-=mp.insert(r--).second));
        }
        std::cout << mp.size() << std::endl;
        return 0;
    }
};
namespace p362_tree_array{
    struct node{
        int l, r, c;
        bool operator < (const node &other) {
            return r < other.r;
        }
    };
const int N = 50002;
std::vector<int> selected(N), _f(N), tr(N);

    int main(int argc,const char *argv[]){
        int n, res = 0;
        std::iota(begin(_f), end(_f), 0);

        std::function<int(int)> _find = [&](int i){
            return _f[i] == i ? i : _f[i] = _find(_f[i]); };
        std::function<void(int, int)> _update = [&](int x, int v){
            for(; x<N; x+=x&-x)tr[x] += v; };
        std::function<int(int)> _query = [&](int x){
            int ans = 0;
            for(; x; x-=x&-x)ans += tr[x];
            return ans;
        };

        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::vector<node> nodes(n);
        for(auto &nd : nodes){
            std::cin >> nd.l >> nd.r >> nd.c;
        }
        std::sort(begin(nodes), end(nodes));
        for(auto [l, r, c] : nodes){
            c -= _query(r) - _query(l-1);
            while(c>0 && r>=l){
                if(!selected[r]){
                    selected[r] = 1;
                    ++res;
                    --c;
                    _f[r] = r - 1;
                    _update(r, 1);
                }
                r = _find(r);
            }
        }
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p362{
    struct node{
        int l, r, c;
        bool operator < (const node &other){
            return r < other.r;
        }
    };
    int main(int argc,const char *argv[]){
        int n, res = 0, i;
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::vector<node> nodes(n);
        std::vector<int>  selected(50002);
        for(auto &nd : nodes){
            std::cin >> nd.l >> nd.r >> nd.c;
        }
        std::sort(begin(nodes), end(nodes));
        for(auto [l, r, c] : nodes){
            i = l;
            while(i<=r && c)c -= selected[i++];
            while(r>=l && c>0){
                if(!selected[r]){
                    selected[r] = 1;
                    ++res;
                    --c;
                }
                --r;
            }
        }
        std::cout << res << std::endl;
        return 0;
    }
};

namespace p354{
using pii = std::pair<int, int>;
const int N = 300005;
int fa[N][22], deep[N], w[N];
int head[N << 1], next[N << 1], to[N << 1];
int d1[N << 1], d2[N << 1], res[N];
std::vector<pii> op1[N], op2[N];
int n, m, idx, lg;

void _add_adge(int x, int y){
    to[++idx] = y;
    next[idx] = head[x];
    head[x]   = idx;
}
void _deal_f(int x, int p){
    deep[x]  = deep[p] + 1;
    fa[x][0] = p;
    for(int i=1; (1<<i)<=deep[x]; ++i){
        fa[x][i] = fa[fa[x][i-1]][i-1];
    }
    for(int t=head[x]; t ; t=next[t]){
        if(to[t] == p)continue;
        _deal_f(to[t], x);
    }
}
int _lca(int x, int y){
    if(deep[x] < deep[y])std::swap(x, y);
    for(int i=lg; i>=0; --i){
        if(deep[fa[x][i]] >= deep[y])x = fa[x][i];
    }
    if(x == y)return x;
    for(int i=lg; i>=0; --i){
        if(fa[x][i] == fa[y][i])continue;
        x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}
void _update(int s, int e, int n){
    int lca = _lca(s, e);
    op1[s].emplace_back(deep[s], 1);
    op2[e].emplace_back(deep[s] - 2*deep[lca] + n, 1);

    op2[lca].emplace_back(deep[s] - 2*deep[lca] + n, -1);
    op1[fa[lca][0]].emplace_back(deep[s], -1);
}
void _query(int x, int p, int n){
    int t1 = w[x] + deep[x];
    int t2 = w[x] - deep[x] + n;
    int p1 = d1[t1], p2 = d2[t2];
    for(int t=head[x]; t; t=next[t]){
        if(to[t] == p)continue;
        _query(to[t], x, n);
    }
    for(auto &[i, v] : op1[x])d1[i] += v;
    for(auto &[i, v] : op2[x])d2[i] += v;
    res[x] = (d1[t1] - p1) + (d2[t2] - p2);
}
    int main(int argc,const char *argv[]){
        int u, v;
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        lg = int(log(n) / log(2)) + 1;
        for(int i=1; i<n; ++i){
            std::cin >> u >> v;
            _add_adge(u, v);
            _add_adge(v, u);
        }
        for(int i=1; i<=n; ++i)std::cin >> w[i];
        _deal_f(1, 0);
        for(int i=0; i<m; ++i){
            std::cin >> u >> v;
            _update(u, v, n);
        }
        _query(1, 0, n);
        for(int i=1; i<=n; ++i)std::cout << res[i] << " ";
        return 0;
    }
};
namespace p353{
const int N = 1e5 + 5;
struct node {int l, r, m,  id;} tree[N * 60];
int to[N << 1], next[N << 1], head[N << 1], lg[N];
int deep[N], fa[N][22], idx, code, cntz;
int rt[N];
    int main(int argc,const char *argv[]){
        int n, m, x, y, z;
        std::cin >> n >> m;
        std::vector<int> res (n);
        for(int i=1; i<=n; ++i)lg[i] = lg[i-1] + (1 << lg[i-1] == i);
        std::function<void(int, int)> _add_edge
            = [&](int x, int y){
                to[++idx] = y;
                next[idx] = head[x];
                head[x]   = idx;
            };
        std::function<void(int, int)> _deal_f
            = [&](int x, int p){
                deep[x]  = deep[p] + 1;
                fa[x][0] = p;
                for(int i=1; (1<<i)<=deep[x]; ++i){
                    fa[x][i] = fa[fa[x][i-1]][i-1];
                }
                for(int id=head[x]; id ; id=next[id]){
                    if(to[id] == p)continue;
                    _deal_f(to[id], x);
                }
            };
        std::function<int(int, int)> _lca
            = [&](int x, int y){
                if(deep[x] < deep[y])std::swap(x, y);
                while(deep[x] > deep[y])x = fa[x][lg[deep[x]-deep[y]] - 1];
                if(x == y)return x;
                for(int i=lg[deep[x]]; i>=0; --i){
                    if(fa[x][i] == fa[y][i])continue;
                    x = fa[x][i], y = fa[y][i];
                }
                return fa[x][0];
            };
        std::function<void(int)> _pushup
            = [&](int id){
                int l = tree[id].l, r = tree[id].r;
                int v = tree[l].m >= tree[r].m ? l : r;
                tree[id].m  = tree[v].m;
                tree[id].id = tree[v].id;
            };
        std::function<void(int &, int, int, int, int)> _update
            = [&](int &id, int l, int r, int x, int v){
                if(!id) id = ++code;
                if(l == r){
                    tree[id].m += v;
                    tree[id].id = l;
                    return ;
                }
                int m = l + ((r - l) >> 1);
                if(x <= m){
                    _update(tree[id].l, l, m, x, v);
                }else{
                    _update(tree[id].r, m+1, r, x, v);
                }
                _pushup(id);
            };
        std::function<int(int, int, int, int)> _merge
            = [&](int p, int q, int l, int r){
                if(!p || !q)return p | q;
                if(l == r){
                    tree[p].m += tree[q].m;
                    return p;
                }
                int m = l + ((r - l) >> 1);
                tree[p].l = _merge(tree[p].l, tree[q].l, l, m);
                tree[p].r = _merge(tree[p].r, tree[q].r, m+1, r);
                _pushup(p);
                return p;
            };
        std::function<void(int, int)> _query
            = [&](int x, int p){
                for(int id=head[x]; id ; id=next[id]){
                    if(to[id] == p)continue;
                    _query(to[id], x);
                    rt[x] = _merge(rt[x], rt[to[id]], 1, cntz);
                }
                if(tree[rt[x]].m == 0)return;
                res[x-1] = tree[rt[x]].id;
            };
        for(int i=1; i<n; ++i){
            std::cin >> x >> y;
            _add_edge(x, y);
            _add_edge(y, x);
        }
        _deal_f(1, 0);
        std::vector<int> a(m+1), b(m+1), zp(m+1), idz;
        for(int i=1; i<=m; ++i)std::cin >> a[i] >> b[i] >> zp[i];
        idz = zp;
        std::sort(begin(idz), end(idz));
        cntz =  unique(begin(idz), end(idz)) - idz.begin();
        for(int i=1; i<=m; ++i){
            int p  = _lca(a[i], b[i]), pp = fa[p][0];
            int zi = std::lower_bound(begin(idz), end(idz), zp[i]) - begin(idz);
            _update(rt[a[i]], 1, cntz, zi, 1);
            _update(rt[b[i]], 1, cntz, zi, 1);
            _update(rt[p], 1, cntz, zi, -1);
            _update(rt[pp], 1, cntz, zi, -1);
        }
        _query(1, 0);
        for(auto &x : res)std::cout << zp[x] << std::endl;
        return 0;
    }
};

namespace p353_fuck{
const int N = 100200;
int to[N << 1], head[N << 1], next[N << 1];
int fa[N << 1][22], deep[N], lg[N], idx;
std::unordered_map<int, std::unordered_map<int, int>> mp;
    int main(int argc,const char *argv[]){
        int n, m, x, y, z;
        std::cin >> n >> m;
        std::vector<int> res;
        for(int i=1; i<=n; ++i){
            lg[i] = lg[i-1] + (1 << lg[i-1] == i);
        }
        std::function<void(int, int)> _add_edge
            = [&](int x, int y){
                to[++idx] = y;
                next[idx] = head[x];
                head[x]   = idx;
            };
        std::function<void(int, int)> _deal_f
            = [&](int x, int p){
                deep[x]  = deep[p] + 1;
                fa[x][0] = p;
                for(int i=1; (1<<i)<=deep[x]; ++i){
                    fa[x][i] = fa[fa[x][i-1]][i-1];
                }
                for(int id=head[x]; id; id=next[id]){
                    if(to[id] == p)continue;
                    _deal_f(to[id], x);
                }
            };
        std::function<int(int, int)> _lca
            = [&](int x, int y){
                if(deep[x] < deep[y])std::swap(x, y);
                while(deep[x] > deep[y])x = fa[x][lg[deep[x] - deep[y]] - 1];
                if(x == y)return x;
                for(int i=lg[deep[x]]; i>=0; --i){
                    if(fa[x][i] == fa[y][i])continue;
                    x = fa[x][i], y = fa[y][i];
                }
                return fa[x][0];
            };
        std::function<void(int, int, int)> _update
            = [&](int x, int y, int z){
                ++mp[x][z];
                ++mp[y][z];
                int p = _lca(x, y);
                --mp[p][z];
                --mp[fa[p][0]][z];
            };
        std::function<void(int, int)> _query
            = [&](int x, int p){
                for(int id=head[x]; id; id=next[id]){
                    if(to[id] == p)continue;
                    _query(to[id], x);
                    for(auto &[k, v] : mp[to[id]])mp[x][k] += v;
                }
                if(!mp[x].size())return;
                std::vector<std::pair<int, int>> t(begin(mp[x]), end(mp[x]));
                std::sort(begin(t), end(t), [&](auto &a, auto &b){
                        return a.second == b.second ?
                               a.first > b.first :
                               a.second < b.second; });
                res[x-1] = t.back().first;
            };
        for(int i=1; i<n; ++i){
            std::cin >> x >> y;
            _add_edge(x, y);
            _add_edge(y, x);
        }
        _deal_f(1, 0);
        for(int i=0; i<m; ++i){
            std::cin >> x >> y >> z;
            _update(x, y, z);
        }
        _query(1, 0);
        for(auto &x : res)std::cout << x << std::endl;
        return 0;
    }
};
//352. 闇の連鎖
namespace p352{
const int N = 100200;
int head[N << 1], next[N << 1], edge[N << 1], to[N << 1];
int deep[N], fa[N << 1][22], lg[N], date[N];
int idx, ans;
    int main(int argc,const char *argv[]){
        int n, m, a, b;
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
        std::function<void(int, int, int)> _add_edge
            = [&](int a, int b, int v){
                edge[++idx] = a;
                to[idx]     = b;
                next[idx]   = head[a];
                head[a]     = idx;
            };
        std::function<void(int, int)> _deal_f
            = [&](int x, int p){
                deep[x]  = deep[p] + 1;
                fa[x][0] = p;
                for(int i=1; (1 << i)<=deep[x]; ++i){
                    fa[x][i] = fa[fa[x][i-1]][i-1];
                }
                for(int t=head[x]; t; t=next[t]){
                    if(to[t] == p)continue;
                    _deal_f(to[t], x);
                }
            };
        std::function<int(int, int)> _lca
            = [&](int x, int y){
                if(deep[x] < deep[y])std::swap(x, y);
                while(deep[x] > deep[y])x = fa[x][lg[deep[x] - deep[y]] - 1];
                if(x == y)return x;
                for(int i=lg[deep[x]]; i>=0; --i){
                    if(fa[x][i] == fa[y][i])continue;
                    x = fa[x][i], y = fa[y][i];
                }
                return fa[x][0];
            };
        std::function<void(int, int, int)> _update
            = [&](int x, int y, int v){
                date[x] += v;
                date[y] += v;
                date[_lca(x, y)] -= v << 1; 
            };
        std::function<void(int, int)> _query
            = [&](int x, int p){
                for(int t=head[x]; t ; t=next[t]){
                    if(to[t] == p)continue;
                    _query(to[t], x);
                    date[x] += date[to[t]];
                    if(date[to[t]] == 0){
                        ans += m;
                    }else if(date[to[t]] == 1){
                        ans += 1;
                    }
                }
            };
        for(int i=1; i<n; ++i){
            std::cin >> a >> b;
            _add_edge(a, b, 0);
            _add_edge(b, a, 0);
        }
        _deal_f(1, 0);
        for(int i=0; i<m; ++i){
            std::cin >> a >> b;
            _update(a, b, 1);
        }
        _query(1, 0);
        std::cout << ans << std::endl;
        return 0;
    }
};
// 差分
namespace p144{
    struct _node{
        int w, id;
        _node(int w, int i) : w(w), id(i) {}
    };
int trie[100010 * 31][2];
    int main(int argc,const char *argv[]){
        int n, u, v, w, idx = 0;
        std::cin >> n;
        std::unordered_map<int, std::vector<_node>> e;
        std::vector<int> d(n+1), vi(n+1);
        for(int i=0; i<n; ++i){
            std::cin >> u >> v >> w;
            e[u].emplace_back(w, v);
            e[v].emplace_back(w, u);
        }
        std::function<void(int)> _dfs_add = [&](int id){
            vi[id] = 1;
            for(auto &x : e[id]){
                if(vi[x.id])continue;
                d[x.id] = d[id] ^ x.w;
                _dfs_add(x.id);
            }
        };
        _dfs_add(0);
        std::function<void(int)> _insert = [&](int x){
            int p = 0;
            for(int i=31; i>=0; --i){
                int cur = x >> i & 1;
                if(!trie[p][cur])trie[p][cur] = ++idx;
                p = trie[p][cur];
            }
        };
        std::function<int(int)> _search = [&](int x){
            int p = 0, ans = 0;
            for(int i=31; i>=0; --i){
                int cur = x >> i & 1;
                if(trie[p][!cur]){
                    p = trie[p][!cur];
                    ans = ans << 1 | !cur;
                }else{
                    p = trie[p][cur];
                    ans = ans << 1 | cur;
                }
            }
            return ans ^ x;
        };
        int res = 0;
        for(int i=0; i<n; ++i){
            _insert(d[i]);
            res = std::max(res, _search(d[i]));
        }
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p143{
int trie[100010 * 31][2];
    int main(int argc,const char *argv[]){
        int N, idx = 0;
        std::cin >> N;
        std::function<void(int)> _insert = [&](int x){
            int p = 0;
            for(int i=31; i>=0; --i){
                int cur = x >> i & 1;
                if(!trie[p][cur])trie[p][cur] = ++idx;
                p = trie[p][cur];
            }
        };
        std::function<int(int x)> _search = [&](int x){
            int ans = 0, p = 0;
            for(int i=31; i>=0; --i){
                int cur = x >> i & 1;
                if(trie[p][!cur]){
                    p = trie[p][!cur];
                    ans = ans << 1 | !cur;
                }else{
                    p = trie[p][cur];
                    ans = ans << 1 | cur;
                }
            }
            return ans ^ x;
        };
        int res = 0, x;
        while(N--){
            std::cin >> x;
            _insert(x);
            res = std::max(res, _search(x));
        }
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p101{
    int main(int argc,const char *argv[]){
        int N, P, H, M, A, B;
        std::cin >> N >> P >> H >> M;
        std::vector<int> h(N);
        std::unordered_set<int> mp;
        h[0] = H;
        while(M--){
            std::cin >> A >> B;
            int l = std::min(A, B), r = std::max(A, B);
            if(!mp.insert(l * N + r).second)continue;
            if(r - l < 2)continue;
            --h[l], ++h[r - 1];
        }
        int sum = 0;
        for(auto &x : h)std::cout << (sum += x) << std::endl;
        return 0;
    }
};
namespace{
    int main(int argc,const char *argv[]){
        int n, m, l, r, c;
        std::cin >> n >> m;
        std::vector<int> nums(n+1), dc(n+1);
        for(int i=0; i<n; ++i)std::cin >> nums[i];
        dc = nums;
        for(int i=1; i<n; ++i)dc[i] -= nums[i-1];
        while(m--){
            std::cin >> l >> r >> c;
            dc[l-1] += c, dc[r] -= c;
        }
        int sum = 0;
        for(int i=0; i<n; ++i){
            std::cout << (sum += dc[i]) << " ";
        }
        std::cout << std::endl;
        return 0;
    }
};
namespace p100{
    int main(int argc,const char *argv[]){
        long long n, pre = 0, q = 0, p = 0, val;
        std::cin >> n;
        std::vector<long long> nums(n+1);
        for(int i=1; i<=n; ++i)std::cin >> nums[i];
        for(int i=2; i<=n; ++i){
            long long c = nums[i] - nums[i-1];
            if(c > 0){
                p += c;
            }else{
                q -= c;
            }
        }
        std::cout << std::max(p, q) << std::endl;
        std::cout << abs(p - q) + 1 << std::endl;
        return 0;
    }
};

namespace p99{
int e[5002][5002];
    int main(int argc,const char *argv[]){
        int N, R, x, y, w;
        std::cin >> N >> R;
        int m = R, n = R, res = 0;
        while(N--){
            std::cin >> x >> y >> w;
            e[x + 1][y + 1] += w;
            m = std::max(m, x + 1);
            n = std::max(n, y + 1);
        }
        for(int i=1; i<=m; ++i){
            for(int j=0; j<=n; ++j){
                e[i][j] += e[i][j-1] + e[i-1][j] - e[i-1][j-1];
            }
        }
        for(int i=R; i<=m; ++i){
            for(int j=R; j<=n; ++j){
                res = std::max(res, e[i][j] - e[i-R][j] - e[i][j-R] + e[i-R][j-R]);
            }
        }
        std::cout << res << std::endl;
        return 0;
    }
};

namespace p98{
    int main(int argc,const char *argv[]){
        using ll = long long;
        using pll = std::pair<ll, ll>;
        ll n, N, A, B;
        std::cin >> n;
        std::function<void(void)> _deal = [&](void){
            std::cin >> N >> A >> B;
            std::function<pll(ll, ll)> _dfs = [&](ll n, ll m){
                if(n == 0)return (pll){0, 0};
                ll len = 1ll << (n - 1), cnt = 1ll << (2*n - 2);
                auto [x, y] = _dfs(n-1, m % cnt);
                int pos = m / cnt;
                if(pos == 0)return (pll){-y-len, -x+len};
                if(pos == 1)return (pll){x+len, y+len};
                if(pos == 2)return (pll){x+len, y-len};
                return (pll){y-len, x-len};
            };
            auto [x1, y1] = _dfs(N, A - 1);
            auto [x2, y2] = _dfs(N, B - 1);
            double x = x1 - x2, y = y1 - y2;
            std::printf("%.0lf", sqrt(x*x + y*y) * 5);
        };
        while(n--)_deal();
        return 0;
    }
};

