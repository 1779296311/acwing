/*********************************************
*     ------------------------
*     ------------------------
*     file name: 8.cpp
*     author   : @ JY
*     date     : 2020--11--28
**********************************************/

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <climits>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <stack>
#include <stdlib.h>

namespace p134{
    using ll = long long;
    int n;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n;
        std::vector<ll> nums(n), mp(n);
        std::iota(begin(mp), end(mp), 0);
        for(int i=0; i<n; ++i)std::cin >> nums[i];
        std::sort(begin(mp), end(mp), [&](auto &a, auto &b){
            return nums[a] == nums[b] ? a < b : nums[a] < nums[b]; });
        ll f = 1, ans = 1, i = 0, pre = INT_MAX;
        while(i < n){
            int j = i;
            while(++j<n && nums[mp[i]] == nums[mp[j]]);
            ll mi = mp[i], ma = mp[j-1];
            f ? pre = pre > ma ? mi : (f=0, ma)
              : pre = pre < mi ? ma : (++ans, f=1, mi);
            //if(f){
                //pre = pre > ma ? mi : (f=0, ma);
            //}else{
                //pre = pre < mi ? ma : (++ans, f=1, mi);
            //}
            i = j;
        }
        std::cout <<ans << std::endl;
        return 0;
    }
};
namespace p133{
    using ll  = long long;
    using pll = std::vector<ll, ll>;
    ll l;
    int n, m, add, u, v, t;
    std::queue<ll> ql, qm, qr;
    int _calc(int t){
        ll ans, a = -1, b = -1, c = -1;
        if(ql.size()) a = ql.front() + add * t;
        if(qm.size()) b = qm.front() + add * t;
        if(qr.size()) c = qr.front() + add * t;
        ans = std::max({a, b, c});
        if(ans == a){
            ql.pop();
        }else if(ans == b){
            qm.pop();
        }else{
            qr.pop();
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m >> add >> u >> v >> t;
        std::vector<int> bu(n);
        for(auto &b : bu)std::cin >> b;
        std::sort(begin(bu), end(bu), [&](int &a, int &b){return a > b;});
        for(auto &b : bu)qm.push(b);
        for(int i=1; i<=m; ++i){
            ll len = _calc(i - 1);
            if(!(i % t))std::cout << len << " ";
            ql.push(len*u/v - i*add);
            qr.push(len - len*u/v - i*add);
        }
        std::cout << std::endl;
        for(int i=1; i<=(n+m); ++i){
            ll len = _calc(m);
            if(!(i % t))std::cout << len << " ";
        }
        std::cout << std::endl;
        return 0;
    }
};

namespace p132_1{
    int n, t, code, k;
    std::string p;
    int main(int argc,const char *argv[]){
        std::function<void(void)> _deal = [&](void){
            std::unordered_map<int, int> mp;
            std::vector<std::queue<int>> q(t+1, std::queue<int>());
            for(int i=1; i<=t; ++i){
                std::cin >> n;
                for(int j=1; j<=n; ++j){
                    std::cin >> code;
                    mp[code] = i;
                }
            }
            std::cout << "Scenario #" << ++k << std::endl;
            while(std::cin >> p && p[0] !='S'){
                if(p[0] == 'E'){
                    std::cin >> code;
                    if(!q[mp[code]].size())q[0].push(mp[code]);
                    q[mp[code]].push(code);
                }else{
                    std::cout << q[q[0].front()].front() << std::endl;
                    q[q[0].front()].pop();
                    if(!q[q[0].front()].size())q[0].pop();
                }
            }
            std::cout << std::endl;
        };
        while(std::cin >> t && t)_deal();
        return 0;
    }
};
namespace p132{
int t, n, code, k;
std::string p;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::function<void(void)> _deal = [&](void){
        std::unordered_map<int, int> mp;
        std::queue<std::deque<int>*> qq;
        std::queue<int> ordermp;
        std::unordered_map<int, std::deque<int>> q;
        std::vector<int> vi(t+1);
        for(int i=1; i<=t; ++i){
            std::cin >> n;
            for(int j=1; j<=n; ++j){
                std::cin >> code;
                mp[code] = i;
            }
        }
        std::cout << "Scenario #" << ++k << std::endl;
        std::cin >> p;
        while(p != "STOP"){
            if(p == "ENQUEUE"){
                std::cin >> code;
                if(!vi[mp[code]]){
                    vi[mp[code]] = 1;
                    qq.push(&q[mp[code]]);
                    ordermp.push(mp[code]);
                }
                q[mp[code]].push_back(code);
            }else if(p == "DEQUEUE"){
                auto dq = qq.front();
                std::cout << dq->front() << std::endl;
                dq->pop_front();
                if(!dq->size()){
                    qq.pop();
                    vi[ordermp.front()] = 0;
                    ordermp.pop();
                }
            }
            std::cin >> p;
        }
        std::cout << std::endl;
        std::cin >> t;
    };
    std::cin >> t;
    while(t)_deal();
    return 0;
}
};
namespace p131{
    using ll = long long;
    int n;
    int main(int argc,const char *argv[]){
        std::function<void(void)> _deal = [&](void){
            std::vector<ll> ra(n), st;
            ll ans = 0;
            for(auto &r : ra)std::cin >> r;
            ra.emplace_back(0);
            for(int i=0; i<=n; ++i){
                while(st.size() && ra[st.back()] >= ra[i]){
                    ll m = st.back();
                    st.pop_back();
                    ll l = st.size() ? st.back() : -1;
                    ans = std::max<ll>(ans, ra[m] * (i - l - 1));
                }
                st.push_back(i);
            }
            std::cout << ans << std::endl;
            std::cin >> n;
        };
        std::cin >> n;
        while(n)_deal();
        return 0;
    }
};
//197. 阶乘分解  
namespace p130{
    using ll = long long;
    const int N = 1e6 + 12, MOD = 1e8;
    int cnt, n;
    int p[N], vi[N], sum[N];
void _ispri(int n){
    for(int i=2; i<=n; ++i){
        if(!vi[i])p[cnt++] = i;
        for(int j=0; p[j]<=n/i; ++j){
            vi[p[j] * i] = 1;
            if(i % p[j] == 0)break;
        }
    }
}
ll _calc(int n, int p) {
    ll ans = 0;
    while(n)ans += n/p, n/=p;
    return ans;
}
std::vector<ll> _mul(std::vector<ll> a, int b){
    int t = 0;
    std::vector<ll> ans;
    for(auto &dig : a){
        t += dig * b;
        ans.emplace_back(t % MOD);
        t /= MOD;
    }
    while(t)ans.emplace_back(t % MOD), t /= MOD;
    return ans;
}
std::vector<ll> _div(std::vector<ll> a, int b){
    std::vector<ll> ans;
    ll t = 0;
    for(int i=a.size()-1; i>=0; --i){
        t = t * 10 + a[i];
        ans.emplace_back(t / b);
        t %= b;
    }
    reverse(begin(ans), end(ans));
    while(ans.size()>1 && !ans.back())ans.pop_back();
    return ans;
}
int main(int argc,const char *argv[]){
    int a, b, c;
    std::cin >> n;
    a = n << 1, b = n, c = n + 1;
    _ispri(a);
    for(int i=0; i<cnt; ++i){
        sum[i] = _calc(a, p[i]) - _calc(b, p[i]) * 2;
    }
    for(int i=0; i<cnt && p[i] <= c; ++i){
        int k = 0;
        while(c % p[i] == 0){
            c /= p[i];
            ++k;
        }
        sum[i] -= k;
    }
    std::vector<ll> ans(1, 1);
    for(int i=0; i<cnt ; ++i){
        while(sum[i]--)ans = _mul(ans, p[i]);
    }
    printf("%lld", ans.back());
    for(int i=ans.size()-2; i>=0; --i)printf("%08lld", ans[i]);
    return 0;
}

};
namespace p197{
    const int N = 1e6 + 12;
    using ll = long long;
    int n;
    ll vi[N], p[N];
    void _ispri(int pn){
        for(int i=2; i<=pn; ++i){
            if(vi[i])continue;
            p[++p[0]] = i;
            for(ll j=i*2; j<=pn; j += i)vi[j] = 1;
        }
    }
    ll _power(ll a, ll b){
        ll ans = 1;
        while(b){
            if(b & 1)ans = ans * a;
            a = a * a;
            b >>= 1;
        }
        return ans;
    }
    ll _calc(int n, int p){
        int ans = 0;
        while(n){
            ans += n / p;
            n /= p;
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        std::cin >> n;
        _ispri(n);
        for(int i=1; i<=p[0]; ++i){
            std::cout << p[i] << " " << _calc(n, p[i]) << std::endl;
        }
        return 0;
    }
};
namespace p889{
//2、满足条件的01序列 给定n个0和n个1，它们将按照某种顺序排成长度为2n的序列，求它们能排列成的所有序列中，能够满足任意前缀序列中0的个数都不少于1的个数的序列有多少个。 
    using ll = long long;
    ll n, MOD = 1e9 + 7;
    ll _power(ll a, ll b){
        ll ans = 1;
        while(b){
            if(b & 1)ans = ans * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return ans;
    }
    int main(int argc,const char *argv[]){
        std::cin >> n;
        int l = n, r = n * 2;
        ll ans = 1;
        for(int i=r; i>r-l; --i)ans = ans * i % MOD;
        for(int i=1; i<=l; ++i)ans = ans * _power(i, MOD - 2);
        ans = ans * _power(n+1, MOD - 2);
        return 0;
    }
};
namespace p130_fuck{
    using ll = long long;
    ll n, ans;
    int main(int argc,const char *argv[]){
        std::cin >> n;
        std::function<void(int, int)> _dfs = [&](int t, int c){
            if(c > n)return;
            if(!t && c==n)++ans;
            if(t) _dfs(t - 1, c);
            _dfs(++t, ++c);
        };
        _dfs(0, 0);
        std::cout << ans << std::endl;
        return 0;
    }
};
namespace p129{
    std::vector<int> ans, st(64);
    int main(int argc,const char *argv[]){
        int n, cnt = 0;
        std::function<void(int, int)> _dfs = [&](int t, int c){
            if(cnt >= 20 || c > n)return;
            if(!t && c == n){
                for(auto &x : ans)std::cout << x;
                std::cout << std::endl;
                ++cnt;
                return;
            }
            if(t){
                int x = st[t];
                ans.emplace_back(x);
                _dfs(t - 1, c);
                ans.pop_back();
                st[t] = x;
            }
            st[++t] = ++c;
            _dfs(t, c);
        };
        std::cin >> n;
        _dfs(0, 0);
        return 0;
    }
};
namespace p128{
int Q, x;
char p;
const int N = 1e6 + 12;
int sums[N], ans[N];
std::stack<int> l, r;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> Q;
    ans[0] = -1e6;
    while(Q--){
        std::cin >> p;
        switch(p){
            case 'L':
                if(l.size())r.push(l.top());l.pop();
                break;
            case 'R':
                if(r.size()){
                    l.push(r.top());r.pop();
                    sums[l.size()] = sums[l.size()-1] + l.top();
                    ans[l.size()]  = std::max(ans[l.size()-1], sums[l.size()]);
                }
                break;
            case 'D':
                if(l.size())l.pop();
                break;
            case 'Q':
                std::cin >> x;
                std::cout << ans[x] << std::endl;
                break;
            case 'I':
                std::cin >> x;
                l.push(x);
                sums[l.size()] = sums[l.size()-1] + x;
                ans[l.size()]  = std::max(ans[l.size()-1], sums[l.size()]);
                break;
        }
    }
    return 0;
}
};
namespace p128_fuck{
int Q, ptr;
std::string p;
std::vector<int> nums;
std::vector<std::string> ps;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> Q;
    while(std::cin >> p)ps.emplace_back(p);
    for(int i=0; i<ps.size(); ++i){
        if(ps[i] == "R"){
            ptr += nums.size() != ptr;
        }else if(ps[i] == "L"){
            ptr -= ptr > 0;
        }else if(ps[i] == "D"){
            if(ptr) nums.erase(begin(nums)+ --ptr);
        }else if(ps[i] == "I"){
            nums.insert(begin(nums) + ptr++, std::stoi(ps[++i]));
        }else{
            int idx = std::stoi(ps[++i]);
            int sum = 0, ans = -1e5;
            for(int i=0; i<=idx; ++i){
                sum += nums[i];
                ans = std::max(ans, sum);
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}
};
