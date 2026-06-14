// 二叉搜索树（BST）实现
// 支持：插入、删除、查找、中序遍历
// 删除时处理了三种情况：叶子节点、单子节点、双子节点（用后继节点替换）

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

    // 递归插入：小于当前节点走左子树，大于走右子树
    TreeNode* insertNode(TreeNode* node, int data) {
        if (node == NULL)
            return new TreeNode(data);
        if (data < node->data)
            node->left = insertNode(node->left, data);
        else if (data > node->data)
            node->right = insertNode(node->right, data);
        return node;
    }

    // 递归删除：找到目标后分情况处理
    // 双子节点时找右子树最小值（后继）替换，再递归删除后继
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

    // 中序遍历（BST 中序遍历结果为有序序列）
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

    // 递归查找节点
    TreeNode* searchNode(TreeNode* root, int data) {
        if (root == NULL || root->data == data) return root;
        if (data < root->data)
            return searchNode(root->left, data);
        return searchNode(root->right, data);
    }

    // 找以 root 为根的子树中最小值节点（一路向左）
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