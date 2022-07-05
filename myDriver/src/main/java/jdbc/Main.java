package jdbc;

import java.sql.DriverManager;


/*


测试


 */
public class Main {
    public static void main(String[] args) {
        try {
            Class.forName("jdbc.TSDBDriver");
            //连接，这一步是检测url格式是否正确，正确的话封装一个用来连接的对象出来
            ConnectionImp myConnection= (ConnectionImp) DriverManager.getConnection("jdbc:tsdb://127.0.0.1:8686","user111","password111");
            //发送数据，用封装好的对象发送数据给服务器，为连接数据库请求
            StatementImp statementImp=(StatementImp) myConnection.createStatement();
            //连接成功之后，进行操作，
            ResultSetIpm resultSetIpm=(ResultSetIpm) statementImp.Query("SELECT * from {mytest}");
//            ResultSetIpm resultSetIpm1=(ResultSetIpm) statementImp.ShowTables("SELECT * from {mytest}");

            while (resultSetIpm.next()){
                System.out.println(resultSetIpm.getString("id")+" "+resultSetIpm.getString("name")+" "+resultSetIpm.getString("age"));
            }
            boolean b1=statementImp.AddUser("aaaaa");
            if (b1){
                System.out.println("=====================" +
                        "用户添加成功" +
                        "=====================");
            }

            boolean b2=statementImp.DeleteUser("aaaaa");
            if (b2){
                System.out.println("=====================" +
                        "用户删除成功" +
                        "=====================");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}