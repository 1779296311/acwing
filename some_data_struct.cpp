/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_data_struct.cpp
*     author   : @ JY
*     date     : 2020--12--01
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <cmath>
#include <cstring>
#include <climits>
#include <set>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <functional>
#include <stdlib.h>

namespace p163{
    using pii = std::pair<int, int>;
    const int N = 100012;
    int n, m, k, x, cnt, ans;
    int d[N], del[N], pre[N], nxt[N];
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    void _remove(int x){
        del[x] = 1;
        pre[nxt[x]] = pre[x];
        nxt[pre[x]] = nxt[x];
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            std::cin >> x;
            if(!x)continue;
            if(!k || (long long)x*d[k] < 0){
                d[++k] = x;
            }else{
                d[k] += x;
            }
        }
        for(int i=1; i<=k; ++i){
            if(d[i] > 0) ans += d[i], ++cnt;
            pre[i] = i - 1;
            nxt[i] = i < k ? i + 1 : 0;
            q.emplace(abs(d[i]), i);
        }
        while(cnt > m){
            auto t = q.top();q.pop();
            while(del[t.second])t=q.top(),q.pop();
            auto [v, i] = t;
            if(d[i] > 0 || (pre[i] && nxt[i])){
                ans -= v;
                d[i] = d[i] + d[pre[i]] + d[nxt[i]];
                q.emplace(abs(d[i]), i);
                _remove(pre[i]);
                _remove(nxt[i]);
                --cnt;
            }
        }
        std::cout << ans << std::endl;
        return 0;
    }
};

namespace p161{
    const int N = 100012;
    int t, n;
    int trie[N << 1][10];
    std::string str;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> t;
        std::function<void(void)> _deal = [&](void){
            std::cin >> n;
            int code = 0;
            bzero(trie, N * 10 * 4 * 2);
            std::unordered_set<int> mp;
            std::vector<std::string> strs(n);
            for(auto &s : strs)std::cin >> s;
            for(auto &str : strs){
                int cur = 0, pre = code;
                for(auto &c : str){
                    if(!trie[cur][c-'0'])trie[cur][c-'0'] = ++code;
                    cur = trie[cur][c-'0'];
                    if(mp.count(cur)){
                        std::cout << "NO" << std::endl;
                        return ;
                    }
                }
                if(pre == code){
                    std::cout << "NO" << std::endl;
                    return ;
                }
                mp.insert(cur);
            }
            std::cout << "YES" << std::endl;
        };
        while(t--)_deal();
        return 0;
    }
};

