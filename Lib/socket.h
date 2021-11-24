//
// Created by 75108 on 2021/11/24.
//

#ifndef ACM_SOCKET_H
#define ACM_SOCKET_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	Socket	
#include <iostream>
#include <stdlib.h>
#include <string>
#include <winsock2.h>

using namespace std;

class socket_tcp {
public:
    socket_tcp();
    socket_tcp(const string&, const short&);
    ~socket_tcp() {}

protected:
    WSADATA wsaSatrup;
    SOCKET hSocket;
    SOCKADDR_IN tcpAdr;
    void ErrorHandling(const string& s);
};

class tcpserver_sock :private socket_tcp {
public:
    tcpserver_sock();
    void listen(int);
    void accecptc();
private:
    SOCKET clntSock;
    SOCKADDR_IN clntAdr;
    int szClntAddr;
};

#endif //ACM_SOCKET_H
