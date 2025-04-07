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
    void preorder(TreeNode* root, vector<int>& result){
        if(root == NULL){
            return;
        }
        result.push_back(root->val);
        preorder(root->left, result);
        preorder(root->right, result);
    }
    void postorder(TreeNode* root, vector<int>& result){
        if(root == NULL){
            return;
        }
        postorder(root->left, result);
        postorder(root->right, result);
        result.push_back(root->val);
    }
};
void main(){
    TreeNode* root = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    root->left = node2;
    root->right = node3;
    root->left->left = node4;
    Solution obj;
    vector<int> result = obj.inorderTraversal(root);
    for(int i=0; i<result.size(); i++){
        cout<<result[i]<<" ";
    }
}