import com.Dao.AddUserDao;
import com.Dao.LoginDao;
import jdbc.StatementImp;

public class text {
    public static void main(String[] args) {
        LoginDao loginDao=new LoginDao();
        StatementImp statementImp=loginDao.login("user111","password111");

        AddUserDao addUserDao=new AddUserDao();
        if (addUserDao.AddUser(statementImp,"user","pass")){
            System.out.println("添加成功");
        }


    }
}
