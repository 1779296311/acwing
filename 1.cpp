/*********************************************
*     ------------------------
*     ------------------------
*     file name: 1.cpp
*     author   : @ JY
*     date     : 2020--11--17
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include <cmath>
#include <numeric>
#include <functional>
#include <stdlib.h>

namespace p1{

    int main(int argc,const char *argv[]){
        int a, b;
        std::cin >> a >> b;
        std::cout<<a + b<<std::endl;
        return 0;
    }
};
namespace pack9{
    int main(int argc,const char *argv[]){
        int N, V;
        std::cin >> N >> V;
        std::vector<std::vector<int>> dp(N+2, std::vector<int>(V+1));
        std::vector<int> vv(N), ww(N);
        for(int i=0; i<N; ++i)std::cin >> vv[i] >> ww[i];
        for(int i=N-1; i>=0; --i){
            for(int j=0; j<=V; ++j){
                dp[i][j] = dp[i+1][j];
                if(j>=vv[i])dp[i][j] = std::max(dp[i][j], dp[i+1][j-vv[i]] + ww[i]);
            }
        }
        std::vector<int> res;
        for(int i=0; i<N; ++i){
            if(V>=vv[i] && dp[i][V] == dp[i+1][V-vv[i]] + ww[i]){
                res.emplace_back(i+1);
                V -= vv[i];
            }
        }
        for(auto &x : res)std::cout<< x << " ";
        std::cout << std::endl;
        return 0;
    }
};
namespace pack8{
    int main(int argc,const char *argv[]){
        using ll = long long;
        ll N, V, v, w, MOD = 1e9 + 7;
        std::cin >> N >> V;
        std::vector<ll> dp0(V+1), dp1(V+1, 1);
        for(int i=0; i<N; ++i){
            std::cin >> v >> w;
            for(int j=V; j>=v; --j){
                int val = dp0[j-v] + w;
                if(val > dp0[j]){
                    dp0[j] = val;
                    dp1[j] = dp1[j-v];
                }else if(val == dp0[j]){
                    dp1[j] = (dp1[j] + dp1[j-v]) % MOD;
                }
            }
        }
        std::cout<< dp1[V] <<std::endl;
        return 0;
    }
};
namespace packmul7{
    int main(int argc,const char *argv[]){
        int N, V, p, root;
        std::cin >> N >> V;
        std::vector<int> vv(N), ww(N);
        std::vector<std::vector<int>> sons(N);
        for(int i=0; i<N; ++i){
            std::cin >> vv[i] >> ww[i] >> p;
            if(--p < 0){
                root = i;
            }else{
                sons[p].emplace_back(i);
            }
        }
        std::vector<std::vector<int>> dp(N, std::vector<int>(V+1));
        std::function<void(int)> _dfs = [&](int id){
            for(int j=vv[id]; j<=V; ++j)dp[id][j] = ww[id];
            for(auto &son : sons[id]){
                _dfs(son);
                for(int j=V; j>=vv[id]; --j){
                    for(int k=vv[son]; k<=j-vv[id]; ++k){
                        dp[id][j] = std::max(dp[id][j], dp[id][j-k] + dp[son][k]);
                    }
                }
            }
        };
        _dfs(root);
        std::cout << dp[root][V] << std::endl;
        return 0;
    }
}
namespace packmul6{
    int main(int argc,const char *argv[]){
        int N, V, v, w;
        std::cin >> N >> V;
        std::vector<int> dp(V+1), s(N);
        std::vector<std::vector<int>> vv(N);
        std::vector<std::vector<int>> ww(N);
        for(int i=0; i<N; ++i){
            std::cin >> s[i];
            vv[i].resize(s[i]), ww[i].resize(s[i]);
            for(int k=0; k<s[i]; ++k){
                std::cin >> vv[i][k] >> ww[i][k];
            }
        }
        for(int i=0; i<N; ++i){
            for(int j=V; j>=0; --j){
                for(int k=0; k<s[i]; ++k){
                    if(j>=vv[i][k]){
                        dp[j] = std::max(dp[j], dp[j-vv[i][k]] + ww[i][k]);
                    }
                }
            }
        }
        std::cout << dp[V] <<std::endl;
        return 0;
    }
};

namespace packmul5{
    int main(int argc,const char *argv[]){
        int N, V, M, v, m, w;
        std::cin >> N >> V >> M;
        std::vector<std::vector<int>> dp(V+1, std::vector<int>(M+1));
        for(int i=0; i<N; ++i){
            std::cin >> v >> m >> w;
            for(int j=V; j>=v; --j){
                for(int k=M; k>=m; --k){
                    dp[j][k] = std::max(dp[j][k], dp[j-v][k-m] + w);
                }
            }
        }
        std::cout << dp[V][M] <<std::endl;
        return 0;
    }
}

namespace packmul4{
#define _calc(i) dp[(i)] = std::max(dp[(i)], dp[(i) - v] + w);
    struct node{
        int k, val;
        node() : k(0), val(0) {}
        node(int i, int v) : k(i), val(v) {}
    }q[20000];
    int main(int argc,const char *argv[]){
        int N, V, v, w, s;
        std::cin >> N >> V;
        std::vector<int> dp(V+1);
        std::function<void(int,int)> _pack01 = [&](int v, int w){
            for(int j=V; j>=v; --j)_calc(j); };
        std::function<void(int,int)> _packcmp = [&](int v, int w){
            for(int j=v; j<=V; ++j)_calc(j); };
        std::function<void(int, int, int)> _packmul = [&](int v, int w, int s){
            for(int mod=0; mod<v; ++mod){
                int l = 0, r = 0;
                int end = (V - mod) / v;
                for(int k=0; k<=end; ++k){
                    int val = dp[mod + k * v] - k * w;
                    while(l < r && q[r-1].val <= val)--r;
                    q[r++] = {k, val};
                    while(l < r && q[l].k + s < k)++l;
                    dp[mod + k * v] = q[l].val + k * w;
                }
            }
        };
        for(int i=0; i<N; ++i){
            std::cin >> v >> w >> s;
            if(s == -1)_pack01(v, w);
            if(s ==  0)_packcmp(v, w);
            if(s > 0)_packmul(v, w, s);
        }
        std::cout << dp[V] << std::endl;
        return 0;
    }
};
namespace packmul3{
    struct node{
        int k, val;
        node() : k(0), val(0) {}
        node(int i, int v) : k(i), val(v) {}
    };
    int main(int argc,const char *argv[]){
        int N, V, v, w, s;
        std::vector<int> dp(V+1);
        std::vector<node> q(20000);
        std::cin >> N >> V;
        for(int i=0; i<N; ++i){
            std::cin >> v >> w >> s;
            for(int mod=0; mod<v; ++mod){
                int l = 0, r = 0;
                int end = (V - mod) / v;
                for(int k=0; k<=end; ++k){
                    int val = dp[mod + k * v] - k * w;
                    while(l < r && q[r-1].val <= val)--r;
                    q[r++] = {k, val};
                    while(l < r && q[l].k + s < k)++l;
                    dp[mod + k * v]  = q[l].val + k * w;
                }
            }
        }
        std::cout << dp[V] << std::endl;
        return 0;
    }
};
namespace packmul2{
#define _calc(i) dp[(i)] = std::max(dp[(i)], dp[(i) - v] + w);
    int main(int argc,const char *argv[]){
        int N, V, v, w, s;
        std::cin >> N >> V;
        std::vector<int> dp(V+1);
        std::function<void(int,int)> _pack01 = [&](int v, int w){
            for(int j=V; j>=v; --j)_calc(j); };
        std::function<void(int,int)> _packcmp = [&](int v, int w){
            for(int j=v; j<=V; ++j)_calc(j); };
        std::function<void(void)> _deal = [&](void){
            if(v * s > V){
                _packcmp(v, w);
            }else{
                int n = 1;
                while(s > n){
                    _pack01(n * v, n * w);
                    s -= n;
                    n <<= 1;
                }
                if(s)_pack01(s * v, s * w);
            }
        };
        for(int i=0; i<N; ++i){
            std::cin >> v >> w >> s;
            _deal();
        }
        std::cout<< dp[V] << std::endl;
        return 0;
    }
};
namespace packmul1{
    int main(int argc,const char *argv[]){
        int N, V, v, w, s;
        std::cin >> N >> V;
        std::vector<int> dp(V+1);
        std::function<void(int, int)>  _pack01
            = [&](int v, int w){
                for(int j=V; j>=v; --j){
                    dp[j] = std::max(dp[j], dp[j-v] + w);
                }
            };
        std::function<void(int, int)> _packcomp
            = [&](int v, int w){
                for(int j=v; j<=V; ++j){
                    dp[j] = std::max(dp[j], dp[j-v] + w);
                }
            };
        std::function<void(int, int, int)> _deal
            = [&](int v, int w, int s){
                if(v * s > V){
                    _packcomp(v, w);
                }else{
                    int n = 1;
                    while(s > n){
                        _pack01(v * n, w * n);
                        s -= n;
                        n <<= 1;
                    }
                    if(s)_pack01(v * s, w * s);
                }
            };
        for(int i=0; i<N; ++i){
            std::cin >> v >> w >> s;
            _deal(v, w, s);
        }
        std::cout << dp[V] <<std::endl;
        return 0;
    }
};
namespace packcomp{
    int main(int argc,const char *argv[]){
        int N, V, v, w;
        std::cin >> N >> V;
        std::vector<int> dp(V+1);
        for(int i=0; i<N; ++i){
            std::cin >> v >> w;
            for(int j=v; j<=V; ++j){
                dp[j] = std::max(dp[j], dp[j-v] + w);
            }
        }
        std::cout << dp[V] <<std::endl;
        return 0;
    }
};

namespace pack01{
    int main_better(int argc,const char *argv[]){
        int N, V, v, w;
        std::cin >> N >> V;
        std::vector<int> dp(V+1);
        for(int i=0; i<N; ++i){
            std::cin >> v >> w;
            for(int j=V; j>=v; --j){
                dp[j] = std::max(dp[j], dp[j-v] + w);
            }
        }
        std::cout << dp[V] <<std::endl;
        return 0;
    }
    int pack01(int V, std::vector<std::vector<int>> vw){
        std::vector<int> dp(V+1);
        int len = vw.size();
        for(int i=0; i<len; ++i){
            for(int j=V; j>=vw[i][0]; --j){
                dp[j] = std::max(dp[j], dp[j-vw[i][0]] + vw[i][1]);
            }
        }
        return dp[V];
    }
    int main(int argc,const char *argv[]){
        int N, V;
        std::cin >> N >> V;
        std::vector<std::vector<int>> vw(N, std::vector<int>(2));
        for(int i=0; i<N; ++i){
            std::cin >> vw[i][0] >> vw[i][1];
        }
        std::cout << pack01(V, vw) << std::endl;
        return 0;
    }
};

