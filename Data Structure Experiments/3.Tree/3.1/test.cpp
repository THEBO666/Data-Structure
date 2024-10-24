#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 打印二叉树的中序遍历（用于验证结果）
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

// 使用先序序列（包括空节点）非递归构建二叉树
TreeNode* buildTree(const vector<int>& preorder) {
    if (preorder.empty()) return nullptr;

    stack<TreeNode*> nodeStack;
    TreeNode* root = new TreeNode(preorder[0]);  // 创建根节点
    nodeStack.push(root);
    bool expectLeft = true;  // 控制是否填充左子节点

    for (size_t i = 1; i < preorder.size(); ++i) {
        if (preorder[i] != -1) {  // 非空节点
            TreeNode* newNode = new TreeNode(preorder[i]);
            if (expectLeft) {
                nodeStack.top()->left = newNode;
            } else {
                nodeStack.top()->right = newNode;
                nodeStack.pop();  // 右子节点完成后弹栈
            }
            nodeStack.push(newNode);
            expectLeft = true;  // 下一个节点是左子节点
        } else {  // 空节点
            if (expectLeft) {
                expectLeft = false;  // 左子节点为空，准备填右子节点
            } else {
                nodeStack.pop();  // 右子节点为空，弹栈
            }
        }
    }

    return root;
}

int main() {
    // 示例输入：先序序列，-1 表示空节点
    vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5};

    // 构建二叉树
    TreeNode* root = buildTree(preorder);

    // 打印二叉树的中序遍历（验证树的结构）
    cout << "Inorder Traversal: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
