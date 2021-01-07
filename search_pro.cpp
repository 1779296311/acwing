/*********************************************
*
*     ------------------------
*     ------------------------
*     file name: search_pro.cpp
*     author   : @ JY
*     date     : 2020--12--28
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
#include <climits>
#include <cstring>
#include <vector>
#include <queue>
#include <functional>
#include <stdlib.h>

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
namespace p195{
    const int N = 5;
    const int fun[9] {-2, -1, 2, -1, -2, 1, 2, 1, -2};
    const int mp[9]  {6, 7, 4, 5, 2, 3, 0, 1};
    const char ed[N][N]{
        {'1','1','1','1','1'},
        {'0','1','1','1','1'},
        {'0','0','*','1','1'},
        {'0','0','0','0','1'},
        {'0','0','0','0','0'},
    };
    char e[N][N];
    int t, sx, sy;
    int _f(){
        int ans = 0;
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(e[i][j] == '*')continue;
                ans += ed[i][j] != e[i][j];
            }
        }
        return ans;
    }
    bool _valid(int x, int y){return x>=0 && y>=0 && x<N && y<N;}
    bool _ida_star(int dep, int now, int x, int y, int pre){
        int f = _f();
        if(!f)return true;
        if(f + now > dep)return false;
        for(int i=0; i<8; ++i){
            int x1 = x + fun[i], y1 = y + fun[i + 1];
            if(!_valid(x1, y1) || i == pre)continue;
            std::swap(e[x][y], e[x1][y1]);
            if(_ida_star(dep, now + 1, x1, y1, mp[i]))return true;
            std::swap(e[x][y], e[x1][y1]);
        }
        return false;
    }
    void _init(){
        for(int i=0; i<N; ++i)scanf("%s", e[i]);
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(e[i][j] != '*')continue;
                sx = i, sy = j;
                break;
            }
        }
    }
    void _deal(int dep=0){
        _init();
        while(!_ida_star(dep, 0, sx, sy, -1) && dep<=15)++dep;
        std::cout << (dep>15 ? -1 : dep) << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};

namespace p194{
    const int N = 16;
    const int fun[5] {0, 1, 0, -1, 0};
    int e[N][N];
    int n;
    int tv[6], vi[N][N], ttv[N << 2][N][N];
    inline bool _valid(int x, int y){return ~x && ~y && x<n && y<n;}
    void _dfs(int color, int x, int y){
        vi[x][y] = 1;
        for(int i=0; i<4; ++i){
            int x1 = x + fun[i];
            int y1 = y + fun[i + 1];
            if(!_valid(x1, y1) || vi[x1][y1])continue;
            vi[x1][y1] = 2;
            if(color != e[x1][y1])continue;
            _dfs(color, x1, y1);
        }
    }
    bool _fill(int color){
        int f = 0;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(color != e[i][j])continue;
                if(vi[i][j] != 2)continue;
                _dfs(color, i, j);
                f = 1;
            }
        }
        return f;
    }
    int _f(){
        int ans = 0;
        for(int i=0; i<6; ++i)tv[i] = 0;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(vi[i][j] == 1)continue;
                ans += !tv[e[i][j]]++;
            }
        }
        return  ans;
    }
    bool _ida_star(int dep, int now, int color){
        int f = _f();
        if(f == 0)return true;
        if(now + f > dep)return false;
        std::memcpy(ttv[now], vi, sizeof vi);
        for(int i=0; i<6; ++i){
            if(i == color)continue;
            if(_fill(i) && _ida_star(dep, now + 1, i))return true;
            std::memcpy(vi, ttv[now], sizeof vi);
        }
        return false;
    }
    void _init(){
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                scanf("%d", &e[i][j]);
            }
        }
        std::memset(vi, 0, sizeof vi);
    }
    bool _deal(int dep=0){
        if(scanf("%d", &n), !n)return false;
        _init();
        _dfs(e[0][0], 0, 0);
        while(!_ida_star(dep, 0, e[0][0]))++dep;
        return printf("%d\n", dep);
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p193{
    struct node {
        int x, y, cost, f_cost;
        node () {};
        node (int x, int y, int cost, int f)
        : x(x), y(y), cost(cost), f_cost(f) {};
        bool operator < (const node &other) const {
            return f_cost > other.f_cost;
        }
    };
    std::priority_queue<node> q;
    int p;
    int _gcd(int x, int y){return y ? _gcd(y, x % y) : x;}
    int _f(int x){
        if(x > p)return 1;
        int ans = 0;
        while(x < p)++ans, x <<= 1;
        return ans;
    }
    bool _check(int x, int y, int c){
        if(x == p || y == p)return true;
        if(x < y)std::swap(x, y);
        if(!y)return false;
        if(x == y)return false;
        if(y > p)return false;
        if(x > p && !y)return false;
        if(x > p*2)return false;
        if(p % _gcd(x, y))return false;
        q.emplace(x, y, c, c + _f(x));
        return false;
    }
    int _a_star(){
        if(!p)return 0;
        q.emplace(1, 0, 0, _f(1));
        while(q.size()){
            auto [x, y, cost, fc] = q.top();
            q.pop();
            if(_check(x+y, x, cost + 1))return cost + 1;
            if(_check(x+y, y, cost + 1))return cost + 1;
            if(_check(x+x, x, cost + 1))return cost + 1;
            if(_check(x+x, y, cost + 1))return cost + 1;
            if(_check(y+y, x, cost + 1))return cost + 1;
            if(_check(y+y, y, cost + 1))return cost + 1;
            if(_check(x-y, x, cost + 1))return cost + 1;
            if(_check(x-y, y, cost + 1))return cost + 1;
        }
        return -1;
    }
    void _deal(){
        std::cin >> p;
        std::cout << _a_star() << std::endl;
    }
    int main(int argc,const char *argv[]){
         _deal();
        return 0;
    }
};
namespace p192{
    const int N = 100;
    const int next_x[3][4] = {{-2, 1, 0, 0}, {-1, 1, 0, 0}, {-1, 2, 0, 0}};
    const int next_y[3][4] = {{0, 0, -2, 1}, {0, 0, -1, 2}, {0, 0, -1, 1}};
    const int next_l[3][4] = {{2, 2, 1, 1}, {1, 1, 0, 0}, {0, 0, 2, 2}};
    struct node{
        int x, y, l;
        node () {};
        node (int x, int y, int l)
            : x(x), y(y), l(l) {};
    };
    int d[N][N][3];
    int sx, sy, sl;
    char c;
    inline bool _valid(int x, int y){ return x>=0 && y>=0 && x<=N && y<=N; }
    void _bfs(){
        std::queue<node> q;
        d[N>>1][N>>1][0] = 0;
        q.emplace(N>>1, N>>1, 0);
        while(q.size()){
            auto now = q.front();q.pop();
            for(int i=0; i<4; ++i){
                int x1 = now.x + next_x[now.l][i];
                int y1 = now.y + next_y[now.l][i];
                int l1 = next_l[now.l][i];
                if(!_valid(x1, y1))continue;
                if(d[x1][y1][l1] != -1)continue;
                d[x1][y1][l1] = d[now.x][now.y][now.l] + 1;
                q.emplace(x1, y1, l1);
            }
        }
    }
    int _calc(int x, int y){
        int ans = 0;
        if(x > N){
            int k = (x - N) / 3 + 1;
            x -= k * 3, ans += k * 2;
        }
        if(y > N){
            int k = (y - N) / 3 + 1;
            y -= k * 3, ans += k * 2;
        }
        return ans + d[x][y][0];
    }
    bool _deal(){
        if(!(std::cin >> c >> sx >> sy))return false;
        std::memset(d, -1, sizeof d);
        _bfs();
        sx += N >> 1, sy += N >> 1;
        int ans = INT_MAX;
        if(c == 'U'){
            ans = _calc(sx, sy);
        }else if(c == 'H'){
            for(int i=-2; i<=2; ++i){
                ans = std::min(ans, _calc(sx+i, sy-1) + abs(i) + 1);
                ans = std::min(ans, _calc(sx+i, sy+2) + abs(i) + 1);
            }
        }else{
            for(int i=-2; i<=2; ++i){
                ans = std::min(ans, _calc(sx-1, sy+i) + abs(i) + 1);
                ans = std::min(ans, _calc(sx+2, sy+i) + abs(i) + 1);
            }
        }
        std::cout << ans << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
}
namespace p192_tle{
    const int next_x[3][4] {{0, 1,  0, -1}, {0, 2,  0, -1}, {0, 1,  0, -2}};
    const int next_y[3][4] {{2, 0, -1,  0}, {1, 0, -1,  0}, {1, 0, -2,  0}};
    const int next_l[3][4] {{2, 0,  2,  0}, {1, 2,  1,  2}, {0, 1,  0,  1}};
    struct rec {
        int x, y, l;
        int cost, f_cost;
        rec () {};
        rec (int x, int y, int l, int cost , int f_cost)
         : x(x), y(y), l(l), cost(cost), f_cost(f_cost){};
        bool operator < (const rec &other) const {
            return f_cost > other.f_cost;
        }
    };
    char c;
    int sl, sx, sy;
    inline int _f(int x, int y){return (abs(x) + abs(y)) >> 1 ;}
    int _a_start(){
        if(sx == 0 && sy == 0 && sl == 2)return 0;
        std::priority_queue<rec> q;
        q.emplace(sx, sy, sl, 0, 0 + _f(sx, sy));
        while(q.size()){
            auto [x, y, l, cost, f_cost] = q.top();
            q.pop();
            for(int i=0; i<4; ++i){
                int x1 = x + next_x[l][i];
                int y1 = y + next_y[l][i];
                int l1 = next_l[l][i];
                if(x1 == 0 &&
                     y1 == 0 &&
                     l1 == 2)return cost + 1;
                q.emplace(x1, y1, l1, cost + 1, cost + 1 + _f(x1, y1));
            }
        }
        return -1;
    }
    bool _deal(){
        if(!(std::cin >> c >> sx >> sy))return false;
        sl = (c=='U') ? 2 : (c=='V' ? 1 : 0);
        std::cout << _a_start() << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p191{
    const int N = 366, M = 16;
    const int dx[] = {0,-1,1,0,0,-2,2,0,0};
    const int dy[] = {0,0,0,-1,1,0,0,-2,2};
    struct st{
        int day, x, y, a, b, c, d;
        st () {};
        st (int day, int x, int y, int a, int b, int c, int d) :
           day(day), x(x), y(y), a(a), b(b), c(c), d(d)  {};
    };
    int n, x;
    int state[N], vi[N][M][7][7][7][7];
    inline int  _get(int x, int y){return (x << 2 | y) ;}
    inline bool _valid(int x, int y){return x>=0 && y>=0 && x<3 && y<3;}
    int _weather(int x, int y){
        return (1 << _get(x+1, y))   | (1 << _get(x, y+1))|
               (1 << _get(x+1, y+1)) | (1 << _get(x, y));
    }
    int _check(st node){
        auto [now, x, y, a, b, c, d] = node;
        if(now - a > 6 || now - b > 6)return false;
        if(now - d > 6 || now - c > 6)return false;
        if(state[now] & _weather(x, y))return false;
        if(vi[now][_get(x, y)][a][b][c][d])return false;
        return vi[now][_get(x, y)][a][b][c][d] = true;
    }
    bool _bfs(){
        if(state[1] &
           ((1 << 5) | (1 << 6) |
            (1 << 9) | (1 << 10)) ) return false;
        std::queue<st> q;
        q.emplace(1, 1, 1, 0, 0, 0, 0);
        vi[1][_get(1, 1)][0][0][0][0] = 1;
        while(q.size()){
            auto [now, x, y, a, b, c ,d] = q.front();
            q.pop();
            for(int j=0; j<9; ++j){
                int x1 = x + dx[j], y1 = y + dy[j];
                if(!_valid(x1, y1))continue;
                int a1 = a, b1 = b, c1 = c, d1 = d;
                if(!x1 && !y1)a1 = now + 1;
                if(!x1 && y1==2)b1 = now + 1;
                if(x1==2 && !y1)c1 = now + 1;
                if(x1==2 && y1==2)d1 = now + 1;
                if(!_check({now + 1, x1, y1, a1, b1, c1, d1}))continue;
                if(now + 1 == n)return true;
                q.emplace(now+1, x1, y1, a1, b1, c1, d1);
            }
        }
        return false;
    }
    bool _deal(){
        std::cin >> n;
        if(!n)return false;
        std::memset(state, 0, sizeof state);
        std::memset(vi, 0, sizeof vi);
        for(int i=1; i<=n; ++i){
            int t = 0;
            for(int j=0; j<M; ++j){
                std::cin >> x;
                t |= x << j;
            }
            state[i] = t;
        }
        std::cout << _bfs() << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};

namespace p190{
    using pss = std::pair<std::string, std::string>;
    std::vector<pss> strs;
    std::string st, ed;
    bool _check(std::string &str,
                std::queue<std::string> &q,
                std::string &x, std::string &y,
                std::unordered_set<std::string> &self,
                std::unordered_set<std::string> &other){
        int pos = str.find(x);
        while(pos != std::string::npos){
            if(pos == std::string::npos)return false;
            std::string tmp {str.begin(), str.begin() + pos};
            tmp += y;
            tmp += str.substr(pos + x.size());
            if(other.count(tmp))return true;
            if(self.insert(tmp).second)q.emplace(tmp);
            pos = str.find(x, pos + 1);
        }
        return false;
    }
    std::string _bfs(){
        if(st == ed)return "0";
        std::unordered_set<std::string> mp1, mp2;
        std::queue<std::string> q1, q2;
        q1.emplace(st);
        q2.emplace(ed);
        mp1.emplace(st);
        mp2.emplace(ed);
        for(int i=1; i<=10; ++i){
            int size = q1.size();
            while(size--){
                auto str = q1.front();q1.pop();
                for(auto &[x, y] : strs){
                    std::cout << str << "  " << x << "   " << y << std::endl;
                    if(!_check(str, q1, x, y, mp1, mp2))continue;
                    return std::to_string(i);
                }
            }
            ++i;
            size = q2.size();
            while(size-- ){
                auto str = q2.front();q2.pop();
                for(auto &[x, y] : strs){
                    if(!_check(str, q2, y, x, mp2, mp1))continue;
                    return std::to_string(i);
                }
            }
        }
        return "NO ANSWER!";
    }
    void _deal(){
        std::cin >> st >> ed;
        std::string x, y;
        while(std::cin >> x && std::cin >> y)strs.push_back({x, y});
        return ;
        std::cout << _bfs() << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p189{
    using pii = std::pair<int, int>;
    const int N = 128;
    int fun[9] {0, 1, -1, -1, 1, 1, 0, -1, 0};
    int n, m, tot, si, sj;
    int vi[N][N];
    char e[N][N];
    bool _valid(int x, int y){return x>=0 && y>=0 && x<n && y<m;}
    void _debug(){
        std::cout << tot << "----"<< std::endl;
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                std::cout << vi[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    int _bfs(){
        if(!tot)return 0;
        int ans = 0;
        std::queue<pii> q;
        q.emplace(si, sj);
        vi[si][sj] = 1;
        _debug();
        while(q.size()){
            int size = q.size();
            ++ans;
            while(size--){
                auto [x, y] = q.front();q.pop();
                for(int i=0; i<8; ++i){
                    int x1 = x + fun[i], y1 = y + fun[i + 1];
                    if(!_valid(x1, y1) || vi[x1][y1])continue;
                    if(!--tot)return ans;
                    vi[x1][y1] = 1;
                    q.emplace(x1, y1);
                }
            }
            _debug();
        }
        return ans;
    }
    void _deal(){
        std::cin >> m >> n >> sj >> si;
        for(int i=0; i<n; ++i)std::cin >> e[i];
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                if(e[i][j] == '.')continue;
                vi[i][j] = 1;
                ++tot;
            }
        }
        tot = n * m - tot - 1;
        si = n - si, --sj;
        std::cout << _bfs() << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p188{
    using pii  = std::pair<int, int>;
    using ppii = std::pair<pii, int>;
    const int N = 256;
    int fun[9] {-2, -1, 2, -1, -2, 1, 2, 1, -2};
    int r, c;
    int tot, si, sj;
    int vi[N][N];
    char e[N][N];
    bool _valid(int x, int y){return x>=0 && y>=0 && x<r && y<c;}
    int _bfs(){
        int ans = 0;
        if(tot == 0)return ans;
        std::queue<ppii> q;
        q.push({{si, sj}, tot});
        vi[si][sj] = 1;
        while(q.size()){
            int size = q.size();
            ++ans;
            while(size--){
                auto [pos, d] = q.front();q.pop();
                auto [x, y] = pos;
                for(int i=0; i<8; ++i){
                    int x1 = x + fun[i], y1 = y + fun[i + 1];
                    if(!_valid(x1, y1) || vi[x1][y1])continue;
                    vi[x1][y1] = 1;
                    if(e[x1][y1] == 'H')--d;
                    if(!d)return ans;
                    q.push({{x1, y1}, d});
                }
            }
        }
        return ans;
    }
    void _deal(){
        std::cin >> c >> r;
        for(int i=0; i<r; ++i)std::cin >> e[i];
        for(int i=0; i<r; ++i){
            for(int j=0; j<c; ++j){
                char t = e[i][j];
                if(t == 'K'){
                    si = i, sj = j;
                }else if(t == 'H'){
                    ++tot;
                }else if(t == '*'){
                    vi[i][j] = 1;
                }
            }
        }
        std::cout << _bfs() << std::endl;;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p187{
    const int N = 64;
    int hs[N], up[N], down[N];
    int t, n, dep;
    bool _dfs(int dep, int idx, int un, int dn){
        if(idx == n)return true;
        if(un + dn > dep)return false;
        int f = 0;
        for(int i=0; i<un; ++i){
            if(up[i] >= hs[idx])continue;
            int t = up[i];
            up[i] = hs[idx];
            if(_dfs(dep, idx + 1, un, dn))return true;
            up[i] = t;
            f = 1;
            break;
        }
        if(!f){
            up[un] = hs[idx];
            if(_dfs(dep, idx + 1, un + 1, dn))return true;
        }
        f = 0;
        for(int i=0; i<dn; ++i){
            if(down[i] <= hs[idx])continue;
            int t = down[i];
            down[i] = hs[idx];
            if(_dfs(dep, idx + 1, un, dn))return true;
            down[i] = t;
            f = 1;
            break;
        }
        if(!f){
            down[dn] = hs[idx];
            if(_dfs(dep, idx + 1, un, dn + 1))return true;
        }
        return false;
    }
    bool _deal(){
        std::cin >> n;
        if(!n)return false;
        for(int i=0; i<n; ++i)std::cin >> hs[i];
        dep = 0;
        while(!_dfs(dep, 0, 0, 0))++dep;
        std::cout << dep << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};
namespace p186{
    using pii  = std::pair<int, int>;
    using ppii = std::pair<int, pii>;
    const int N = 64;
    int n, ts[N], dep;
    std::vector<ppii> routes;
    bool _valid(int i, int d){
        for(; i<60; i+=d){
            if(!ts[i])return false;
        }
        return true;
    }
    bool _dfs(int dep, int d, int sum, int start){
        if(dep == d)return sum == n;
        if(routes[start].first * (dep - d) + sum < n)return false;
        int size = routes.size();
        for(int i=start; i<size; ++i){
            auto [len, bd] = routes[i];
            auto [be, dd]  = bd;
            if(!_valid(be, dd))continue;
            for(int j=be; j<60; j+=dd)--ts[j];
            if(_dfs(dep, d + 1, sum + len, i))return true;
            for(int j=be; j<60; j+=dd)++ts[j];
        }
        return false;
    }
    void _deal(){
        std::cin >> n;
        for(int i=0; i<n; ++i){
            int x;
            std::cin >> x;
            ++ts[x];
        }
        for(int i=0; i<60; ++i){
            for(int j=i+1; i+j<60; ++j){
                if(!_valid(i, j))continue;
                routes.push_back({(59-i)/j + 1, {i, j}});
            }
        }
        std::sort(rbegin(routes), rend(routes));
        while(!_dfs(dep, 0, 0, 0))++dep;
        std::cout << dep << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p185{
    using pii = std::pair<int, int>;
    const int r = 5, c = 7;
    int tmp[c][r][c], ctmp[c][r][16];
    int e[r][c], cnt[16];
    int n, x, idx;
    pii path[c], points[r * c + 1];
    bool _valid(int i){ return i>=0 && i<r; }
    void _hang(int i){
        int y = 0;
        for(int j=0; j<c; ++j){
            if(!e[i][j])continue;
            e[i][y++] = e[i][j];
        }
        while(y<c)e[i][y++] = 0;
    }
    void _hang(){
        for(int i=0; i<r; ++i)_hang(i);
    }
    void _update(){
        for(int i=0; i<idx; ++i){
            auto [x, y] = points[i];
            --cnt[e[x][y]];
            e[x][y] = 0;
        }
        _hang();
    }
    bool _cntpoint(int i, int j){
        int i1 = i, i2 = i, color = e[i][j];
        while(i1-1>=0 && e[i1-1][j]==color)--i1;
        while(i2+1<r  && e[i2+1][j]==color)++i2;
        if(i2 - i1 + 1 >= 3){
            points[idx++] = {i, j};
            return true;
        }
        int j1 = j, j2 = j;
        while(j1-1>=0 && e[i][j1-1]==color)--j1;
        while(j2+1<c  && e[i][j2+1]==color)++j2;
        if(j2 - j1 + 1 >= 3){
            points[idx++] = {i, j};
            return true;
        }
        return false;
    }
    int _clear(){
        int ans = 0;
        while(1){
            idx = 0;
            for(int i=0; i<r; ++i){
                for(int j=0; j<c; ++j){
                    if(!e[i][j])continue;
                    _cntpoint(i, j);
                }
            }
            if(!idx)break;
            ans += idx;
            _update();
        }
        return ans;
    }
    void _move(int i, int j, int f){
        int ti = i + f;
        std::swap(e[i][j], e[ti][j]);
        _hang(i), _hang(ti);
    }
    bool _dfs(int st, int tot){
        std::cout << st  << "  "<< tot << std::endl;
        if(st == n)return !tot;
        if(!tot)return false;
        for(int i=0; i<=10; ++i){
            if(cnt[i] == 1 || cnt[i] == 2)return false;
        }
        for(int i=0; i<r; ++i){
            for(int j=0; j<c; ++j){
                if(!e[i][j])continue;
                for(int f=1; f>=-1; f-=2){
                    if(!_valid(i + f))continue;
                    if(f==-1 && e[i-1][j])continue;
                    path[st] = {i * f, j};
                    std::memcpy(tmp[st],  e, sizeof e);
                    std::memcpy(ctmp[st], cnt, sizeof cnt);
                    _move(i, j, f);
                    if(_dfs(st + 1, tot - _clear()))return true;
                    std::memcpy(cnt, ctmp[st], sizeof cnt);
                    std::memcpy(e, tmp[st], sizeof e);
                }
            }
        }
        return false;
    }
    void _debug(){
        for(int i=0; i<r; ++i){
            for(int j=0; j<c; ++j)std::cout << e[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout <<  "------" << std::endl;
    }
    void _deal(){
        std::cin >> n;
        int tot = 0;
        for(int i=0; i<r; ++i){
            int j = 0;
            while(std::cin >> x, x){
                ++tot;
                e[i][j++] = x;
                ++cnt[x];
            }
        }
        if(!_dfs(0, tot)){
            std::cout << -1 << std::endl;
            return ;
        }
        for(int i=0; i<n; ++i){
            auto [x, y] = path[i];
            std::cout
                << abs(x) << " "
                << y << " "
                << ((x >= 0) ? 1 : -1) <<
            std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }

/*
5
1 1 2 3 4 0
3 3 1 2 3 5 4 0
3 5 5 3 2 2 0
5 5 3 5 2 4 2 0
0
*/

};
namespace p184{
    const int N = 36;
    int n, k;
    int mp[N], mp1[N];
    int vi[N];
    char s1[N], s2[N], s3[N];
    bool _check(){
        int add = 0;
        for(int i=n-1; i>=0; --i){
            int a = mp[s1[i] - 'A'];
            int b = mp[s2[i] - 'A'];
            int c = mp[s3[i] - 'A'];
            if(~a && ~b && ~c){
                int t = a + b;
                if(add == -1){
                    if((t % n != c) && ((t + 1) % n != c))return false;
                    if(!i && t >= n)return false;
                }else{
                    if((t + add) % n != c)return false;
                    if(!i && t + add >= n)return false;
                    add = (t + add) / n;
                }
            }else{
                add = -1;
            }
        }
        return true;
    }
    bool _dfs(int idx){
        if(idx == k)return true;
        for(int i=0; i<n; ++i){
            if(vi[i])continue;
            vi[i] = 1;
            mp[mp1[idx]] = i;
            if(_check() && _dfs(idx + 1))return true;
            mp[mp1[idx]] = -1;
            vi[i] = 0;
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> s1 >> s2 >> s3;
        for(int i=n-1; i>=0; --i){
            int c1 = s1[i] - 'A';
            int c2 = s2[i] - 'A';
            int c3 = s3[i] - 'A';
            if(!vi[c1])vi[c1] = 1, mp1[k++] = c1;
            if(!vi[c2])vi[c2] = 1, mp1[k++] = c2;
            if(!vi[c3])vi[c3] = 1, mp1[k++] = c3;
        }
        std::memset(vi,  0, sizeof vi);
        std::memset(mp, -1, sizeof mp);
        _dfs(0);
        for(int i=0; i<n; ++i)std::cout << mp[i] << " ";
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p183{
    const int n = 9, rn = 3;
    const int score[n][n] {
        {6, 6, 6, 6, 6,  6, 6, 6, 6},
        {6, 7, 7, 7, 7,  7, 7, 7, 6},
        {6, 7, 8, 8, 8,  8, 8, 7, 6},
        {6, 7, 8, 9, 9,  9, 8, 7, 6},
        {6, 7, 8, 9, 10, 9, 8, 7, 6},
        {6, 7, 8, 9, 9,  9, 8, 7, 6},
        {6, 7, 8, 8, 8,  8, 8, 7, 6},
        {6, 7, 7, 7, 7,  7, 7, 7, 6},
        {6, 6, 6, 6, 6,  6, 6, 6, 6},
    };
    int e[n][n];
    int ans, f;
    int ro[n], co[n], re[n];
    int bitcnt[1 << n], num[1 << n];
    int _lowbit(int x){return x & -x;}
    void _init(){
        for(int i=0; i<n; ++i)num[1 << i] = i;
        for(int i=0; i<(1 << n); ++i){
            for(int j=i; j; j^=_lowbit(j))++bitcnt[i];
        }
        for(int i=0; i<n; ++i)ro[i] = co[i] = re[i] = (1 << n) - 1;
    }
    int _index(int x, int y){
        return x / rn * rn + y / rn;
    }
    void _bit(int x, int y, int i){
        ro[x] ^= (1 << i);
        co[y] ^= (1 << i);
        re[_index(x, y)] ^= (1 << i);
    }
    void _dfs(int cnt, int sco){
        if(!cnt){
            ans = std::max(ans, sco);
            f   = 1;
            return;
        }
        int bn = n + 1, x, y;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j])continue;
                int bit = ro[i] & co[j] & re[_index(i, j)];
                if(!bit)return ;
                if(bitcnt[bit] >= bn)continue;
                bn = bitcnt[bit];
                x = i, y = j;
            }
        }
        int bit = ro[x] & co[y] & re[_index(x, y)];
        int sc  = score[x][y];
        for(; bit; bit^=_lowbit(bit)){
            int i = num[_lowbit(bit)];
            _bit(x, y, i);
            e[x][y] = i + 1;
            _dfs(cnt - 1, sco + sc * (i+1));
            e[x][y] = 0;
            _bit(x, y, i);
        }
    }
    void _deal(){
        _init();
        int cnt = n * n;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cin >> e[i][j];
                if(!e[i][j])continue;
                ans += score[i][j] * e[i][j];
                _bit(i, j, e[i][j] - 1);
                --cnt;
            }
        }
        _dfs(cnt, ans);
        std::cout << (f ? ans : -1) << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
