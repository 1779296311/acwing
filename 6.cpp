/*********************************************
*     ------------------------
*     ------------------------
*     file name: 6.cpp
*     author   : @ JY
*     date     : 2020--11--26
**********************************************/
#include <iostream>
#include <functional>
#include <numeric>
#include <climits>
#include <cmath>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
namespace p119{
int T, N, x, y, INF = 1e9;
using pii = std::pair<int, int>;
struct node{
    double x, y;
    int type;
    bool operator < (const node &other){
        return x < other.x;
    }
}points[100002 << 1], t[100002 << 1];
double _calc(node &a, node &b){
    if(a.type == b.type)return INF;
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}
double _dfs(int l, int r){
    if(l == r)return INF;
    int mid = l + ((r - l) >> 1);
    double mdx = points[mid].x;
    double ans = std::min(_dfs(l, mid), _dfs(mid+1, r));
    int i = l, j = mid + 1, k = 0;
    for(int p=l; p<=r; ++p){
        if(j>r || (i<=mid && points[i].y < points[j].y)){
            t[p] = points[i++];
        }else{
            t[p] = points[j++];
        }
    }
    for(int i=l; i<=r; ++i)points[i] = t[i];
    for(int i=l; i<=r; ++i){
        if(points[i].x >= mdx-ans && points[i].x <= mdx+ans){
            t[k++] = points[i];
        }
    }
    for(int i=0; i<k; ++i){
        for(int j=i-1; ~j&&t[i].y-t[j].y<=ans; --j){
            ans = std::min(ans, _calc(t[i], t[j]));
        }
    }
    return ans;
};
int main(int argc,const char *argv[]){
    std::cin >> T;
    std::function<void(void)> _deal = [&](void){
        std::cin >> N;
        for(int i=0; i<N<<1; ++i){
            std::cin >> points[i].x >> points[i].y;
            points[i].type = i < N;
        }
        std::sort(points, points + (N << 1));
        printf("%.3lf\n", _dfs(0, (N << 1) - 1) );
    };
    while(T--)_deal();
    return 0;
}
};
namespace p118{
int _power(int x, int n){
    int ans = 1;
    while(n){
        if(n & 1)ans *= x;
        x *= x;
        n >>= 1;
    }
    return ans;
}
int e[1010][1010];
    int main(int argc,const char *argv[]){
        int n;
        std::function<void(int, int, int)> _dfs = [&](int n, int i, int j){
            if(n == 1){
                e[i][j] = 1;
                return;
            }
            int len = _power(3, n - 2);
            _dfs(n - 1, i, j);
            _dfs(n - 1, i+len, j+len);
            _dfs(n - 1, i+len*2, j);
            _dfs(n - 1, i, j+len*2);
            _dfs(n - 1, i+len*2, j+len*2);
        };
        std::function<void(void)> _deal = [&](void){
            if(n == -1)return;
            _dfs(n, 1, 1);
            int len = _power(3, n-1);
            for(int i=1; i<=len; ++i){
                for(int j=1; j<=len; ++j){
                    e[i][j] ? std::cout << 'X' : std::cout << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "-\n";
        };
        while(std::cin >> n)_deal();
        return 0;
    }
};
namespace p117{
    int main(int argc,const char *argv[]){
        std::vector<std::vector<char>> e(13, std::vector<char>(4));
        for(int i=0; i<13; ++i){
            for(int j=0; j<4; ++j){
                std::cin >> e[i][j];
            }
        }
        std::unordered_map<char, int> mp;
        std::unordered_map<char, int> midx {{'A', 0},{'2', 1}, {'3', 2}, {'4', 3},{'5', 4},
                                            {'6', 5}, {'7', 6}, {'8', 7},{'9', 8},{'0', 9}, {'J', 10},
                                            {'Q', 11},{'K', 12}};
        std::vector<int> index(13, 4);
        for(int i=0; i<4; ++i){
            char l = e[12][i];
            while(1){
                if(l == 'K')break;
                ++mp[midx[l]];
                l = e[midx[l]][--index[midx[l]]];
            }
        }
        int ans = 0;
        for(auto &[k, n] : mp)ans += n == 4;
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace P116{
    int main(int argc,const char *argv[]){
        std::vector<std::pair<int, int>> ans;
        int state = 0;
        char c;
        for(int i=0; i<16; ++i){
            std::cin >> c;
            state |= (c == '+') << i;
        }
        for(int s=1; s < (1 << 16); ++s){
            int t = state;
            for(int i=0; i<16; ++i){
                if(!(s & (1 << i)))continue;
                int x = i / 4, y = i % 4;
                for(int j=0; j<4; ++j)state ^= (1 << (x * 4 + j)) ^ (1 << (j * 4 + y));
                state ^= 1 << i;
                ans.emplace_back(x+1, y+1);
            }
            if(state == 0)break;
            ans.clear();
            state = t;
        }
        std::cout << ans.size() << std::endl;
        for(auto &[x, y] : ans)std::cout << x << " " << y << std::endl;
        return 0;
    }
};

namespace p115{
const int N = 10012;
int n, r, a, b, res = 0;
struct node{
    int father, sum, size;
    double avg;
}nodes[N];
int _find(){
    double ans = -1, a = 0;
    for(int i=1; i<=n; ++i){
        if(i != r && a < nodes[i].avg){
            ans = i;
            a = nodes[i].avg;
        }
    }
    return ans;
}
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> r;
        for(int i=1; i<=n; ++i){
            auto &[f, s, si, avg] = nodes[i];
            std::cin >> avg;
            si = 1;
            res += avg;
            s = avg;
        }
        for(int i=1; i<n; ++i){
            std::cin >> a >> b;
            nodes[b].father = a;
        }
        for(int i=1; i<n; ++i){
            int tar = _find();
            int f   = nodes[tar].father;
            nodes[f].size += nodes[tar].size;
            nodes[f].sum  += nodes[tar].sum;
            nodes[f].avg   = (double)nodes[f].sum / nodes[f].size;
            for(int i=1; i<=n; ++i){
                if(nodes[i].father == tar){
                    nodes[i].father = f;
                }
            }
            res += nodes[tar].sum * nodes[f].size;
            nodes[tar].avg = -1;
        }
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p114{
std::vector<int> mul(std::vector<int> &a, int b){
    std::vector<int> ans;
    int t = 0;
    for(auto &dig : a){
        t += dig * b;
        ans.emplace_back(t % 10);
        t /= 10;
    }
    while(t){
        ans.emplace_back(t % 10);
        t /= 10;
    }
    return ans;
}
std::vector<int> div(std::vector<int> &a, int b){
    std::vector<int> ans;
    int t = 0, x;
    for(int i=a.size()-1; i>=0; --i){
        t = t * 10 + a[i];
        x = t / b;
        if(x || ans.size())ans.emplace_back(x);
        t %= b;
    }
    std::reverse(begin(ans), end(ans));
    return ans;
}
std::vector<int> max_(std::vector<int> a, std::vector<int> b){
    if(a.size() > b.size())return a;
    if(a.size() < b.size())return b;
    if(std::vector<int>{rbegin(a), rend(a)} <
            std::vector<int>{rbegin(b), rend(b)})return b;
    return a;
}
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int n;
        std::cin >> n;
        std::vector<std::pair<int, int>> pe(n + 1);
        for(auto &[f, s] : pe){
            std::cin >> f >> s;
            f *= s;
        }
        std::sort(begin(pe) + 1, end(pe));
        std::vector<int> res(1, 0), m(1, 1);
        for(int i=0; i<=n; ++i){
            if(i)res = max_(res, div(m, pe[i].second));
            m = mul(m, pe[i].first / pe[i].second);
        }
        for(int i=res.size()-1; i>=0; --i)std::cout << res[i];
        std::cout << std::endl;
        return 0;
    }
};
namespace p113{
    bool compare(int a, int b);
    std::vector<int> specialSort(int N){
        std::vector<int> res(N);
        std::iota(begin(res), end(res), 1);
        std::stable_sort(begin(res), end(res), compare);
        return res;
    }
};

namespace p112{
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int n, d, ans = 0;
        std::cin >> n >> d;
        std::vector<std::pair<double, double>> lo(n);
        for(auto &[f, s] : lo){
            std::cin >> f >> s;
            if(s > d){
                std::cout << -1 << std::endl;
                return 0;
            }
            double dx = sqrt(d*d-s*s);
            double x1 = f - dx, x2 = f + dx; 
            f = x2, s = x1;
        }
        std::sort(begin(lo), end(lo));
        double end = INT_MIN;
        for(auto &[e, s] : lo){
            if(s > end){
                end = e;
                ++ans;
            }
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p111{
using pii = std::pair<int, int>;
int N;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> N;
    std::vector<std::pair<int, int>> cows(N);
    for(auto &[f, s] : cows) std::cin >> f >> s;
    std::vector<int> ans(N), mp(N);
    std::iota(begin(mp), end(mp), 0);
    std::sort(begin(mp), end(mp), [&](auto &a, auto &b){
        return cows[a].first < cows[b].first; });
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    for(auto &i : mp){
        if(!q.size() || q.top().first >= cows[i].first){
            ans[i] = q.size() + 1;
            q.emplace(cows[i].second, q.size() + 1);
        }else{
            auto tp = q.top();q.pop();
            ans[i] = tp.second;
            tp.first = cows[i].second;
            q.push(tp);
        }
    }
    std::cout << q.size() << std::endl;
    for(auto &x : ans) std::cout << x << std::endl;
    return 0;
}
};
namespace p110_2{
    int main(int argc,const char *argv[]){
        int n, m, i = 0, j = -1, ans = 0;
        std::cin >> n >> m;
        std::vector<std::pair<int, int>> cows(n), cn(m);
        for(auto &[f, s] : cows)std::cin >> f >> s;
        for(auto &[f, s] : cn)std::cin >> f >> s;
        std::sort(begin(cows), end(cows));
        std::sort(begin(cn), end(cn));
        std::priority_queue<int> q;
        while(++j<m){
            while(i<n && cn[j].first >= cows[i].first)q.push(-cows[i++].second);
            while(q.size() && -q.top() < cn[j].first)q.pop();
            while(q.size() && cn[j].second--)q.pop(), ++ans;
        }
        std::cout << ans << std::endl;
        return 0;
    }
};

namespace p110{
int C, L, ans;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> C >> L;
    std::vector<std::pair<int, int>> minmax(C);
    std::map<int, int> cn;
    for(int i=0; i<C; ++i)std::cin >> minmax[i].first >> minmax[i].second;
    for(int i=0; i<L; ++i){
        int x, y;
        std::cin >> x >> y;
        cn[x] += y;
    }
    std::sort(begin(minmax), end(minmax));
    cn[0] = cn[1001] = C;
    for(int i=C-1; i>=0; --i){
        auto it = cn.upper_bound(minmax[i].second);
        if((--it)->first < minmax[i].first)continue;
        ++ans;
        if(!--it->second) cn.erase(it);
    }
    std::cout << ans << std::endl;
    return 0;
}
};
