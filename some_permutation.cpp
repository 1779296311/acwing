/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_permutation.cpp
*     author   : @ JY
*     date     : 2020--11--30
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <cmath>
#include <stdlib.h>

namespace p432{
    int n;
    int main(int argc,const char *argv[]){
        std::cin >> n;
        std::function<std::vector<int>(std::vector<int>&a, std::vector<int> &b)> _add
            = [&](std::vector<int>&a, std::vector<int> &b){
                std::vector<int> ans;
                int t = 0, len1 = a.size(), len2 = b.size();
                for(int i=0; i<len1 || i<len2 || t; ++i){
                    if(i < len1)t += a[i];
                    if(i < len2)t += b[i];
                    ans.push_back(t % 10);
                    t /= 10;
                }
                return ans;
        };
        std::vector<int> ans(1, 2), two(1, 2);
        for(int i=2; i<=n; ++i){
            ans = _add(ans, ans);
            ans = _add(ans, two);
        }
        for(int i=ans.size()-1; i>=0; --i)std::cout << ans[i] << " ";
        std::cout << std::endl;
        return 0;
    }
};
namespace p{
    int n, m;
    int st[int (1e5)], top, addr;
    std::vector<int> nums;
    void call(int x, int ret_addr){
        int base = top;
        st[++top] = x;
        st[++top] = ret_addr;
        st[++top] = base;
    }
    int ret(){
        int ret_addr = st[top - 1];
        top = st[top];
        return ret_addr;
    }
    int main(int argc,const char *argv[]){
        std::cin >> n >>m;
        call(1, 0);
        while(top){
            int x = st[top - 2];
            switch(addr){
                case 0:
                    if(nums.size() > m || nums.size() + (m-x+1) < m){
                        addr = ret();
                        break;
                    }
                    if(x == m + 1){
                        for(auto &x : nums)std::cout << x << " ";
                        std::cout << std::endl;
                        addr = ret();
                    }
                    nums.push_back(x);
                    call(x+1,1);
                    addr = 0;
                    break;
                case 1:
                    nums.pop_back();
                    call(x+1, 2);
                    addr = 0;
                    break;
                case 2:
                    addr = ret();
                    break;
            }
        }
        return 0;
    }
};
