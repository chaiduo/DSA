// AVL 树（自平衡二叉搜索树）实现
// 每次插入/删除后通过旋转维护平衡因子在 [-1, 1] 之间
// 四种旋转情况：LL（右旋）、RR（左旋）、LR（先左后右）、RL（先右后左）

#include <iostream>
using namespace std;

// 定义二叉树的节点
struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode():data(0), left(nullptr), right(nullptr){}
    TreeNode(int value):data(value),left(nullptr), right(nullptr){}
};

// 获取节点的高度
int getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// 右旋操作：用于 LL 情况（左子树过高）
TreeNode* rightRotate(TreeNode* node) {
    TreeNode* newRoot = node->left;
    TreeNode* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

// 左旋操作：用于 RR 情况（右子树过高）
TreeNode* leftRotate(TreeNode* node) {
    TreeNode* newRoot = node->right;
    TreeNode* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

// 获取节点的平衡因子（左子树高度 - 右子树高度）
int getBalanceFactor(TreeNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 插入节点到 AVL 树中，插入后检查并修正平衡
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    } else {
        cout << "已存在相同数值的节点！" << endl;
        return root;
    }

    // 更新节点的高度
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // 获取节点的平衡因子
    int balanceFactor = getBalanceFactor(root);

    // 平衡的四种情况
    // 左左情况：需要执行右旋操作
    if (balanceFactor > 1 && value < root->left->data) {
        return rightRotate(root);
    }
    // 右右情况：需要执行左旋操作
    if (balanceFactor < -1 && value > root->right->data) {
        return leftRotate(root);
    }
    // 左右情况：需要先对左子树进行左旋操作，再对根节点进行右旋操作
    if (balanceFactor > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // 右左情况：需要先对右子树进行右旋操作，再对根节点进行左旋操作
    if (balanceFactor < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 中序遍历打印 AVL 树
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}
// 平衡二叉树的删除操作，删除后同样需要修正平衡
TreeNode* deleteNode(TreeNode* root, int target) {
    if (root == NULL) {
        return NULL;
    }
    if (target < root->data) {
        root->left = deleteNode(root->left, target);
    } else if (target > root->data) {
        root->right = deleteNode(root->right, target);
    } else {
        // 找到待删除节点
        if (root->left == NULL && root->right == NULL) {
            // 叶子节点
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            // 只有一个子节点
            TreeNode* child = (root->left != NULL ? root->left : root->right);
            free(root);
            return child;
        } else {
            // 有两个子节点，找到后继节点
            TreeNode* successor = root->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data);
        }
    }

    // 更新节点高度
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // 平衡修正：删除后同样需要检查四种旋转情况
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        // 左左
        return rightRotate(root);
    } else if (balance > 1 && getBalanceFactor(root->left) < 0) {
        // 左右
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        // 右右
        return leftRotate(root);
    } else if (balance < -1 && getBalanceFactor(root->right) > 0) {
        // 右左
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
int main() {
    TreeNode* root = nullptr;
    int values[] = {7, 15, 5, 9, 8, 6, 10};

    // 向 AVL 树中插入节点
    for (int value : values) {
        root = insertNode(root, value);
    }

    // 打印 AVL 树
    cout << "AVL 树的中序遍历结果为: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}