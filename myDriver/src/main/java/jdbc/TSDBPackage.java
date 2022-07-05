package jdbc;

import java.io.IOException;
import java.io.OutputStream;

import java.net.Socket;
/*
打包消息，解封消息的类
之中有很多将short int 变为byte数组的方法
或将byte数组变为short int的方法 低端转换
例如  short 513 =byte[]  00000010 00000001
 */
public class TSDBPackage {

    /*
    头协议
     */
    private byte headDeal;

    /*
    版本号
     */
    private byte version;

    /*
    消息内容
     */
    private String payload;

    /*
    标志位
     */
   // private byte signal=0;
    
//    public static final byte OVER=10;

    public static final int SECRET=0X8F;


    public TSDBPackage(byte headDeal,String payload) {
        this.headDeal=headDeal;
        this.payload=payload;
        this.version= TSDBDriver.getVersion();
    }
    /*
    8 byte 1+2+1+4+1
     */

    public  byte[] bytes(short x){
        byte[] ret=new byte[2];
        ret[0] = (byte)((x >> 8) & 0xff);
        ret[1] = (byte)(x & 0xff);
        return ret;
    }
    /*
    打包
     */
    public byte[] creatPackage(){
        int len=payload.length();
        int payLen=len+9;
        byte[] bytes=new byte[payLen];
        byte[] lengh=toHH(payLen);
        //协议头
        bytes[0]=this.headDeal;
        //对长度byte数组进行验证
        short crc= CRC.crc16(lengh);
        //crc验证
        byte[] crcs=bytes(crc);
        System.arraycopy(crcs, 0,bytes, 1, 2);
        /*
        从3 开始
        版本号
         */
        bytes[3]=this.version;
        /*
        消息长度
        从4开始
         */
        System.arraycopy(lengh, 0,bytes, 4, 4);
        /*
        拼接消息包从8开始
         */
        System.arraycopy(this.payload.getBytes(), 0,bytes, 8, len);
        /*
        结束符
         */
        bytes[payLen-1]=10;
        /*
        异或处理
         */
            return Xor(bytes);

    }

    public  short getShort(byte argB1,byte argB2) {
        return (short) ((argB1 & 0xFF)| (argB2 << 8));
    }
    /*
    将int转换成byte数组
     */
    public static byte[] toHH(int n) {
        byte[] b = new byte[4];
        b[3] = (byte) (n & 0xff);
        b[2] = (byte) (n >> 8 & 0xff);
        b[1] = (byte) (n >> 16 & 0xff);
        b[0] = (byte) (n >> 24 & 0xff);
        return b;
    }



    /*
    解包获得数据，只解析结果集
     */
    public Object[] solveAPackage(byte[] aPack,int lengh){
        int i;
        for(i = 0;i < lengh;i++)if (aPack[i] == -123)break;
        byte [] aPackage=new byte[i+1];

        System.arraycopy(aPack, 0,aPackage, 0,i+1);
        //获得异或后的数据包
        aPackage=Xor(aPackage);
        //取出4byte 长度
        byte[] len=new byte[4];
        System.arraycopy(aPackage, 4,len, 0, 4);
                /*
                crc 对长度进行计算
                 */
        short crc16= CRC.crc16(len);
                /*
                获得包中crc的值
                 */
        short crcRe=getShort(aPackage[2],aPackage[1]);

        //包整体的长度，方面后面校验
        int length=aPackage.length;
        int lenRe=toInt(len);

        //取出4byte 长度
                /*
                校验成功，获得payload

                返回一个数组，两个内容

                {协议，内容}

                crc 验证完整性  数据包长度  数据版本
                 */
        System.out.println("=====测试代码，收到了一个包=======");
        System.out.println(length+" "+lenRe);
        System.out.println(crc16+" "+crcRe);
        System.out.println(aPackage[3]+" "+ TSDBDriver.getVersion());



        if ((length==lenRe)&&(crc16==crcRe)&&(aPackage[3]== TSDBDriver.getVersion())){
           System.out.println("======解包成功，解析协议========");
            switch (aPackage[0]) {

                        /*
                        成功响应，返回数据
                        1100 0000
                         */
                case TSDBDriver.MESS_SUCCESS:
                    String res=getResult(aPackage);
                    return new Object[]{TSDBDriver.MESS_SUCCESS,res};
                            /*
                            操作语句失败
                            1100 0001
                             */
                case TSDBDriver.OPER_FAIL:
                    return new Object[]{TSDBDriver.OPER_FAIL};
                            /*
                            连接成功，返回文件树
                            1100 1001
                             */
                case TSDBDriver.CONN_SUCCESS:
                    return new Object[]{TSDBDriver.CONN_SUCCESS,getResult(aPackage)};
                            /*
                            连接失败
                            1000 1001
                             */
                case TSDBDriver.CONN_FAIL:

                    return new Object[]{TSDBDriver.OPER_FAIL};
                            /*
                            首次连接成功返回了数据库名
                             1000 0001
                             */
                case TSDBDriver.RESP_REQUIRE:
                    String res1=getResult(aPackage);

                    return new Object[]{TSDBDriver.RESP_REQUIRE,res1};
                            /*
                            数据传送完毕，服务端断开连接
                             */
                case TSDBDriver.DONE_DISCONN:
                    return new Object[]{TSDBDriver.DONE_DISCONN};

                default:

                    return null;
            }
        }
        return null;

    }


    public  int toInt(byte[] b){
        int res = 0;
        for(int i=0;i<b.length;i++){
            res += (b[i] & 0xff) << ((3-i)*8);
        }
        return res;
    }



    public String getResult(byte [] aPackage){
        /*
        消息长度为 1+2+1+4+1 len-9 byte
        0 消息头
        1-2 crc 校验
        3 标志位
        4-7 消息长度
       len-1 结束符\n
         */
        int j=0;
        int len=aPackage.length;
        int lens=len-9;
         len-=1;
        //创建一个byte长度为消息长度
        byte [] bytes=new byte[lens];
        /*
        读取长度从1+2+4处开始
         */
        for (int i = 8; i < len; i++) {
            bytes[j]=aPackage[i];
            j++;
        }

        return new String(bytes);
    }





    /*

    进行数据解密

    简单的异或算法解密
 */
    public byte[] Xor(byte[] chs){
//        char [] chs =input.toCharArray();
        for(int i=0;i<chs.length;i++){
            chs[i]=(byte) (chs[i]^SECRET);
        }

        return chs;
    }

    /*
    发送数据方法
     */

    public void send(byte[] bytes, Socket socket){
        OutputStream conn= null;
        try {
            conn = socket.getOutputStream();
            conn.write(bytes);
            conn.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
