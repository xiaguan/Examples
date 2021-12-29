# 日志系统
## 各个主类
### Logger
1. m_name       //logger的名称
2. m_level      //满足level级别才可以输出
3. m_appenders  //log输出的地方，是个链表，比如说一个日志可以同时输到std和file里面 
4. log()  //将满足level级别的log通过m_appenders的log()输出 
5. 各种级别函数简化调用log()如：debug(ptr event)
6. addAppender       //向m_appenders中添加链表
7. delAppeder        //删除


### LogEvent 
这个类是log事件，有log的各种信息
1. 各种标识不一一列举（如：文件名，行号，消息内容）
2. 有各种get_xx函数用于返回LogEvent的内容，主要提供给formatter使用

### LogAppender
log输出类，是个基类
1.  m_level             //满足级别输出
2. m_formatter(ptr)     // formatter对象的shared_ptr指针
3. log                     //纯虚函数

#### StdOutAppender继承自LogAppender
1. override 父类的log，通过formatter将log按格式输出


#### FileOutAppender继承自LogAppender
比LogAppender多了两个成员
1. m_filename       // 输出文件名
2.m_file            //输出文件流
3.reopen()          //重新打开文件

### LogFormatter
格式控制类,略复杂
public下有另一个FormatterItem类（基类）
        // %m 消息体
        // %p level
        // % r -- 启动后的时间
        // % c -- 日志名称
        // %t --线程id
        // %n -- 换行
        //  %d -- 时间
        // %f -- 文件名
        // %l -- 行号
成员：
1. m_items          //子类的vector
2. m_pattern        // 格式控制  如：%d %s ...
3. void init()      //初始化函数，涉及到算法，不展开
#### FormatterItem
有一个纯虚函数format用于处理格式
##### MessageFormatItem继承自FormatterItem 
用于返回event的contetn
#### 还有很多例如LevelFormatItem 返回level ...

### 其他闲杂函数
#### LogLevel::ToString(level) :const char * 将level转换为const cahr *



