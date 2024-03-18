#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to check if two trees are identical
bool areIdentical(struct TreeNode* tree1, struct TreeNode* tree2) {
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;

    return (tree1->val == tree2->val) &&
           areIdentical(tree1->left, tree2->left) &&
           areIdentical(tree1->right, tree2->right);
}

// Function to check if tree2 is a subtree of tree1
bool isSubtree(struct TreeNode* tree1, struct TreeNode* tree2) {
    if (tree2 == NULL)
        return true;
    if (tree1 == NULL)
        return false;

    // Check if the current subtree of tree1 is identical to tree2
    if (areIdentical(tree1, tree2))
        return true;

    // Recursively check in the left and right subtrees of tree1
    return isSubtree(tree1->left, tree2) || isSubtree(tree1->right, tree2);
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
    // Larger tree
    struct TreeNode* largerTree = createNode(3);
    largerTree->left = createNode(4);
    largerTree->right = createNode(5);
    largerTree->left->left = createNode(1);
    largerTree->left->right = createNode(2);

    // Subtree
    struct TreeNode* subtree = createNode(4);
    subtree->left = createNode(1);
    subtree->right = createNode(2);

    // Check if subtree is a subtree of largerTree
    if (isSubtree(largerTree, subtree)) {
        printf("The second tree is a subtree of the first tree.\n");
    } else {
        printf("The second tree is not a subtree of the first tree.\n");
    }

    // Free allocated memory
    free(largerTree->left->left);
    free(largerTree->left->right);
    free(largerTree->right);
    free(largerTree->left);

    free(subtree->left);
    free(subtree->right);
    free(subtree);

    return 0;
}
