package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;


/*
* 修改用户权限
* */
@Repository
public class ModifyingUserRightsDao {

    public boolean ModifyingUserRights(StatementImp result, String user, int privilege){
        String st="";
        return result.ModifyingUserRights(st);
    }
}
