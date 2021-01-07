/*********************************************
*     ------------------------
*     ------------------------
*     file name: test.cpp
*     author   : @ JY
*     date     : 2020--12--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <algorithm>

struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode (int x) : val(x), left(NULL), right(NULL) {}
};
namespace p2{
    TreeNode *buildTree_in_post(std::vector<int> &in, std::vector<int> &post){
        int len = in.size();
        std::unordered_map<int, int> mp;
        for(int i=0; i<len; ++i)mp[in[i]]   = i;
        std::function<TreeNode*(int, int, int, int)> _dfs
            = [&](int il, int ir, int pl, int pr){
                TreeNode *head = NULL;
                if(il>=ir || pl>=pr)return head;
                head = new TreeNode(post[pr - 1]);
                int len = mp[post[pr - 1]] - il;
                head->left  = _dfs(il, il + len, pl, pl + len);
                head->right = _dfs(il + len + 1, ir, pl + len, pr - 1);
                return head;
            };
        return _dfs(0, len, 0, len);
    }
    TreeNode *buildTree_in_pre(std::vector<int> &pre, std::vector<int> &in){
        std::unordered_map<int, int> mp;
        for(int i=in.size()-1; i>=0; --i)mp[in[i]] = i;
        std::function<TreeNode *(int, int, int, int)> _dfs
            = [&](int pl, int pr, int il, int ir){
                TreeNode *head = NULL;
                if(pl >= pr)return head;
                int len = mp[pre[pl]] - il;
                head = new TreeNode(pre[pl]);
                head->left  = _dfs(pl + 1, pl + len + 1, il, il + len);
                head->right = _dfs(pl + len + 1, pr, il + len + 1, ir);
                return head;
            };
        return _dfs(0, in.size(), 0, in.size());
    }
};
namespace p1{
    const int N = 64;
    int n, f = 0;
    int pre[N], post[N];
    std::vector<int> in;
    std::unordered_map<int, int> mp;
    int main(int argc,const char *argv[]){
        std::cin >> n;
        for(int i=0; i<n; ++i)std::cin >> pre[i];
        for(int i=0; i<n; ++i)std::cin >> post[i];
        for(int i=0; i<n; ++i)mp[post[i]] = i;
        std::function<void(int, int, int)> _dfs
            = [&](int root, int l, int r){
                if(l >= r)return;
                if(l == r-1){
                    in.emplace_back(pre[root]);
                    return ;
                }
                int ll = mp[pre[root + 1]];
                f |= ll == r - 2;
                _dfs(root + 1, l, ll + 1);
                in.emplace_back(pre[root]);
                _dfs(root + ll - l + 2, ll + 1, r - 1);
            };
        _dfs(0, 0, n);
        std::cout << (f ? "No" : "Yes") << std::endl;
        for(auto &x : in)std::cout << x << " ";
        std::cout << std::endl;
        return 0;
    }
};
int main(int argc,const char *argv[]){
    std::ios::sync_with_stdio(false);
    int n, ans = 0;
    std::cin >> n;
    std::vector<int> nums(n), dp(n);
    for(auto &x : nums)std::cin >> x;
    for(int ml = 0; ml<n-2; ++ml){
        for(int mr = ml + 1; mr<n-1; ++mr){
            if(nums[ml] <= nums[mr])continue;
            int cntl = 0, cntr = 0;
            for(int l = 0; l<ml; ++l)cntl += nums[l] < nums[mr];
            for(int r = mr + 1; r<n; ++r)cntr += nums[r] > nums[ml];
            ans += cntl * cntr;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