//x -- 所以坐标为(r,c)(r,c)的火柴，编号为1+r(2n+1)+c
//y -- 所以坐标为(r,c)(r,c)的火柴，编号为1+r(2n+1)+c+n
namespace p182{
    const int N = 64;
    int t, n, m, d, tmp, D;
    int vi[N], tvi[N];
    std::vector<int> square[64];
    bool _check(std::vector<int> &sq){
        for(auto &x : sq){
            if(vi[x])return false;
        }
        return true;
    }
    int  _f(){
        std::memcpy(tvi, vi, sizeof vi);
        int ans = 0;
        for(int i=0; i<m; ++i){
            if(!_check(square[i]))continue;
            for(auto &x : square[i])vi[x] = 1;
            ++ans;
        }
        std::memcpy(vi, tvi, sizeof vi);
        return ans;
    }
    bool _dfs(int dep){
        if(dep + _f() > D)return false;
        for(int i=0; i<m; ++i){
            if(!_check(square[i]))continue;
            for(auto &x : square[i]){
                vi[x] = 1;
                if(_dfs(dep + 1))return true;
                vi[x] = 0;
            }
            return false;
        }
        return true;
    }
    void _init(){
        for(int l=1; l<=n; ++l){
            for(int i=0; i+l<=n; ++i){
                for(int j=0; j+l<=n; ++j){
                    square[m].clear();
                    auto &sq = square[m++];
                    for(int k=0; k<l; ++k){
                        sq.emplace_back(1 + i * d + j + k);
                        sq.emplace_back(1 + (i + l) * d + j + k);
                        sq.emplace_back(1 + (i + k) * d + j + n);
                        sq.emplace_back(1 + (i + k) * d + j + n + l);
                    }
                }
            }
        }
        for(int i=0; i<m; ++i){
            for(auto &x : square[i])std::cout << x << " ";
            std::cout << std::endl;
        }
    }
    void _deal(){
        std::cin >> n;
        m = 0, D = 0, d = n << 1 | 1;
        _init();
        std::memset(vi, 0, sizeof(vi));
        std::cin >> tmp;
        for(int i=0, x; i<tmp; ++i){
            std::cin >> x;
            vi[x] = 1;
        }
        while(!_dfs(0))++D;
        std::cout << D << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};
namespace p181{
    const int op[8][7]{
        {0,   2,  6, 11, 15, 20, 22},
        {1,   3,  8, 12, 17, 21, 23},
        {10,  9,  8,  7,  6,  5,  4},
        {19, 18, 17, 16, 15, 14, 13},
        {23, 21, 17, 12,  8,  3,  1},
        {22, 20, 15, 11,  6,  2,  0},
        {13, 14, 15, 16, 17, 18, 19},
        {4,   5,  6,  7,  8,  9, 10}
    };
    const int preops [8] {5, 4, 7, 6, 1, 0, 3, 2};
    const int center [8] {6, 7, 8, 11, 12, 15, 16, 17};
    int e[24], d, pre[128], sums[4];
    bool _check(){
        int x = e[center[0]];
        for(auto &i : center){
            if(x != e[i])return false;
        }
        return true;
    }
    int _f(){
        std::memset(sums, 0, sizeof sums);
        for(auto &i : center)++sums[e[i]];
        return 8 - *std::max_element(sums, sums + 4);
    }
    void _opera(int i){
        int f = e[op[i][0]];
        for(int j=0; j<6; ++j)e[op[i][j]] = e[op[i][j + 1]];
        e[op[i][6]] = f;
    }
    bool _dfs(int d, int D, int last){
        if(d + _f() > D)return false;
        if(_check())return true;
        for(int i=0; i<8; ++i){
            if(last == preops[i])continue;
            pre[i] = i;
            _opera(i);
            if(_dfs(d + 1, D, i))return true;
            _opera(preops[i]);
        }
        return false;
    }
    bool _deal(){
        std::cin >>e[0];
        if(!e[0])return false;
        for(int i=1; i<24; ++i)std::cin >> e[i];
        for(d=0; !_dfs(0, d, -1); ++d);
        if(d == 0){
            std::cout << "No moves needed" << std::endl;
            std::cout << e[center[0]] << std::endl;
            return true;
        }
        std::string ans;
        for(int i=0; i<d; ++i)ans += pre[i] + 'A';
        std::cout << ans << std::endl;
        std::cout << e[center[0]] << std::endl;
        return true;
    }
    int main(int argc,const char *argv[]){
        while(_deal());
        return 0;
    }
};

namespace p180{
    const int N = 16;
    int n, t;
    int books[N], tmp[N][N];
    int _f(){
        int ans = 0;
        for(int i=0; i<n-1; ++i){
            if(books[i+1] != books[i] + 1) ++ans;
        }
        return (ans + 2) / 3;
    }
    bool _check(){
        for(int i=0; i<n; ++i){
            if(books[i] != i + 1)return false;
        }
        return true;
    }
    void _get(int d, int tl, int sl, int sr){
        int i, k;
        for(k=tl,i=sl; i<=sr; ++k,++i)books[k] = tmp[d][i];
        for(i=tl; i<sl; ++k,++i)books[k] = tmp[d][i];
    }
    bool _dfs(int d, int D){
        if(d + _f() > D)return false;
        if(_check())return true;
        for(int l=1; l<n; ++l){
            for(int r=l; r<n; ++r){
                for(int t=0; t<l; ++t){
                    memcpy(tmp[d], books, sizeof books);
                    _get(d, t, l, r);
                    if(_dfs(d + 1, D))return true;
                    memcpy(books, tmp[d], sizeof books);
                }
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n;
        for(int i=0; i<n; ++i)std::cin >> books[i];
        int d = 0;
        while(d<5 && !_dfs(0, d))++d;
        if(d < 5){
            std::cout << d << std::endl;
            return ;
        }
        std::cout << "5 or more" << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};
namespace p180_tle{
    const int N = 16;
    int n, t;
    std::vector<int> st,  ed;
    std::vector<int> tmp, ne;
    std::set<std::vector<int>> vi1;
    std::set<std::vector<int>> vi2;
    void _get(int tl, int sl, int sr){
        int i = 0, k;
        for(; i<tl; ++i)ne[i] = tmp[i];
        for(k=sl; k<=sr; ++k,++i)ne[i] = tmp[k];
        for(k=tl; k<sl; ++k,++i)ne[i] = tmp[k];
        for(k=sr+1; k<n; ++k,++i)ne[i] = tmp[k];
        for(int i=0; i<n; ++i)std::cout << ne[i] << "  ";
    }
    std::string _bfs(){
        if(st == ed)return "0";
        std::queue<std::vector<int>> q1;
        std::queue<std::vector<int>> q2;
        q1.emplace(st);
        q2.emplace(ed);
        vi1.emplace(st);
        vi2.emplace(ed);
        for(int i=1; i<=2; ++i){
            int size = q1.size();
            while(size--){
                tmp = q1.front();q1.pop();
                for(int sl=1; sl<n; ++sl){
                    for(int sr=sl; sr<n; ++sr){
                        for(int tl=0; tl<sl; ++tl){
                            _get(tl, sl, sr);
                            if(vi2.count(ne))return std::to_string(i);
                            if(!vi1.insert(ne).second)continue;
                            q1.emplace(ne);
                        }
                    }
                }
            }
        }
        for(int i=3; i<=4; ++i){
            int size = q2.size();
            while(size--){
                tmp = q2.front();q2.pop();
                for(int sl=1; sl<n; ++sl){
                    for(int sr=sl; sr<n; ++sr){
                        for(int tl=0; tl<sl; ++tl){
                            _get(tl, sl, sr);
                            if(vi1.count(ne))return std::to_string(i);
                            if(!vi2.insert(ne).second)continue;
                            q2.emplace(ne);
                        }
                    }
                }
            }
        }
        return "5 or more";
    }
    void _deal(){
        std::cin >> n;
        st.resize(n);
        tmp.resize(n);
        ne.resize(n);
        vi1.clear();
        vi2.clear();
        for(int i=0; i<n; ++i)std::cin >> st[i];
        ed = st;
        std::sort(begin(ed), end(ed));
        std::cout << _bfs() << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};
namespace p179{
    using pis = std::pair<int, std::string>;
    using psc = std::pair<std::string, char>;
    const int  dx[4]{-1, 0, 1, 0}, dy[4]{0, 1, 0, -1};
    const char op[4]{'u', 'r', 'd', 'l'};
    std::string ed {"12345678x"}, start;
    char e[12];
    int  v[9], t[16];
    int _df(std::string state){
        int ans = 0;
        for(int i=0; i<9; ++i){
            if(state[i] == 'x')continue;
            int t = state[i] - '1';
            ans += abs(t/3 - i/3) + abs(t%3 - i%3);
        }
        return ans;
    }
    bool _check(){
        std::function<int(int, int)> _merge
            = [&](int l, int r){
                if(l >= r)return 0;
                int m = l + ((r - l) >> 1);
                int ans = _merge(l, m) + _merge(m + 1, r);
                int li = l, ri = m + 1;
                for(int i=l; i<=r; ++i){
                    if(ri>r || (li<=m && v[li] < v[ri])){
                        t[i] = v[li++];
                    }else{
                        ans += m - li + 1;
                        t[i] = v[ri++];
                    }
                }
                for(int i=l; i<=r; ++i)v[i] = t[i];
                return ans;
            };
        return !(_merge(0, 7) & 1);
    }
    bool _valid(int x, int y){ return ~x && ~y && x<3 && y<3; }
    std::string _A_star(){
        std::unordered_map<std::string, int> dist;
        std::unordered_map<std::string, psc> pre;
        std::unordered_set<std::string> vis;
        dist[start] = 0;
        std::priority_queue<pis, std::vector<pis>,
                                 std::greater<pis>> q;
        q.emplace(_df(start), start);
        while(q.size()){
            auto [d, now] = q.top();q.pop();
            if(!now.compare(ed))break;
            if(!vis.insert(now).second)continue;
            int idx = now.find('x');
            int x = idx / 3, y = idx % 3;
            std::string ori = now;
            for(int i=0; i<4; ++i){
                int x1 = x + dx[i], y1 = y + dy[i];
                if(!_valid(x1, y1))continue;
                std::swap(now[x*3+y], now[x1*3+y1]);
                if(!dist.count(now) || dist[now] > dist[ori] + 1){
                    dist[now] = dist[ori] + 1;
                    pre[now]  = {ori, op[i]};
                    q.emplace(dist[now] + _df(now), now);
                }
                std::swap(now[x*3+y], now[x1*3+y1]);
            }
        }
        std::string ans;
        while(ed.compare(start)){
            auto [f, s] = pre[ed];
            ans += s, ed = f;
        }
        std::reverse(begin(ans), end(ans));
        return ans;
    }
    void _deal(){
        char c;
        for(int i=0,k=0; i<9; ++i){
            std::cin >> c;
            start += c;
            if(c == 'x')continue;
            v[k++] = c - '0';
        }
        if(!_check()){
            std::cout << "unsolvable" << std::endl;
        }else{
            std::cout << _A_star() << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p178{
    using pii = std::pair<int, int>;
    const int N = 1024, INF = 0x3f3f3f3f;
    int s, t, k;
    int n, m, idx, tidx;
    int head[N],  to[N << 7],  ne[N << 7],  val[N << 7],  vi[N];
    int thead[N], tto[N << 7], tne[N << 7], tval[N << 7], tvi[N];
    int sp[N];
    struct node {
        int x, dist, spx;
        node () : x(-1), dist(INF), spx(INF){};
        node (int x, int d, int s) : x(x), dist(d), spx(s){};
        bool operator < (const node &other) const {
            return dist + spx > other.dist + other.spx;
        }
    };
    void _tadd(int x, int y, int l){
       tto[++tidx] = y;
       tval[tidx]  = l;
       tne[tidx]   = thead[x];
       thead[x]    = tidx;
    }
    void _add(int x, int y, int l){
        to[++idx] = y;
        val[idx]  = l;
        ne[idx]   = head[x];
        head[x]   = idx;
    }
    void _dij(){
        std::priority_queue<pii, std::vector<pii>,
                                 std::greater<pii>> q;
        q.emplace(0, t);
        sp[t] = 0;
        while(q.size()){
            auto [d, now] = q.top();q.pop();
            if(tvi[now])continue;
            tvi[now] = 1;
            for(int i=thead[now]; i; i=tne[i]){
                int y = tto[i];
                if(sp[y] <= d + tval[i])continue;
                sp[y] = d + tval[i];
                q.emplace(sp[y], y);
            }
        }
    }
    int _A_star(){
        std::priority_queue<node> q;
        q.emplace(s, 0, sp[s]);
        while(q.size()){
            auto [now, dist, spx] = q.top();q.pop();
            ++vi[now];
            if(vi[t] == k)return dist;
            for(int i=head[now]; i; i=ne[i]){
                int y = to[i], d = val[i];
                if(vi[y] >= k)continue;
                q.emplace(y, dist+d, sp[y]);
            }
        }
        return -1;
    }

    void _deal(){
        int a, b, l;
        std::memset(vi,    0, sizeof vi);
        std::memset(tvi,   0, sizeof tvi);
        std::memset(sp,  INF, sizeof sp);
        std::cin >> n >> m;
        for(int j=0; j<m; ++j){
            std::cin >> a >> b >> l;
            _add(a, b, l), _tadd(b, a, l);
        }
        std::cin >> s >> t >> k;
        _dij();
        k += s == t;
        std::cout << _A_star() << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _deal();
        return 0;
    }
};
namespace p177{
    using pii = std::pair<int, int>;
    const int N = 1024;
    int fun[5] {0, 1, 0, -1, 0};
    int t, n, m, vi[N][N];
    char e[N][N];
    pii mp, gp;
    std::vector<pii> zs;
    int  _distance(int x1, int y1, int x2, int y2){
        return abs(x1 - x2) + abs(y1 - y2);
    }
    bool _valid(int x, int y, int i){
        if(x<0  || y<0 || x>=n ||
           y>=m || e[x][y] == 'X'){
            return false;
        }
        for(auto [f, s] : zs){
            if(_distance(x, y, f, s) <= i * 2)return false;
        }
        return true;
    }
    int _bfs(){
        std::memset(vi, 0, sizeof vi);
        std::queue<pii> q1, q2;
        q1.emplace(mp.first, mp.second);
        q2.emplace(gp.first, gp.second);
        vi[mp.first][mp.second] = 1;
        vi[gp.first][gp.second] = 2;
        for(int i=1; q1.size()||q2.size(); ++i){
            int k = 3;
            while(k--){
                int size = q1.size();
                while(size--){
                    auto [x, y] = q1.front();q1.pop();
                    if(!_valid(x, y, i))continue;
                    for(int f=0; f<4; ++f){
                        int x1 = x + fun[f], y1 = y + fun[f + 1];
                        if(!_valid(x1, y1, i))continue;
                        if(vi[x1][y1] == 1)continue;
                        if(vi[x1][y1] == 2)return i;
                        vi[x1][y1] = 1;
                        q1.emplace(x1, y1);
                    }
                }
            }
            int size = q2.size();
            while(size--){
                auto [x, y] = q2.front();q2.pop();
                if(!_valid(x, y, i))continue;
                for(int f=0; f<4;++f){
                    int x1 = x + fun[f], y1 = y + fun[f + 1];
                    if(!_valid(x1, y1, i))continue;
                    if(vi[x1][y1] == 2)continue;
                    if(vi[x1][y1] == 1)return i;
                    vi[x1][y1] = 2;
                    q2.emplace(x1, y1);
                }
            }
        }
        return -1;
    } 
    void _deal(){
        zs.clear();
        std::cin >> n >> m;
        for(int i=0; i<n; ++i){
            scanf("%s", e[i]);
            for(int j=0; j<m; ++j){
                if(e[i][j] == 'M'){
                    mp = {i, j};
                }else if(e[i][j] == 'G'){
                    gp = {i, j};
                }else if(e[i][j] == 'Z'){
                    zs.emplace_back(i, j);
                }
            }
        }
        std::cout << _bfs() << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};
namespace p176{
    using pii = std::pair<int, int>;
    const int N = 1024, INF = 0x3f3f3f3f;
    int n, m, idx, q;
    int c, s, e;
    int head[N << 1], ne[N << 4], val[N << 4], to[N << 4];
    int vi[N][N >> 3], di[N][N >> 3], cost[N];
    struct node {
        int x, o, cost;
        node (int x, int o, int c) : x(x), o(o), cost(c) {}
        node () : x(-1), o(-1), cost(INF) {}
        bool operator < (const node &other) const {
            return cost > other.cost;
        }
    };
    void _add(int x, int y, int v){
        to[++idx] = y;
        val[idx]  = v;
        ne[idx]   = head[x];
        head[x]   = idx;
    }
    std::string _bfs(){
        std::memset(vi,   0, sizeof vi);
        std::memset(di, INF, sizeof di);
        di[s][0] = 0;
        std::priority_queue<node> q;
        q.emplace(s, 0, 0);
        while(q.size()){
            auto [now, oil, co] = q.top();q.pop();
            if(now == e)return std::to_string(co);
            if(vi[now][oil])continue;
            vi[now][oil] = 1;
            int &d = di[now][oil + 1];
            if(oil < c && d > co + cost[now]){
                d = co + cost[now];
                q.emplace(now, oil + 1, d);
            }
            for(int i=head[now]; i; i=ne[i]){
                if(val[i] > oil)continue;
                int y = to[i], &d = di[y][oil - val[i]];
                if(d <= co)continue;
                d = co;
                q.emplace(y, oil - val[i], d);
            }
        }
        return "impossible";
    }
    void _deal(){
        std::cin >> c >> s >> e;
        std::cout << _bfs() << std::endl;
    }
    void _init(){
        int x, y, v;
        std::cin >> n >> m;
        for(int i=0; i<n; ++i)std::cin >> cost[i];
        for(int i=0; i<m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v);
            _add(y, x, v);
        }
        std::cin >> q;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _init();
        while(q--)_deal();
        return 0;
    }
};
namespace p175{
    using pii = std::pair<int, int>;
    const int N = 512, INF = 0x3f3f3f3f;
    const int  dx[4]{-1, -1, 1, 1}, dy[4]{-1, 1, 1, -1};
    const int  lx[4]{-1, -1, 0, 0}, ly[4]{-1, 0, 0, -1};
    const char li[4]{'\\', '/', '\\', '/'};
    int t, n, m;
    int vi[N][N], di[N][N];
    char e[N][N];
    inline bool _valid(int x, int y){return ~x && ~y && x<=n && y<=m;}
    std::string _bfs(){
        if(n+m & 1)return "NO SOLUTION";
        std::memset(vi,   0, sizeof vi);
        std::memset(di, INF, sizeof di);
        std::deque<pii> q;
        di[0][0] = 0;
        q.push_back({0, 0});
        while(q.size()){
            auto [x, y] = q.front();q.pop_front();
            if(x == n && y == m)return std::to_string(di[x][y]);
            if(vi[x][y])continue;
            vi[x][y] = 1;
            for(int i=0; i<4;++i){
                int x1 = x + dx[i], y1 = y + dy[i];
                if(!_valid(x1, y1))continue;
                int x2 = x + lx[i], y2 = y + ly[i];
                int w  = e[x2][y2] != li[i];
                if(di[x1][y1] <= di[x][y] + w)continue;
                di[x1][y1] = di[x][y] + w;
                if(w)q.push_back({x1, y1});
                if(!w)q.push_front({x1, y1});
            }
        }
        return "NO SOLUTION" ;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0; i<n; ++i)scanf("%s", e[i]);
        std::cout << _bfs()<< std::endl;;
    }
    int main(int argc,const char *argv[]){
        std::cin >> t;
        while(t--)_deal();
        return 0;
    }
};
namespace p174{
    using pii = std::pair<int, int>;
    const int N = 32, INF = 0x3f3f3f3f;
    const int dx[4] {1, -1, 0, 0}, dy[4] {0, 0, 1, -1};
    const char ops[4] {'n', 's', 'w', 'e'};
    int n, m, k;
    char e[N][N];
    pii box, start, dist[N][N][4];
    int vi[N][N], pre_man[N][N], st[N][N][4];
    struct point {
        int x, y, d;
        point () : x(0), y(0), d(0) {};
        point (int x, int y, int d) : x(x), y(y), d(d) {};
    }endp;
    std::vector<int> path[N][N][4];
    point pre[N][N][4];
    bool _valid(int x, int y){
        return x>=1 && y>=1 && x<=n && y<=m && e[x][y]!='#';
    }
    int _bfs_man(pii be, pii ed, pii bx, std::vector<int> &p){
        std::memset(vi, 0, sizeof vi);
        std::memset(pre_man, -1, sizeof pre_man);
        vi[be.first][be.second] = vi[bx.first][bx.second] = 1;
        std::queue<pii> q;
        q.push(be);
        while(q.size()){
            auto t = q.front(); q.pop();
            auto [x, y] = t;
            if(t == ed){
                p.clear();
                while(~pre_man[x][y]){
                    int d = pre_man[x][y];
                    p.push_back(d);
                    x += dx[d], y += dy[d];
                }
                return p.size();
            }
            for(int i=0; i<4; ++i){
                int a = x - dx[i], b = y - dy[i];
                if(!_valid(a, b) || vi[a][b])continue;
                vi[a][b] = 1;
                q.emplace(a, b);
                pre_man[a][b] = i;
            }
        }
        return -1;
    }
    int _bfs_box(){
        std::memset(st, 0, sizeof st);
        std::queue<point> q;
        for(int i=0; i<4; ++i){
            int a = box.first + dx[i], b = box.second + dy[i];
            int c = box.first - dx[i], d = box.second - dy[i];
            if(!_valid(a, b) || !_valid(c, d))continue;
            std::vector<int> tp;
            int tl = _bfs_man(start, {a, b}, box, tp);
            if(tl == -1)continue;
            q.emplace(c, d, i);
            st[c][d][i]   = 1;
            dist[c][d][i] = {1, tl};
            path[c][d][i] = tp;
            pre[c][d][i]  = {box.first, box.second, -1};
        }
        pii maxv {INF, INF};
        while(q.size()){
            point t = q.front();q.pop();
            auto &v = dist[t.x][t.y][t.d];
            if(e[t.x][t.y] == 'T' && v < maxv)endp = t, maxv = v;
            auto px = t.x + dx[t.d], py = t.y + dy[t.d];
            for(int i=0; i<4; ++i){
                int a = t.x + dx[i], b = t.y + dy[i];
                int c = t.x - dx[i], d = t.y - dy[i];
                if(!_valid(a, b) || !_valid(c, d))continue;
                std::vector<int> tp;
                int tl = _bfs_man({px, py}, {a, b}, {t.x, t.y}, tp);
                if(tl == -1)continue;
                pii di {v.first + 1, v.second + tl};
                if(!st[c][d][i]){
                    q.emplace(c, d, i);
                    st[c][d][i] = 1;
                    dist[c][d][i] = di;
                    path[c][d][i] = tp;
                    pre[c][d][i]  = t;
                }else if(dist[c][d][i] > di){
                    dist[c][d][i] = di;
                    path[c][d][i] = tp;
                    pre[c][d][i]  = t;
                }
            }
        }
        return maxv.first != INF;
    }
    void _deal(){
        for(int i=1; i<=n; ++i){
            scanf("%s", e[i] + 1);
            for(int j=1; j<=m; ++j){
                char c = e[i][j];
                if(c == 'S'){
                    start = {i, j};
                }else if(c == 'B'){
                    box   = {i, j};
                }
            }
        }
        std::cout << "Maze #" << ++k << std::endl;
        std::string res {"Impossible."};
        if(_bfs_box()){
            res = "";
            while(~endp.d){
                res += ops[endp.d] - 32;
                for(auto &i : path[endp.x][endp.y][endp.d])res += ops[i];
                endp = pre[endp.x][endp.y][endp.d];
            }
            std::reverse(begin(res), end(res));
        }
        std::cout << res << std::endl << std::endl;
    }
    int main(int argc,const char *argv[]){
        while(std::cin >> n >> m && n && m)_deal();
        return 0;
    }
};

namespace p173{
    const int N = 1024;
    char e[N][N];
    int  d[N][N];
    std::queue<std::pair<int, int>> q;
    int fun[5] {0, 1, 0, -1, 0};
    int n, m;
    inline bool _valid(int x, int y){return x>=1 && y>=1 && x<=n && y<=m;}
    void _bfs(){
        while(q.size()){
            auto [x, y] = q.front();q.pop();
            for(int i=0; i<4; ++i){
                int x1 = x + fun[i], y1 = y + fun[i + 1];
                if(!_valid(x1, y1) || e[x1][y1] == '1')continue;
                if(d[x1][y1] != 0)continue;
                d[x1][y1] = d[x][y] + 1;
                q.emplace(x1, y1);
            }
        }
    }
    void _deal(){
        for(int i=1; i<=n; ++i){
            scanf("%s", e[i] + 1);
            for(int j=1; j<=m; ++j){
                if(e[i][j] == '1')q.emplace(i, j);
            }
        }
        _bfs();
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                std::cout << d[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        while(std::cin >> n >> m)_deal();
        return 0;
    }
};
namespace p172{
    struct rec { int x, y, l; } st, ed;
    const int N = 512;
    const int fun[5] {0, 1, 0, -1, 0};
    const int next_x[3][4] {{0, 1,  0, -1}, {0, 2,  0, -1}, {0, 1,  0, -2}};
    const int next_y[3][4] {{2, 0, -1,  0}, {1, 0, -1,  0}, {1, 0, -2,  0}};
    const int next_l[3][4] {{2, 0,  2,  0}, {1, 2,  1,  2}, {0, 1,  0,  1}};
    int n, m;
    char e[N][N];
    int  d[N][N][3];
    bool _valid(int x, int y){ return x>=1 && y>=1 && x<=n && y<=m; }
    bool _valid(rec &ne){
        int x = ne.x, y = ne.y, l = ne.l;
        if(!_valid(x, y))return false;
        if(e[x][y] == '#')return false;
        if(l==0)return e[x][y+1] != '#';
        if(l==1)return e[x+1][y] != '#';
        return e[x][y] == '.';
    }
    void _init(){
        for(int i=1; i<=n; ++i){
            for(int j=0; j<=m; ++j){
                if(e[i][j] == 'O'){
                    ed.x = i, ed.y = j, ed.l = 2;
                    e[i][j] = '.';
                }else if(e[i][j] == 'X'){
                    for(int f=0; f<4; ++f){
                        int i1 = i + fun[f], j1 = j + fun[f + 1];
                        if(!_valid(i1, j1) || e[i1][j1] != 'X')continue;
                        st.x = std::min(i, i1);
                        st.y = std::min(j, j1);
                        st.l = f & 1;
                        e[i1][j1] = e[i][j] = '.';
                        break;
                    }
                    if(e[i][j] != '.'){
                        e[i][j] = '.';
                        st.x = i, st.y = j, st.l = 2;
                    }
                }
                for(int k=0; k<3; ++k)d[i][j][k] = -1;
            }
        }
    }
    int _bfs(){
        std::queue<rec> q;
        q.push(st);
        d[st.x][st.y][st.l] = 0;
        while(q.size()){
            auto [x, y, l] = q.front();q.pop();
            for(int i=0; i<4; ++i){
                int i1 = x + next_x[l][i], j1 = y + next_y[l][i];
                rec ne { i1, j1, next_l[l][i] };
                if(!_valid(ne))continue;
                if(~d[ne.x][ne.y][ne.l])continue;
                d[ne.x][ne.y][ne.l] = d[x][y][l] + 1;
                if(ne.x == ed.x &&
                   ne.y == ed.y &&
                   ne.l == ed.l)return d[ne.x][ne.y][ne.l];
                q.push(ne);
            }
        }
        return -1;
    }
    void _deal(){
        for(int i=0; i<n; ++i)scanf("%s", e[i] + 1);
        _init();
        std::cout << st.x << " " << st.y << " " << st.l << std::endl;
        std::cout << ed.x << " " << ed.y << " " << ed.l << std::endl;
        int ans = _bfs();
        if(ans == -1){
            puts("Impossible");
        }else{
            std::cout << ans << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        while(std::cin >> n >> m && n && m)_deal();
        return 0;
    }
};

namespace p171{
    using ll = long long;
    const int N = 64;
    ll g[N], ans = -1, sums[1 << 24], tsums[1 << 24], idx, tidx;
    ll w, n;
    void _dfs1(ll s, int now){
        tsums[tidx++] = s;
        for(int i=now; i<n/2; ++i){
            if(s + g[i] > w)continue;
            _dfs1(s + g[i], i + 1);
        }
    }
    void _dfs2(ll s, int now){
        int pos = std::upper_bound(sums, sums + idx + 1, w - s) - sums - 1;
        ans = std::max(ans, s + sums[pos]);
        for(int i=now; i<n; ++i){
            if(s + g[i] > w)continue;
            _dfs2(s + g[i], i + 1);
        }
    }
    int main(int argc,const char *argv[]){
        std::cin >> w >> n;
        for(int i=0; i<n; ++i)std::cin >> g[i];
        std::sort(g, g + n, [&](ll a, ll b){ return a > b; });
        _dfs1(0, 0);
        std::sort(tsums, tsums + tidx);
        sums[0] = tsums[0];
        for(int i=1; i<tidx; ++i){
            while(tsums[i] == sums[idx])i++;
            sums[++idx] = tsums[i];
        }
        _dfs2(0, n / 2);
        std::cout << ans << std::endl;
        return 0;
    }
};

namespace p170{
    const int N = 128;
    int n, deep, x[N], vi[N];
    bool _dfs(int now, int pre){
        if(x[now] == n)return true;
        if(now >= deep)return false;
        for(int i=now; i>=1; --i){
            for(int j=i; j>=1; --j){
                int t = x[i] + x[j];
                if(!vi[t] && t >= pre){
                    vi[t]  = 1;
                    x[now + 1] = t;
                    if(_dfs(now + 1, t))return true;
                    x[now + 1] = 0;
                    vi[t]  = 0;
                }else if(!vi[t]){
                    break;
                }
            }
        }
        return false;
    }
    void _deal(){
        x[1] = 1, x[2] = 2;
        deep = n;
        if(n > 2){
            int k = n > 20 ? 6 : 3;
            for(; k<=10; ++k){
                deep = k;
                std::memset(vi, 0, sizeof vi);
                std::memset(x, 0, sizeof x);
                x[1] = 1, x[2] = 2;
                if(_dfs(2, 3))break;
            }
        }
        for(int i=1; i<=deep; ++i)std::cout << x[i] << " ";
        std::cout << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        while(std::cin >> n && n)_deal();
        return 0;
    }
};
namespace p169{
    const int n = 16, rn = 4;
    std::string sdline;
    int bitcnt[1 << n], num[1 << n];
    int state[n][n], st[n][n];
    int bstate[n*n+1][n][n],bstate2[n*n+1][n][n];
    char e[n][n], et[n*n+1][n][n];
    inline int _lowbit(int x){return x & -x;}
    void _draw(int x, int y, int c){
        e[x][y] = c + 'A';
        for(int i=0; i<n; ++i){
            state[x][i] &= ~(1 << c);
            state[i][y] &= ~(1 << c);
        }
        int tx = x / rn * rn, ty = y / rn * rn;
        for(int i=0; i<4; ++i){
            for(int j=0; j<4; ++j){
                state[tx+i][ty+j] &= ~(1 << c);
            }
        }
        state[x][y] = 1 << c;
    }
    void _init(){
        for(int i=0; i<n; ++i)num[1 << i] = i;
        for(int i=0; i<(1<<n); ++i){
            for(int j=i; j; j^=_lowbit(j))++bitcnt[i];
        }
    }
    bool _dfs(int p){
        if(!p)return true;
        int tp = p;
        memcpy(bstate[tp], state, sizeof state);
        memcpy(et[tp], e, sizeof e);
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j] != '-')continue;
                if(!state[i][j]){
                    memcpy(state, bstate[tp], sizeof state);
                    memcpy(e, et[tp], sizeof e);
                    return false;
                }
                if(bitcnt[state[i][j]] == 1){
                    _draw(i, j, num[state[i][j]]);
                    --p;
                }
            }
        }
        if(!p)return true;
        for(int i=0; i<n; ++i){
            int sor = 0, sand = (1 << n) - 1, drawn = 0;
            for(int j=0; j<n; ++j){
                sand &= ~(sor & state[i][j]);
                sor |= state[i][j];
                if(e[i][j] != '-')drawn |= state[i][j];
            }
            if(sor != (1 << n) - 1){
                memcpy(state, bstate[tp], sizeof state);
                memcpy(e, et[tp], sizeof e);
                return false;
            }
            for(int j=sand; j; j^=_lowbit(j)){
                int t = _lowbit(j);
                if(drawn & t)continue;
                for(int k=0; k<n; ++k){
                    if(!(state[i][k] & t))continue;
                    _draw(i, k, num[t]);
                    --p;
                    break;
                }
            }
        }
        if(!p)return true;
        for(int j=0; j<n; ++j){
            int sor = 0, sand = (1 << n) - 1, drawn = 0;
            for(int i=0; i<n; ++i){
                sand &= ~(sor & state[i][j]);
                sor |= state[i][j];
                if(e[i][j] != '-')drawn |= state[i][j];
            }
            if(sor != (1 << n) - 1){
                memcpy(state, bstate[tp], sizeof state);
                memcpy(e, et[tp], sizeof e);
                return false;
            }
            for(int i=sand; i; i^=_lowbit(i)){
                int t = _lowbit(i);
                if(drawn & t)continue;
                for(int k=0; k<n; ++k){
                    if(!(state[k][j] & t))continue;
                    _draw(k, j, num[t]);
                    --p;
                    break;
                }
            }
        }
        if(!p)return true;
        for(int i=0; i<n; ++i){
            int sor = 0, sand = (1 << n) - 1, drawn = 0;
            for(int j=0; j<n; ++j){
                int x = i / rn * rn + j / rn;
                int y = i % rn * rn + j % rn;
                sand &= ~(sor & state[x][y]);
                sor |= state[x][y];
                if(e[x][y] != '-')drawn |= state[x][y];
            }
            if(sor != (1 << n) - 1){
                memcpy(state, bstate[tp], sizeof state);
                memcpy(e, et[tp], sizeof e);
                return false;
            }
            for(int j=sand; j; j^=_lowbit(j)){
                int t = _lowbit(j);
                if(drawn & t)continue;
                for(int k=0; k<n; ++k){
                    int x = i / rn * rn + k / rn;
                    int y = i % rn * rn + k % rn;
                    if(!(state[x][y] & t))continue;
                    _draw(x, y, num[t]);
                    --p;
                    break;
                }
            }
        }
        if(!p)return true;
        int tb = n + 1, x, y;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j] != '-')continue;
                if(bitcnt[state[i][j]] >= tb)continue;
                tb = bitcnt[state[i][j]];
                x = i, y = j;
            }
        }
        memcpy(bstate2[tp], state, sizeof state);
        for(int i=state[x][y]; i; i^=_lowbit(i)){
            memcpy(state, bstate2[tp], sizeof state);
            _draw(x, y, num[_lowbit(i)]);
            if(_dfs(p - 1))return true;
        }
        memcpy(state, bstate[tp], sizeof state);
        memcpy(e, et[tp], sizeof e);
        return false;
    }
    void _deal(){
        for(int i=0; i<n; ++i)e[0][i] = sdline[i];
        for(int i=1; i<n; ++i){
            std::cin >> sdline;
            for(int j=0; j<n; ++j)e[i][j] = sdline[j];
        }
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                state[i][j] = (1 << n) - 1;
            }
        }
        int p = 16 << 4;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j] == '-')continue;
                _draw(i, j, e[i][j] - 'A');
                --p;
            }
        }
        _dfs(p);
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cout << e[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _init();
        while(std::cin >> sdline)_deal();
        return 0;
    }
};

