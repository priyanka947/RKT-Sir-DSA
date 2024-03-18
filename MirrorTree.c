#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a mirror tree of the original binary tree
struct TreeNode* createMirrorTree(struct TreeNode* root) {
    if (root == NULL)
        return NULL;

    struct TreeNode* mirroredRoot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    mirroredRoot->val = root->val;
    mirroredRoot->left = createMirrorTree(root->right);
    mirroredRoot->right = createMirrorTree(root->left);

    return mirroredRoot;
}

// Function to perform in-order traversal of a binary tree
void inOrderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    printf("%d ", root->val);
    inOrderTraversal(root->right);
}

// Function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Driver program to test the above function
int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Original Binary Tree (In-Order): ");
    inOrderTraversal(root);
    printf("\n");

    // Create a mirror tree
    struct TreeNode* mirroredRoot = createMirrorTree(root);

    printf("Mirror Binary Tree (In-Order): ");
    inOrderTraversal(mirroredRoot);
    printf("\n");

    // Free allocated memory
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
    free(mirroredRoot);

    return 0;
}
