#include <bits/stdc++.h>
#include<vector>
using namespace std;

class BinaryTreeNode 
    {
    public : 
        T data;
        BinaryTreeNode<T> *left;
        BinaryTreeNode<T> *right;

        BinaryTreeNode(T data) {
            this -> data = data;
            left = NULL;
            right = NULL;
        }
    };
int countUnivalTrees(BinaryTreeNode<int> *root){
    if(root == NULL){
        return 0;
    }
        if(root->left == NULL && root->right == NULL){
            return 1;
        }
        int left = countUnivalTrees(root->left);
        int right = countUnivalTrees(root->right);
        if(root->left != NULL && root->right != NULL){
            if(root->data == root->left->data && root->data == root->right->data){
                return left + right + 1;
            }
        }
        if(root->left != NULL && root->right == NULL){
            if(root->data == root->left->data){
                return left + right + 1;
            }
        }
        if(root->left == NULL && root->right != NULL){
            if(root->data == root->right->data){
                return left + right + 1;
            }
        }
        return left + right;
}