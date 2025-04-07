/*
Given : Root of a binary tree.
Return : The same tree where every subtree (of the given tree) not containing a 1 has been removed.
subtree of a node is node plus every node that is a descendant of node.
Intuition: 
*/
#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {//function to prune the tree
        if (root == nullptr) {//if the root is null
            return nullptr;//return null
        }
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (root->val == 0 && root->left == nullptr && root->right == nullptr) {//if the root value is 0 and the left and right children are null
            return nullptr;//return null
        }
        
    }
};