/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        int level=true; //level=true for even indexed levels
        q.push(root);
        while(!q.empty()){
            int sz=q.size();
            int ma=INT_MAX;
            int mi=INT_MIN;
            for(int i=0;i<sz;i++){
                if(level){
                    TreeNode *tmp=q.front();
                    q.pop();
                    if(tmp->val%2==0 || tmp->val<=mi)
                        return false;
                    mi=tmp->val;
                    if(tmp->left)
                        q.push(tmp->left);
                    if(tmp->right)
                        q.push(tmp->right);
                }
                else{
                    TreeNode *tmp=q.front();
                    q.pop();
                    if(tmp->val%2==1 || tmp->val>=ma)
                        return false;
                    ma=tmp->val;
                    if(tmp->left)
                        q.push(tmp->left);
                    if(tmp->right)
                        q.push(tmp->right);
                }
            }
            level^=true;
        }
        return true;
    }
};