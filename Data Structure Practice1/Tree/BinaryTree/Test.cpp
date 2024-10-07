#include "BinaryTree.hpp"

int main()
{
    BTNode<int> *root = BuyNode(1);
    BTNode<int> *left = BuyNode(2);
    BTNode<int> *right = BuyNode(3);
    BTNode<int> *left1 = BuyNode(4);
    BTNode<int> *right1 = BuyNode(5);
    root->left = left;
    root->right = right;
    left->left = left1;
    left->right = right1;
    // PreOrder(root);
    // std::cout << std::endl;
    // InOrder(root);
    // std::cout << std::endl;
    // PostOrder(root);
    std::cout<<TreeHeight(root);
    return 0;
}
