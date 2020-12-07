/*********************************************
*     ------------------------
*     ------------------------
*     file name: 3.cpp
*     author   : @ JY
*     date     : 2020--11--20
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stdlib.h>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {};
};
namespace al7{
    int main(int argc,const char *argv[]){
        using ll = long long;
        int A, B, MOD = 9901;
        std::function<ll(ll, ll)> _pow = [&](ll a, ll b){
            ll ans = 1;
            while(b){
                if(b & 1)ans = ans * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }
            return ans;
        };
        std::function<ll(ll, ll)> _sum = [&](ll p,  ll k){
            if(!k)return (ll)1;
            if(k & 1)return (1 + _pow(p, (k/2+1))) * _sum(p, k >> 1) % MOD;
            return (p * _sum(p, k - 1) + 1) % MOD;
        };
        std::cin >> A >> B;
        ll res = 1;
        for(int i=2; i<=A; ++i){
            int cnt = 0;
            while(A % i == 0)++cnt, A /= i;
            if(cnt)res = res * _sum(i, cnt * B) % MOD;
        }
        if(A==0)res = 0;
        std::cout << res << std::endl;
        return 0;
    }
};
namespace al6{
    int main(int argc,const char *argv[]){
        std::function<void()> _deal = [&](void){
            std::vector<std::vector<int>> e(7, std::vector<int>(7)),
                                          e1(7, std::vector<int>(7));
            std::string t;
            int ok = 0, res = 7;
            for(int i=1; i<=5; ++i){
                std::cin >> t;
                for(int j=1; j<=5; ++j){
                    e[i][j] = t[j-1] - '0';
                }
            }
            int all = 1 << 5;
            for(int i=0; i<=all; ++i){
                e1 = e;
                int ans = 0;
                for(int j=1; j<=5; ++j){
                    if(!(i & (1 << (j - 1))))continue;
                    ++ans;
                    e1[1][j]   ^= 1;
                    e1[1][j+1] ^= 1;
                    e1[1][j-1] ^= 1;
                    e1[2][j]   ^= 1;
                }
                for(int j=1; j<=4; ++j){
                    for(int k=1; k<=5; ++k){
                        if(e1[j][k])continue;
                        ++ans;
                        e1[j][k]   ^= 1;
                        e1[j+1][k] ^= 1;
                        e1[j+2][k] ^= 1;
                        e1[j+1][k+1] ^= 1;
                        e1[j+1][k-1] ^= 1;
                    }
                }
                if(ans > 6)continue;
                ok = 1;
                for(int j=1; j<=5; ++j){
                    for(int k=1; k<=5; ++k){
                        if(!e1[j][k]){
                            ok = 0;
                            break;
                        }
                    }
                }
                if(ok)res = std::max(res, ans);
            }
            if(res <= 6){
                std::cout << res << std::endl;
                return;
            }
            std::cout << "-1" << std::endl;
        };
        int n;
        std::cin >> n;
        while(n--)_deal();
        return 0;
    }
};
namespace al5{
    int main(int argc,const char *argv[]){
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> ans;
        std::function<void(int)> _deal = [&](int x){
            std::vector<int> t;
            while(x){
                t.emplace_back(__builtin_ctz(x & (-x)) + 1);
                x &= (x - 1);
            }
            ans.emplace_back(t);
        };
        int all = (1 << n);
        for(int i=0; i<all; ++i){
            if(__builtin_popcount(i) != m)continue;
            _deal(i);
        }
        std::sort(begin(ans), end(ans));
        for(auto &val : ans){
            for(auto &x : val){
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
        return 0;
    }
    int _fuck(int argc,const char *argv[]){
        int n, m;
        std::cin >> n >> m;
        std::vector<int> ans, vi(n+1);
        std::function<void(int k)> _dfs = [&](int k){
            if(ans.size() == m){
                for(auto &x : ans)std::cout << x << " ";
                std::cout<<std::endl;
                return;
            }
            for(int i=k; i<=n; ++i){
                if(vi[i])continue;
                if(ans.size())continue;
                vi[i] = 1;
                ans.emplace_back(i);
                _dfs(i+1);
                ans.pop_back();
                vi[i] = 0;
            }
        };
        _dfs(1);
        return 0;
    }
};
namespace al4{
    int main(int argc,const char *argv[]){
        int n;
        std::cin >> n;
        std::vector<int> ans, vi(n+1);
        std::function<void(void)> _dfs = [&](void){
            for(auto &x : ans)std::cout << x << " ";
            std::cout << std::endl;
            for(int i=1; i<=n; ++i){
                if(vi[i])continue;
                if(ans.size() && ans.back() > i)continue;
                vi[i] = 1;
                ans.push_back(i);
                _dfs();
                ans.pop_back();
                vi[i] = 0;
            }
        };
        _dfs();
        return 0;
    }
};
namespace al3{
    int main(int argc,const char *argv[]){
        int n, INF = 0x3f3f3f3f;
        std::cin >> n;
        int all = (1 << n);
        std::vector<std::vector<int>> dp(all, std::vector<int>(n, INF));
        std::vector<std::vector<int>> e(n, std::vector<int>(n));
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cin >> e[i][j];
            }
        }
        dp[1][0] = 0;
        for(int state=0; state<all; ++state){
            for(int cur=0; cur<n; ++cur){
                if(state & (1 << cur))continue;
                for(int pre=0; pre<n; ++pre){
                    if(!(state & (1 << pre)))continue;
                    dp[state | (1 << cur)][cur] =
                        std::min(dp[state | (1 << cur)][cur], dp[state][pre] + e[pre][cur]);
                }
            }
        }
        std::cout << dp[all - 1][n - 1] << std::endl;
        return 0;
    }
    int kru(int argc,const char *argv[]){
        int n, res = 0, val;
        std::cin >> n;
        std::vector<std::vector<int>> e;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cin >> val;
                e.push_back({i, j, val});
            }
        }
        std::vector<int> _f(n);
        std::iota(begin(_f), end(_f), 0);
        std::function<int(int)> _find = [&](int i){
            return _f[i] == i ? i : _f[i] = _find(_f[i]); };
        std::sort(begin(e), end(e), [&](auto &a, auto &b){
                return a[2] < b[2]; });
        for(auto &x : e){
            int pa = _find(x[0]), pb = _find(x[1]);
            if(pa == pb)continue;
            res += x[2];
            _f[pa] = pb;
            if(!--n)break;
        }
        std::cout << res << std::endl;
        return 0;
    }
    int dij(int argc,const char *argv[]){
        using pii = std::pair<int, int>;
        int n, val, INF = 0x3f3f3f3f;
        std::cin >> n;
        std::vector<pii> es[n];
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cin >> val;
                es[i].emplace_back(val, j);
            }
        }
        std::function<int(void)> _dij = [&](void){
            std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
            std::vector<int> dis(n, INF), vi(n);
            q.emplace(0, 0);
            dis[0] = 0;
            while(q.size()){
                auto [d, cur] = q.top();q.pop();
                if(vi[cur])continue;
                vi[cur]  = 1;
                for(auto &[dd, to] : es[cur]){
                    if(dis[to] > dd + d){
                        dis[to] = dd + d;
                        q.emplace(dis[to], to);
                    }
                }
            }
            return dis[n-1];
        };
        std::cout << _dij() << std::endl;
        return 0;
    }
};
namespace al2{
    int main(int argc,const char *argv[]){
        long long a, b, p, ans = 0;
        std::cin >> a >> b >> p;
        while(b){
            if(b & 1)ans = (ans + a) % p;
            a = a * 2 % p;
            b >>= 1;
        }
        std::cout << ans % p << std::endl;
        return 0;
    }
};
namespace al1{
    int main(int argc,const char *argv[]){
        long long a, b, p, ans = 1;
        std::cin >> a >> b >> p;
        while(b){
            if(b & 1)ans = ans * a % p;
            a = a * a % p;
            b >>= 1;
        }
        std::cout << ans % p << std::endl;
        return 0;
    }
};

class Solution{
    public:
        TreeNode *lowestCommonAncestor_better(TreeNode *root, TreeNode *p, TreeNode *q){
            std::function<TreeNode*(TreeNode *)> _dfs = [&](TreeNode *root) {
                if(!root || root==p || root==q)return root;
                auto l = _dfs(root->left);
                auto r = _dfs(root->right);
                if(l && r)return root;
                return l ? l : r;
            };
            return _dfs(root);
        }
        TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q){
            struct _node{
                bool l, r;
                TreeNode *res;
                _node(int l, int r, TreeNode *ans) :
                    l(l), r(r), res(ans) {}
            };
            std::function<_node(TreeNode *root)> _dfs
                = [&](TreeNode *root){
                    if(!root)return (_node){0, 0, 0};
                    auto left  = _dfs(root->left);
                    auto right = _dfs(root->right);
                    auto findp = left.l || right.l || root==p;
                    auto findq = left.r || right.r || root==q;;
                    auto res = left.res ? left.res : (right.res ? right.res : NULL);
                    if(res==NULL)res = findq&&findp ? root : NULL;
                    return (_node){findp, findq, res};
                };
            return _dfs(root).res;
        }
        int maxDiff(std::vector<int> &nums){
            if(!nums.size())return 0;
            int dp0 = 0, dp1 = -nums[0];
            for(int i=1; i<nums.size(); ++i){
                dp0 = std::max(dp0, dp1 + nums[i]);
                dp1 = std::max(dp1, 0 - nums[i]);
            }
            return dp0;
        }
        bool isContinuous(std::vector<int> numbers){
            if(numbers.size() < 5)return false;
            std::sort(begin(numbers), end(numbers));
            int zero = 0;
            for(int i=0; i<4; ++i){
                if(numbers[i] == 0){
                    ++zero;
                }else{
                    if(numbers[i] == numbers[i+1]){
                        return false;
                    }
                    if((zero-=(numbers[i+1] - numbers[i] - 1)) < 0)return false;
                }
            }
            return true;
        }
        char firstNotRepeating(std::string s){
            std::unordered_map<int, int> mp;
            for(auto &x : s)++mp[x];
            for(auto c : s)if(mp[c]==1)return c;
            return '#';
        }
        std::string printMinNumber(std::vector<int> &nums){
            std::vector<std::string> t;
            for(auto &x : nums)t.emplace_back(std::to_string(x));
            std::sort(begin(t), end(t), [&](auto &a, auto &b){
                    return a + b < b + a; });
            std::string res;
            for(auto &x : t)res += x;
            return res;
        }

        int numOf1Between1AndN_Solution(int n){
            int res = 0, dig = 1, t = 0;
            while(n){
                int m = n % 10;
                n /= 10;
                res += n * dig;
                if(m == 1){
                    res += t + 1;
                }else if(m > 0){
                    res += dig;
                }
                t += m * dig;
                dig *= 10;
            }
            return res;
        }
    public:
        std::string str;
        std::unordered_map<int, int> mp;
        int pos = -1;
        void insert(char ch){
            str += ch;
            ++mp[ch];
            if(pos==-1 && mp[ch]<2){
                pos = str.size() - 1;
                return ;
            }
            if(pos != -1 && ch != str[pos])return;
            for(int i=pos; i<str.size(); ++i){
                if(mp[str[i]] < 2){
                    pos = i;
                    return;
                }
            }
            pos = -1;
        }
        char firstAppearingOnce(){
            if(pos == -1)return '#';
            return str[pos];
        }
};