namespace p160_kmp{
    const int N = 1e5 + 12;
    int n, m, q, x;
    int ne[N], cnt[N];
    std::string c1, c2;
    void _get_next(){
        int j = 1, jump = 0;
        while(j<=m){
            if(c2[j] == c2[jump]){
                ne[++j] = ++jump;
            }else if(!jump){
                ne[++j] = 0;
            }else{
                jump = ne[jump];
            }
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m >> q;
        std::cin >> c1 >> c2;
        _get_next();
        int j = 0, i = 0;
        while(i<n && j<=m){
            if(c1[i] == c2[j]){
                ++i, ++j;
                ++cnt[j];
            }else if(!j){
                ++cnt[j];
                ++i;
            }else{
                j = ne[j];
            }
        }
        for(int i=m; i; --i)cnt[ne[i]] += cnt[i];
        while(q--){
            std::cin >> x;
            std::cout << cnt[x] - cnt[x+1] << std::endl;
        }
        return 0;
    }
};
namespace p160_hash{
    using ull = unsigned long long;
    const ull hash_code = 131;
    const int N = 2e5 + 12;
    int n, m, q, x;
    std::string c1, c2;
    ull a[N], b[N], _pow[N], cnt[N];
    ull _get_hash(ull *sums,  int l, int len){
        int r = l + len - 1;
        return sums[r] - sums[l-1] * _pow[len];
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m >> q;
        std::cin >> c1 >> c2 ;
        _pow[0] = 1;
        for(int i=1; i<=n; ++i){
            a[i]   = a[i-1] * hash_code + c1[i-1];
            _pow[i] = _pow[i-1] * hash_code;
        }
        for(int i=1; i<=m; ++i){
            b[i] += b[i-1] * hash_code + c2[i-1];
        }
        for(int i=1; i<=n; ++i){
            int l = 0, r = std::min(n - i + 1, m) + 1;
            while(l < r){
                int mid = l + ((r - l) >> 1);
                if(_get_hash(a, i, mid) !=
                   _get_hash(b, 1, mid)){
                    r = mid;
                }else{
                    l = mid + 1;
                }
            }
            ++cnt[r - 1];
        }
        std::function<void(void)> _deal = [&](void){
            std::cin >> x;
            std::cout << cnt[x] << std::endl;
        };
        while(q--)_deal();
        return 0;
    }
};
void mb_next(int *next, std::string str){
    int len = str.size();
    for(int i=2, j=0; i<=len; ++i){
        while(j && str[i] != str[j+1])j = next[j];
        if(str[i] == str[j+1])++j;
        next[i] = j;
    }
}
namespace p159_kmp2{
    using vvc = std::vector<std::vector<char>>;
    const int N = 10024;
    int n, m, l;
    std::string tmp;
    int next1[N], next2[N];
    void _get_next(int *next, vvc &str){
        int j = 1, jump = 0, len = str.size();
        while(j<=len){
            if(str[j] == str[jump]){
                next[++j] = ++jump;
            }else if(!jump){
                next[++j] = 0;
            }else{
               jump = next[jump];
            }
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        std::vector<std::vector<char>> s1(n+1, std::vector<char>(m+1)),
                                       s2(m+1, std::vector<char>(n+1));
        for(int i=0; i<n; ++i){
            std::cin >> tmp;
            for(int j=0; j<m; ++j){
                s2[j][i] = s1[i][j] = tmp[j];
            }
        }
        _get_next(next1, s1);
        _get_next(next2, s2);
        std::cout << (n - next1[n]) * (m - next2[m]) << std::endl;
        return 0;
    }
};
namespace p159{
    const int N = 10024;
    bool ism[N];
    char str[N][128];
    int n, m, next[N];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        for(int i=0; i<n; ++i){
            std::cin >> str[i];
            for(int l=1; l<=m; ++l){
                if(ism[l])continue;
                bool is_m = 0;
                for(int k=l; k<m; k+=l){
                    for(int p=0; p<l && (k+p)<m; ++p){
                        if(str[i][p] != str[i][k+p]){
                            is_m = 1;
                            break;
                        }
                    }
                    if(is_m)break;
                }
                if(is_m)ism[l] = true;
            }
        }
        int wid;
        for(int l=1; l<=m; ++l){
            if(!ism[l]){
                wid = l;
                break;
            }
        }
        for(int i=0; i<n; ++i)str[i][wid] = 0;
        int j = 1, jump = 0;
        while(j<=n){
            if(!strcmp(str[j], str[jump])){
                next[++j] = ++jump;
            }else if(!jump){
                next[++j] = 0;
            }else{
                jump = next[jump];
            }
        }
        std::cout << wid * (n - next[n]) << std::endl;
        return 0;
    }
};
namespace p158{
    std::string str1, str2, ans;
    int _min_dis(std::string &str){
        int len = str.size();
        for(int i=0; i<len; ++i)str += str[i];
        int i = 0, j = 1, k;
        while(i<len && j<len){
            for(k=0; k<len && str[i+k] == str[j+k]; ++k);
            if(k == len)break;
            if(str[i+k] > str[j+k]){
                i = i + k + 1;
                i += i == j;
            }else{
                j = j + k + 1;
                j += i == j;
            }
        }
        return std::min(i, j);
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> str1 >> str2;
        int len1 = str1.size(), len2 = str2.size();
        std::function<bool(void)> _check = [&](void){
            int l1 = _min_dis(str1), l2 = _min_dis(str2);
            ans = {begin(str1) + l1, begin(str1) + l1 + len1};
            return ans == std::string {begin(str2) + l2, begin(str2) + l2 + len2};
        };
        if(len1 != len2 || !_check()){
            std::cout << "No";
        }else{
            std::cout << "Yes" << std::endl;
            std::cout << ans  << std::endl;
        }
        return 0;
    }
};
namespace p157{
    int n;
    std::string str1, str2;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::function<std::string(std::string &str, int &idx)> _dfs
            = [&](std::string &str, int &idx){
                std::vector<std::string> tmp;
                ++idx;
                while(str[idx] == '0')tmp.emplace_back(_dfs(str, idx));
                ++idx;
                std::sort(begin(tmp), end(tmp));
                std::string ans = "0";
                for(auto &s : tmp)ans += s;
                return ans + '1';
            };
        std::function<void(void)> _deal = [&](void){
            std::cin >> str1 >> str2;
            str1 = '0' + str1 + '1';
            str2 = '0' + str2 + '1';
            int idx1 = 0, idx2 = 0;
            if(_dfs(str1, idx1) == _dfs(str2, idx2)){
                std::cout << "same" << std::endl;
            }else{
                std::cout << "different" << std::endl;
            }
        };
        while(n--)_deal();
        return 0;
    }
};
namespace p156{
    using ull = unsigned long long;
    const ull N = 1024, hash_code_c = 131, hash_code_r = 13331;
    int m, n ,a ,b, q;
    ull  sm[N][N], t[N][N], _powc, _powr;
    std::unordered_set<int> mp;
    void _calc_hash(ull (*sums)[N], int row, int col){
        for(int i=1; i<=row; ++i){
            for(int j=1; j<=col; ++j){
                scanf("%1u", &sums[i][j]);
                sums[i][j] += sums[i-1][j] * hash_code_r;
                sums[i][j] += sums[i][j-1] * hash_code_c;
                sums[i][j] -= sums[i-1][j-1] * hash_code_c * hash_code_r;
            }
        }
    }
    ull _pow(ull a, ull b){
        ull ans = 1;
        while(b){
            if(b & 1)ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        scanf("%d%d%d%d", &m, &n, &a, &b);
        _powr = _pow(hash_code_r, a);
        _powc = _pow(hash_code_c, b);
        _calc_hash(sm, m, n);
        for(int i=a; i<=m; ++i){
            for(int j=b; j<=n; ++j){
                ull hash_code = sm[i][j];
                hash_code -= sm[i][j-b] * _powc;
                hash_code -= sm[i-a][j] * _powr;
                hash_code += sm[i-a][j-b] * _powc * _powr;
                mp.insert(hash_code);
            }
        }
        scanf("%d", &q);
        std::function<void(void)> _deal = [&](void){
            _calc_hash(t, a, b);
            std::cout << mp.count(t[a][b]) << std::endl;
        };
        while(q--)_deal();
        return 0;
    }
};
namespace p155{
    using pii = std::pair<int, int>;
    const int N = 1e5 + 12;
    int n, waitn, endt, t, m, p;
    std::queue<pii> waitq;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> ends;
    std::set<pii> runs;
    bool _alloc(int t, int m, int p){
        for(auto it=begin(runs); it!=end(runs); ++it){
            auto tmp = it, nxt = ++tmp;
            if(nxt == end(runs))break;
            int start = it->first + it->second;
            if(start + m > nxt->first)continue;
            runs.emplace(start, m);
            ends.emplace(t+p, start);
            return true;
        }
        return false;
    }
    void _back(int t){
        while(ends.size() && ends.top().first <= t){
            int nowtime = ends.top().first;
            while(ends.size() && ends.top().first == nowtime){
                auto[et, start] = ends.top();ends.pop();
                runs.erase(runs.lower_bound({start, 0}));
            }
            while(waitq.size()){
                if(_alloc(nowtime, waitq.front().first, waitq.front().second)){
                    waitq.pop();
                }else{
                    break;
                }
            }
            endt = nowtime;
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        runs.emplace(-1, 1);
        runs.emplace(n, 1);
        while(1){
            std::cin >> t >> m >> p;
            if(!t && !m && !p)break;
            _back(t);
            if(!_alloc(t, m, p)){
                waitq.emplace(m, p);
                ++waitn;
            }
        }
        _back(1e9 + 12);
        std::cout << endt << std::endl << waitn << std::endl;
        return 0;
    }
};
namespace p154{
    int n, k;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> k;
        std::vector<int> nums(n), mins, maxs;
        std::deque<int> st;
        for(auto &x : nums) std::cin >> x;
        for(int i=0; i<n; ++i){
            while(st.size() && nums[st.back()] >= nums[i])st.pop_back();
            st.push_back(i);
            while(i - st.front() >= k)st.pop_front();
            mins.emplace_back(nums[st.front()]);
        }
        while(st.size())st.pop_back();
        for(int i=0; i<n; ++i){
            while(st.size() && nums[st.back()] <= nums[i])st.pop_back();
            st.push_back(i);
            while(i-st.front() >= k)st.pop_front();
            maxs.emplace_back(nums[st.front()]);
        }
        for(int i=k-1; i<n; ++i)std::cout << mins[i] << " ";
        std::cout << std::endl;
        for(int i=k-1; i<n; ++i)std::cout << maxs[i] << " ";
        std::cout <<  std::endl;
        return 0;
    }
};
namespace p153{
    const int N = 1024, M = N * N, INF = 0x3f3f3f3f;
    int head[N], to[N], next[N], idx;
    int col[N], nums[N];
    void _add(int f, int t){
        to[++idx] = t;
        next[idx] = head[f];
        head[f]   = idx;
    }
    int _dfs(int x, int c){
        col[x] = c;
        for(int t=head[x]; t; t=next[t]){
            int y = to[t];
            if(col[y] == 0 && !_dfs(y, 3 - c)){
                return 0;
            }else if(col[y] == c){
                return 0;
            }
        }
        return 1;
    }
    int n, x;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        for(int i=1; i<=n; ++i)std::cin >> nums[i];
        for(int i=1; i<=n; ++i){
            int min_ = INF;
            for(int j=n; j>i; --j){
                if(nums[i] < nums[j] && nums[i] > min_){
                    _add(i, j), _add(j, i);
                }
                min_ = std::min(min_, nums[j]);
            }
        }
        for(int i=1; i<=n; ++i){
            if(!col[i] && !_dfs(i, 1)){
                std::cout << 0 << std::endl;
                return 0;
            }
        }
        std::stack<int> s1, s2;
        s1.push(nums[1]);
        int now = 1, case1, case2;
        std::cout << "a ";
        for(int i=2; i<=n; ++i){
            case1 = (s1.size() && s1.top() == now);
            case2 = (s2.size() && s2.top() == now);
            while(case1 || case2){
                if(case1)std::cout << "b ", s1.pop();
                if(case2){
                    if(col[i] == 1)std::cout << "a ", s1.push(nums[i++]);
                    std::cout << "d ", s2.pop();
                }
                ++now;
                case1 = (s1.size() && s1.top() == now);
                case2 = (s2.size() && s2.top() == now);
            }
            if(i > n)break;
            if(col[i] == 1)std::cout << "a ", s1.push(nums[i]);
            if(col[i] == 2)std::cout << "c ", s2.push(nums[i]);
        }
        case1 = (s1.size() && s1.top() == now);
        case2 = (s2.size() && s2.top() == now);
        while(case1 || case2){
            if(case1)std::cout << "b ", s1.pop();
            if(case2)std::cout << "d ", s2.pop();
            ++now;
            case1 = (s1.size() && s1.top() == now);
            case2 = (s2.size() && s2.top() == now);
        }
        return 0;
    }
};
namespace p162{
    int N, M, x;
    std::vector<int> n, m;
    std::priority_queue<int> big;
    std::priority_queue<int, std::vector<int>, std::greater<int>> small;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> M >> N;
        for(int i=0; i<M; ++i){
            std::cin  >> x;
            m.emplace_back(x);
        }
        for(int i=0; i<N; ++i){
            std::cin >> x;
            n.emplace_back(x);
        }
        for(int i=0, j=0; i<M || j<N; ++i){
            if(i<M){
                if(!big.size() && !small.size()){
                    big.push(m[i]);
                }else if(m[i] < big.top()){
                    big.push(m[i]);
                }else{
                    small.push(m[i]);
                }
            }
            while(j<N && i>=M || n[j] == i+1){
                if(big.size() != j+1){
                    while(big.size() < j+1)big.push(small.top()), small.pop();
                    while(big.size() > j+1)small.push(big.top()), big.pop();
                }
                std::cout << big.top() << std::endl;
                ++j;
            }
        }
        return 0;
    }
};
namespace p152{
    int N, M, ans;
    char c;
    std::vector<int> h;
    int _calc(){
       std::vector<int> st;
        int res = 0;
        for(int i=0; i<=M; ++i){
            while(st.size() && h[st.back()] >= h[i]){
                auto cur = st.back();st.pop_back();
                auto l = st.size() ? st.back() : -1;
                res = std::max(res, h[cur] * (i - l - 1));
            }
            st.push_back(i);
        }
        return res;
    };
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> N >> M;
        h.resize(M + 1);
        while(N--){
            for(int i=0; i<M; ++i){
                std::cin >> c;
                h[i] += c=='F' ? 1 : -h[i];
            }
            ans = std::max(ans, _calc());
        }
        std::cout << ans * 3 << std::endl;
        return 0;
    }
};
namespace p151{
    using ll = int;
    using funcalc = std::function<ll(ll, ll)>;
    struct _calc_fun{
        static ll _add(ll a, ll b) {return a + b;};
        static ll _sub(ll a, ll b) {return a - b;};
        static ll _mul(ll a, ll b) {return a * b;};
        static ll _div(ll a, ll b) {return a / b;};
        static ll _pow(ll a, ll b) {
            ll ans = 1;
            while(b>0){
                if(b & 1)ans *= a;
                a *= a;
                b >>= 1;
            }
            return ans;
        };
    };
    std::unordered_map<char, std::pair<int, funcalc>> mp
    {
        {'+', {1, _calc_fun::_add}},
        {'-', {1, _calc_fun::_sub}},
        {'*', {2, _calc_fun::_mul}},
        {'/', {2, _calc_fun::_div}},
        {'^', {3, _calc_fun::_pow}},
    };
    const int N = 1e6 + 12;
    char ex[N],  st[N], str[N];
    int nums[N], op[N];
    bool isn[N];
    ll num, nptr, opptr, stptr;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> (str + 2);
        int len = strlen(str + 2) + 1;
        str[1] = '(', str[++len] = ')';
        for(int i=1,j=1; i<=len; ++i){
            if(str[i] == '-' && str[i-1]=='('){
                ex[j++] = '0';
            }
            ex[j++] = str[i];
        }
        len = strlen(ex+1);
        for(int i=1; i<=len; ++i){
            if(std::isdigit(ex[i])){
                while(std::isdigit(ex[i])) num = num * 10 + ex[i++] - '0';
                op[++opptr] = num;
                isn[opptr]  = 1;
                num = 0;
                --i;
            }else if(ex[i] == '('){
                st[++stptr] = ex[i];
            }else if(ex[i] == ')'){
                while(stptr && st[stptr] != '(')op[++opptr] = st[stptr--];
                stptr -= !!stptr;
            }else{
                while(stptr &&
                        mp[st[stptr]].first >= mp[ex[i]].first){
                    op[++opptr] = st[stptr--];
                }
                st[++stptr] = ex[i];
            }
        }
        ll a, b, i = 1;
        while(i <= opptr){
            if(isn[i]){
                nums[++nptr] = op[i++];
            }else{
                auto [l, _op] = mp[op[i++]];
                b = nums[nptr--], a = nums[nptr--];
                nums[++nptr] = _op(a, b);
            }
        }
        std::cout << nums[nptr] << std::endl;
        return 0;
    }
};
namespace p150{
    std::string str;
    int ans, len;
    std::stack<int> st;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> str;
        len = str.size();
        for(int i=0; i<len; ++i){
            char c = str[i];
            if(st.size()){
                int d = c - str[st.top()];
                if(d==1 || d==2){
                    st.pop();
                }else{
                    st.push(i);
                }
            }else{
                st.push(i);
            }
            if(st.size()){
                ans = std::max(ans, i - st.top());
            }else{
                ans = std::max(ans, i + 1);
            }
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p149{
    using puu64 = std::pair<std::int64_t, std::int64_t>;
    std::int64_t n, k, x, t, ans;
    std::priority_queue<puu64,
                        std::vector<puu64>,
                        std::greater<puu64>> q;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> k;
        for(int i=0; i<n; ++i){
            std::cin >> x;
            q.emplace(x, 0);
        }
        while((q.size()-1) % (k - 1))q.emplace(0, 0);
        while(q.size() >= 1){
            t = 0, x = -1;
            for(int i=0; i<k; ++i){
                auto [v, d] = q.top();q.pop();
                t += v;
                x  = std::max(x, d);
            }
            q.emplace(t, x + 1);
            ans += t;
        }
        std::cout << ans << std::endl;
        std::cout << q.top().second << std::endl;
        return 0;
    }
};
namespace p148{
    const int N = 10024;
    int m, n, new_, ans;
    std::priority_queue<int> q;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> m;
        while(std::cin >> n)q.push(n * -1);
        while(--m){
            new_  = q.top();q.pop();
            new_ += q.top();q.pop();
            ans += new_ * -1;
            q.push(new_);
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p147{
    using ll = long long;
    const int N = 1e5 + 12, INF = 0x3f3f3f3f;
    int n, k, ans;
    ll d[N], del[N], pre[N], next[N];
    struct _cmp{
        bool operator () (const int &a, const int &b){
            return d[a] > d[b];
        }
    };
    std::priority_queue<int, std::vector<int>, _cmp> q;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> k;
        std::cin >> d[1];
        d[0] = INF;
        for(int i=2; i<=n; ++i){
            std::cin >> d[i];
            d[i-1] = d[i] - d[i-1];
        }
        for(int i=1; i<=n; ++i){
            q.push(i);
            pre[i]  = i-1;
            next[i] = i >=n ? 0 : i + 1;
        }
        while(k--){
            int t = q.top();q.pop();
            while(del[t]){
                t = q.top();q.pop();
            }
            ans += d[t];
            del[pre[t]]  = del[next[t]] = 1;
            d[t]         = d[pre[t]] + d[next[t]] - d[t];
            pre[t]       = pre[pre[t]];
            next[t]      = next[next[t]];
            next[pre[t]] = t;
            pre[next[t]] = t;
            q.push(t);
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p146{
    using pii = std::pair<int, int>;
    int t, n, m;
    int a[1024 << 1], b[1024 << 1], c[1024 << 1];
    void _merge(){
        std::priority_queue<pii, std::vector<pii>,
                                 std::greater<pii>> q;
        for(int i=1; i<=n; ++i)q.emplace(a[1] + b[i], 1);
        for(int i=1; i<=n; ++i){
            auto [s, p] = q.top();q.pop();
            c[i] = s;
            q.emplace(s+a[p+1]-a[p], p+1);
        }
        for(int i=1; i<=n; ++i)a[i] = c[i];
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> t;
        std::function<void(void)> _deal = [&](void){
            std::cin >> m >> n;
            for(int i=1; i<=n; ++i){
                std::cin >> a[i];
            }
            std::sort(a+1, a+1+n);
            while(--m){
                for(int i=1; i<=n; ++i)std::cin >> b[i];
                _merge();
            }
            for(int i=1; i<=n; ++i)std::cout << a[i] << " ";
            std::cout << std::endl;
        };
        while(t--)_deal();
        return 0;
    }
};
namespace p146_fuck{
    int t, n, m, k;
    int nums[1024][1024], idx[1024];
    struct _cmp{
        bool operator ()(const int &a, const int &b){
            int difa = nums[a][idx[a]] - nums[a][idx[a] - 1];
            int difb = nums[b][idx[b]] - nums[b][idx[b] - 1];
            return difa == difb  ? nums[a][idx[a]] < nums[b][idx[b]] : difa > difb;
        }
    };
    std::priority_queue<int, std::vector<int>, _cmp> q;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> t;
        std::function<void(void)> _deal = [&](void){
            int sum = 0;
            std::cin >> m >> n;
            k = n;
            for(int i=1; i<=m; ++i){
                for(int j=1; j<=n; ++j){
                    std::cin >> nums[i][j];
                }
                std::sort(nums[i]+1, nums[i] + n + 1);
                sum += nums[i][1];
            }
            for(int i=1; i<=m; ++i)idx[i] = 2;
            while(q.size())q.pop();
            for(int i=1; i<=m; ++i)q.push(i);
            while(k--){
                std::cout << sum << " ";
                if(!q.size())break;
                int i = q.top();q.pop();
                sum += nums[i][idx[i]] - nums[i][idx[i]-1];
                if(++idx[i] <= n)q.push(i);
            }
            std::cout << std::endl;
        };
        while(t--)_deal();
        return 0;
    }
};
namespace p143_pq1{
    const int N = 1e4 + 12;
    int n;
    using pii = std::pair<int, int>;
    std::priority_queue<int> q;
    pii nodes[N];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::function<void(void)> _deal = [&](void){
            for(int i=0; i<n; ++i){
                std::cin >> nodes[i].first >> nodes[i].second;
            }
            std::sort(nodes, nodes + n, [&](auto &a, auto &b){
                return a.second < b.second; });
            for(int i=0; i<n; ++i){
                auto[v, t] = nodes[i];
                if(q.size() == t){
                    if(q.top() * -1 < v){
                        q.pop();
                        q.push(v * -1);
                    }
                }else{
                    q.push(v * -1);
                }
            }
            int ans = 0;
            while(q.size())ans += q.top(),q.pop();
            std::cout << ans * -1 << std::endl;
        };
        while(std::cin >> n)_deal();
        return 0;
    }
};
namespace p143_pq{
    const int N = 1e4 + 12;
    int n;
    using pii = std::pair<int, int>;
    std::priority_queue<int> q;
    pii nodes[N];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::function<void(void)> _deal = [&](void){
            int ans = 0, max_ = -1e8, j = 0;
            while(q.size())q.pop();
            for(int i=0; i<n; ++i){
                std::cin >> nodes[i].first >> nodes[i].second;
                max_ = std::max(max_, nodes[i].second);
            }
            std::sort(nodes, nodes+n, [&](auto &a, auto &b){
                    return a.second > b.second; });
            for(int i=max_; i>=1; --i){
                while(j<n && nodes[j].second >= i){
                    q.push(nodes[j++].first);
                }
                if(q.size())ans += q.top(), q.pop();
            }
            std::cout << ans << std::endl;
        };
        while(std::cin >> n)_deal();
        return 0;
    }
};
namespace p143_uf{
    const int N = 10012;
    using pii = std::pair<int, int>;
    int n;
    int _f[N];
    pii nodes[N];
    int _find(int i){
        return i == _f[i] ? i : _find(_f[i]);
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::function<void(void)> _deal = [&](void){
            int max_ = -1e5, ans = 0, pos;
            for(int i=0; i<n; ++i){
                std::cin >> nodes[i].first >> nodes[i].second;
                nodes[i].first *=  -1;
                max_ = std::max(max_, nodes[i].second);
            }
            std::sort(nodes, nodes+n);
            for(int i=0; i<=max_; ++i)_f[i] = i;
            for(auto &[v, e] : nodes){
                if((pos = _find(e))){
                    ans += v * -1;
                    _f[pos] = pos - 1;
                }
            }
            std::cout << ans << std::endl;
        };
        while(std::cin >> n)_deal();
        return 0;
    }
};
namespace p142_better{
    const int N = 1e6 + 12;
    std::string wd;
    int n, m, code;
    int trie[N][26], cnt[N];
    void _add_trie(){
        int cur = 0;
        for(auto &c : wd){
            if(!trie[cur][c-'a'])trie[cur][c-'a'] = ++code;
            cur = trie[cur][c-'a'];
        }
        ++cnt[cur];
    }
    int _search_trie(){
        int ans = 0, cur = 0;
        for(auto &c : wd){
            if(!trie[cur][c-'a'])break;
            cur  = trie[cur][c-'a'];
            ans += cnt[cur];
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        for(int i=0; i<n; ++i){
            std::cin >> wd;
            _add_trie();
        }
        for(int i=0; i<m; ++i){
            std::cin >> wd;
            std::cout << _search_trie() << std::endl;
        }
        return 0;
    }
};
namespace p142{
    int N, M, code;
    std::string wd;
    struct Trie{
        Trie *next[26];
        int is_end = 0;
    };
    Trie *head = new Trie();
    void _add_trie(){
        Trie *cur = head;
        for(auto &c : wd){
            if(!cur->next[c-'a'])cur->next[c-'a'] = new Trie();
            cur = cur->next[c-'a'];
        }
        ++cur->is_end;
    }
    int _search_trie(){
        int ans = 0;
        Trie *cur = head;
        for(auto &c : wd){
            if(!cur->next[c-'a'])break;
            cur = cur->next[c-'a'];
            ans += cur->is_end;
        }
        return ans;
    }
    void _des_trie(Trie *head){
        for(auto ptr : head->next){
            if(ptr)_des_trie(ptr);
        }
        delete head;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> N >> M;
        for(int i=0; i<N; ++i){
            std::cin >> wd;
            _add_trie();
        }
        for(int i=0; i<M; ++i){
            std::cin >> wd;
            std::cout << _search_trie() << std::endl;
        }
        _des_trie(head);
        return 0;
    }
};
//对于某一字符串 S[1S[1～i]i]，在它众多的next[i]next[i]的“候选项”中，如果存在某一个next[i]next[i]，使得: ii % (i−next[i])==0(i−next[i])==0 ，那么 S[1S[1～ (i−next[i])](i−next[i])] 可以为 S[1S[1 ～ i]i] 的循环元而 i/(i−next[i])i/(i−next[i]) 即是它的循环次
namespace p141{
    int n, k;
    std::string str;
    int next[1000012];
    void _get_next(){
        int i = 1, jump = 0;
        while(i <= n){
            if(str[i] == str[jump]){
                next[++i] = ++jump;
            }else if(!jump){
                next[++i] = 0;
            }else{
                jump = next[jump];
            }
        }
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::function<void(void)> _deal = [&](void){
            _get_next();
            std::cout << "Test case #" << ++k << std::endl;
            for(int i=1; i<=n; ++i){
                if(!next[i] || i%(i - next[i]))continue;
                std::cout << i << " " << i / (i - next[i]) << std::endl;
            }
            std::cout << std::endl;
        };
        while(std::cin >> n && n && std::cin >> str)_deal();
        return 0;
    }
};

namespace p140{
    const int N = 3e5 + 12;
    using ull = unsigned long long;
    ull hash_code = 131, len;
    ull sums[N], _pow[N], sa[N], height[N], cnt[N];
    char str[N];
    ull _get_hash(int l, int r){
        return sums[r] - sums[l] * _pow[r - l];
    }
    std::map<std::pair<int, int>, int> mp;
    int _calc(int idx1, int idx2){
        int ans = 0, p = 1, l = 0;
        if(idx1 > idx2)std::swap(idx1, idx2);
        while(p){
            if( (idx2+l+p <= len) &&
                  (_get_hash(idx1, idx1+l+p) ==
                   _get_hash(idx2, idx2+l+p)) ) {
                l += p;
                p <<= 1;
                ans = std::max(ans, l);
            }else{
                p >>= 1;
            }
        }
        return ans;
    }
    int _bsearch(int idx1, int idx2){
        if(idx1 > idx2)std::swap(idx1, idx2);
        int l = 0, r = len - idx2 + 1;
        while(l < r){
            int m = l + ((r - l) >> 1);
            if(idx2 + m > len ||
                    _get_hash(idx1, idx1+m) !=
                    _get_hash(idx2, idx2+m)){
                r = m;
            }else{
                l = m + 1;
            }
        }
        return l;
    };
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> str;
        len = strlen(str);
        _pow[0] = 1;
        for(int i=1; i<=len; ++i){
            sums[i] = sums[i-1] * hash_code + (str[i-1] - 'a');
            _pow[i] = _pow[i-1] * hash_code;
            sa[i]   = i;
        }
        std::sort(sa, sa + len, [&](int a, int b){
            int l  = _calc(a, b);
            return str[a + l] < str[b + l]; });
        for(int i=1; i<len; ++i){
            height[i] = _calc(sa[i], sa[i-1]);
        }
        for(int i=0; i<len; ++i)std::cout << sa[i] << " ";
        std::cout << std::endl;
        //std::cout << std::endl << 0 << " ";
        //for(int i=1; i<len; ++i)
            //std::cout << std::max(mp[{sa[i], sa[i-1]}], mp[{sa[i-1], sa[i]}])<< " ";
        for(int i=0; i<len; ++i)std::cout << height[i] << " ";
        std::cout << std::endl;
        return 0;
    }
};
namespace p140_fuck{
    using ull = unsigned long long;
    ull hash_code = 131;
    const int N = 8e5;
    ull sa[N], height[N], sums[N], _pow[N], len;
    std::map<std::string, int> mp;
    std::map<int, std::string> is;
    std::string wd;
    int _calc(int i1, int i2){
        int ans = 0, p = 1, l = 0;
        ++i1, ++i2;
        while(p){
            std::cout << i1+l+p-1 << std::endl;
            std::cout << i2+l+p-1 << std::endl;

            std::cout << sums[i1+l+p-1] << "   " << sums[i1-1] * _pow[l+p] << std::endl;
            std::cout << sums[i2+l+p-1] << "   " << sums[i2-1] * _pow[l+p] << std::endl;
            std::cout << ( (sums[i1+l+p-1] - sums[i1-1] * _pow[l+p]) ==
                           (sums[i2+l+p-1] - sums[i2-1] * _pow[l+p])) << std::endl;

                if((i2+l+p-1 <= len) && (sums[i1+l+p-1] - sums[i1-1] * _pow[l+p]) ==
                    (sums[i2+l+p-1] - sums[i2-1] * _pow[l+p])) {
                l += p;
                p <<= 1;
                ans = std::max(ans, l);
            }else{
                p >>= 1;
            }
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> wd;
        len = wd.size();
        _pow[0] = 1;
        for(int i=1; i<=len; ++i){
            sums[i] = sums[i-1] * hash_code + (wd[i-1] - 'a');
            _pow[i] = _pow[i-1] * hash_code;
        }
        for(int i=len-1; i>=0; --i){
            auto str = wd.substr(i);
            mp.emplace(str, i);
            is[i] = str;
        }
        _calc(5, 6);
        return 0;
        int k = 0;
        for(auto &[f, s] : mp)sa[k++] = s;
        for(int i=1; i<=len; ++i){
            int l = std::min(sa[i], sa[i-1]);
            int r = std::max(sa[i], sa[i-1]);
            //height[i] = _calc(l, r);
        }
        for(int i=0; i<len; ++i)std::cout << sa[i] << " ";
        std::cout << std::endl;
        for(int i=0; i<len; ++i)std::cout << height[i] << " ";
        return 0;
    }
};

namespace p139_hash{
    using ull = long long;
    ull hash_code = 131, N = 1e6 + 12, k = 0;
    int len;
    std::string wd;
    std::vector<int> psums(N+2), tsums(N+2), _pow(N+2, 1);
    int _check(int i, int m){
        int ans = 0;
        if((psums[i] - psums[i-m-1] * _pow[m+1] ==
                tsums[i] - tsums[i+m+1] * _pow[m+1])){
            ans = 1;
        }
        if(i+1+m <= len && (psums[i] - psums[i-m-1] * _pow[m+1]==
                tsums[i+1] - tsums[i+1+m+1] * _pow[m+1])){
            ans = 2;
        }
        return ans;

    };
    void _deal(){
        int ans = 0;
        len = wd.size();
        _pow[0] = 1;
        for(int i=1; i<=len; ++i){
            psums[i] = psums[i-1] * hash_code + (wd[i-1] - 'a');
            _pow[i]  = _pow[i-1] * hash_code;
        }
        for(int i=len; i>=1; --i){
            tsums[i] = tsums[i+1] * hash_code + (wd[i-1]-'a');
        }
        for(int i=1; i<=len; ++i){
            int l = 0, r = std::min(i, len - i + 1);
            while(l < r){
                int m = l + ((r - l) >> 1);
                int t = _check(i, m);
                if(!t){
                    r = m;
                }else{
                    ans = std::max((m << 1) + t, ans);
                    l = m + 1;
                }
            }
        }
        std::cout <<"Case " << ++k << ": " << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        while(std::cin >> wd && wd != "END")_deal();
        return 0;
    }
};
namespace p139_manacher{
    int n, k;
    std::string wd, wd1;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::function<void(void)> _init = [&](void){
            int len = wd1.size(), j = 0, i = 0;
            wd.resize(len);
            wd[0] = '#';
            while(i<len)wd[++j] = wd1[i++], wd[++j] = '#';
        };
        std::function<void(void)> _deal = [&](void){
            _init();
            int len = wd.size();
            std::vector<int> p(len+len);
            int M = 0, R = 0, ans = 0;
            for(int i=0; i<len; ++i){
                p[i] = R > i ? std::min(R-i, p[(M << 1) - i]) :1;
                while(i+p[i]<len && i-p[i]>=0 &&
                        wd[i+p[i]] == wd[i-p[i]])++p[i];
                if(i + p[i] > R)R = p[i] + i, M = i;
                ans = std::max(ans, p[i]);
            }
            std::cout <<"Case " << ++k << ": " << ans - 1 << std::endl;
        };
        while(std::cin >> wd1 && wd1 != "END")_deal();
        return 0;
    }
};
namespace p138{
    using ull = unsigned long long;
    ull n, hash_code = 131, l1, r1, l2, r2;
    std::string s;
    int main(int argc,const char *argv[]){
        std::cin >> s >> n;
        int len = s.size();
        std::vector<ull> sums(len+1), _pow(len+1, 1);
        for(int i=1; i<=len; ++i){
            sums[i] = sums[i-1] * hash_code + (s[i-1] - 'a');
            _pow[i] = _pow[i-1] * hash_code;
        }
        while(n--){
            std::cin >> l1 >> r1 >> l2 >> r2;
            if(sums[r1] - sums[l1-1] * _pow[r1-l1+1]==
                    sums[r2] - sums[l2-1] * _pow[r2-l2+1]){
                std::cout << "Yes" << std::endl;
            }else{
                std::cout << "No" << std::endl;
            }
        }
        return 0;
    }
};
namespace p138_fuck{
    std::string s;
    int m, l1, l2, r1, r2;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> s >> m;
        while(m--){
            std::cin >> l1 >> r1 >> l2 >> r2;
            if(s.substr(l1-1, r1-l1+1) != s.substr(l2-1, r2-l2+1)){
                std::cout << "No" << std::endl;
            }else{
                std::cout << "Yes" << std::endl;
            }
        }
        return 0;
    }
};
namespace p137_better{
    int n;
    std::vector<int> sn1(12), sn2(12);
    std::set<std::vector<int>> mp;
    std::vector<int> _get_min(std::vector<int> &sn){
        int i = 0, j = 1, k;
        while(i<6 && j<6){
            for(k=0; k<6 && sn[i+k] == sn[j+k]; ++k);
            if(k==6)break;
            if(sn[i+k] > sn[j+k]){
                i  = i + k + 1;
                i += i == j;
            }else{
                j  = j + k + 1;
                j += i == j;
            }
        }
        int be = std::min(i, j);
        return {begin(sn)+be, begin(sn)+be+6};
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        while(n--){
            for(int i=0; i<6; ++i)std::cin >> sn1[i];
            for(int i=6; i<12;++i)sn1[i] = sn1[i-6];
            sn2 = sn1;
            std::reverse(begin(sn2), end(sn2));
            bool f = !mp.insert(_get_min(sn1)).second |
                    (sn2!=sn1 && (!mp.insert(_get_min(sn2)).second));
            if(f){
                 std::cout << "Twin snowflakes found." << std::endl;
                 return 0;
            }
        }
        std::cout << "No two snowflakes are alike." << std::endl;
        return 0;
    }
};
namespace p137{
    int n;
    std::vector<int> wds(6);
    std::vector<std::string> ok;
    std::unordered_set<std::string> mp;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        for(int i=0; i<n; ++i){
            for(auto &wd : wds) std::cin >> wd;
            auto ix = std::min_element(begin(wds), end(wds));
            for(auto idx=begin(wds); idx!=end(wds); ++idx){
                if(*idx != *ix)continue;
                std::string t1, t2, t3, t4, wd1, wd2;
                for(auto it = begin(wds); it!=idx; ++it)t1 += std::to_string(*it) + '-';
                for(auto it = idx; it!=end(wds); ++it)  t2 += std::to_string(*it) + '-';
                for(auto it = idx; it>=begin(wds); --it)t3 += std::to_string(*it) + '-';
                for(auto it = --end(wds); it!=idx; --it)t4 += std::to_string(*it) + '-';
                wd1 = t2 + t1, wd2 = t3 + t4;
                ok.emplace_back(wd1);
                if(wd1 != wd2)ok.emplace_back(wd2);
            }
            for(auto &wd : ok){
                if(!mp.insert(wd).second){
                    std::cout << "Twin snowflakes found." << std::endl;
                    return 0;
                }
            }
            ok.clear();
        }
        std::cout << "No two snowflakes are alike." << std::endl;
        return 0;
    }
};
namespace p136{
    using ll = long long;
    ll n, x;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::map<ll, int> mp {{INT_MIN, -1}, {INT_MAX, -1}};
        for(int i=0; i<n; ++i){
            std::cin >> x;
            if(i){
                auto itm = mp.lower_bound(x);
                auto itl = itm, itr = itm;
                auto [fm, sm] = *itm;
                auto [fl, sl] = *--itl;
                auto [fr, sr] = itr==--mp.end() ? *itr : *++itr;
                ll a = abs(fm-x), b = abs(fl-x), c = abs(fr-x);
                ll ans = std::min({a, b, c});
                ll idx = ans == b ? sl : (ans == a ? sm : sr);
                std::cout << ans << " " << ++idx << std::endl;
            }
            mp.emplace(x, i);
        }
        return 0;
    }
};
namespace p135{
    using ll = long long;
    ll n, m, ans;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;
        std::vector<int> nums(n+1);
        for(int i=1; i<=n; ++i) std::cin >> nums[i];
        for(int i=1; i<=n; ++i)nums[i] += nums[i-1];
        std::deque<ll> st {0};
        for(int i=1; i<=n; ++i){
            while(st.size() && nums[st.back()] >= nums[i])st.pop_back();
            while(st.size() && i - st.front() > m)st.pop_front();
            ans = std::max<ll>(ans, nums[i] - nums[st.front()]);
            st.push_back(i);
        }
        std::cout << ans << std::endl;
        return 0;
    }
};
