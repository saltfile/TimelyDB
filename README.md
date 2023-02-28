自研发时序数据库



<div align=center>
<img src="https://github.com/saltfile/imgs_libs/blob/master/logo1.jpg" width="400px" height="200px">
</div>

<h2>TimelyDB时序数据库V0.1</h2>

·使用简单，对比influxDB时序数据库过于复杂的使用方式这款自研发数据库更为简单适合小部分时序控件存储<br>
·不用过多考虑冷数据过多的问题，使用环形内存的方式将过冷数据覆盖</br>
·自研发作品


以下是对关键模块的描述：
<h1>数据接收服务端</h1>

协议构成：首先是协议头（执行对应编号），然后是两位crc校验负责与后面的数据进行对比做长度校验；后面是4位长度以及对应的数据消息体；最后一位就是结束符。<br>
如图：
<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/xieyi.jpg" width="601px" height="60px">
</div>
服务端设计：由于是单机版的初代版本所以就使用了epoll lt作为服务端使用，在后续的1.2版本之中会加入连接池的设计。
如图：
<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/fuwuduan.jpg" width="352px" height="452px">
</div>
<br>
<h1>语法解析</h1>
首先，通过分词模块中的token进行对比，解析出关键语句类似于select insert等然后生成对应的sql词数组，生成对应的语法树检测语法是否正常，然后然后生成对应的执行树/责任链,
通过调用源语或引擎部分将数据结果发给封包器

<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/%E8%AF%AD%E6%B3%95%E8%A7%A3%E6%9E%90%E6%89%A7%E8%A1%8C.jpg" width="1000px" height="260px">
</div>


<h1>引擎部分</h1>

文件系统：
通过读取磁盘中的信息，将对应的数据表、库抽象为数据结构。
如图：

<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/filetree.jpg" width="1056px" height="520px">
</div>

环形存储：
将数据以环形的方式进行存储，并且定时落盘
如图：


<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/quancun.jpg" width="721px" height="551x">
</div>

<h1>索引部分</h1>
一层索引为跳表用来确定时间维度数据
二层索引为红黑树用来确定数据维度
如图：

<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/suoyin.jpg" width="1056px" height="520px">
</div>



最后,是底层文件数据的存储格式，不多介绍如图所示。


<div>
<img src="https://github.com/saltfile/imgs_libs/blob/master/wenjian.jpg" width="1200px" height="300px">
</div>












