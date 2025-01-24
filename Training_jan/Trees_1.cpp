/*
Node root = new Node(1);
Node node2 = new Node(2);
Node node3 = new Node(3);
Node node4 = new Node(4);

root.left = node2;
root.right = node3;
root.left.left = node4;

DFS: Inorder, Preorder, Postorder
Inorder: left, root, right
Preorder: root, left, right
Postorder: left, right, root

*/
//Inorder Traversal
#include <vector>
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
    void inorder(TreeNode* root, vector<int>& result){
        if(root == NULL){
            return;
        }
        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }
};