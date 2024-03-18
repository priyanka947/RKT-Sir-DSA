#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to perform a left rotation on the binary tree rooted at 'root'
struct TreeNode* leftRotate(struct TreeNode* root) {
    if (root == NULL || root->right == NULL) {
        return root;
    }

    struct TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    return newRoot;
}

// Function to perform a right rotation on the binary tree rooted at 'root'
struct TreeNode* rightRotate(struct TreeNode* root) {
    if (root == NULL || root->left == NULL) {
        return root;
    }

    struct TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    return newRoot;
}

// Function to perform an inorder traversal of the binary tree
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

// Function to insert a new node with the given value into the binary tree
struct TreeNode* insertNode(struct TreeNode* root, int val) {
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (val < root->val) {
        root->left = insertNode(root->left, val);
    } else if (val > root->val) {
        root->right = insertNode(root->right, val);
    }

    return root;
}

// Driver program to test the above functions
int main() {
    // Example usage
    struct TreeNode* root = NULL;

    // Insert nodes into the binary tree
    root = insertNode(root, 3);
    root = insertNode(root, 2);
    root = insertNode(root, 4);
    root = insertNode(root, 1);
    root = insertNode(root, 5);

    // Print the original binary tree
    printf("Original Binary Tree (Inorder): ");
    inorderTraversal(root);
    printf("\n");

    // Perform left rotation
    root = leftRotate(root);

    // Print the binary tree after left rotation
    printf("Binary Tree after Left Rotation (Inorder): ");
    inorderTraversal(root);
    printf("\n");

    // Perform right rotation
    root = rightRotate(root);

    // Print the binary tree after right rotation
    printf("Binary Tree after Right Rotation (Inorder): ");
    inorderTraversal(root);
    printf("\n");

    // Free allocated memory (optional)
    // Note: Proper memory deallocation depends on the complete structure of your program
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
