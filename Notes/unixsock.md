# Unix网络编程
## 常用函数
### socket 函数
为了执行网络I/O ,第一步一定是调用socket函数，指定期望通信的协议类型
```
#include <sys/socket.h>
int  socket(int family , int type, int protocol);
```

family 指明协议族。type是套接字类型。protocaol。
成功时返回非负描述符，若出错返回-1

### connect 函数
TCP客户用connect 函数来建立与TCP服务器的连接。
```
int connect(in sockff, const struct sockaddr * servaddr, socklen_t addrlen)
```
sockfd 是由socket函数返回的套接字描述符，然后传入serv的sockadr_in和长度。

### bind函数
bind 函数把一个本地协议地址赋予 一个套接字。
```
int bind(int sockfd, const struct sockaddr *myaddr,socklen_t addrlen);
```
### listen函数
listen函数由tcp服务器调用，它做两件事
1. 将套接字设为Listen状态
2. 规定了内核应该为相应套接字排队的最大连接个数。

```
int listen(int sockfd, int backlog);
```
### accept函数
由TCP服务器调用，用于从已完成连接队列对头返回下一个已完成连接。如果已完成队列为空，那么进程被置于休眠状态。
```
int accept(int sockfd,struct sockaddr * cliaddr,socklne_t *addrlen)
```
