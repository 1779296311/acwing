/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_bit.cpp
*     author   : @ JY
*     date     : 2020--11--30
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <stdlib.h>

namespace p998{
int n, m;
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::vector<int> opx(n);
    std::vector<std::string> opp(n);
    for(int i=0; i<n; ++i)std::cin >> opp[i] >> opx[i];
    int val = 0, ans = 0;
    std::function<int(int, int)> _calc = [&](int bit, int x){
        for(int i=0; i<n; ++i){
            int t = opx[i] >> bit & 1;
            if(opp[i][0] == 'A'){
                x &= t;
            }else if(opp[i][0] == 'O'){
                x |= t;
            }else{
                x ^= t;
            }
        }
        return x;
    };
    for(int i=29; i>=0; --i){
        int zero = _calc(i, 0);
        int one  = _calc(i, 1);
        if(val + (1 << i)<=m && one > zero){
            val |= 1 << i;
            ans |= one <<  i;
        }else{
            ans |= zero << i;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
};

