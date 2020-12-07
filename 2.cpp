/*********************************************
*     ------------------------
*     ------------------------
*     file name: 2.cpp
*     author   : @ JY
*     date     : 2020--11--18
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stdlib.h>

struct TreeNode{
    int val;
    TreeNode *left, *right, *father;
    TreeNode(int v) : val(v), left(NULL), right(NULL), father(NULL) {}
};
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int v) : val(v) , next(NULL){}
};
namespace d13{
    class RDcode{
        std::string serialize(TreeNode *root){
            std::function<std::string (TreeNode *)> _dfs
                = [&](TreeNode *root){
                    if(!root)return std::string("^");
                    auto l = _dfs(root->left);
                    auto r = _dfs(root->right);
                    std::string head = std::to_string(root->val);
                    return head + "_" + l + "_" + r;
                };
            return _dfs(root);
        }
        TreeNode *deserialize(std::string data){
            std::vector<std::string> vals;
            std::stringstream ss;
            std::string t;
            ss << data;
            while(std::getline(ss, t, '_')){
                vals.emplace_back(t);
            }
            int index = 0, len = vals.size();
            std::function<TreeNode*(void)> _dfs = [&](void){
                if(vals[index] == "^"){
                    ++index;
                    return (TreeNode*) 0;
                }
                TreeNode *root = new TreeNode(std::stoi(vals[index++]));
                root->left  = _dfs();
                root->right = _dfs();
                return root;
            };
            return _dfs();
        }
    };
    class Solution{
        public:
            std::vector<std::vector<int>> permutation(std::vector<int>& nums){
                int len = nums.size();
                std::vector<std::vector<int>> res;
                std::vector<int> ans, vi(len);
                std::sort(begin(nums), end(nums));
                std::function<void(void)> _dfs = [&](void){
                    if(ans.size() == len){
                        res.emplace_back(ans);
                        return;
                    }
                    for(int i=0; i<len; ++i){
                        if(i && nums[i]==nums[i-1] && !vi[i-1])continue;
                        if(vi[i])continue;
                        vi[i] = 1;
                        ans.emplace_back(nums[i]);
                        _dfs();
                        ans.pop_back();
                        vi[i] = 0;
                    }
                };
                _dfs();
                return res;
            }
            std::vector<std::vector<int>> printFromTopBottomIII(TreeNode *root){
                if(!root)return {};
                std::vector<std::vector<int>> res;
                std::vector<int> ans;
                std::queue<TreeNode *> q;q.push(root);
                int f = 0;
                while(q.size()){
                    int size = q.size();
                    while(size--){
                        auto t = q.front();q.pop();
                        if(t->left)q.push(t->left);
                        if(t->right)q.push(t->right);
                        ans.emplace_back(t->val);
                    }
                    if(f & 1){
                        res.emplace_back(rbegin(ans), rend(ans));
                    }else{
                        res.emplace_back(begin(ans), end(ans));
                    }
                    ans.clear();
                    f ^= 1;
                }
                return res;
            }
            std::vector<std::vector<int>> printFromTopToBottomII(TreeNode *root){
                if(!root)return {};
                std::vector<std::vector<int>> res;
                std::vector<int> ans;
                std::queue<TreeNode *> q;
                q.push(root);
                while(q.size()){
                    int size = q.size();
                    while(size--){
                        auto t = q.front();q.pop();
                        if(t->left)q.push(t->left);
                        if(t->right)q.push(t->right);
                        ans.emplace_back(t->val);
                    }
                    res.emplace_back(ans);
                    ans.clear();
                }
                return res;
            }
            std::vector<int> printFromTopToBottom(TreeNode *root){
                if(!root)return {};
                std::vector<int> res;
                std::queue<TreeNode *> q;
                q.push(root);
                while(q.size()){
                    int size = q.size();
                    while(size--){
                        auto cur = q.front();q.pop();
                        if(cur->left)q.push(cur->left);
                        if(cur->right)q.push(cur->right);
                        res.emplace_back(cur->val);
                    }
                }
                return res;
            }
            ListNode *entryNodeOfLoop(ListNode *head){
                if(!head || !head->next)return NULL;
                ListNode *slow = head, *fast = head;
                do{
                    slow = slow->next;
                    fast = fast->next->next;
                }while(slow && fast && slow != fast);
                if(!fast)return fast;
                slow = head;
                while(slow != fast){
                    fast = fast->next;
                    slow = slow->next;
                }
                return slow;
            }
            void reOrderArray(std::vector<int> &array){
                std::partition(begin(array), end(array), [&](auto x){return x&1 ;});
            }
            bool isNumber(std::string s){
                int len = s.size(), i = 0, j = len - 1;
                while(i<len && s[i] == ' ')++i;
                if(i==len)return false;
                if(s[i] == 'e' || s[i] == 'E')return false;
                while(j>=0 && s[j]==' ')--j;
                if(i>j)return false;
                if(s[j] == 'e' || s[j] == 'E')return false;
                i += s[i] == '-' || s[i] == '+';
                int point = 0, e = 0, num = 0;
                while(i <= j){
                    if(s[i] == 'e' || s[i] == 'E'){
                        if(!num)return false;
                        e = 1;
                    }else if(s[i] == '+' || s[i] =='-'){
                        if((s[i-1] != 'e' && s[i-1] != 'E')){
                            return false;
                        }
                    }else if(std::isdigit(s[i])){
                        num = 1;
                    }else if(s[i] == '.'){
                        if(point || e)return false;
                        if(!num && i==j)return false;
                        point = 1;
                    }else{
                        return false;
                    }
                    ++i;
                }
                return true;
            }
            bool isMatch2_fuck_fuck_fuck(std::string s, std::string p){
                int len1 = s.size(), len2 = p.size();
                if(!len1 && !len2)return true;
                if(!len2)return false;
                if(!len1 && len2){
                    if(len2&1)return false;
                    for(int i=1; i<len2; i+=2){
                        if(p[i] != '*')return false;
                    }
                    return true;
                }
                std::vector<std::vector<int>> dp(len1, std::vector<int>(len2));
                dp[0][0] = s[0] == p[0] || p[0] == '.';
                if(len2 > 1)dp[0][1] = dp[0][0] && p[1] == '*';
                if(len2 > 1)dp[0][1] = p[1] == '*';
                for(int i=2; i<len2; ++i){
                    dp[0][i] = dp[0][i-1] && (s[0]==p[i] || p[i] == '.');
                    if(!dp[0][i-2])continue;
                    dp[0][i] |= p[i] == '*';
                }
                for(int i=1; i<len1; ++i){
                    for(int j=1; j<len2; ++j){
                        if(s[i] == p[j] || p[j] == '.'){
                            dp[i][j] = dp[i-1][j-1];
                        }else if(p[j] == '*'){
                            dp[i][j] = j > 1 && dp[i][j-2];
                            dp[i][j] |= dp[i-1][j] && (s[i]==p[j-1] || p[j-1] == '.');
                        }
                    }
                }
                return dp[len1-1][len2-1];
            }
            bool isMatch(std::string s, std::string p){
                int len1 = s.size(), len2 = p.size();
                if(!len2)return !len1;
                std::vector<std::vector<int>> dp(len1+1, std::vector<int>(len2+1));
                dp[0][0] = 1;
                for(int i=2; i<=len2; ++i)dp[0][i] = dp[0][i-2] && p[i-1] == '*';
                for(int i=1; i<=len1; ++i){
                    for(int j=1; j<=len2; ++j){
                        if((s[i-1]==p[j-1] || p[j-1] == '.')){
                            dp[i][j] = dp[i-1][j-1];
                        }else if(p[j-1] == '*' && j>1){
                            dp[i][j] = dp[i][j-2];
                            dp[i][j] |= dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.');
                        }
                    }
                }
                return dp[len1][len2];
            }
            int maxProductAfterCutting(int length){
                if(length < 4)return length - 1;
                int res = 1;
                if(length % 3 == 1)res = 4, length -= 4;
                if(length % 3 == 2)res = 2, length -= 2;
                while(length)res *= 3, length -= 3;
                return res;
            }
            int movingCOunt(int threshold, int rows, int cols){
                if(!rows || !cols)return 0;
                std::unordered_set<int> mp;
                int res = 0;
                std::vector<int> _fun {0, 1, 0, -1, 0};
                std::function<void(int, int)> _dfs
                    = [&](int i, int j){
                        if(!mp.insert(i * cols + j).second)return ;
                        if(i%10 + i/10 + j%10 + j/10 > threshold)return;
                        ++res;
                        for(int f=0; f<4; ++f){
                            int i1 = i + _fun[f];
                            int j1 = j + _fun[f + 1];
                            if(i1<0 || j1<0 || i1>=rows || j1>=cols)continue;
                            _dfs(i1, j1);
                        }
                    };
                _dfs(0, 0);
                return res;
            }
            bool hasPath(std::vector<std::vector<char>> &matrix, std::string &str){
                if(!matrix.size() || !matrix[0].size())return false;
                int m = matrix.size(), n = matrix[0].size();
                std::vector<int> _fun  {0, 1, 0, -1, 0};
                std::function<bool(int, int, int)> _dfs
                    = [&](int i, int j, int l){
                        if(matrix[i][j] != str[l])return false;
                        if(l == str.size() - 1)return true;
                        int ori = matrix[i][j];
                        matrix[i][j] = '1';
                        for(int f =0; f<4; ++f){
                            int i1 = i + _fun[f];
                            int j1 = j + _fun[f+1];
                            if(i1<0 || j1<0 || i1>=m || j1>=n) continue;
                            if(_dfs(i1, j1, l+1))return true;
                        }
                        matrix[i][j] = ori;
                        return false;
                    };
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(_dfs(i, j, 0))return true;
                    }
                }
                return false;
            }
            TreeNode *inorderSuccessor(TreeNode *p){
                TreeNode *res = p->right;
                if(res){
                    while(res && res->left)res = res->left;
                    return res;
                }
                res = p;
                while(res && res->father && res->father->right == res)res = res->father;
                return res->father;
            }
            TreeNode *buildTree_be(std::vector<int> &preorder, std::vector<int> &inorder){
                int size = inorder.size();
                std::unordered_map<int, int> mp;
                for(int i=0; i<size; ++i)mp[inorder[i]] = i;
                std::function<TreeNode *(int, int, int, int)> _dfs
                    = [&](int pl, int pr, int il, int ir){
                        if(pl >= pr) return (TreeNode *)NULL;
                        int len = mp[preorder[pl]] - il;
                        TreeNode *root = new TreeNode(preorder[pl]);
                        root->left = _dfs(pl+1, pl+len+1, il, il + len);
                        root->right = _dfs(pl+len+1, pr, il+len+1, ir);
                        return root;
                    };
                return _dfs(0, size, 0, size);
            }
            TreeNode *buildTree_better(std::vector<int> &preorder, std::vector<int> &inorder){
                std::unordered_map<int, int> mp;
                int len = preorder.size(), root = 0;
                for(int i=0; i<len; ++i)mp[inorder[i]] = i;
                std::function<TreeNode *(int, int)> _dfs = [&](int l, int r){
                    TreeNode *head = NULL;
                    if(l==r || root==len)return head;
                    int m = mp[preorder[root]];
                    if(l>m || r<m)return head;
                    head = new TreeNode(preorder[root++]);
                    head->left = _dfs(l, m);
                    head->right = _dfs(m+1, r);
                    return head;
                };
                return _dfs(0, len);
            }
            TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder){
                int len = preorder.size(), root = 0;
                std::function<TreeNode *(int, int)> _dfs
                    = [&](int l, int r){
                        TreeNode *head = NULL;
                        if(root>len || l==r)return head;
                        for(int i=l; i<r; ++i){
                            if(inorder[i] == preorder[root]){
                                head = new TreeNode(preorder[root++]);
                                head->left  = _dfs(l, i);
                                head->right = _dfs(i + 1, r);
                                break;
                            }
                        }
                        return head;
                    };
                return _dfs(0, len);
            }
            std::string replaceSpaces_better(std::string &str){
                int len = str.size(), nlen = len;
                for(auto &c : str)nlen += (c==' ') << 1;
                int i = len, j = nlen;
                str.resize(nlen);
                while(--i>=0){
                    if(str[i] == ' '){
                        str[--j] = '0';
                        str[--j] = '2';
                        str[--j] = '%';
                    }else{
                        str[--j] = str[i];
                    }
                }
                return str;
            }
            std::string replaceSpaces(std::string &str){
                std::string rep {"%20"}, t, res;
                for(auto &c : str){
                    if(c==' '){
                        res += rep;
                    }else{
                        res += c;
                    }
                }
                return res;
            }
            bool searchArray(std::vector<std::vector<int>> &array, int target){
                if(!array.size() || !array[0].size())return false;
                int m = array.size(), n = array[0].size(), i = m-1, j = 0;
                while(i>=0 && j<n){
                    int c = array[i][j];
                    if(c == target)return false;
                    if(c < target){
                        ++j;
                    }else {
                        --i;
                    }
                }
                return false;
            }
            int duplicateInArrayII_better(std::vector<int> &nums){
                int slow = 0, fast = 0;
                while(fast==0 || fast!=slow){
                    fast = nums[nums[fast]];
                    slow = nums[slow];
                }
                fast = 0;
                while(fast != slow){
                    fast = nums[fast];
                    slow = nums[slow];
                }
                return slow;
            }
            int duplicateInArrayII(std::vector<int> &nums){
                int l = 1, r = nums.size() - 1;
                while(l < r){
                    int m = l + ((r - l) >> 1);
                    int cnt = 0;
                    for(auto &x : nums)cnt += x>=l && x<=m;
                    if(cnt > m - l + 1){
                        r = m;
                    }else{
                        l = m + 1;
                    }
                }
                return r;
            }
            int duplicateInArray(std::vector<int> &nums){
                std::unordered_set<int> mp;
                int res = -1, len = nums.size();
                for(auto &x : nums){
                    if(x<0 || x>=len)return -1;
                    if(!mp.insert(x).second){
                        res = x;
                    }
                }
                return res;
            }
    };
    int main(int argc,const char *argv[]){
        ;
        return 0;
    }
};
