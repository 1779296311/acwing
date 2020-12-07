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
    int _des_trie(Trie *head){
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
