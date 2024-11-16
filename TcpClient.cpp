#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // 连接到ws2_32.lib库



int main()
{
    //system("chcp 65001");//This works!
    //std::wcout.imbue(std::locale("chs"));
   // std::wcin.imbue(std::locale("chs"));
    std::string serverip = "127.0.0.1";
    uint16_t serverport = 8888;
    // 初始化 Winsock
    WSADATA wsaData;
    int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaStartupResult != 0)
    {
        std::cerr << "WSAStartup failed with error: " << wsaStartupResult << std::endl;
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport);

    // 将IP地址从字符串转换为二进制形式
    server.sin_addr.S_un.S_addr=inet_addr(serverip.c_str());

    // 创建 socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        std::cerr << "socket error" << std::endl;
        WSACleanup();
        return 1;
    }

    // 连接到服务器
    int result = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if (result == SOCKET_ERROR)
    {
        std::cerr << "connect error..." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 2;
    }

    std::string message;
    while (true)
    {
        std::cout << "Please Enter@ ";
        std::getline(std::cin, message);

        // 发送消息
        send(sockfd, message.c_str(), message.size(), 0);

        char buffer[4096];
        int n = recv(sockfd, buffer, sizeof(buffer), 0);
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << buffer << std::endl;
        }
    }

    // 关闭 socket 和清理 Winsock
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

