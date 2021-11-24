//
// Created by 75108 on 2021/11/24.
//

#include "socket.h"

using namespace std;

// 基类的错误处理
void socket_tcp::ErrorHandling(const string& s) {
    cout << s << endl;
    exit(1);
}

// 基类的默认构造函数
socket_tcp::socket_tcp(const string& ipadress, const short& port) {

    // windows平台下socket的启动
    if (WSAStartup(MAKEWORD(2, 2), &wsaSatrup) != 0)
        ErrorHandling("WSAStartup() error!");
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        ErrorHandling("socket() error!");

    // tcpAdr的初始化，默认为127.0.0.1:4567
    memset(&tcpAdr, 0, sizeof(tcpAdr));
    tcpAdr.sin_family = AF_INET;
    tcpAdr.sin_addr.s_addr = inet_addr(data(ipadress));
    tcpAdr.sin_port = htons(port);
}

tcpserver_sock::tcpserver_sock() :socket_tcp("127.0.0.1", (short)4567) {
    tcpAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(hSocket, (SOCKADDR*)&tcpAdr, sizeof(tcpAdr)) == -1)
        ErrorHandling("bind() error");
    else
        cout << "bind() done....." << endl;
}

void tcpserver_sock::listen(int a = 5) {
    if (::listen(hSocket, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error...");
    else {
        cout << "listen() success" << endl;
    }
}

void tcpserver_sock::accecptc() {
    szClntAddr = sizeof(clntAdr);
    clntSock = accept(hSocket, (SOCKADDR*)&clntAdr, &szClntAddr);
    if (clntSock == INVALID_SOCKET)
        ErrorHandling("accept() error");
    else
        cout << "accept() done " << endl;
}

socket_tcp::socket_tcp() : socket_tcp("127.0.0.1", 4567) {}

