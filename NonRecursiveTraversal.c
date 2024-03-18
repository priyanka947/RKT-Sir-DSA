#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Structure to represent a stack node for iterative traversal
struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

// Structure to represent a stack for iterative traversal
struct Stack {
    struct StackNode* top;
};

// Function to create a new stack node
struct StackNode* createStackNode(struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push a node onto the stack
void push(struct Stack* stack, struct TreeNode* node) {
    struct StackNode* newNode = createStackNode(node);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a node from the stack
struct TreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    struct TreeNode* poppedNode = stack->top->node;
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return poppedNode;
}

// Function to perform iterative inorder traversal
void inorderTraversal(struct TreeNode* root) {
    struct Stack* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("%d ", current->val);

        current = current->right;
    }
}

// Function to perform iterative postorder traversal
void postorderTraversal(struct TreeNode* root) {
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    struct TreeNode* current = root;

    push(stack1, current);

    while (!isEmpty(stack1)) {
        current = pop(stack1);
        push(stack2, current);

        if (current->left != NULL) {
            push(stack1, current->left);
        }

        if (current->right != NULL) {
            push(stack1, current->right);
        }
    }

    while (!isEmpty(stack2)) {
        current = pop(stack2);
        printf("%d ", current->val);
    }
}

// Driver program to test the above functions
int main() {
    // Example usage
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->left->left = root->left->right = NULL;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->right->left = root->right->right = NULL;

    printf("Inorder traversal: ");
    inorderTraversal(root);

    printf("\nPostorder traversal: ");
    postorderTraversal(root);

    // Free allocated memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
