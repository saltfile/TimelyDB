package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class AddUserDao {

    public boolean AddUser(StatementImp result,String user,String password){
        String st="grant select,,update,delete on *.* to "+ user+"@“%” Identified by ”"+password+"”;";
        return result.AddUser(st);
    }
}
