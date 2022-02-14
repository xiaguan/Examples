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

## 套接字地址结构
### IPV4套接字地址结构
IPv4套接字地址，它以sockaddr_in命名，定义在<netinet/in.h>头文件中
```
struct in_addr{
    in_addr_t s_addr;     // 32-bit IPV4 address(网络字节序)
}

struct sockaddr_in{
    uint8_t sin_len;
    sa_family_t sin_family;
    in_port_t sin_port;   // 16字节 port number
    struct in_addr sin_addr;   // ipv4地址
    char sin_zero[8];     //不使用
}
```
### 通用套接字地址结构
  当作一个参数传递进任何套接字函数时，套接字地址结构总是以引用形式（也就是以指向该结构的指针）来传递。
  通用套接字地址结构：
  ```
  struct sockaddr{
      uint8_t sa_lne;
      sa_family_t sa_family;   //address family
      char sa_data[14];      // protocol-specific address
  }

### 常用函数
#### inet_pton和inet_ntop
这两个函数对于ipv4和ipv6都适用。函数名中的p和n分别代表表达（presentation）和数值（numeric）。
```
#include <arpa/inet.h>
int inet_pton(int family,const char * strptr,void  * addrptr);
//成功返回1，表达格式有误返回0，出错返回-1
const char * inet_ntop(int family,const void * addrptr,char * str ptr, size_t len);
//成功则返回指向结果的指针，若出错则为NULL
```
len参数
```
#define INET_ADDRSTRLEN 16   // IPV4
#define INET6_ADDRSTRLEN 46  // IPV6
```

example:
```
inet_pton(AF_INET,m_serv_adres.c_str(),&m_serv_addr.sin_addr);

char ipadress[INET_ADDRSTRLEN];
inet_ntop(AF_INET,&serv_addr.sin_addr,ipadress,sizeof(ipadress)); 
log_msg += std::string(ipadress);
```

inet_ntop存在一个问题：它要求调用者传递一个二进制地址的指针。为了解决问题，我们自行编写一个sock_ntop，只用传入sockaddr和长度（区分IPV4和IPV6）。（存在一定设计问题，后面再补）

#### readn,writen和readline函数
由于TCP(或其他字节流套接字)的缓冲区问题，read和write的返回值并不是我们期望的值。我们需要手动编写一个指定大小的read和write函数，readline并不是必要的。但你通过阅读另一本书，发现socket编程接口提供了专门用于socket数据读写的函数。
1. TCP
```
#include <sys/types.h>
#include <sys/socket.h>

ssize_t recv(int sockfd,void * buf,size_t len,int flags);
ssize_t send(int sockfd,const void * buf,size_t len,int flags);
```
flags:通常设为0。（其他值可以查手册）

但，这样的函数，同样存在上述问题。
编写readn,writen函数如下:
编写时候的tips,在C语言中，void指针可以指向任何数据类型的变量。



 

