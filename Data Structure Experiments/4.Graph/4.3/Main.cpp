#include "../4.1/Graph1.hpp"
#include <iostream>
#include <vector>
#include <string>

const std::string name[30]={"风雨操场","建筑学馆","信息学馆","文法学馆",
                            "图书馆","生科楼","1号教学楼","1食堂",
                            "2食堂","1舍","2舍","3舍","4舍","5舍",
                            "北门","西门","南门","东门","小西门","医务室"
                            };

void initMap(Graph_Matrix<std::string,int,false>&g1)
{
    g1.addEdge("风雨操场","西门",200);
    g1.addEdge("风雨操场","小西门",180);
    g1.addEdge("风雨操场","北门",60);
    g1.addEdge("风雨操场","建筑学馆",80);
    g1.addEdge("建筑学馆","北门",70);
    g1.addEdge("建筑学馆","图书馆",50);
    g1.addEdge("建筑学馆","文法学馆",100);
    g1.addEdge("文法学馆","西门",300);
    g1.addEdge("文法学馆","图书馆",80);
    g1.addEdge("文法学馆","1食堂",60);
    g1.addEdge("1食堂","3舍",150);
    g1.addEdge("1食堂","1号教学楼",180);
    g1.addEdge("1食堂","1舍",100);
    g1.addEdge("1舍","2舍",150);
    g1.addEdge("1舍","2食堂",50);
    g1.addEdge("小西门","3舍",100);
    g1.addEdge("2舍","3舍",100);
    g1.addEdge("小西门","2舍",80);
    g1.addEdge("北门","医务室",390);
    g1.addEdge("图书馆","信息学馆",60);
    g1.addEdge("图书馆","生科楼",70);
    g1.addEdge("图书馆","1号教学楼",200);
    g1.addEdge("1号教学楼","5舍",130);
    g1.addEdge("1号教学楼","2食堂",100);
    g1.addEdge("2食堂","4舍",200);
    g1.addEdge("信息学馆","医务室",90);
    g1.addEdge("信息学馆","生科楼",80);
    g1.addEdge("生科楼","东门",130);
    g1.addEdge("生科楼","5舍",120);
    g1.addEdge("5舍","4舍",100);
    g1.addEdge("5舍","东门",260);
    g1.addEdge("医务室","东门",390);
    g1.addEdge("4舍","东门",260);
}
int main()
{
    
    Graph_Matrix<std::string,int,false> school(name,20);
    // 以邻接矩阵的方式存储，便于读入
    initMap(school);
    while(1)
    {
        std::cout << "\n********** 东北大学浑南校区校园导游咨询系统 **********" << std::endl;
        std::cout << "1. 查看校园地图信息" << std::endl;
        std::cout << "2. 查询任意两景点的最短路径" << std::endl;
        std::cout << "3. 查询遍历全部景点的最省时间行程" << std::endl;
        std::cout << "4. 退出系统" << std::endl;
        std::cout << "请输入您的选择（1-4）：";
        int n;
        std::string src,dst;
        std::cin >> n;

        switch (n)
        {
        case 1:
            /* code */
            break;
        case 2:
            std::cout << "请输入两个景点的名称: " << std::endl;
            std::cin>>src>>dst;
            school.Dijkstra(src,dst);
            break;
        }
    }
    return 0;
}