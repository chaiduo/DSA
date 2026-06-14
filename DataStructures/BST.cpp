// Binary Search Tree (BST) Implementation
// Supports: insert, delete, search, in-order traversal
// Deletion handles three cases: leaf node, single child node, two children node (replace with successor)

#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): data(0), left(nullptr), right(nullptr){}
    TreeNode(int a): data(a), left(nullptr), right(nullptr){};
};

class BSTTree
{
private:
    TreeNode* root = nullptr;

    // Recursive insert: less than current node go left subtree, greater go right subtree
    TreeNode* insertNode(TreeNode* node, int data) {
        if (node == NULL)
            return new TreeNode(data);
        if (data < node->data)
            node->left = insertNode(node->left, data);
        else if (data > node->data)
            node->right = insertNode(node->right, data);
        return node;
    }

    // Recursive delete: find target then handle different cases
    // For two children, find minimum in right subtree (successor) to replace, then recursively delete successor
    TreeNode* deleteNode(TreeNode* root, int data) {
        if (root == NULL) {
            cout << "not found " << endl;
            return root;
        }
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        } else if(root->left && root->right){
            TreeNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        } else {
            TreeNode* t = root;
            if(root->left == nullptr)root = root->right;
            if(root->right == nullptr)root = root->left;
            delete t;
        }
        return root;
    }

    // In-order traversal (BST in-order traversal yields sorted sequence)
    void inOrder(TreeNode* root) {
        if (root == NULL) return;
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

public:
    BSTTree(){}

    void insertNode(int data){
        root = this->insertNode(root, data);
    }

    void deleteNode(int data){
        root = this->deleteNode(root, data);
    }

    // Recursively search for node
    TreeNode* searchNode(TreeNode* root, int data) {
        if (root == NULL || root->data == data) return root;
        if (data < root->data)
            return searchNode(root->left, data);
        return searchNode(root->right, data);
    }

    // Find minimum value node in subtree rooted at root (always go left)
    TreeNode* minValueNode(TreeNode* root) {
        TreeNode* current = root;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void inOrder(){
        this->inOrder(root);
        cout << endl;
    }
};


int main() {
    BSTTree bst;
    bst.insertNode(40);
    bst.insertNode(30);
    bst.insertNode(20);
    bst.insertNode(10);
    bst.insertNode(50);
    bst.insertNode(60);
    bst.insertNode(70);
    bst.inOrder();
    bst.deleteNode(40);
    bst.inOrder();
    return 0;
}