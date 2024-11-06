#include "BinaryTree.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <sys/types.h>
#include <cstdio>


int main()
{
    // std::vector<int> vt = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, -1};
    // Node *root = CreateTree(vt);
    // PreOrder(root);
    // std::cout << std::endl;
    // InOrder(root);
    // std::cout << std::endl;
    // PostOrder(root);
    // std::cout << std::endl;
    // LevelOrder(root);
    // std::cout << std::endl;
    // std::cout << TreeSize(root);
    
    Node *root=nullptr;
    while (true)
    {
        std::vector<int> vt;
        std::cout << "Please select function: " << std::endl;
        std::cout << "1. Create Binary Tree" << std::endl;
        std::cout << "2. PreOrder" << std::endl;
        std::cout << "3. InOrder" << std::endl;
        std::cout << "4. PostOrder" << std::endl;
        std::cout << "5. LevelOrder" << std::endl;
        std::cout << "6. TreeSize" << std::endl;
        std::cout << "7. TreeHeight" << std::endl;
        std::cout << "8. Destory Tree" << std::endl;
        int n;
        std::cin >> n;
        switch (n)
        {
            case 1:
                while(1)
                {
                    int temp;
                    std::cin>>temp;
                    vt.push_back(temp);
                    if(getchar()!=' ') break;
                }
                root=CreateTree(vt);
            break;
            case 2:
                PreOrder(root);
                std::cout<<std::endl;
                getch();
            break;
            case 3:
                InOrder(root);
                std::cout<<std::endl;
                getch();
            break;
            case 4:
                PostOrder(root);
                std::cout<<std::endl;
                getch();
            break;
            case 5:
                LevelOrder(root);
                std::cout<<std::endl;
                getch();
            break;
            case 6:
                std::cout<<TreeSize(root)<<std::endl;
                getch();
            break;
            case 7:
                std::cout<<TreeHeight(root)<<std::endl;
                getch();
            break;
            case 8:
                bool flag=DestroyTree(root);
                if(flag)
                    std::cout<<"Success Destory"<<std::endl;
                else
                {
                    std::cout<<"Fatal Destory"<<std::endl;
                }
            break;

        }
    }
    // system("pause");
    return 0;
}
