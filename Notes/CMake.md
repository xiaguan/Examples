# Cmake 的简单学习
## 基本指令
### project
定义工程名称，同时隐式定义了两个cmake的变量： 
<projectname>_BINARY_DIR  //projectname是项目名称
<projectname>_SOURCE_DIR  
也可以这样用：
PROJECT_BINARY_DIR
PROJECT_SOURCE_DIR

### set
set指令可以用来显示的定义变量
set(SRC_LIST main.c) or set(SRC_LIST main.c t1.c t2.c)

### message([SEND_ERROR | STATUS | FATAL_ERROR] "message")
向终端输出用户定义的信息： 
包含三种类型 : 
1. SEND_ERROR #生成错误，生成过程被跳过
2. STATUS #输出前缀为--d的信息
3. FATAL_ERROR #立即终止所有的cmake过程

### add_executalbe()

### add_subdirectory(source_dr [binary_dir][EXCLUDE_FROM_ALL]) 
这个指令用于向当前工程添加存放源文件的子目录，斌可以指定中间二进制和目标二进制存放的位置。
EXCLUDE_FROM_ALL：将这个目录从编译过程中排除，

## 基本的语法规则
使用${} 取得变量中的值，在if语句中可以直接使用变量名
指令 （参数1 参数2 ...）参数之间使用空格或者分号隔开 
### Tips
可以使用双引号将源文件包含起来。fun c.c 可以使用set防止报错






