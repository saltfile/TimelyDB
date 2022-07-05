package jdbc;

import jdbc.src.MyStatement;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class StatementImp extends MyStatement {


    public StatementImp(Socket socket) {
        super(socket);
    }


    //查询数据库
   /* @Override
    public ResultSet executeQuery(String sql) throws SQLException {
        InputStream inputStream = null;
        try {
            //将执行语句进行简单的处理
            sql = toLowerCase(sql);
            // 打包发给服务器
            TSDBPackage tsdbPackage = new TSDBPackage(MyStatement.SELECT, sql);
            byte[] aPackage = tsdbPackage.creatPackage();
            Object[] result = null;
            //发送数据
            tsdbPackage.send(aPackage, super.socket);
            byte[] bowl = new byte[1024];
            //收集结果
            inputStream = super.socket.getInputStream();
            int read = 0;
            if ((read = inputStream.read(bowl)) != -1) {
                result = tsdbPackage.solveAPackage(bowl, read);
            }
            byte res = (byte) result[0];
            if (res == TSDBDriver.MESS_SUCCESS) {
                return new ResultSetIpm((String) result[1]);
            } else if (res == TSDBDriver.OPER_FAIL) {
                System.out.println("操作语句失败，语法错误，或者其他原因");
                return null;
            } else {
                System.out.println("网络不稳定，请稍后再使用");
                return null;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }*/

    private boolean General_boolean(byte num, String sql) {
        InputStream inputStream = null;
        try {
            sql = toLowerCase(sql);
            TSDBPackage tsdbPackage = new TSDBPackage(num, sql);
            byte[] aPackage = tsdbPackage.creatPackage();
            Object[] result = null;
            tsdbPackage.send(aPackage, super.socket);
            byte[] bowl = new byte[1024];
            inputStream = super.socket.getInputStream();
            int read = 0;
            //解包
            if ((read = inputStream.read(bowl)) != -1) {
                result = tsdbPackage.solveAPackage(bowl, read);
            }
            byte res = (byte) result[0];
            if (res == TSDBDriver.MESS_SUCCESS) {
                return true;
            } else if (res == TSDBDriver.OPER_FAIL) {
                System.out.println("操作语句失败，语法错误，或者其他原因");
                return false;
            } else {
                System.out.println("网络不稳定，请稍后再使用");
                return false;
            }
        } catch (IOException e) {

            e.printStackTrace();
        }
        return false;
    }

    private ResultSetIpm General_result(byte num, String sql) {
        InputStream inputStream = null;
        try {
            //将执行语句进行简单的处理
            sql = toLowerCase(sql);
            // 打包发给服务器
            TSDBPackage tsdbPackage = new TSDBPackage(num, sql);
            byte[] aPackage = tsdbPackage.creatPackage();
            Object[] result = null;
            //发送数据
            tsdbPackage.send(aPackage, super.socket);
            byte[] bowl = new byte[1024];
            //收集结果
            inputStream = super.socket.getInputStream();
            int read = 0;
            if ((read = inputStream.read(bowl)) != -1) {
                result = tsdbPackage.solveAPackage(bowl, read);
            }
            byte res = (byte) result[0];
            if (res == TSDBDriver.MESS_SUCCESS) {
                return new ResultSetIpm((String) result[1]);
            } else if (res == TSDBDriver.OPER_FAIL) {
                System.out.println("操作语句失败，语法错误，或者其他原因");
                return null;
            } else {
                System.out.println("网络不稳定，请稍后再使用");
                return null;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;

    }


    //添加用户
    public boolean AddUser(String sql) {
        return General_boolean(TSDBDriver.ADD_USER, sql);
    }

    //删除用户
    public boolean DeleteUser(String sql) {
        return General_boolean(TSDBDriver.DELETE_USER, sql);
    }

    //修改用户权限
    public boolean ModifyingUserRights(String sql) {
        return General_boolean(TSDBDriver.MODIFYING_USER_RIGHTS, sql);
    }

    //创建数据库
    public boolean CreateDatabase(String sql) {
        return General_boolean(TSDBDriver.CREATE_DATABASE, sql);
    }

    //删除数据库
    public boolean DeleteDatabase(String sql) {
        return General_boolean(TSDBDriver.DELETE_DATABASE, sql);
    }

    //新建表
    public boolean CreateTable(String sql) {
        return General_boolean(TSDBDriver.CREATE_TABLE, sql);
    }

    //删除表
    public boolean DeleteTable(String sql) {
        return General_boolean(TSDBDriver.DELETE_TABLE, sql);
    }

    //查看表信息
    public ResultSetIpm ShowTables(String sql) {
        return General_result(TSDBDriver.SHOW_TABLES, sql);
    }

    //查看数据库信息
    public ResultSetIpm ShowDatabases(String sql) {
        return General_result(TSDBDriver.SHOW_DATABASES, sql);
    }

    //切换数据库
    public boolean SwitchDatabase(String sql) {
        return General_boolean(TSDBDriver.SWITCH_DATABASE, sql);
    }

    //清除缓存
    public boolean ClearCache(String sql) {
        return General_boolean(TSDBDriver.CLEAR_CACHE, sql);
    }

    //批处理数据
    public boolean BatchData(String sql) {
        return General_boolean(TSDBDriver.BATCH_DATA, sql);
    }

    //查询语句
    public ResultSetIpm Query(String sql) {
        return General_result(TSDBDriver.QUERY, sql);
    }

    //alter语句
    public boolean Alter(String sql) {
        return General_boolean(TSDBDriver.ALTER, sql);
    }

    public String toLowerCase(String sql) {
        char[] re = sql.toCharArray();
        int len = re.length;
        for (int i = 0; i < len; i++) {
            char index = re[i];
            if (re[i] == '{') {
                re[i++] = ' ';
                for (; re[i] != '}' && i < len; i++) {
                }
                if (re[i] == '}') {
                    re[i] = ' ';
                }
            } else {
                if (index >= 65 && index <= 90) {
                    re[i] += 32;
                }
            }
        }


        return new String(re);
    }
}
