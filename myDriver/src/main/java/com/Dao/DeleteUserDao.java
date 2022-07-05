package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class DeleteUserDao {
    public boolean DeleteUser(StatementImp result, String user){
        String st="drop user "+user+"@'%';";
        return result.DeleteUser(st);
    }
}
