/*********************************************
*     ------------------------
*     ------------------------
*     file name: 5.cpp
*     author   : @ JY
*     date     : 2020--11--25
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <cstring>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <stdlib.h>

namespace p109_mege{
using ll = long long;
ll K, N, M, T;
int nums[500002], t[500002], tmp[500002];
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::function<bool(ll, ll, ll)> _check = [&](ll start, ll pre, ll end){
        ll i = pre - 1, ans = 0, j, k;
        while(++i < end)t[i] = nums[i];
        std::sort(t + pre, t + end);
        k = 0, i = start, j = pre;
        while(i<pre && j<end){
            tmp[k++] = t[i] > t[j] ? t[j++] : t[i++];
        }
        while(i<pre)tmp[k++] = t[i++];
        while(j<end)tmp[k++] = t[j++];
        i = 0;
        while(i<k && i<M)ans += pow(tmp[i++] - tmp[--k], 2);
        return ans <= T;
    };
    std::function<void(void)> _deal = [&](void){
        std::cin >> N >> M >> T;
        for(int i=0; i<N; ++i)std::cin >> nums[i];
        ll start = 0, end = 0, ans = 0, len = 0;
        while(end < N){
            len = 1;
            while(len){
                if(end + len <= N &&
                        _check(start, end, end + len)){
                    end += len;
                    len <<= 1;
                    for(int i=start; i<end; ++i)t[i] = tmp[i-start];
                }else{
                    len >>= 1;
                }
            }
            start = end;
            ++ans;
        }
        std::cout << ans << std::endl;
    };
    std::cin >> K;
    while(K--)_deal();
    return 0;
}
};
namespace p109{
using ll = long long;
ll K, N, M, T;
int nums[500002], t[500002];
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::function<bool(ll, ll)> _check = [&](ll l, ll r){
        ll k = 0, i = l, ans = 0, j = 0;
        while(i<r)t[k++] = nums[i++];
        std::sort(t, t + k);
        while(j<M && j<k)ans += pow(t[j++] - t[--k], 2);
        return ans <= T;
    };
    std::function<void(void)> _deal = [&](void){
        std::cin >> N >> M >> T;
        for(int i=0; i<N; ++i)std::cin >> nums[i];
        ll start = 0, end = 0, len = 0, ans = 0;
        while(end < N){
            len = 1;
            while(len){
                if(end + len <= N &&
                        _check(start, end + len)){
                    end += len;
                    len <<= 1;
                }else{
                    len >>= 1;
                }
            }
            start = end;
            ++ans;
        }
        std::cout << ans << std::endl;
    };
    std::cin >> K;
    while(K--)_deal();
    return 0;
}
};
namespace p109_fuck{
int K, N, M, T;
int nums[500002], t[500002];
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> K;
    std::function<bool(int, int)> _check = [&](int l, int r){
        int k = 0;
        for(int i=l; i<=r; ++i)t[k++] = nums[i];
        std::sort(t, t + k);
        int ans = 0, i = 0;
        while(i<M && i<k){
            ans += std::pow((t[i++] - t[--k]), 2);
        }
        return ans > T;
    };
    std::function<void(void)> _deal = [&](void){
        std::cin >> N >> M >> T;
        for(int i=0; i<N; ++i)std::cin >> nums[i];
        int ans = 0, start = 0;
        while(start < N){
            int l = start, r = N;
            while(l < r){
                int m = l + ((r - l) >> 1);
                if(_check(start, m)){
                    r = m;
                }else{
                    l = m + 1;
                }
            }
            start = r;
            ++ans;
        }
        std::cout << ans << std::endl;
    };
    while(K--)_deal();
    return 0;
}
};

namespace p108{
using ll = long long;
const int N = 510;
int n, x, t[N*N], b[N*N], c[N*N];
ll _merge(int *nums, int l, int r){
    if(l >= r)return 0;
    int m = l + ((r - l) >> 1);
    ll ans = 0;
    ans += _merge(nums, l, m);
    ans += _merge(nums, m + 1, r);
    int li = l, ri = m + 1;
    for(int i=l; i<=r; ++i){
        if(ri>r || (li<=m && nums[li]<nums[ri])){
            t[i] = nums[li++];
        }else{
            ans += m - li + 1;
            t[i] = nums[ri++];
        }
    }
    for(int i=l; i<=r; ++i)nums[i] = t[i];
    return ans;
}
    int main(int argc,const char *argv[]){
        std::function<void(void)> _deal = [&](void){
            for(int i=0, j=0; i<n * n; ++i){
                std::cin >> x;
                if(x == 0)continue;
                b[j++] = x;
            }
            for(int i=0, j=0; i<n * n; ++i){
                std::cin >> x;
                if(x == 0)continue;
                c[j++] = x;
            }
            int cnt1 = _merge(b, 0, n * n - 1);
            int cnt2 = _merge(c, 0, n * n - 1);
            if((cnt1&1) == (cnt2&1)){
                std::cout << "TAK" << std::endl;
            }else{
                std::cout << "NIE" << std::endl;
            }
        };
        while(std::cin >> n)_deal();
        return 0;
    }
};
namespace p107{
using ll = long long;
const int N = 500002;
ll tree[N],nums[N], mp[N];
int n;
void _update(int x, int v){
    for(; x<N; x+=x&-x)tree[x] += v;
}
int _query(int x){
    ll ans = 0;
    for(; x; x-=x&-x)ans += tree[x];
    return ans;
}
int main(int argc,const char *argv[]){
    std::function<void(void)> _deal = [&](void){
        for(int i=1; i<=n; ++i){
            std::cin >> nums[i];
            mp[i] = nums[i];
        }
        std::sort(mp+1, mp+n+1);
        ll ans = 0;
        for(int i=n; i>0; --i){
            int idx = std::lower_bound(mp+1,mp+n+1, nums[i]) - mp;
            ans += _query(idx - 1);
            _update(idx, 1);
        }
        std::cout << ans << std::endl;
        std::cin >> n;
        std::memset(tree, 0, sizeof(tree));
    };
    std::cin >> n;
    while(n)_deal();
    return 0;
}

};
namespace p106{
    int main(int argc,const char *argv[]){
        int p, n, m, x;
        std::function<void(void)> _deal
            = [&](void){
                std::priority_queue<int> bigq;
                std::priority_queue<int, std::vector<int>, std::greater<int>> smallq;
                std::vector<int> ans;
                std::cin >> n >> m;
                int all = 0;
                while(m--){
                    ++all;
                    std::cin >> x;
                    int f = bigq.size() > smallq.size();
                    if(!bigq.size() || x <= bigq.top()){
                        bigq.push(x);
                    }else{
                        smallq.push(x);
                        f -= 1;
                    }
                    if(f > 0)smallq.push(bigq.top()), bigq.pop();
                    if(f < 0)bigq.push(smallq.top()), smallq.pop();
                    if(all & 1)ans.emplace_back(bigq.top());
                }
                std::cout << n << " " << ans.size() << std::endl;
                for(int i=0; i<ans.size(); ++i){
                    std::cout << ans[i] << ((i+1)%10 || (i==ans.size()-1) ? " " : "\n");
                }
                std::cout << std::endl;
            };
        std::cin >> p;
        while(p--)_deal();
        return 0;
    }
};
namespace p105{
using ll = long long;
int N, M, T, x, y;
ll row[100100], col[100100];
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        std::cin >> N >> M >> T;
        for(int i=1; i<=T; ++i){
            std::cin >> x >> y;
            ++row[x], ++col[y];
        }
        row[0] = std::accumulate(row, row + N + 1, 0);
        col[0] = std::accumulate(col, col + M + 1, 0);
        std::function<ll(ll *, int)> _calc = [&](ll *nums, int len){
            for(int i=1; i<=len; ++i)nums[i] -= nums[0] / len;
            for(int i=2; i<=len; ++i)nums[i] += nums[i-1];
            std::sort(nums+1, nums+len+1);
            ll ans = 0;
            for(int i=1; i<=len; ++i){
                ans += abs(nums[i] - nums[(len + 1) >> 1]);
            }
            return ans;
        };
        if(row[0] % N == 0 && col[0] % M == 0){
            std::cout << "both " << _calc(row, N) + _calc(col, M);
        }else if(row[0] % N == 0){
            std::cout << "row " << _calc(row, N);
        }else if(col[0] % M == 0){
            std::cout << "column " << _calc(col, M);
        }else{
            std::cout << "impossible" << std::endl;
        }
        return 0;
    }
};
namespace p104{
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int N;
        std::cin >> N;
        std::vector<int> nums(N);
        for(auto &x : nums)std::cin >> x;
        std::nth_element(begin(nums), begin(nums) + (N >> 1), end(nums));
        std::cout << 
        std::accumulate(begin(nums), end(nums), 0, [&](int ans, auto &a){
                return ans + abs(a - nums[N>>1]); }) 
        << std::endl;
        return 0;
    }
};

namespace p103{
int code, n, m;
struct _node{
    int i, a, b;
    bool operator < (const _node &other) {
        return a == other.a ?
               b > other.b  :
               a > other.a  ;
    }
}mv[200002];
std::unordered_map<int, int> mp2;
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int x;
        std::cin >> n;
        for(int i=0; i<n; ++i){
            std::cin >> x;
            ++mp2[x];
        }
        std::cin >> m;
        for(int i=0; i<m; ++i){
            std::cin >> x;
            mv[i].i = i;
            mv[i].a = mp2[x];
        }
        for(int i=0; i<m; ++i){
            std::cin >> x;
            mv[i].b = mp2[x];
        }
        std::sort(mv, mv + m);
        std::cout << mv[0].i + 1 << std::endl;
        return 0;
    }
};
namespace p103_fuck{
    struct node{
        int i, a, b;
        node(int i, int a, int b) : i(i), a(a), b(b) {}
    };
    int main(int argc,const char *argv[]){
        std::ios::sync_with_stdio(false);
        int n, m, x;
        std::cin >> n;
        std::map<int, int> stor, mp1, mp2;
        for(int i=0; i<n; ++i){
            std::cin >> x;
            ++stor[x];
        }
        std::cin >> m;
        for(int i=0; i<m; ++i){
            std::cin >> x;
            mp1.emplace(i, x);
        }
        for(int i=0; i<m; ++i){
            std::cin >> x;
            mp2.emplace(i, x);
        }
        std::vector<node> mv;
        for(int i=0; i<m; ++i)mv.emplace_back(i, mp1[i], mp2[i]);
        std::sort(begin(mv), end(mv), [&](auto &a, auto &b){
                return stor[a.a] == stor[b.a] ?
                       stor[a.b] > stor[b.b] :
                       stor[a.a] > stor[b.a];
                });
        std::cout << mv[0].i << std::endl;
        return 0;
    }
};
namespace p102{
    int main(int argc,const char *argv[]){
        int N, F;
        std::ios::sync_with_stdio(false);
        std::cin >> N >> F;
        std::vector<double> cows(N), sums(N);
        for(auto &x : cows)std::cin >> x;
        std::function<bool(double)> _check = [&](double m){
            sums.clear();
            sums[0] = cows[0] - m;
            for(int i=1; i<N; ++i)sums[i] = sums[i-1] + (cows[i] - m);
            double min_ = 0;
            for(int i=0, j=F-1; j<N; ++j, ++i){
                if(sums[j] - min_ >= 0)return true;
                min_ = std::min(min_, sums[i]);
            }
            return false;
        };
        double l = 1, r = 2000;
        while(r-l > 1e-5){
            double m = (l + r) / 2.0;
            if(_check(m)){
                l = m;
            }else{
                r = m;
            }
        }
        std::cout << (int)(r*1000) << std::endl;
        return 0;
    }
};
