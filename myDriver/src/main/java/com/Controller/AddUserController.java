//package com.Controller;
//
//import com.Dao.AddUserDao;
//import com.Entity.ResponseResult;
//import jdbc.ResultSetIpm;
//import jdbc.StatementImp;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.stereotype.Controller;
//import org.springframework.web.bind.annotation.RequestMapping;
//import org.springframework.web.bind.annotation.RequestMethod;
//
//
//
//@Controller
//public class AddUserController {
//
//    @Autowired
//    private AddUserDao addUserDao;
//
//
//    /*
//     *添加用户
//     * */
//    @RequestMapping(value = "adduser", method = RequestMethod.POST)
//    public ResponseResult AddUser(Object connection,String user, String password){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=addUserDao.AddUser(connection1,user,password);
//        if (result){
//            return new ResponseResult("添加成功",null,1);
//        }
//        return new ResponseResult("添加失败",null,0);
//    }
//
//    /*
//     * 切换数据库
//     * */
//
//    @RequestMapping(value = "switchdatabase", method = RequestMethod.POST)
//    public ResponseResult SwitchDatabase(Object connection, String databasename){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=switchDatabaseDao.SwitchDatabase(connection1,databasename);
//        if (result){
//            return new ResponseResult("切换成功",null,1);
//        }
//        return new ResponseResult("切换失败",null,0);
//    }
//
//    /*
//     * 查看表信息
//     * */
//    @RequestMapping(value = "showtables", method = RequestMethod.GET)
//    public ResponseResult ShowTables(Object connection, String tablename){
//        StatementImp connection1=(StatementImp)connection;
//        ResultSetIpm result=showTablesDao.ShowTables(connection1,tablename);
//        if (result!=null){
//            return new ResponseResult("查询成功",result,1);
//        }
//        return new ResponseResult("查询失败",result,0);
//    }
//
//    @RequestMapping(value = "showdatabases", method = RequestMethod.POST)
//    public ResponseResult AddUser(Object connection, String databasename){
//        StatementImp connection1=(StatementImp)connection;
//        ResultSetIpm result=showDatabasesDao.ShowDatabases(connection1,databasename);
//        if (result!=null){
//            return new ResponseResult("查询成功",result,1);
//        }
//        return new ResponseResult("查询失败",result,0);
//    }
//
//    /*
//     * 查询语句
//     * */
//    @RequestMapping(value = "query", method = RequestMethod.GET)
//    public ResponseResult AddUser(Object connection){
//        StatementImp connection1=(StatementImp)connection;
//        ResultSetIpm result=queryDao.Query(connection1);
//        if (result!=null){
//            return new ResponseResult("查询成功",result,1);
//        }
//        return new ResponseResult("查询失败",result,0);
//    }
//
//    @RequestMapping(value = "modifyinguserrightsdao", method = RequestMethod.POST)
//    public ResponseResult AddUser(Object connection, String user, int privilege){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=modifyingUserRightsDao.ModifyingUserRights(connection1,user,privilege);
//        if (result){
//            return new ResponseResult("修改成功",null,1);
//        }
//        return new ResponseResult("修改失败",null,0);
//    }
//    @RequestMapping(value = "login", method = RequestMethod.POST)
//    public ResponseResult login(String username, String password){
//
//        StatementImp result=loginDao.login(username,password);
//        if (result!=null){
//            return new ResponseResult("登录成功",result,1);
//        }
//        return new ResponseResult("用户名或密码错误",null,0);
//    }
//
//    @RequestMapping(value = "deleteuser",method = RequestMethod.POST)
//    public ResponseResult DeleteUser(Object connection,String user){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result =deleteUserDao.DeleteUser(connection1,user);
//        if (result){
//            return new ResponseResult("删除成功",null,1);
//        }
//        return new ResponseResult("删除失败",null,0);
//    }
//
//    @RequestMapping(value = "deletetable", method = RequestMethod.POST)
//    public ResponseResult AddUser(Object connection, String tablename){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=deleteTableDao.DeleteTable(connection1,tablename);
//        if (result){
//            return new ResponseResult("删除成功",null,1);
//        }
//        return new ResponseResult("删除失败",null,0);
//    }
//
//    /*
//     * 清除缓存
//     * */
//    @RequestMapping(value = "clearcache", method = RequestMethod.POST)
//    public ResponseResult ClearCache(Object connection){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=clearCacheDao.ClearCache(connection1);
//        if (result){
//            return new ResponseResult("清除成功",null,1);
//        }
//        return new ResponseResult("清除失败",null,0);
//    }
//
//    /*
//     *创建数据库
//     * */
//
//    @RequestMapping(value = "createdatabase", method = RequestMethod.POST)
//    public ResponseResult CreateDatabase(Object connection, String databasename){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=createDatabaseDao.CreateDatabase(connection1,databasename);
//        if (result){
//            return new ResponseResult("创建成功",null,1);
//        }
//        return new ResponseResult("创建失败",null,0);
//    }
//    /*
//     *新建表
//     * */
//    @RequestMapping(value = "createtable", method = RequestMethod.POST)
//    public ResponseResult CreateTable(Object connection, String tablename){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=createTableDao.CreateTable(connection1,tablename);
//        if (result){
//            return new ResponseResult("添加成功",null,1);
//        }
//        return new ResponseResult("添加失败",null,0);
//    }
//    /*
//     * 删除数据库
//     * */
//    @RequestMapping(value = "deletedatabase", method = RequestMethod.POST)
//    public ResponseResult DeleteDatabase(Object connection, String databasename){
//        StatementImp connection1=(StatementImp)connection;
//        boolean result=deleteDatabaseDao.DeleteDatabase(connection1,databasename);
//        if (result){
//            return new ResponseResult("删除成功",null,1);
//        }
//        return new ResponseResult("删除失败",null,0);
//    }
//    /*
//     * 查看表信息
//     * */
//    @RequestMapping(value = "showtables", method = RequestMethod.GET)
//    public ResponseResult ShowTables(Object connection, String tablename){
//        StatementImp connection1=(StatementImp)connection;
//        ResultSetIpm result=showTablesDao.ShowTables(connection1,tablename);
//        if (result!=null){
//            return new ResponseResult("查询成功",result,1);
//        }
//        return new ResponseResult("查询失败",result,0);
//    }
//
//    /*
//     * 批处理数据
//     * */
//    @RequestMapping(value = "batchdata", method = RequestMethod.POST)
//    public ResponseResult BatchData(Object connection, String user) {
//
//
//        return new ResponseResult("添加成功",null,1);
//    }
//}