namespace p169_f{
    const int n = 16, rn = 4;
    std::string sdline;
    int bitcnt[1 << n], num[1 << n];
    int ro[n], co[n], re[n];
    std::string et[n] {
       {"--A----C-----O-I"},
       {"-J--A-B-P-CGF-H-"},
       {"--D--F-I-E----P-"},
       {"-G-EL-H----M-J--"},
       {"----E----C--G---"},
       {"-I--K-GA-B---E-J"},
       {"D-GP--J-F----A--"},
       {"-E---C-B--DP--O-"},
       {"E--F-M--D--L-K-A"},
       {"-C--------O-I-L-"},
       {"H-P-C--F-A--B---"},
       {"---G-OD---J----H"},
       {"K---J----H-A-P-L"},
       {"--B--P--E--K--A-"},
       {"-H--B--K--FI-C--"},
       {"--F---C--D--H-N-"},
    };
    char e[n][n], te[n][n];
    inline int _lowbit(int x){ return x & -x; }
    inline int _index(int x, int y){ return (x / rn) * rn + (y / rn); }
    void _init(){
        for(int i=0; i<(1 << n); ++i){
            for(int j=i; j; j^=_lowbit(j)){
                ++bitcnt[i];
            }
        }
        for(int i=0; i<n; ++i)num[1 << i] = i;
    }
    void _bit(int x, int y, int i){
        ro[x] ^= 1 << i;
        co[y] ^= 1 << i;
        re[_index(x, y)] ^= 1 << i;
    }
    bool _dfs(int p){
        if(!p)return true;
        memcpy(e, te, sizeof e);
        int tp = p;
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(e[i][j] != '-')continue;
                int bit = ro[i] & co[j] & re[_index(i, j)];
                if(bit == 0){
                    memcpy(e, te, sizeof e);
                    p = tp;
                    return false;
                }
                if(bitcnt[bit] != 1)continue;
                int k = num[bitcnt[bit]];
                _bit(i, j, k);
                e[i][j] = k + 'A';
                --p;
            }
        }
        int bn = n + 1, x, y;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j] != '-')continue;
                int bit = ro[i] & co[j] & re[_index(i, j)];
                if(bn <= bitcnt[bit])continue;
                bn = bitcnt[bit];
                x = i, y = j;
            }
        }
        int bit = ro[x] & co[y] & re[_index(x, y)];
        for(; bit; bit ^= _lowbit(bit)){
            int i = num[_lowbit(bit)];
            _bit(x, y, i);
            e[x][y] = i + 'A';
            if(_dfs(p - 1))return true;
            e[x][y] = '-';
            _bit(x, y, i);
        }
        memcpy(te, e, sizeof e);
        return false;
    }
    void _deal(){
        //for(int i=0; i<n; ++i)e[0][i] = sdline[i];
        //for(int i=1; i<n; ++i){
            //std::cin >> sdline;
            //for(int j=0; j<n; ++j)e[i][j] = sdline[j];
        //}
        int p = n << 4;
        for(int i=0; i<n; ++i){
            ro[i] = co[i] = re[i] = (1 << n) - 1;
            for(int j=0; j<n; ++j){
                if(e[i][j] == '-')continue;
                _bit(i, j, e[i][j] - 'A');
                --p;
            }
        }
        _dfs(p);
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cout << e[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _init();
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j)e[i][j] = et[i][j];
        }
        _deal();
        //while(std::cin >> sdline)_deal();
        return 0;
    }
};
//using namespace p169;

