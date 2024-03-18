#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to perform in-order traversal and check if the binary tree is a BST
bool isBSTUtil(struct TreeNode* root, long long int* prev) {
    if (root == NULL) {
        return true;
    }

    // Check the left subtree
    if (!isBSTUtil(root->left, prev)) {
        return false;
    }

    // Check the current node
    if (root->val <= *prev) {
        return false;
    }

    // Update the previous value
    *prev = root->val;

    // Check the right subtree
    return isBSTUtil(root->right, prev);
}

// Function to check whether the binary tree is a BST
bool isBST(struct TreeNode* root) {
    long long int prev = LLONG_MIN;
    return isBSTUtil(root, &prev);
}

// Driver program to test the above functions
int main() {
    // Example usage
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 2;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 1;
    root->left->left = root->left->right = NULL;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->right->left = root->right->right = NULL;

    // Check if the binary tree is a BST
    if (isBST(root)) {
        printf("The binary tree is a Binary Search Tree.\n");
    } else {
        printf("The binary tree is not a Binary Search Tree.\n");
    }

    // Free allocated memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
