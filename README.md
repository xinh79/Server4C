# Server4C

新增线程池代码，C实现，现在此项目已被废弃，笔者将开始转战C++

## HTTP Server

----

#### 简介

本项目为应用C编写的基于epoll边沿非阻塞触发模式的HTTP网络服务器，在本项目中，目前主要完成的工作有：

- 使用epoll边沿非阻塞触发完成服务器
- 通过对字符串的处理，对HTTP请求进行解析
- 传输HTTP请求的信息

----

#### 实验环境

操作系统: Ubuntu 18.04

编辑工具：Visual Studio Code

编译工具: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0

排查工具：gdb/printf

----

#### 编译

```shell
$ make clean
$ make
```

----

#### 运行

```shell
$ ./app [port] [workdir]
```

port为用户传入的端口号，workdir为用户指定的工作目录，游览器提出申请时，默认看到的工作目录。

----

#### 实验测试输出

在终端输入命令：`./app 8888 /home/h/Documents`

下图为实验结果测试图-服务器初始化：

![1](/pic/实验结果测试图-服务器初始化.png)

游览器连接服务器后：

![2](/pic/游览器连接服务器后-1.png)

![3](/pic/游览器连接服务器后-2.png)

从游览器点击music文件夹后：

![4](/pic/从游览器点击music文件夹后-1.png)

![5](/pic/从游览器点击music文件夹后-2.png)

游览器显示类容：

![6](/pic/游览器显示内容.png)

----

#### 压力测试

使用Apache Bench对土豆服务器进行压力测试

启动服务器后，输入命令：`ab -c 100 -n 10000 -r "http://192.168.253.129:8888/"`

![6](/pic/ab_yaliceshi.jpg)

