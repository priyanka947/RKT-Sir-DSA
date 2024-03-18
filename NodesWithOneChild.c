#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to print nodes with only one child in a binary tree
void printNodesWithOneChild(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Check if the node has only one child
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        printf("%d ", root->val);

    // Recursively check left and right subtrees
    printNodesWithOneChild(root->left);
    printNodesWithOneChild(root->right);
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
    root->left->right = NULL;
    root->right->left = NULL;
    root->right->right = createNode(6);

    printf("Nodes with only one child: ");
    printNodesWithOneChild(root);
    printf("\n");

    // Free allocated memory
    free(root->left->left);
    free(root->left);
    free(root->right->right);
    free(root->right);
    free(root);

    return 0;
}