namespace p168 {
    const int N = 64, INF = 0x3f3f3f3f;
    int n, m, ans = INF;
    int minv[N], mins[N];
    int r[N], h[N];
    int v, s;
    void _dfs(int dep){
        if(!dep){
            if(v == n)ans = std::min(s, ans);
            return;
        }
        if(v + minv[dep] > n)return;
        if(s + mins[dep] > ans)return;
        auto &rl = r[dep], &hl = h[dep];
        rl = std::min(r[dep+1]-1, (int)sqrt(n - v));
        for(; rl>=dep; --rl){
            hl = std::min(h[dep+1]-1,(int)((double)(n - v)/rl/rl));
            for(; hl>=dep; --hl){
                if(s + (double)2 * (n-v)/rl > ans)continue;
                if(dep == m)s += rl * rl;
                s += 2 * rl * hl;
                v += rl * rl * hl;
                _dfs(dep - 1);
                s -= 2 * rl * hl;
                v -= rl * rl * hl;
                if(dep == m)s -= rl * rl;
            }
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        for(int i=1; i<=m; ++i){
            minv[i] = minv[i-1] + i * i * i;
            mins[i] = mins[i-1] + i * i;
        }
        r[m+1] = h[m+1] = INF;
        _dfs(m);
        if(ans == INF)ans = 0;
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p167{
    const int N = 64 << 1;
    int n, len, sum, cnt;
    int sti[N], vi[N];
    bool _dfs(int sn, int clen, int now){
        if(sn > cnt)return true;
        if(clen == len)return _dfs(sn + 1, 0, 1);
        int fail = 0;
        for(int i=now; i<=n; ++i){
            if(vi[i] || fail == sti[i] || sti[i] + clen > len)continue;
            vi[i] = 1;
            if(_dfs(sn, clen + sti[i], i + 1))return true;
            vi[i] = 0;
            fail  = sti[i];
            if(clen==0 || sti[i]+clen == len)return false;
        }
        return false;
    }
    void _deal(){
        sum = 0;
        for(int i=1; i<=n; ++i){
            std::cin >> sti[i];
            sum += sti[i];
        }
        std::sort(sti+1, sti + n + 1, [&](int a, int b){return a > b;});
        for(len=1[sti]; len<=sum; ++len){
            if(sum % len)continue;
            cnt = sum / len;
            std::memset(vi, 0, sizeof vi);
            if(_dfs(1, 0, 1))break;
        }
        std::cout << len << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        while(std::cin >> n && n)_deal();
        return 0;
    }
};
namespace p166{
    std::string sd;
    int bitcnt[1 << 9], num[1 << 9];
    int ro[9], co[9], re[9];
    char e[9][9];
    inline int _index(int x, int y){
        return (x / 3) * 3 + (y / 3);
    }
    inline int _lowbit(int x){
        return x & -x;
    }
    inline void _bit(int x, int y, int i){
        ro[x] ^= 1 << i;
        co[y] ^= 1 << i;
        re[_index(x, y)] ^= 1 << i;
    }
    bool _dfs(int n){
        if(!n)return true;
        int tn = 10, x, y;
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(e[i][j] != '.')continue;
                int bit = ro[i] & co[j] & re[_index(i, j)];
                if(!bit)return 0;
                if(tn <= bitcnt[bit])continue;
                tn = bitcnt[bit];
                x = i, y = j;
            }
        }
        int b = ro[x] & co[y] & re[_index(x, y)];
        for(; b; b^=_lowbit(b)){
            int i = num[_lowbit(b)];
            e[x][y] = i + '1';
            _bit(x, y, i);
            if(_dfs(n - 1))return 1;
            _bit(x, y, i);
            e[x][y] = '.';
        }
        return 0;
    }
    void _deal(){
        for(int i=0,k=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                e[i][j] = sd[k++];
            }
            ro[i] = co[i] = re[i] = (1 << 9) - 1;
        }
        int n = 81;
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(e[i][j] == '.')continue;
                _bit(i, j, e[i][j] - '1');
                --n;
            }
        }
        _dfs(n);
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                std::cout << e[i][j];
            }
        }
        std::cout << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        for(int i=0; i<(1<<9); ++i){
            for(int j=i; j; j^=_lowbit(j)){
                ++bitcnt[i];
            }
        }
        for(int i=0; i<9; ++i)num[1 << i] = i;
        while(std::cin >> sd && sd[0] != 'e')_deal();
        return 0;
    }
};
namespace p165{
    using ll = long long;
    const int N = 36;
    int n, w, ans = INT_MAX;
    ll cats[N], cars[N];
    void _dfs(int cnt, int idx){
        if(idx == n){
            ans = std::min(ans, cnt);
            return;
        }
        if(cnt >= ans)return;
        for(int i=1; i<=cnt; ++i){
            if(cars[i] + cats[idx] > w)continue;
            cars[i] += cats[idx];
            _dfs(cnt, idx + 1);
            cars[i] -= cats[idx];
        }
        cars[cnt + 1] = cats[idx];
        _dfs(cnt + 1, idx + 1);
        cars[cnt + 1] = 0;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> w;
        for(int i=0; i<n; ++i){
            std::cin >> cats[i];
        }
        std::sort(cats, cats + n, [&](ll a, ll b){return a > b;});
        _dfs(0, 0);
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p164{
    const int N = 3e4 + 12;
    int n, m, idx, x, y;
    int to[N << 1], head[N << 1], ne[N << 1], in[N];
    std::bitset<N> bs[N];
    std::queue<int> q;
    std::vector<int> tp;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _init(){
        std::cin >> n >> m;
        for(int i=0; i<m; ++i){
            std::cin >> x >> y;
            ++in[y];
            _add(x, y);
        }
    }
    void _deal(){
        for(int i=1; i<=n; ++i){
            if(!in[i])q.push(i);
        }
        while(q.size()){
            x = q.front();q.pop();
            tp.push_back(x);
            for(int i=head[x]; i; i=ne[i]){
                y = to[i];
                if(!--in[y])q.push(y);
            }
        }
        for(int i=n-1; i>=0; --i){
            x = tp[i];
            bs[x][x] = 1;
            for(int j=head[x]; j; j=ne[j]){
                y = to[j];
                bs[x] |= bs[y];
            }
        }
        for(int i=1; i<=n; ++i){
            std::cout << bs[i].count() << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        _init();
        _deal();
        return 0;
    }
};
