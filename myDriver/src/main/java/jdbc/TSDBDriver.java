package jdbc;

import java.sql.*;
import java.util.Properties;
import java.util.logging.Logger;

/*
保存协议的位置
bio 另起线程连接服务器，连接成功则销毁线程
将线连接交给主线程维护

 */
public class TSDBDriver implements java.sql.Driver {
    /*
    添加用户
    0000 0000
     */
    public static final byte ADD_USER = (byte) -256;

    /*
    删除用户
    0000 0001
     */
    public static final byte DELETE_USER = (byte) -255;

    /*
    修改用户权限
    0000 0010
     */
    public static final byte MODIFYING_USER_RIGHTS = (byte) -254;

    /*
    创建数据库
    0000 0011
     */
    public static final byte CREATE_DATABASE = (byte) -253;

    /*
    删除数据库
    0000 01000
     */
    public static final byte DELETE_DATABASE = (byte) -252;

    /*
    新建表
    0000 0101
     */
    public static final byte CREATE_TABLE = (byte) -251;

    /*
    删除表
    0000 0110
     */
    public static final byte DELETE_TABLE = (byte) -250;

    /*
    查看表信息
    0000 0111
     */
    public static final byte SHOW_TABLES = (byte) -249;

    /*
    查看数据库信息
    0000 1000
     */
    public static final byte SHOW_DATABASES = (byte) -248;

    /*
    切换数据库
    0000 1001
     */
    public static final byte SWITCH_DATABASE = (byte) -247;

    /*
    清除缓存
    0000 1011
     */
    public static final byte CLEAR_CACHE = (byte) -246;

    /*
    批处理数据
    0100 0000
     */
    public static final byte BATCH_DATA = (byte) -192;

    /*
    查询语句
    0100 0001
     */
    public static final byte QUERY = (byte) -191;

    /*
    alter语句
    0100 0011
     */
    public static final byte ALTER = (byte) -190;

    /*
    请求连接
    1000 0000
     */
    public static final byte REQUEST_CONNECTION = (byte) -128;

    /*
    请求响应
    1000 0001
     */
    public static final byte REQUEST_RESPONSE = (byte) -127;

    /*
    ping命令
    1000 0100
     */
    public static final byte PING = (byte) -124;

    /*
    pang命令
    1000 0101
     */
    public static final byte PANG = (byte) -123;

    /*
    数据传送完毕，断开连接
    1000 0111
     */
    public static final byte DONE_DISCONN = -121;

    public static final byte CONN_REPEAT = -120;

    /*
    响应成功，回复数据
    1286432168421
    1100 0000
     */
    public static final byte MESS_SUCCESS = -64;

    /*
    操作语句失败
    1100 0001
     */
    public static final byte OPER_FAIL = -63;

    /*
    连接成功，返回树文件
    1100 1001
     */
    public static final byte CONN_SUCCESS = -55;


    /*
      首次连接成功返回了数据库名
      */
    public static final byte RESP_REQUIRE = -53;

    /*
    连接失败
    1100 1010
     */
    public static final byte CONN_FAIL = -54;

    public final static byte version = 0;



    public static byte getVersion() {
        return version;
    }


    public TSDBDriver() throws SQLException {

    }

    static {
        try {
            DriverManager.registerDriver(new TSDBDriver());


        } catch (SQLException var1) {
            throw new RuntimeException("Can't register driver!");
        }
    }

    @Override
    public Connection connect(String url, Properties info) throws SQLException {
        String[] head = url.split("//");
        if (head[0].equals("jdbc:tsdb:")) {
            //如果ip和端口符合规则，就开始连接
            if (acceptsURL(head[1])) {
                ConnectionImp connectionImp = new ConnectionImp(head[1], info);
                Thread thread = new Thread(connectionImp);
                thread.start();
                return connectionImp;
            }
            System.out.println("协议格式错误，加载驱动失败");
            return null;
        }
        System.out.println("协议格式错误，加载驱动失败");
        return null;
    }

    /*
    192.0.0.1:3306
     */
    @Override
    public boolean acceptsURL(String url) throws SQLException {
        if (url == null || "".equals(url)) {
            return false;
        }

        String regex = "(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\." +
                "(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])" +
                "\\:([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-4]\\d{4}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])";
        return url.matches(regex);
    }

    @Override
    public DriverPropertyInfo[] getPropertyInfo(String url, Properties info) throws SQLException {
        return new DriverPropertyInfo[0];
    }
//    public static byte bit2byte(String bString){
//        byte result=0;
//        for(int i=bString.length()-1,j=0;i>=0;i--,j++){
//            result+=(Byte.parseByte(bString.charAt(i)+"")*Math.pow(2, j));
//        }
//        return result;
//    }

    @Override
    public int getMajorVersion() {
        System.out.println("indexTSDB: beginning ,version:" + getVersion());
        return 0;
    }

    @Override
    public int getMinorVersion() {
        System.out.println("444444444444444444444444444444");
        return 0;
    }

    @Override
    public boolean jdbcCompliant() {
        System.out.println("55555555555555555555");
        return false;
    }

    @Override
    public Logger getParentLogger() throws SQLFeatureNotSupportedException {
        System.out.println("6666666666666666666666666");
        return null;
    }
}
