package jdbc;

import jdbc.src.MyConnection;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

public class ConnectionImp extends MyConnection implements Runnable{

  Socket socket;

    String url;

    Properties info;

    public ConnectionImp(String url, Properties info) {
        this.url=url;
        this.info=info;
    }

    @Override
    public void run() {

            /*
            以下字符字符串解析就是获得ip 与端口，进行tcp连接
             */
             String[] str=url.split(":");
             String ip=str[0];
             int port=Integer.parseInt(str[1]);
            String sql=info.get("user")+","+info.get("password");
            //创建包发送连接消息
            TSDBPackage tsdbPackage=new TSDBPackage(TSDBDriver.REQUEST_CONNECTION,sql);
            byte[] aPackage=tsdbPackage.creatPackage();
            Socket mysocket=null;
            try {

                mysocket=new Socket(ip, port);

                Object[] result=null;
                int i=-1;
                do {
                    //包装协议，发送连接包
                    tsdbPackage.send(aPackage,mysocket);
                    InputStream conn_r=mysocket.getInputStream();
                    byte[] bytes=new byte[1024];
                    int read=0;
                    //发送数据包进行连接请求
                    if ((read=conn_r.read(bytes))!=0){
                       result=tsdbPackage.solveAPackage(bytes,read);
                    }
                    i++;
                    /*
                    判断结果集首位与协议是否相等，相等连接成功，获得数据库名字
                     */
                }while (((byte)result[0]!=TSDBDriver.CONN_SUCCESS)&&i<3);
                if (((byte)result[0]==TSDBDriver.CONN_SUCCESS)){
                    System.out.println("已经连接数据库:"+result[1]);
                    info.setProperty("database",(String) result[1]);
                    socket=mysocket;
                    return;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

        System.out.println("未连接数据库,当前网络连接波动大");
        return;
    }

    @Override
    public Statement createStatement() throws SQLException {
        while (socket==null){
            try {
                Thread.sleep(Long.parseLong("100"));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        StatementImp statementImp=new StatementImp(this.socket);
        return statementImp;
    }
}
