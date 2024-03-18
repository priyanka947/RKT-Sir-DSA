#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to print all internal nodes of a tree with even values
void printInternalNodesEven(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL || root->right != NULL) {
        // Check if the value is even and print
        if (root->val % 2 == 0) {
            printf("%d ", root->val);
        }
    }

    // Recursively print internal nodes in left and right subtrees
    printInternalNodesEven(root->left);
    printInternalNodesEven(root->right);
}

// Function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Driver program to test the above functions
int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Internal nodes with even values: ");
    printInternalNodesEven(root);
    printf("\n");

    // Free allocated memory
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
