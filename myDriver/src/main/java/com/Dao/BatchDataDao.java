package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class BatchDataDao {
    public boolean AddUser(StatementImp result, String user, int privilege){
        String st="";
        return result.BatchData(st);
    }

}
