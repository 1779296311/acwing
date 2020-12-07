/*********************************************
*     ------------------------
*     ------------------------
*     file name: 7.cpp
*     author   : @ JY
*     date     : 2020--11--27
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <functional>
#include <cstdlib>

namespace p127{
    using pii = std::pair<int, int>;
    using ll  = long long;
    ll N, M, i, ans, money;
    struct _cmp{
        bool operator()(const pii &a, const pii &b){
            return a.first == b.first ? a.second > b.second : a.first > b.first;
        }
    };
    int cnt[112];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> M >> N;
        std::vector<pii> m(M), t(N);
        for(auto &[f, s] : m)std::cin >> f >> s;
        for(auto &[f, s] : t)std::cin >> f >> s;
        std::sort(begin(m), end(m), _cmp());
        std::sort(begin(t), end(t), _cmp());
        for(auto &[tt, tc] : t){
            while(i < M && m[i].first >= tt)++cnt[m[i++].second];
            for(int j=tc; j<112; ++j){
                if(cnt[j]){
                    ++ans;
                    money += tt * 500 + (tc << 1);
                    --cnt[j];
                    break;
                }
            }
        }
        std::cout << ans << " " << money << std::endl;
        return 0;
    }
};
namespace p127_fuck{
    int N, M, money, ans;
    using pii = std::pair<int, int>;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> M >> N;
        std::vector<pii> m(M), t(N), temp;
        for(auto &[f, s] : m)std::cin >> f >> s;
        for(auto &[f, s] : t)std::cin >> f >> s;
        std::sort(begin(m), end(m), [&](auto &a, auto &b){
            return a.first == b.first ? a.second < b.second : a.first < b.first; });
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        for(auto &node : t) q.push(node);
        int i = -1;
        while(q.size() && ++i < M){
            auto [t1, t2] = q.top();
            while(i<M && (t1>m[i].first || t2>m[i].second))++i;
            if(i == M)break;
            auto [m1, m2] = m[i];
            while(q.size() && q.top().first <= m1 && q.top().second<=m2){
                temp.push_back(q.top());q.pop();
            }
            std::sort(begin(temp), end(temp), [&](auto &a, auto &b){
                return 250*a.first + a.second < 250*b.first + b.second; });
            ++ans, money += temp.back().first * 250 + temp.back().second;
            temp.pop_back();
            for(auto &node : temp)q.push(node);
            temp.clear();
        }
        std::cout << ans << " " << (money << 1) << std::endl;
        return 0;
    }
};
namespace p126{
    int N, ans = -1e5;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> N;
        std::vector<std::vector<int>> e(N + 1, std::vector<int>(N + 1));
        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                std::cin >> e[i][j];
                ans = std::max(e[i][j], ans);
            }
        }
        if(ans <= 0){
            std::cout << ans << std::endl;
            return 0;
        }
        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                e[i][j] += e[i][j-1];
            }
        }
        for(int l=1; l<=N; ++l){
            for(int r=l; r<=N; ++r){
                int sum = 0;
                for(int i=1; i<=N; ++i){
                    sum += e[i][r] - e[i][l-1];
                    ans = std::max(ans, sum);
                    sum = std::max(sum, 0);
                }
            }
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p125{
    using ll = long long;
    ll N, ans = -1e6, w;
    int main(int argc,const char *argv[]){
        std::cin >> N;
        std::vector<std::pair<ll, ll>> cows(N);
        for(auto &[f, s] : cows) std::cin >> f >> s;
        std::sort(begin(cows), end(cows), [&](auto &a, auto &b){
            return a.first + a.second < b.first + b.second; });
        for(auto &[f, s] : cows){
            ans = std::max(ans, w - s);
            w += f;
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p124{
int N, in, out;
std::string itoc {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
std::unordered_map<char, int> ctoi{
          {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
          {'A',10}, {'B',11}, {'C',12}, {'D',13}, {'E',14}, {'F',15}, {'G',16}, {'H',17}, {'I',18}, {'J',19},
          {'K',20}, {'L',21}, {'M',22}, {'N',23}, {'O',24}, {'P',25}, {'Q',26}, {'R',27}, {'S',28}, {'T',29},
          {'U',30}, {'V',31}, {'W',32}, {'X',33}, {'Y',34}, {'Z',35}, {'a',36}, {'b',37}, {'c',38}, {'d',39},
          {'e',40}, {'f',41}, {'g',42}, {'h',43}, {'i',44}, {'j',45}, {'k',46}, {'l',47}, {'m',48}, {'n',49},
          {'o',50}, {'p',51}, {'q',52}, {'r',53}, {'s',54}, {'t',55}, {'u',56}, {'v',57}, {'w',58}, {'x',59},
          {'y',60}, {'z',61}
};
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::string ans, num;
    std::vector<int> dig;
    std::cin >> N;
    std::function<void(void)> _deal = [&](void){
        std::cin >> in >> out >> num;
        int len = num.size();
        for(auto &c : num)dig.push_back(ctoi[c]);
        //for(auto &c : num){
            //if(std::isdigit(c)){
                //dig.push_back(c - '0');
            //}else if(std::isupper(c)){
                //dig.push_back(c - 'A' + 10);
            //}else{
                //dig.push_back(c - 'a' + 36);
            //}
        //}
        std::reverse(begin(dig), end(dig));
        while(len){
            int x = 0;
            for(int i=len-1; i>=0; --i){
                x = x * in + dig[i];
                dig[i] = x / out;
                x %= out;
            }
            while(!dig[len-1] && len>0)--len;
            ans += itoc[x];
        }
        std::reverse(begin(ans), end(ans));
        std::cout << in  << " " << num << std::endl;
        std::cout << out << " " << ans << std::endl << std::endl;;
        ans.clear(), dig.clear();
    };
    while(N--)_deal();
    return 0;
}
};

namespace p123_1{
int N, ans;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> N;
    std::vector<int> px(N), py(N);
    for(int i=0; i<N; ++i){
        std::cin >> px[i] >> py[i];
    }
    std::sort(begin(py), end(py));
    std::sort(begin(px), end(px));
    for(int i=0; i<N; ++i)px[i] -= i;
    std::sort(begin(px), end(px));
    for(auto &y : py)ans += abs(py[N >> 1] - y);
    for(auto &x : px)ans += abs(px[N >> 1] - x);
    std::cout << ans << std::endl;
    return 0;
}
};
namespace p123{
    using ll = long long;
    int main(const int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        ll n, res = 0, sug = 0;
        std::cin >> n;
        std::vector<int> kids(n);
        for(auto &k : kids)std::cin >> k;
        sug = std::accumulate(begin(kids), end(kids), 0ll) / n;
        for(auto &x : kids)x -= sug;
        for(int i=1; i<n; ++i)kids[i] += kids[i-1];
        std::sort(begin(kids), end(kids));
        for(int i=0; i<n; ++i){
            res += abs(kids[i] - kids[n >> 1]);
        }
        std::cout << res << std::endl;
        return 0;
    }
};
namespace p122{
using pii = std::pair<int, int>;
const int size = 1012;
int C, N, len;
int sums[size][size];
pii points[size];
std::vector<int> mp;

int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> C >> N;
    mp.emplace_back(0);
    for(int i=0; i<N; ++i){
        std::cin >> points[i].first >> points[i].second;
        mp.emplace_back(points[i].first);
        mp.emplace_back(points[i].second);
    }
    std::sort(begin(mp), end(mp));
    mp.erase(std::unique(begin(mp), end(mp)), end(mp));
    len = mp.size();
    std::function<int(int)> _index = [&](int idx){
        return std::lower_bound(begin(mp), end(mp), idx) - begin(mp);
    };
    std::function<bool(int)> _check = [&](int m){
        for(int li=1,ri=1; ri<len; ++ri){
            while(mp[ri] - mp[li] + 1 > m)++li;
            for(int lj=1,rj=1; rj<len; ++rj){
                while(mp[rj] - mp[lj] + 1 > m)++lj;
                if(sums[ri][rj] - sums[li-1][rj] -
                        sums[ri][lj-1] + sums[li - 1][lj - 1] >= C){
                    return true;
                }
            }
        }
        return false;
    };
    for(int i=0; i<N; ++i){
        int x = _index(points[i].first), y = _index(points[i].second);
        ++sums[x][y];
    }
    for(int i=1; i<len; ++i){
        for(int j=1; j<len; ++j){
            sums[i][j] += sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1];
        }
    }
    int l = 1, r = 10000;
    while(l < r){
        int m = l + ((r - l) >> 1);
        if(_check(m)){
            r = m;
        }else{
            l = m + 1;
        }
    }
    std::cout << r << std::endl;
    return 0;
}
};

namespace p120{
using ll = long long;
ll T, N;
struct node{ ll s, e, d; } nodes[200012];
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> T;
    std::function<ll(ll)> _check = [&](ll idx){
        ll sum = 0;
        for(int i=0; i<N; ++i){
            if(idx < nodes[i].s)continue;
            sum += (std::min(idx, nodes[i].e) - nodes[i].s) / nodes[i].d + 1;
        }
        return sum;
    };
    std::function<void(void)> _deal = [&](void){
        std::cin >> N;
        for(int i=0; i<N; ++i)std::cin >> nodes[i].s >> nodes[i].e >> nodes[i].d;
        ll l = 0, r = INT_MAX - 1;
        while(l < r){
            int m = l + ((r - l) >> 1);
            if(_check(m) & 1){
                r = m;
            }else{
                l = m + 1;
            }
        }
        ll ans = _check(r) - _check(r-1);
        if(ans & 1){
            std::cout << r << " " << ans << std::endl;
        }else{
            std::cout << "There's no weakness." << std::endl;
        }
    };
    while(T--)_deal();
    return 0;
}
};
