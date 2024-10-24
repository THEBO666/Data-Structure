#include "BinaryTree.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
    std::vector<int> vt= {1,2,4,-1,-1,5,-1,-1,3,-1,-1} ;   
    Node *root=CreateTree(vt);
    PreOrder(root);
    std::cout<<std::endl;
    InOrder(root);
    std::cout<<std::endl;
    PostOrder(root);
    std::cout<<std::endl;
    LevelOrder(root);
    std::cout<<std::endl;
    std::cout<<TreeSize(root);
    /*while(true)
    {
        system("cls");
        int a;
        
        std::cout<<"Please select function: "<<std::endl;
        std::cin>>a;
    }*/
    system("pause");
    return 0;
}
