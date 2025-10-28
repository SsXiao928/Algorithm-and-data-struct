 //二叉树中序遍历
class Solution {
    std::vector<int> res;
    void inorder(TreeNode* root){
        if(root == nullptr){
            return;
        }
        mid(root->left);
        res.push_back(root->val);
        mid(root->right);
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        mid(root);
        return res;
    }
};