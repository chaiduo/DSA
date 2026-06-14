// AVL Tree (Self-Balancing Binary Search Tree) Implementation
// After each insert/delete, maintain balance factor in [-1, 1] through rotations
// Four rotation cases: LL (right rotate), RR (left rotate), LR (left then right), RL (right then left)

#include <iostream>
using namespace std;

// Define binary tree node
struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode():data(0), left(nullptr), right(nullptr){}
    TreeNode(int value):data(value),left(nullptr), right(nullptr){}
};

// Get node height
int getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Right rotation: for LL case (left subtree too high)
TreeNode* rightRotate(TreeNode* node) {
    TreeNode* newRoot = node->left;
    TreeNode* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

// Left rotation: for RR case (right subtree too high)
TreeNode* leftRotate(TreeNode* node) {
    TreeNode* newRoot = node->right;
    TreeNode* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

// Get node balance factor (left subtree height - right subtree height)
int getBalanceFactor(TreeNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Insert node into AVL tree, check and fix balance after insertion
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    } else {
        cout << "Node with same value already exists!" << endl;
        return root;
    }

    // Update node height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Get node balance factor
    int balanceFactor = getBalanceFactor(root);

    // Four balance cases
    // LL case: need right rotation
    if (balanceFactor > 1 && value < root->left->data) {
        return rightRotate(root);
    }
    // RR case: need left rotation
    if (balanceFactor < -1 && value > root->right->data) {
        return leftRotate(root);
    }
    // LR case: need left rotation on left subtree first, then right rotation on root
    if (balanceFactor > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RL case: need right rotation on right subtree first, then left rotation on root
    if (balanceFactor < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal to print AVL tree
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}
// Delete operation for balanced binary tree, need to fix balance after deletion
TreeNode* deleteNode(TreeNode* root, int target) {
    if (root == NULL) {
        return NULL;
    }
    if (target < root->data) {
        root->left = deleteNode(root->left, target);
    } else if (target > root->data) {
        root->right = deleteNode(root->right, target);
    } else {
        // Found node to delete
        if (root->left == NULL && root->right == NULL) {
            // Leaf node
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            // Single child node
            TreeNode* child = (root->left != NULL ? root->left : root->right);
            free(root);
            return child;
        } else {
            // Two children, find successor node
            TreeNode* successor = root->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data);
        }
    }

    // Update node height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Balance fix: after deletion, also need to check four rotation cases
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        // LL
        return rightRotate(root);
    } else if (balance > 1 && getBalanceFactor(root->left) < 0) {
        // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        // RR
        return leftRotate(root);
    } else if (balance < -1 && getBalanceFactor(root->right) > 0) {
        // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
int main() {
    TreeNode* root = nullptr;
    int values[] = {7, 15, 5, 9, 8, 6, 10};

    // Insert nodes into AVL tree
    for (int value : values) {
        root = insertNode(root, value);
    }

    // Print AVL tree
    cout << "AVL tree in-order traversal result: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}